#pragma once

#ifndef LIBERO_MATH_VECTOR3
#define LIBERO_MATH_VECTOR3
#include <cassert>
#include "Vector.h"
#include <ostream>

namespace Libero
{
	template<typename T>
	struct Vector<T, 3>
	{
	public:
		// Data
#pragma warning(disable : 4201)
		union
		{
			T _data[3];
			struct { T x, y, z; };
			struct { T r, g, b; };
		};
#pragma warning(default : 4201)

	public:
		// Constructors & ROF:
		Vector<T, 3>() = default;
		Vector<T, 3>(const T& x, const T& y, const T& z)
		{
			_data[0] = x;
			_data[1] = y;
			_data[2] = z;
		}
		Vector<T, 3>(const Vector<T, 3>& other) = default;
		Vector<T, 3>(Vector<T, 3>&& other) = default;
		Vector<T, 3>& operator=(const Vector<T, 3>& other) = default;
		Vector<T, 3>& operator=(Vector<T, 3>&& other) = default;
		~Vector<T, 3>() = default;

		// conversion constructors: (last element: 0)
		Vector<T, 3>(const Vector<T, 2>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
		}
		Vector<T, 3>(Vector <T, 2>&& other) 
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
		}
		Vector<T, 3>(const Vector<T, 4>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = other.z;
		}
		Vector<T, 3>(Vector<T, 4>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = other.z;
		}

		// conversion operators: last element(s): 0
		Vector<T, 3> operator()(const Vector<T, 2>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
		}
		Vector<T, 3> operator()(Vector <T, 2>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = 0;
		}
		Vector<T, 3> operator()(const Vector<T, 4>& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = other.z;
		}
		Vector<T, 3> operator()(Vector<T, 4>&& other)
		{
			_data[0] = other.x;
			_data[1] = other.y;
			_data[2] = other.z;
		}

		// Print
		std::ostream& Cout(std::ostream& out) const
		{
			out << "(" << x << ", " << y << ", " << z << ")";
		}

		// Data access:
		T Data(int idx) const;
		T& Data(int idx);
		T operator[](int idx) const;
		T& operator[](int idx);

		// Member operators:
		Vector<T, 3> operator-() const;
		Vector<T, 3> operator+=(const Vector<T, 3>& other);
		Vector<T, 3> operator-=(const Vector<T, 3>& other);
		Vector<T, 3> operator*=(float scalar);
		Vector<T, 3> operator/=(float scalar);
	};


	// IMPORTANT STUFF:
	template<typename T>
	T Dot(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return static_cast<T>(lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
	}

	template<typename T>
	Vector<T, 3> Cross(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return Vector<T, 3>{
			lhs.y* rhs.z - lhs.z * rhs.y,
				lhs.z* rhs.x - lhs.x * rhs.z,
				lhs.x* rhs.y - lhs.y * rhs.x};
	}

	template<typename T>
	Vector<T, 3> Abs(const Vector<T, 3>& vector)
	{
		return Vector<T, 3>(std::abs(vector.x), std::abs(vector.y), std::abs(vector.z));
	}

	// arithmetic operator overloads (non-member)
	template<typename T>
	Vector<T, 3> operator+(const Vector<T, 3>& lhs, const Vector<T, 3> rhs)
	{
		return Vector<T, 3>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	template<typename T>
	Vector<T, 3> operator-(const Vector<T, 3>& lhs, const Vector<T, 3> rhs)
	{
		return Vector<T, 3>(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	template<typename T>
	Vector<T, 3> operator*(const Vector<T, 3>& lhs, const Vector<T, 3> rhs) // NOT DOT!
	{
		return Vector<T, 3>(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	template<typename T>
	Vector<T, 3> operator*(const Vector<T, 3>& lhs, const float a)
	{
		return Vector<T, 3>(lhs.x * a, lhs.y * a, lhs.z * a);
	}

	template<typename T>
	Vector<T, 3> operator*(const float a, const Vector<T, 3>& rhs)
	{
		return rhs * a;
	}

	template<typename T>
	Vector<T, 3> operator/(const Vector<T, 3>& lhs, const Vector<T, 3> rhs)
	{
		return Vector<T, 3>(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	template<typename T>
	Vector<T, 3> operator/(const Vector<T, 3>& lhs, const float a)
	{
		return Vector<T, 3>(lhs.x / a, lhs.y / a, lhs.z / a);
	}

	// relational operators
	template<typename T>
	bool operator==(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return (lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2]);
	}

	template<typename T>
	bool operator!=(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	bool operator<=(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return (Length(lhs) < Length(rhs) || lhs == rhs);
	}

	template<typename T>
	bool operator>=(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return (Length(lhs) > Length(rhs) || lhs == rhs);
	}

	template<typename T>
	bool operator<(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return !(lhs >= rhs);
	}

	template<typename T>
	bool operator>(const Vector<T, 3>& lhs, const Vector<T, 3>& rhs)
	{
		return !(lhs <= rhs);
	}

	// operator overloads (member)
	template<typename T>
	Vector<T, 3> Vector<T, 3>::operator-() const
	{
		return Vector<T, 3>(-x, -y, -z);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::operator+=(const Vector<T, 3>& other)
	{
		this->x = this->x + other.x;
		this->y = this->y + other.y;
		this->z = this->z + other.z;

		return *this;
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::operator-=(const Vector<T, 3>& other)
	{
		return (*this += -other);
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::operator*=(float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;

		return *this;
	}

	template<typename T>
	Vector<T, 3> Vector<T, 3>::operator/=(float scalar)
	{
		this->x /= scalar;
		this->y /= scalar;
		this->z /= scalar;

		return *this;
	}
	// ------------

	// Data access 
	template<typename T>
	T Vector<T, 3>::Data(int idx) const
	{
		assert(idx < 3);
		return _data[idx];
	}

	template<typename T>
	T& Vector<T, 3>::Data(int idx)
	{
		assert(idx < 3);
		return _data[idx];
	}

	template<typename T>
	T Vector<T, 3>::operator[](int idx) const
	{
		assert(idx < 3);
		return _data[idx];
	}

	template<typename T>
	T& Vector<T, 3>::operator[](int idx)
	{
		assert(idx < 3);
		return _data[idx];
	}
}
#endif