#include "BubbleState.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "EnemyState.h" 
#include "ECS_Engine.h"
#include "ColliderComponent.h"

using namespace Libero;

BubbleStateComponent::BubbleStateComponent()
    : m_pBubbleState{nullptr}
{
    
}

BubbleStateComponent::~BubbleStateComponent()
{
    if (m_pBubbleState)
    {
        delete m_pBubbleState;
        m_pBubbleState = nullptr;
    }
}

IState* BubbleStateComponent::GetState()
{
    return m_pBubbleState;
}

void BubbleStateComponent::SetNewState(IState* pNewState)
{
    if (!pNewState || m_pBubbleState == pNewState) return;

    if (m_pBubbleState) delete m_pBubbleState;
    m_pBubbleState = pNewState;
}



BubbleFlying::BubbleFlying(const Vector2f& vel, float lifetime)
    : m_FlyVelocity{vel}
    , m_Flytime{lifetime}
{

}

void BubbleFlying::OnEnter(GameObject* pObj)
{
    SpriteComponent* pSprite = pObj->GetComponent<SpriteComponent>();
    if (!pSprite) return;

    pSprite->SetActive(true);

    BubbleStateComponent* pBubble = pObj->GetComponent<BubbleStateComponent>();
    if (!pBubble) return;

    BoxCollider2DComponent* pBox = pObj->GetComponent<BoxCollider2DComponent>();
    pBox->SetActive(true);

    pBubble->SetIsInUse(true);
}

IState* BubbleFlying::Update(float dt, GameObject* pObj)
{
    // Move along flying:
    pObj->GetTransform()->Translate(m_FlyVelocity * dt);

    // Increase flying timer:
    m_Flytimer += dt;
    if (m_Flytimer > m_Flytime) return new BubbleFloating();

    BoxCollider2DComponent* pMyBox = pObj->GetComponent<BoxCollider2DComponent>();
    if (!pMyBox) return nullptr;

    // Check collision with Enemies:
    for (EnemyComponent* pEnemy : ECSLocator::Locate()->GetAllComponents<EnemyComponent>())
    {
        if (pEnemy->GetIsBubbled()) continue;

        BoxCollider2DComponent* pBox = pEnemy->GetOwnerEntity()->GetComponent<BoxCollider2DComponent>();
        if (!pBox) continue;

        Rectf box1 = pBox->GetBox();
        Rectf box2 = pMyBox->GetBox();
        box1.m_LeftTop += pEnemy->GetOwnerEntity()->GetComponent<Transform2DComponent>()->GetPosition();
        box2.m_LeftTop += pObj->GetTransform()->GetPosition();

        // Check if collision:
        if (box1.Overlap(box2))
        {
            pEnemy->SetNewState(new EnemyBubbledState());
            pEnemy->GetState()->OnEnter(pEnemy->GetOwnerEntity()->GetComponent<CharacterComponent>());
            return new BubbleBurst();
        }
    }

    return nullptr;
}



BubbleFloating::BubbleFloating(float lifetime, float floatPower)
    : m_FloatTime{lifetime}
    , m_FloatTimer{}
    , m_FloatPower{floatPower}
{
}

IState* BubbleFloating::Update(float dt, GameObject* pObj)
{
    // Don't move (for now)
    pObj->GetTransform()->Translate({ 0.f, m_FloatPower * dt });

    // Increase lifetime:
    m_FloatTimer += dt;
    if (m_FloatTimer > m_FloatTime)
    {
        return new BubbleBurst();
    }

    

    return nullptr;
}

void BubbleBurst::OnEnter(GameObject* pObj)
{
    BubbleStateComponent* pBubble = pObj->GetComponent<BubbleStateComponent>();
    if (!pBubble) return;

    // Make invisible:
    SpriteComponent* pSprite = pObj->GetComponent<SpriteComponent>();
    pSprite->SetActive(false);

    // Ignore box:
    BoxCollider2DComponent* pBox = pObj->GetComponent<BoxCollider2DComponent>();
    pBox->SetActive(false);

    pBubble->SetIsInUse(false); // Set the bubble on not in use
}
