#pragma once

#include "BigMath.h"
#include <stdint.h>

namespace BigMath
{
	BIG_MATH_API uint32_t BinaryExponentiation(uint32_t base, uint32_t exp, uint32_t modulus);
}