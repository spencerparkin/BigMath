#include "Helpers.h"
#include <list>

namespace BigMath
{
	uint32_t BinaryExponentiation(uint32_t base, uint32_t exp, uint32_t modulus)
	{
		// It wouldn't be hard to write a non-recursive version of this.  Maybe do that?

		uint32_t result = 0;

		if (exp == 0)
			result = 1 % modulus;
		else if (exp == 1)
			result = base % modulus;
		else if (exp % 2 == 0)
		{
			uint32_t subResult = BinaryExponentiation(base, exp / 2, modulus);
			result = (subResult * subResult) % modulus;
		}
		else
		{
			uint32_t subResultA = BinaryExponentiation(base, (exp - 1) / 2, modulus);
			uint32_t subResultB = BinaryExponentiation(base, exp - (exp - 1) / 2, modulus);
			result = (subResultA * subResultB) % modulus;
		}

		return result;
	}
}