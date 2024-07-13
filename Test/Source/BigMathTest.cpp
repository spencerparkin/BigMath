#include "BigInteger.h"
#include <iostream>

using namespace BigMath;

int main(int argc, char** argv)
{
	BigInteger A, B;

	A.FromInteger(0x1234ABCD, 16);

	std::string numberStringA;
	A.ToString(numberStringA);

	std::cout << numberStringA << std::endl;

	return 0;
}