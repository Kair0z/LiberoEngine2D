#include "PCH.h"
#include "CharacterComponent.h"

namespace Libero
{
	CharacterComponent::CharacterComponent(float maxSpeed)
		: m_MaxSpeed{ maxSpeed }
	{
		m_Feet.m_LeftTop = { -10.f, -14.f };
		m_Feet.m_H = 8.f;
		m_Feet.m_W = 20.f;
	}

	void CharacterComponent::AddAcceleration(const Vector2f& acc)
	{
		m_Acceleration += acc;
	}

	void CharacterComponent::AddVelocity(const Vector2f& vel)
	{
		m_Velocity += vel;
	}
}

