#pragma once
#include "LiberoMath.h"

namespace Libero
{
	namespace SpaceMath2D
	{
		Vector2f WorldToScreen(const Vector2f& worldPos, const Rectf& screen);
		Vector2f ScreenToWorld(const Vector2f& screenPos, const Rectf& screen);
	}

	namespace SpaceMath3D
	{

	}
}