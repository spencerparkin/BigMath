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
	 * 
	 * Each method assumes that all big-integer arguments (whether those be given as
	 * parameters or as given as the this-pointer) are already normalized, and each
	 * method will never produce an unormalized result.  If an argument is not normalized,
	 * then we just leave the result of the method as undefined.
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

		/**
		 * Make sure that all digits are less than the base.  This does not
		 * change the value represented by this big integer.
		 * 
		 * Every method of this class assumes its given big integers, whether
		 * given as an argument to the method, or being the class instance itself,
		 * are already normalized before the method executes.  A method will
		 * never produce a big integer that is not normalized as a result.
		 */
		bool Normalize();

		/**
		 * Return true if and only if this big integer is less than the given big integer.
		 * The to big integers in question here must be of the same base.
		 */
		bool IsLessThan(const BigInteger& bigInteger) const;

		/**
		 * Return true if and only if this big integer is greater than the given big integer.
		 * The to big integers in question here must be of the same base.
		 */
		bool IsGreaterThan(const BigInteger& bigInteger) const;

		/**
		 * Return true if and only if this big integer is equal to the given big integer.
		 * The to big integers in question here must be of the same base.
		 */
		bool IsEqualTo(const BigInteger& bigInteger) const;

		/**
		 * Return true if and only if this big integer represents zero.
		 */
		bool IsZero() const;

		/**
		 * Compute the sum of the two given big integers and then set this big
		 * integer to that result.  The given big integers must be of the same base.
		 * 
		 * @param[in] bigIntegerA This is the first summand.
		 * @param[in] bigIntegerB This is the second summand.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool SetAsSum(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB);

		/**
		 * Compute the difference between the two given big integers and then set this
		 * big integer to that result.  Of course, this is not a commutative operation.
		 * The given big integers must be of the same base.
		 * 
		 * @param[in] bigIntegerA This is the first operand.
		 * @param[in] bigIntegerB This is the second operand.
		 * @return True is returned if successful; false, otherwise.  We can fail here if the result would be negative.
		 */
		bool SetAsDifference(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB);

		/**
		 * Compute the product of the two given big integers and then set this
		 * big integer to that result.  The given big integers must be of the same base.
		 * 
		 * Note that there is a way to get O(n log n) time-complexity here using an FFT,
		 * but for simplicity of implimentation, we compute this in time O(n^2).
		 * 
		 * @param[in] bigIntegerA This is the first operand.
		 * @param[in] bigIntegerB This is the second operand.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool SetAsProduct(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB);

		/**
		 * Compute the quotient between the two given big integers and then set
		 * this big integer to the result.  The given big integers must be of the same base.
		 * 
		 * @param[in] bigIntegerA This is the dividend.
		 * @param[in] bigIntegerB This is the divisor.
		 * @param[out] remaidner This will be set to the remainder.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool SetAsQuotient(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB, BigInteger& remainder);

		/**
		 * Using binary exponentiation, calculate the remainder obtained
		 * when dividing this big number by the given modulus.
		 * 
		 * @param[in] modulus This can also be thought of as the divisor.
		 * @param[out] remainder This will hold the result.
		 * @return True is returned if successful; false, otherwise.
		 */
		bool CalcRemainder(uint32_t modulus, uint32_t& remainder) const;

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

		/**
		 * The square brackets operator is overloaded here to provide read-only access to
		 * this big integer's digit array.
		 * 
		 * @param[in] i This is exponent for the desired digit.
		 * @return The desired digit is returned or zero if the given exponent is out of range.
		 */
		uint32_t operator[](uint32_t i) const;

	private:

		std::vector<uint32_t> digitArray;
		uint32_t base;
	};
}