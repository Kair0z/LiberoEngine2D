#include "EnemyState.h"
#include "IEntity.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "MySprites.h"
#include "ECS_Engine.h"
#include "PlayerState.h"
#include "TransformComponent.h"
#include "SubjectMaster.h"
#include "ColliderComponent.h"

EnemyComponent::EnemyComponent(const Libero::Rectf& bounds)
	: m_BoundsToWalk{ bounds }
	, m_pEnemyState{nullptr}
	, m_IsBubbled{false}
	, m_IsPopped{false}
{
	SetNewState(new EnemyIdleState());
}

EnemyComponent::~EnemyComponent()
{
	SafeDelete(m_pEnemyState);
}

ICharacterState* EnemyComponent::GetState()
{
	return m_pEnemyState;
}

void EnemyComponent::SetNewState(ICharacterState* pNewState)
{
	if (!pNewState || m_pEnemyState == pNewState) return;

	delete m_pEnemyState;
	m_pEnemyState = pNewState;
}



//***************
// Enemy Idle:

void EnemyIdleState::OnEnter(CharacterComponent* pCharacter)
{
	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return;

	pCharacter->SetEnableGravity(true);

	EnemyComponent* pEnemy = pOwner->GetComponent<EnemyComponent>();
	if (pEnemy) pEnemy->SetIsBubbled(false);

	SpriteComponent* pSprite = pOwner->GetComponent<SpriteComponent>();
	if (!pSprite) return;

	RigidbodyComponent* pRB = pOwner->GetComponent<RigidbodyComponent>();
	pRB->SetTrigger(false);
	pRB->SetSimulated(true);

	Rectf dest{};
	dest.m_W = 32.f;
	dest.m_H = 32.f;
	pOwner->RemoveComponent<SpriteComponent>();
	pOwner->AddComponent<SpriteComponent>(MySprites::EnemyRightSprite(dest));
}

ICharacterState* EnemyIdleState::Update(float dt, CharacterComponent* pCharacter)
{
	m_ChangeTimer += dt;
	if (m_ChangeTimer >= m_ChangeTime)
	{
		m_Movement = -m_Movement; // Change
		m_ChangeTimer = 0.f;
	}

	m_JumpTimer += dt;
	if (m_JumpTimer >= m_JumpTime) return new EnemyJumpState();

	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return nullptr;

	RigidbodyComponent* pRB = pOwner->GetComponent<RigidbodyComponent>();
	if (!pRB) return nullptr;

	pRB->AddForce({ m_Movement, 0.f });

	return nullptr;
}

//***************
// Enemy Bubbled:

void EnemyBubbledState::OnEnter(CharacterComponent* pCharacter)
{
	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return;

	pCharacter->SetEnableGravity(false);
	pCharacter->SetVelocity({});

	EnemyComponent* pEnemy = pOwner->GetComponent<EnemyComponent>();
	if (pEnemy) pEnemy->SetIsBubbled(true);

	SpriteComponent* pSprite = pOwner->GetComponent<SpriteComponent>();
	if (!pSprite) return;

	Rectf dest{};
	dest.m_W = 32.f;
	dest.m_H = 32.f;
	pOwner->RemoveComponent<SpriteComponent>();
	pOwner->AddComponent<SpriteComponent>(MySprites::BubbledEnemySprite(dest));

	RigidbodyComponent* pRB = pOwner->GetComponent<RigidbodyComponent>();
	pRB->SetTrigger(true);
	pRB->SetSimulated(false);
}

ICharacterState* EnemyBubbledState::Update(float dt, CharacterComponent* pCharacter)
{
	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return nullptr;

	pOwner->GetComponent<Transform2DComponent>()->Translate({ 0.f, m_BubbledSpeed * dt });

	for (PlayerComponent* pPlayer : ECSLocator::Locate()->GetAllComponents<PlayerComponent>())
	{
		BoxCollider2DComponent* pPlayerCollider = pPlayer->GetOwnerEntity()->GetComponent<BoxCollider2DComponent>();
		if (!pPlayerCollider) continue;

		BoxCollider2DComponent* pEnemyCollider = pOwner->GetComponent<BoxCollider2DComponent>();

		Transform2DComponent* pPlayerTransform = pPlayer->GetOwnerEntity()->GetComponent<Transform2DComponent>();
		Transform2DComponent* pEnemyTransform = pOwner->GetComponent<Transform2DComponent>();

		Rectf playerRect = pPlayerCollider->GetBox();
		Rectf enemyRect = pEnemyCollider->GetBox();

		playerRect.m_LeftTop += pPlayerTransform->GetPosition();
		enemyRect.m_LeftTop += pEnemyTransform->GetPosition();

		if (playerRect.Overlap(enemyRect))
		{
			// Notify scorelisteners!:
			SubjectMasterLocator::Locate()->NotifyScore();
			return new EnemyPoppedState();
		}
	}

	m_BubbledTimer += dt;
	if (m_BubbledTimer >= m_BubbledTime) return new EnemyIdleState();

	return nullptr;
}

//***************
// Enemy Popped:

void EnemyPoppedState::OnEnter(CharacterComponent* pCharacter)
{
	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return;

	Rectf dest{};
	dest.m_W = 32.f;
	dest.m_H = 32.f;
	pOwner->RemoveComponent<SpriteComponent>();
	pOwner->AddComponent<SpriteComponent>(MySprites::PoppedEnemySprite(dest));

	EnemyComponent* pEnemy = pOwner->GetComponent<EnemyComponent>();
	pEnemy->SetIsPopped(true);
}

ICharacterState* EnemyPoppedState::Update(float, CharacterComponent*)
{
	return nullptr;
}

//***************
// Enemy Jump:

void EnemyJumpState::OnEnter(CharacterComponent* pCharacter)
{
	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return;

	RigidbodyComponent* pBody = pOwner->GetComponent<RigidbodyComponent>();
	if (!pBody) return;

	pBody->GetB2DBody()->SetLinearVelocity({ pBody->GetB2DBody()->GetLinearVelocity().x, 20.f });
}

ICharacterState* EnemyJumpState::Update(float dt, CharacterComponent* pCharacter)
{
	m_JumpTimer += dt;

	IEntity* pOwner = pCharacter->GetOwnerEntity();
	if (!pOwner) return nullptr;

	RigidbodyComponent* pBody = pOwner->GetComponent<RigidbodyComponent>();
	if (!pBody) return nullptr;

	float yVel = pBody->GetB2DBody()->GetLinearVelocity().y;
	if (yVel > 0) pBody->SetTrigger(true);
	else pBody->SetTrigger(false);

	if (m_JumpTimer > m_JumpTime)
	{
		pBody->SetTrigger(false);
		return new EnemyIdleState();
	}

	return nullptr;
}
