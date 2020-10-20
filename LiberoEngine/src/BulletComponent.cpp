#include "PCH.h"
#include "BulletComponent.h"


namespace Libero
{
	void BulletComponent::ProgressLife(float dt)
	{
		if (!m_IsExpired)
		{
			m_LifeTimer += dt;

			if (m_LifeTimer >= m_Lifetime)
			{
				m_IsExpired = true;
			}
		}
	}

	void BulletComponent::ResetLife()
	{
		m_IsExpired = false;
		m_LifeTimer = 0.f;
	}
	bool BulletComponent::IsExpired() const
	{
		return m_IsExpired;
	}
}

