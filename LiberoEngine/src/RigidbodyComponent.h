#pragma once
#include "Component.h"
#include "LiberoMath.h"

namespace Libero
{
	class Collider2DComponent;

	class RigidbodyComponent : public Component<RigidbodyComponent>
	{
	public:
		enum class BodyType
		{
			Kinematic,
			Static,
			Dynamic
		};

		enum class ForceType
		{
			Impulse,
			Acceleration
		};

		RigidbodyComponent(BodyType type = BodyType::Static);
		~RigidbodyComponent();

		bool IsSimulated() const;
		void SetSimulated(const bool simulated);

		bool GetWeight() const;
		void SetWeight(const float weight);

		void SetTrigger(bool enabled);

		void AddForce(const Vector2f& force);

		b2Body* GetB2DBody() const;

		DefGetSet(Vector2f, m_ForceSum, ForceSum);

		void AttachCollider(Collider2DComponent* pCollider);

	private:
		b2Body* m_pBody;
		Vector2f m_ForceSum{};

		bool m_IsSimulated;
	};
}


