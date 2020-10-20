#pragma once
#include "Component.h"
#include "LiberoMath.h"
#include "LiberoMacros.h"

namespace Libero
{
	class BulletComponent : public Component<BulletComponent>
	{
	public:
		BulletComponent() = default;
		virtual ~BulletComponent() = default;

		DefGetSet(float, m_Lifetime, Lifetime);
		DefGetSet(Vector2f, m_InitialVelocity, InitVelocity);

		void ProgressLife(float dt);
		void ResetLife();

		bool IsExpired() const;

	private:
		Vector2f m_InitialVelocity;
		float m_Lifetime;
		float m_LifeTimer;

		bool m_IsExpired;
	};
}



