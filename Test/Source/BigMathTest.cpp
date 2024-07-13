#include "BigInteger.h"
#include <iostream>

using namespace BigMath;

int main(int argc, char** argv)
{
	BigInteger A, B;

	A.FromInteger(0xDEADBEEF, 16);

	std::string numberStringA;
	A.ToString(numberStringA);

	B.FromBigInteger(A, 10);

	std::string numberStringB;
	B.ToString(numberStringB);

	std::cout << numberStringA << std::endl;
	std::cout << numberStringB << std::endl;

	return 0;
}