#pragma once

#ifndef LIBERO_MATH_VECTOR2
#define LIBERO_MATH_VECTOR2
#include <cassert>
#include "Vector.h"
#include <ostream>

namespace Libero
{
	template<typename T>
	struct Vector<T, 2>
	{
	public:
		// Data
#pragma warning(disable : 4201)
		union
		{
			T _data[2];
			struct { T x, y; };
			struct { T r, g; };
		};
#pragma warning(default : 4201)

	public:
		// Constructors & ROF:
		Vector<T, 2>() = default;
		Vector<T, 2>(const T& x, const T& y)
		{
			_data[0] = x;
			_data[1] = y;
		}
		Vector<T, 2>(const Vector<T, 2>& other) = default;
		Vector<T, 2>(Vector<T, 2>&& other) = default;
		Vector<T, 2>& operator=(const Vector<T, 2>& other) = default;
		Vector<T, 2>& operator=(Vector<T, 2>&& other) = default;
		~Vector<T, 2>() = default;

		// Conversion constructors:
		Vector<T, 2>(const Vector<T, 3>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}
		Vector<T, 2>(Vector<T, 3>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}
		Vector<T, 2>(const Vector<T, 4>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}
		Vector<T, 2>(Vector<T, 4>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}

		// Conversion operators:
		Vector<T, 2> operator()(const Vector<T, 3>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}
		Vector<T, 2> operator()(Vector<T, 3>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}
		Vector<T, 2> operator()(const Vector<T, 4>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}
		Vector<T, 2> operator()(Vector<T, 4>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
		}

		// Print
		std::ostream& Cout(std::ostream& out) const
		{
			out << "(" << x << ", " << y << ")";
		}

		// Data access:
		T Data(int idx) const;
		T& Data(int idx);
		T operator[](int idx) const;
		T& operator[](int idx);
		
		// Member operators:
		Vector<T, 2> operator-() const;
		Vector<T, 2> operator+=(const Vector<T, 2>& other);
		Vector<T, 2> operator-=(const Vector<T, 2>& other);
		Vector<T, 2> operator*=(float scalar);
		Vector<T, 2> operator/=(float scalar);

		bool IsZero() const
		{
			return (x == 0.f && y == 0.f);
		}
	};

	// IMPORTANT STUFF:
	template<typename T>
	T Dot(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return static_cast<T>(lhs.x * rhs.x + lhs.y * rhs.y);
	}

	template<typename T>
	T Cross(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return static_cast<T>(lhs.x * rhs.y - lhs.y * rhs.x);
	}

	template<typename T>
	Vector<T, 2> Abs(const Vector<T, 2>& vector) 
	{
		return Vector<T, 2>(std::abs(vector.x), std::abs(vector.y));
	}

	// arithmetic operator overloads (non-member)
	template<typename T>
	Vector<T, 2> operator+(const Vector<T, 2>& lhs, const Vector<T, 2> rhs)
	{
		return Vector<T, 2>(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	template<typename T>
	Vector<T, 2> operator-(const Vector<T, 2>& lhs, const Vector<T, 2> rhs)
	{
		return Vector<T, 2>(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	template<typename T>
	Vector<T, 2> operator*(const Vector<T, 2>& lhs, const Vector<T, 2> rhs) // NOT DOT!
	{
		return Vector<T, 2>(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	template<typename T>
	Vector<T, 2> operator*(const Vector<T, 2>& lhs, const float a)
	{
		return Vector<T, 2>(lhs.x * a, lhs.y * a);
	}

	template<typename T>
	Vector<T, 2> operator*(const float a, const Vector<T, 2>& rhs)
	{
		return rhs * a;
	}

	template<typename T>
	Vector<T, 2> operator/(const Vector<T, 2>& lhs, const Vector<T, 2> rhs)
	{
		return Vector<T, 2>(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	template<typename T>
	Vector<T, 2> operator/(const Vector<T, 2>& lhs, const float a)
	{
		return Vector<T, 2>(lhs.x / a, lhs.y / a);
	}

	// relational operators
	template<typename T>
	bool operator==(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return (lhs[0] == rhs[0] && lhs[1] == rhs[1]);
	}

	template<typename T>
	bool operator!=(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	bool operator<=(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return (Length(lhs) < Length(rhs) || lhs == rhs);
	}

	template<typename T>
	bool operator>=(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return (Length(lhs) > Length(rhs) || lhs == rhs);
	}

	template<typename T>
	bool operator<(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return !(lhs >= rhs);
	}

	template<typename T>
	bool operator>(const Vector<T, 2>& lhs, const Vector<T, 2>& rhs)
	{
		return !(lhs <= rhs);
	}
	
	// operator overloads (member)
	template<typename T>
	Vector<T, 2> Vector<T, 2>::operator-() const
	{
		return Vector<T, 2>(-x, -y);
	}

	template<typename T>
	Vector<T, 2> Vector<T, 2>::operator+=(const Vector<T, 2>& other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;

		return *this;
	}

	template<typename T>
	Vector<T, 2> Vector<T, 2>::operator-=(const Vector<T, 2>& other)
	{
		return (*this += -other);
	}

	template<typename T>
	Vector<T, 2> Vector<T, 2>::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;

		return *this;
	}

	template<typename T>
	Vector<T, 2> Vector<T, 2>::operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;

		return *this;
	}
	// ------------

	// Data access 
	template<typename T>
	T Vector<T, 2>::Data(int idx) const
	{
		assert(idx < 2);
		return _data[idx];
	}

	template<typename T>
	T& Vector<T, 2>::Data(int idx)
	{
		assert(idx < 2);
		return _data[idx];
	}

	template<typename T>
	T Vector<T, 2>::operator[](int idx) const
	{
		assert(idx < 2);
		return _data[idx];
	}

	template<typename T>
	T& Vector<T, 2>::operator[](int idx)
	{
		assert(idx < 2);
		return _data[idx];
	}
}
#endif