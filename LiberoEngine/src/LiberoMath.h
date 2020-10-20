#pragma once
#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

namespace Libero
{
	using Vector2f = Vector<float, 2>;
	using Vector2d = Vector<double, 2>;
	using Vector2i = Vector<int, 2>;
	using Vector2ui = Vector<uint32_t, 2>;

	using Point2f = Vector<float, 2>;
	using Point2d = Vector<double, 2>;
	using Point2i = Vector<int, 2>;
	using Point2ui = Vector<uint32_t, 2>;

	using Vector3f = Vector<float, 3>;
	using Vector3d = Vector<double, 3>;
	using Vector3i = Vector<int, 3>;
	using Vector3ui = Vector<uint32_t, 3>;

	using Point3f = Vector<float, 3>;
	using Point3d = Vector<double, 3>;
	using Point3i = Vector<int, 3>;
	using Point3ui = Vector<uint32_t, 3>;

	using ColorRGBA = Vector<float, 4>;
	using ColorRGB = Vector<float, 3>;
}

namespace Libero
{
	struct Rectf 
	{
		Vector2f m_LeftTop{};
		float m_W{};
		float m_H{};

		Vector2f GetLeftTop() const
		{
			return m_LeftTop;
		}

		Vector2f GetMid() const
		{
			return { m_LeftTop.x + m_W / 2.f, m_LeftTop.y - m_H / 2.f };
		}

		bool Overlap(const Rectf& other) const
		{
			Point2f l1 = m_LeftTop;
			Point2f l2 = other.m_LeftTop;

			Point2f r1 = m_LeftTop + Vector2f{m_W, -m_H};
			Point2f r2 = other.m_LeftTop + Vector2f{ other.m_W, -other.m_H };

			// If one rectangle is on left side of other 
			if (l1.x >= r2.x || l2.x >= r1.x)
				return false;

			// If one rectangle is above other 
			if (l1.y <= r2.y || l2.y <= r1.y)
				return false;

			return true;
		}

		bool Overlap(const Point2f& point) const
		{
			if (point.x < m_LeftTop.x || point.y > m_LeftTop.y || point.y < m_LeftTop.y - m_H || point.x > m_LeftTop.x + m_W)
			{
				return false;
			}

			return true;
		}
	};
}