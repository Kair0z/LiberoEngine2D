#pragma once
#include <cassert>	
#include <initializer_list>

#ifndef LIBERO_MATH_VECTOR
#define LIBERO_MATH_VECTOR

namespace Libero
{
	template <typename T, size_t S>
	struct Vector	
	{
	public:
		template<typename T, size_t S>
		T& Data(const size_t idx)
		{
			assert(idx < S);
			return _data[idx];
		}

		template<typename T, size_t S>
		T Data(const size_t idx) const
		{
			assert(idx < S);
			return _data(idx);
		}

		template<typename T, size_t S>
		T& operator[](const size_t idx)
		{
			assert(idx < S);
			return _data[idx];
		}

		template<typename T, size_t S>
		T operator[](const size_t idx)
		{
			assert(idx < S);
			return _data[idx];
		}

		template<typename T, size_t S>
		bool IsZero() const
		{
			for (size_t i{}; i < S; ++i)
			{
				if (_data[i] != 0.f) return false;
			}

			return true;
		}

	private:
		T _data[S];
	};

	// Member functions:
	
	// Non-member functions:
	template<typename T, size_t S>
	T SqrMagnitude(const Vector<T, S>& vector)
	{
		return static_cast<T>(Dot(vector, vector));
	}

	template<typename T, size_t S>
	T SqrLength(const Vector<T, S>& vector)
	{
		return SqrMagnitude(vector);
	}

	template<typename T, size_t S>
	T Magnitude(const Vector<T, S>& vector)
	{
		return static_cast<T>(sqrt(SqrMagnitude(vector)));
	}

	template<typename T, size_t S>
	T Length(const Vector<T, S>& vector)
	{
		return static_cast<T>(sqrt(SqrLength(vector)));
	}

	template<typename T, size_t S>
	bool IsZero(const Vector<T, S>& vector)
	{
		bool isZero = true;

		for (int i{}; i < S; ++i)
		{
			if (vector[i] != 0) isZero = false;
		}

		return isZero;
	}

	template<typename T, size_t S>
	T Normalize(Vector<T, S>& vector)
	{
		const T magnitude = Magnitude(vector);

		if (IsZero(vector)) return 0;

		const T inverseMagnitude = static_cast<T>(1.f / magnitude);
		vector *= inverseMagnitude;

		return magnitude;
	}

	template<typename T, size_t S>
	Vector<T, S> Normalized(const Vector<T, S>& vector)
	{
		Vector<T, S> copy = Vector<T, S>(vector);
		Normalize(copy);

		return copy;
	}
}
#endif