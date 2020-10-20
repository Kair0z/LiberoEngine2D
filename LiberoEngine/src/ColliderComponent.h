#pragma once
#include "Component.h"
#include "LiberoMath.h"

namespace Libero
{
	class Collider2DComponent : public Component<Collider2DComponent>
	{
	public:
		Collider2DComponent();
		virtual ~Collider2DComponent();

		b2PolygonShape* GetShape() const;

	protected:
		b2PolygonShape* m_pShape;
	};

	class BoxCollider2DComponent : public Collider2DComponent
	{
	public:
		BoxCollider2DComponent(float hx, float hy)
			:Collider2DComponent()
		{
			m_Box.m_H = 2 * hy;
			m_Box.m_W = 2 * hx;
			m_Box.m_LeftTop.x -= hx;
			m_Box.m_LeftTop.y += hy;

			m_pShape->SetAsBox(hx / 16, hy / 16);
		}
		DefGet(Rectf, m_Box, Box);

		bool Overlap(const BoxCollider2DComponent* pOther);

	private:
		Rectf m_Box;
	};
}


