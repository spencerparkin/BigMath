#include "BigInteger.h"

using namespace BigMath;

BigInteger::BigInteger()
{
	this->base = 0;
}

/*virtual*/ BigInteger::~BigInteger()
{
}

bool BigInteger::FromString(const std::string& integerString, uint32_t desiredBase)
{
	return false;
}

bool BigInteger::ToString(std::string& integerString) const
{
	return false;
}

bool BigInteger::FromInteger(uint64_t integer, uint32_t desiredBase)
{
	return false;
}

bool BigInteger::ToInteger(uint64_t& integer) const
{
	return false;
}

bool BigInteger::FromBigInteger(const BigInteger& bigInteger, uint32_t desiredBase)
{
	return false;
}

bool BigInteger::ToBigInteger(BigInteger& bigInteger, uint32_t desiredBase)
{
	return bigInteger.FromBigInteger(*this, desiredBase);
}