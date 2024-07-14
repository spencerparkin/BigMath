#pragma once

#include "BigMath.h"
#include <stdint.h>
#include <limits>

namespace BigMath
{
	/**
	 * Calculate and return (base ^ exp) % modulus.
	 */
	BIG_MATH_API uint32_t BinaryExponentiation(uint32_t base, uint32_t exp, uint32_t modulus);

	/**
	 * Add two integers, but fail if the result would overflow the bit-width of the integers involved.
	 */
	template<typename T>
	bool AddWithOverflowCheck(T& sum, T a, T b)
	{
		sum = a;
		T room = std::numeric_limits<T>::max() - sum;
		if (b >= room)
			return false;
		sum += b;
		return true;
	}

	/**
	 * Accumulate an integer with another integer, but fail if the result would overflow the bit-width of the integers involved.
	 */
	template<typename T>
	bool AccumulateWithOverflowCheck(T& sum, T a)
	{
		T room = std::numeric_limits<T>::max() - sum;
		if (a >= room)
			return false;
		sum += a;
		return true;
	}
}