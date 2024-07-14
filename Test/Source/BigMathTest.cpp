#include "BigMathTest.h"
#include <iostream>

using namespace BigMath;

//---------------------------------- Test ----------------------------------

Test::Test()
{
}

/*virtual*/ Test::~Test()
{
}

//---------------------------------- Test64BitConversion ----------------------------------

Test64BitConversion::Test64BitConversion()
{
	this->name = "64-bit conversion test";
}

/*virtual*/ Test64BitConversion::~Test64BitConversion()
{
}

/*virtual*/ bool Test64BitConversion::Perform()
{
	BigInteger bigInt;

	uint64_t intA = 0xDEADBEEF;
	if (!bigInt.FromInteger(intA, 16))
		return false;

	uint64_t intB = 0;
	if (!bigInt.ToInteger(intB))
		return false;

	if (intA != intB)
		return false;

	return true;
}

//---------------------------------- TestStringConversion ----------------------------------

TestStringConversion::TestStringConversion()
{
	this->name = "string conversion test";
}

/*virtual*/ TestStringConversion::~TestStringConversion()
{
}

/*virtual*/ bool TestStringConversion::Perform()
{
	BigInteger bigInt;

	std::string stringA = "DEADBEEF";
	if (!bigInt.FromString(stringA, 16))
		return false;

	uint64_t intA = 0;
	if (!bigInt.ToInteger(intA))
		return false;

	if (intA != 0xDEADBEEF)
		return false;

	std::string stringB;
	if (!bigInt.ToString(stringB))
		return false;

	if (stringB != stringA)
		return false;

	return true;
}