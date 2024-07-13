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

		/**
		 * Convert a string to a big integer.  The string should consist of
		 * letters and numbers only.  Case does not matter.
		 * 
		 * @param[in] integerString This is the string to convert.
		 * @param[in] desiredBase The given string expected to be in this base.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool FromString(const std::string& integerString, uint32_t desiredBase);

		/**
		 * Convert this big integer into a string.  The string will be
		 * expressed in the base used by this big integer.
		 * 
		 * @param[out] integerString This will hold the result.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool ToString(std::string& integerString) const;

		/**
		 * Convert a 64-bit integer to a big integer.
		 * 
		 * @param[in] integer This integer gets represented in this big integer as the result.
		 * @param[in] desiredBase The given integer will be represented in this base.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool FromInteger(uint64_t integer, uint32_t desiredBase);

		/**
		 * Convert this big integer to a 64-bit integer.  This can fail if
		 * this big integer doesn't fit in 64 bits.
		 * 
		 * @param[out] integer This will hold the result.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool ToInteger(uint64_t& integer) const;

		/**
		 * Convert a big integer represented in one base to a big integer
		 * represented in another base.  You can achieve the same thing
		 * using the @ref ToInteger and @ref FromInteger methods, but that
		 * will not work if the big integer can't fit into 64 bits.  In fact,
		 * that is attempted here first, but if it doesn't work, a different
		 * algorithm is used to perform the conversion.
		 * 
		 * @param[in] bigInteger This is the integer to convert.
		 * @param[in] desiredBase This big integer will represent the given big integer in this base.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool FromBigInteger(const BigInteger& bigInteger, uint32_t desiredBase);

		/**
		 * This is provided for completeness.  It just calls @ref FromBigInteger.
		 */
		bool ToBigInteger(BigInteger& bigInteger, uint32_t desiredBase);

		// TODO: Support addition, subtraction, multiplication and division.
		// TODO: Support binary exponentiation.

	private:

		/**
		 * Convert a digit into a human-readable character.
		 * 
		 * @param[in] digit This is the digit to convert.
		 * @param[out] digitChar This will hold the result.
		 * @return True is returned if successful; false, otherwise.  The given digit must be less than our base.
		 */
		bool DigitToChar(uint32_t digit, char& digitChar) const;

		/**
		 * Convert a human-readable character into a digit.
		 * 
		 * @param[out] digit This will hold the result.
		 * @param[in] digitChar This is the character to convert.
		 * @return True is returned if successful; false, otherwise.  The resulting digit must be less than our base.
		 */
		bool DigitFromChar(uint32_t& digit, const char digitChar) const;

		std::vector<uint32_t> digitArray;
		uint32_t base;
	};
}