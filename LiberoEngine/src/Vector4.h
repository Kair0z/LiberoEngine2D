#pragma once

#ifndef LIBERO_MATH_VECTOR4
#define LIBERO_MATH_VECTOR4
#include <cassert>
#include "Vector.h"
#include <ostream>

namespace Libero
{
	template<typename T>
	struct Vector<T, 4>
	{
	public:
		// Data
#pragma warning(disable : 4201)
		union
		{
			T _data[4];
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
		};
#pragma warning(default : 4201)

	public:
		// Constructors & ROF:
		Vector<T, 4>() = default;
		Vector<T, 4>(const T& x, const T& y, const T& z, const T& w)
		{
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
			_data[3] = w;
		}
		Vector<T, 4>(const Vector<T, 4>& other) = default;
		Vector<T, 4>(Vector<T, 4>&& other) = default;
		Vector<T, 4>& operator=(const Vector<T, 4>& other) = default;
		Vector<T, 4>& operator=(Vector<T, 4>&& other) = default;
		~Vector<T, 4>() = default;

		// conversion constructors: last element(s): 0
		Vector<T, 4>(const Vector<T, 2>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
			_data[3] = 0;
		}
		Vector<T, 4>(Vector <T, 2>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
			_data[3] = 0;
		}
		Vector<T, 4>(const Vector<T, 3>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = other.z;
			_data[3] = 0;
		}
		Vector<T, 4>(Vector<T, 3>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = other.z;
			_data[3] = 0;
		}

		// conversion operator: last element(s): 0
		Vector<T, 4> operator()(const Vector<T, 2>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
			_data[3] = 0;
		}
		Vector<T, 4> operator()(Vector<T, 2>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
			_data[3] = 0;
		}
		Vector<T, 4> operator()(const Vector<T, 3>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
			_data[3] = 0;
		}
		Vector<T, 4> operator()(Vector<T, 3>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
			_data[3] = 0;
		}

		// Print
		std::ostream& Cout(std::ostream& out) const
		{
			out << "(" << x << ", " << y << ", " << z << ", " << w << ")";
		}

		// Data access:
		T Data(int idx) const;
		T& Data(int idx);
		T operator[](int idx) const;
		T& operator[](int idx);

		// Member operators:
		Vector<T, 4> operator-() const;
		Vector<T, 4> operator+=(const Vector<T, 4>& other);
		Vector<T, 4> operator-=(const Vector<T, 4>& other);
		Vector<T, 4> operator*=(float scalar);
		Vector<T, 4> operator/=(float scalar);
	};

	// IMPORTANT STUFF:
	template<typename T>
	T Dot(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return static_cast<T>(lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z, lhs.w * rhs.w);
	}

	template<typename T>
	Vector<T, 4> Cross(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs, const Vector<T, 4>& ths)
	{
		// https://www.gamedev.net/forums/topic/202131-4d-cross-product/
		return Vector<T, 4>
		{
			lhs.x* rhs.y - rhs.x * lhs.y
				- ths.z,

				lhs.y* rhs.z - rhs.y * lhs.z
				+ ths.w,

				lhs.z* rhs.w - rhs.z * lhs.w
				- ths.x,

				lhs.w* rhs.x - rhs.w * lhs.x
				- ths.y
		};
	}

	template<typename T>
	Vector<T, 4> Abs(const Vector<T, 4>& vector)
	{
		return Vector<T, 4>(std::abs(vector.x), std::abs(vector.y), std::abs(vector.z), std::abs(vector.w));
	}

	// arithmetic operator overloads (non-member)
	template<typename T>
	Vector<T, 4> operator+(const Vector<T, 4>& lhs, const Vector<T, 4> rhs)
	{
		return Vector<T, 4>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	template<typename T>
	Vector<T, 4> operator-(const Vector<T, 4>& lhs, const Vector<T, 4> rhs)
	{
		return Vector<T, 4>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	template<typename T>
	Vector<T, 4> operator*(const Vector<T, 4>& lhs, const Vector<T, 4> rhs) // NOT DOT!
	{
		return Vector<T, 3>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}

	template<typename T>
	Vector<T, 4> operator*(const Vector<T, 4>& lhs, const float a)
	{
		return Vector<T, 3>(lhs.x * a, lhs.y * a, lhs.z * a, lhs.w * a);
	}

	template<typename T>
	Vector<T, 4> operator*(const float a, const Vector<T, 4>& rhs)
	{
		return rhs * a;
	}

	template<typename T>
	Vector<T, 4> operator/(const Vector<T, 4>& lhs, const Vector<T, 4> rhs)
	{
		return Vector<T, 4>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
	}

	template<typename T>
	Vector<T, 4> operator/(const Vector<T, 4>& lhs, const float a)
	{
		return Vector<T, 4>(lhs.x / a, lhs.y / a, lhs.z / a, lhs.w / a);
	}

	// relational operators
	template<typename T>
	bool operator==(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return (lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] && lhs[3] == rhs[3]);
	}

	template<typename T>
	bool operator!=(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	bool operator<=(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return (Length(lhs) < Length(rhs) || lhs == rhs);
	}

	template<typename T>
	bool operator>=(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return (Length(lhs) > Length(rhs) || lhs == rhs);
	}

	template<typename T>
	bool operator<(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return !(lhs >= rhs);
	}

	template<typename T>
	bool operator>(const Vector<T, 4>& lhs, const Vector<T, 4>& rhs)
	{
		return !(lhs <= rhs);
	}

	// operator overloads (member)
	template<typename T>
	Vector<T, 4> Vector<T, 4>::operator-() const
	{
		return Vector<T, 4>(-x, -y, -z, -w);
	}

	template<typename T>
	Vector<T, 4> Vector<T, 4>::operator+=(const Vector<T, 4>& other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;
		this->z = this->z + other.z;
		this->w = this->w + other.w;

		return *this;
	}

	template<typename T>
	Vector<T, 4> Vector<T, 4>::operator-=(const Vector<T, 4>& other)
	{
		return (*this += -other);
	}

	template<typename T>
	Vector<T, 4> Vector<T, 4>::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		this->w *= scalar;

		return *this;
	}

	template<typename T>
	Vector<T, 4> Vector<T, 4>::operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;
		this->w /= scalar;

		return *this;
	}
	// ------------

	// Data access 
	template<typename T>
	T Vector<T, 4>::Data(int idx) const
	{
		assert(idx < 4);
		return _data[idx];
	}

	template<typename T>
	T& Vector<T, 4>::Data(int idx)
	{
		assert(idx < 4);
		return _data[idx];
	}

	template<typename T>
	T Vector<T, 4>::operator[](int idx) const
	{
		assert(idx < 4);
		return _data[idx];
	}

	template<typename T>
	T& Vector<T, 4>::operator[](int idx)
	{
		assert(idx < 4);
		return _data[idx];
	}
}
#endif