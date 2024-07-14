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

//---------------------------------- TestComparison ----------------------------------

TestComparison::TestComparison()
{
	this->name = "comparison test";
}

/*virtual*/ TestComparison::~TestComparison()
{
}

/*virtual*/ bool TestComparison::Perform()
{
	BigInteger bigIntA, bigIntB;

	if (!bigIntA.FromInteger(12345, 10))
		return false;

	if (!bigIntB.FromInteger(54321, 10))
		return false;
	
	if (!bigIntA.IsLessThan(bigIntB))
		return false;

	if (!bigIntA.FromString("DEADBEEF", 16))
		return false;

	if (!bigIntB.FromInteger(0xDEADBEEF, 16))
		return false;

	if (!bigIntA.IsEqualTo(bigIntB))
		return false;

	return true;
}

//---------------------------------- TestAddition ----------------------------------

TestAddition::TestAddition()
{
	this->name = "addition test";
}

/*virtual*/ TestAddition::~TestAddition()
{
}

/*virtual*/ bool TestAddition::Perform()
{
	BigInteger bigIntA, bigIntB;

	uint64_t intA = 221122L;
	uint64_t intB = 889988L;

	if (!bigIntA.FromInteger(intA, 10))
		return false;

	if (!bigIntB.FromInteger(intB, 10))
		return false;

	BigInteger bigIntSum;
	if (!bigIntSum.SetAsSum(bigIntA, bigIntB))
		return false;

	uint64_t sum = 0;
	if (!bigIntSum.ToInteger(sum))
		return false;

	if (sum != intA + intB)
		return false;

	return true;
}

//---------------------------------- TestAddition ----------------------------------

TestSubtraction::TestSubtraction()
{
	this->name = "subtraction test";
}

/*virtual*/ TestSubtraction::~TestSubtraction()
{
}

/*virtual*/ bool TestSubtraction::Perform()
{
	BigInteger bigIntA, bigIntB;

	uint64_t intA = 221122L;
	uint64_t intB = 889988L;

	if (!bigIntA.FromInteger(intA, 10))
		return false;

	if (!bigIntB.FromInteger(intB, 10))
		return false;

	BigInteger bigIntDiff;

	if (bigIntDiff.SetAsDifference(bigIntA, bigIntB) != false)
		return false;

	if (bigIntDiff.SetAsDifference(bigIntB, bigIntA) != true)
		return false;

	uint64_t diff = 0;
	if (!bigIntDiff.ToInteger(diff))
		return false;

	if (diff != intB - intA)
		return false;

	return true;
}