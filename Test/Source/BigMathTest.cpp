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

//---------------------------------- TestSubtraction ----------------------------------

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

//---------------------------------- TestSubtraction ----------------------------------

TestSubtractionWithBarrow::TestSubtractionWithBarrow()
{
	this->name = "subtraction with barrow test";
}

/*virtual*/ TestSubtractionWithBarrow::~TestSubtractionWithBarrow()
{
}

/*virtual*/ bool TestSubtractionWithBarrow::Perform()
{
	BigInteger bigIntA, bigIntB;

	uint64_t intA = 900000L;
	uint64_t intB = 800001L;

	if (!bigIntA.FromInteger(intA, 10))
		return false;

	if (!bigIntB.FromInteger(intB, 10))
		return false;

	BigInteger bigIntDiff;
	if (!bigIntDiff.SetAsDifference(bigIntA, bigIntB))
		return false;

	uint64_t diff = 0;
	if (!bigIntDiff.ToInteger(diff))
		return false;

	if (diff != intA - intB)
		return false;

	return true;
}

//---------------------------------- TestProduct ----------------------------------

TestProduct::TestProduct()
{
	this->name = "product test";
}

/*virtual*/ TestProduct::~TestProduct()
{
}

/*virtual*/ bool TestProduct::Perform()
{
	BigInteger bigIntA, bigIntB;

	uint64_t intA = 123456789;
	uint64_t intB = 987654321;

	if (!bigIntA.FromInteger(intA, 10))
		return false;

	if (!bigIntB.FromInteger(intB, 10))
		return false;

	BigInteger bigIntProduct;
	if (!bigIntProduct.SetAsProduct(bigIntA, bigIntB))
		return false;

	uint64_t product = 0;
	if (!bigIntProduct.ToInteger(product))
		return false;

	if (product != intA * intB)
		return false;

	if (!bigIntProduct.SetAsProduct(bigIntB, bigIntA))
		return false;

	if (!bigIntProduct.ToInteger(product))
		return false;

	if (product != intA * intB)
		return false;

	return true;
}

//---------------------------------- TestDivision ----------------------------------

TestDivision::TestDivision()
{
	this->name = "division test";
}

/*virtual*/ TestDivision::~TestDivision()
{
}

/*virtual*/ bool TestDivision::Perform()
{
	BigInteger bigIntA, bigIntB;

	uint64_t intA = 328;
	uint64_t intB = 8487211;

	if (!bigIntA.FromInteger(intA, 10))
		return false;

	if (!bigIntB.FromInteger(intB, 10))
		return false;

	BigInteger bigIntQuotient, bigIntRemainder;
	if (!bigIntQuotient.SetAsQuotient(bigIntA, bigIntB, bigIntRemainder))
		return false;

	uint64_t quotient = 0;
	if (!bigIntQuotient.ToInteger(quotient))
		return false;

	uint64_t remainder = 0;
	if (!bigIntRemainder.ToInteger(remainder))
		return false;

	if (quotient != intA / intB)
		return false;

	if (remainder != intA % intB)
		return false;

	if (!bigIntQuotient.SetAsQuotient(bigIntB, bigIntA, bigIntRemainder))
		return false;

	if (!bigIntQuotient.ToInteger(quotient))
		return false;

	if (!bigIntRemainder.ToInteger(remainder))
		return false;

	if (quotient != intB / intA)
		return false;

	if (remainder != intB % intA)
		return false;

	return true;
}

//---------------------------------- TestRemainder ----------------------------------

TestRemainder::TestRemainder()
{
	this->name = "remainder test";
}

/*virtual*/ TestRemainder::~TestRemainder()
{
}

/*virtual*/ bool TestRemainder::Perform()
{
	uint32_t intA = 123456783;

	BigInteger bigIntA;
	if (!bigIntA.FromInteger(intA, 10))
		return false;

	uint32_t remainder = 0;
	if (!bigIntA.CalcRemainder(10, remainder))
		return false;

	if (remainder != intA % 10)
		return false;

	return true;
}

//---------------------------------- TestBaseConversion ----------------------------------

TestBaseConversion::TestBaseConversion()
{
	this->name = "base conversion test";
}

/*virtual*/ TestBaseConversion::~TestBaseConversion()
{
}

/*virtual*/ bool TestBaseConversion::Perform()
{
	//std::string numberStringA = "DEADBEEFDEADBEEFDEADBEEF";
	std::string numberStringA = "DEADBEEF";

	BigInteger bigIntA;
	if (!bigIntA.FromString(numberStringA, 16))
		return false;

	BigInteger bigIntB;
	if (!bigIntB.FromBigInteger(bigIntA, 10))
		return false;

	std::string numberStringB;
	if (!bigIntB.ToString(numberStringB))
		return false;

	BigInteger bigIntC;
	if (!bigIntC.FromBigInteger(bigIntB, 16))
		return false;

	std::string numberStringC;
	if (!bigIntC.ToString(numberStringC))
		return false;

	if (numberStringC != numberStringA)
		return false;

	return true;
}