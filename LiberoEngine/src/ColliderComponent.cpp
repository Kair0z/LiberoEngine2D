#include "PCH.h"
#include "ColliderComponent.h"

namespace Libero
{
	Collider2DComponent::Collider2DComponent()
	{
		m_pShape = new b2PolygonShape();
	}

	Collider2DComponent::~Collider2DComponent()
	{
		delete m_pShape;
		m_pShape = nullptr;
	}

	b2PolygonShape* Collider2DComponent::GetShape() const
	{
		return m_pShape;
	}

	bool BoxCollider2DComponent::Overlap(const BoxCollider2DComponent* pOther)
	{
		return m_Box.Overlap(pOther->GetBox());
	}
}

