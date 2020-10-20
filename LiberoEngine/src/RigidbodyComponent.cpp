#include "PCH.h"
#include "RigidbodyComponent.h"
#include "PhysicsMaster.h"
#include "ColliderComponent.h"

namespace Libero
{
	RigidbodyComponent::RigidbodyComponent(BodyType type)
		: m_pBody{nullptr}
	{
		b2BodyDef bodyDef{};

		switch (type)
		{
		case BodyType::Dynamic: bodyDef.type = b2BodyType::b2_dynamicBody; break;
		case BodyType::Kinematic: bodyDef.type = b2BodyType::b2_kinematicBody; break;
		case BodyType::Static: bodyDef.type = b2BodyType::b2_staticBody; break;
		}

		m_pBody = PhysicsMasterLocator::Locate()->CreateBody(bodyDef);
		m_pBody->SetSleepingAllowed(false);
	}

	RigidbodyComponent::~RigidbodyComponent()
	{
		// Destroy the physics body
		PhysicsMasterLocator::Locate()->DestroyBody(m_pBody);
	}

	bool RigidbodyComponent::IsSimulated() const
	{
		return m_pBody->IsEnabled();
	}

	void RigidbodyComponent::SetSimulated(const bool enable)
	{
		m_pBody->SetEnabled(enable);
	}

	bool RigidbodyComponent::GetWeight() const
	{
		return m_pBody->GetMass();
	}

	void RigidbodyComponent::SetWeight(const float weight)
	{
		m_pBody->SetGravityScale(weight);
	}

	void RigidbodyComponent::AddForce(const Vector2f& force)
	{
		m_ForceSum += force;
	}

	b2Body* RigidbodyComponent::GetB2DBody() const
	{
		return m_pBody;
	}

	void RigidbodyComponent::AttachCollider(Collider2DComponent* pCollider)
	{
		b2FixtureDef fixtureDef;
		fixtureDef.shape = pCollider->GetShape();
		
		fixtureDef.density = 0.05f;
		fixtureDef.friction = 0.0001f;

		m_pBody->CreateFixture(&fixtureDef);
	}

	void RigidbodyComponent::SetTrigger(bool enabled)
	{
		m_pBody->GetFixtureList()->SetSensor(enabled);
	}
}

