#pragma once
#include "Component.h"
#include "LiberoMath.h"
#include "LiberoMacros.h"

namespace Libero
{
	class ICharacterState;
	class CharacterComponent : public Component<CharacterComponent>
	{
	public:
		enum class FaceDirection
		{
			LEFT,
			RIGHT
		};

	public:
		CharacterComponent(float maxSpeed);
		virtual ~CharacterComponent() = default;

		DefGetSet(Vector2f, m_Velocity, Velocity);
		DefGetSet(Vector2f, m_Acceleration, Acceleration);
		void AddAcceleration(const Vector2f& acc);
		void AddVelocity(const Vector2f& vel);
		DefGetSet(float, m_MaxSpeed, MaxSpeed);
		DefGetSet(float, m_Drag, Drag);
		DefGetSet(bool, m_CapSpeed, ShouldCapSpeed);
		DefGetSet(bool, m_GravityEnabled, EnableGravity);
		DefGetSet(float, m_GravityScale, GravityScale);
		DefGetSet(bool, m_IsGrounded, IsGrounded);
		DefGetSet(FaceDirection, m_Facing, FaceDirection);
		DefGetSet(Rectf, m_Feet, Feet);

	private:
		Vector2f m_Velocity{};
		Rectf m_Feet{};
		Vector2f m_Acceleration{};
		FaceDirection m_Facing = FaceDirection::LEFT;

		float m_MaxSpeed{};
		float m_GravityScale{ 1.f };
		float m_Drag{};

		bool m_CapSpeed{ true };
		bool m_GravityEnabled{ false };
		bool m_IsGrounded{ false };
	};
}


