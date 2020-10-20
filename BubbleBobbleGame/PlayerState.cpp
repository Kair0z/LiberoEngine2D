#include "PlayerState.h"
#include "InputComponent.h"
#include "CharacterComponent.h"
#include "SpawnComponent.h"
#include "BubbleState.h"
#include "MySprites.h"
#include "ECS_Engine.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "PhysicsMaster.h"

PlayerComponent::PlayerComponent()
    : m_pPlayerState{nullptr}
{
    SetNewState(new PlayerIdleState());
}

PlayerComponent::~PlayerComponent()
{
    if (m_pPlayerState)
    {
        delete m_pPlayerState;
        m_pPlayerState = nullptr;
    }
}

ICharacterState* PlayerComponent::GetState()
{
    return m_pPlayerState;
}

void PlayerComponent::SetNewState(ICharacterState* pNewState)
{
    if (!pNewState || m_pPlayerState == pNewState) return;

    delete m_pPlayerState;
    m_pPlayerState = nullptr;

    m_pPlayerState = pNewState;
}



//***************
// Player Idle:

void PlayerIdleState::OnEnter(CharacterComponent*)
{
}

ICharacterState* PlayerIdleState::ProcessInput(CharacterComponent* pCharacter, InputComponent* pInput)
{
    if (!pInput || !pCharacter) return nullptr;
    
    if (pInput->IsKeyDown(SDLK_p)) return new PlayerShootingState();

    if (!pCharacter->GetIsGrounded()) return nullptr;

    if (pInput->IsKeyDown(SDLK_UP)) return new PlayerJumpState();

    return nullptr;
}


//***************
// Player Shoot:

PlayerShootingState::PlayerShootingState(float time, float bubbleSpeed, float bubbleLifetime)
    : m_ShootingTime{time}
    , m_ShootingTimer{}
    , m_BubbleLifetime{bubbleLifetime}
    , m_ShootingSpeed{bubbleSpeed}
{
}

void PlayerShootingState::OnEnter(CharacterComponent* pCharacter)
{
    IEntity* pOwner = pCharacter->GetOwnerEntity();
    if (!pOwner) return;

    SpawnComponent* pSpawner = pOwner->GetComponent<SpawnComponent>();
    if (!pSpawner) return;

    RigidbodyComponent* pRB = pOwner->GetComponent<RigidbodyComponent>();
    if (!pRB) return;

    float xSpeed = m_ShootingSpeed;
    if (pRB->GetB2DBody()->GetLinearVelocity().x < 0.f) xSpeed = -xSpeed;

    // Check other bubbles:
    const std::vector<BubbleStateComponent*>& allBubbles = ECSLocator::Locate()->GetAllComponents<BubbleStateComponent>();
    GameObject* pRes= nullptr;
    for (BubbleStateComponent* pBubble : allBubbles)
    {
        if (!pBubble->GetIsInUse())
        {
            pRes = (GameObject*)pBubble->GetOwnerEntity();
            pRes->GetTransform()->SetPosition(((GameObject*)pOwner)->GetTransform()->GetPosition());
            pBubble->SetNewState(new BubbleFlying({ xSpeed, 0.f }, m_BubbleLifetime));
            pBubble->GetState()->OnEnter(pRes);
            return;
        }
    }

    // Else: Create new bubble:
    pRes = pSpawner->SpawnGameObject();
    InitializeBubble(pRes, xSpeed);
}

ICharacterState* PlayerShootingState::Update(float dt, CharacterComponent*)
{
    m_ShootingTimer += dt;

    if (m_ShootingTimer > m_ShootingTime) return new PlayerIdleState(); // Go back to idle

    return nullptr;
}

void PlayerShootingState::InitializeBubble(Libero::GameObject* pBubble, float xSpeed)
{
    BubbleStateComponent* pBullet = pBubble->AddComponent<BubbleStateComponent>();
    pBullet->SetNewState(new BubbleFlying({ xSpeed, 0.f }, m_BubbleLifetime));

    // Sprite:
    Rectf dest{};
    dest.m_W = 32.f;
    dest.m_H = 32.f;
    pBubble->AddComponent<SpriteComponent>(MySprites::BubbleSprite(dest));
    pBubble->AddComponent<BoxCollider2DComponent>(16.f, 16.f);
}


//***************
// Player Jump:

PlayerJumpState::PlayerJumpState(float jumpTime)
    : m_JumpTime{jumpTime}
    , m_JumpTimer{0.f}
{
}

void PlayerJumpState::OnEnter(CharacterComponent* pCharacter)
{
    IEntity* pOwner = pCharacter->GetOwnerEntity();
    if (!pOwner) return;

    RigidbodyComponent* pBody = pOwner->GetComponent<RigidbodyComponent>();
    if (!pBody) return;

    pBody->GetB2DBody()->SetLinearVelocity({ pBody->GetB2DBody()->GetLinearVelocity().x, 30.f });
}

ICharacterState* PlayerJumpState::Update(float dt, CharacterComponent* pCharacter)
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
        return new PlayerIdleState();
    }

    return nullptr;
}
