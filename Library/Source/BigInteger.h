#pragma once

#include "BigMath.h"
#include <stdint.h>
#include <vector>
#include <string>

namespace BigMath
{
	/**
	 * These are unsigned integers represented in a 32-bit base with 32-bit digits,
	 * having an arbitrary number of digits.
	 */
	class BIG_MATH_API BigInteger
	{
	public:
		BigInteger();
		virtual ~BigInteger();

		bool FromString(const std::string& integerString, uint32_t desiredBase);
		bool ToString(std::string& integerString) const;

		bool FromInteger(uint64_t integer, uint32_t desiredBase);
		bool ToInteger(uint64_t& integer) const;

		bool FromBigInteger(const BigInteger& bigInteger, uint32_t desiredBase);
		bool ToBigInteger(BigInteger& bigInteger, uint32_t desiredBase);

		// TODO: Support addition, subtraction, multiplication and division.
		// TODO: Support binary exponentiation.

	private:
		std::vector<uint32_t> digitArray;
		uint32_t base;
	};
}