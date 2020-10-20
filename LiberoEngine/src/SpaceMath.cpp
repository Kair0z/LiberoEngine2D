#include "PCH.h"
#include "SpaceMath.h"

// TODO: this should be handled more elegantly
#define LIBEROUNITPIXELSIZE 1.f

namespace Libero
{
	namespace SpaceMath2D
	{
		Vector2f WorldToScreen(const Vector2f& worldPos, const Rectf& screen)
		{
			Vector2f screenPos{};

			// X == right
			// Y == up
			screenPos[0] = screen.m_LeftTop[0] + (screen.m_W / 2) + (worldPos[0] * LIBEROUNITPIXELSIZE);
			screenPos[1] = screen.m_LeftTop[1] + (screen.m_H / 2) - (worldPos[1] * LIBEROUNITPIXELSIZE);

			return screenPos;
		}

		Vector2f ScreenToWorld(const Vector2f& screenPos, const Rectf& screen)
		{
			Vector2f worldOrigin{};
			worldOrigin[0] = screen.m_LeftTop[0] + screen.m_W / 2.f;
			worldOrigin[1] = screen.m_LeftTop[1] + screen.m_H / 2.f;

			screenPos;

			return Vector2f();
		}
	}

	namespace SpaceMath3D
	{

	}
}