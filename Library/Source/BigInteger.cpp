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
	this->base = desiredBase;

	std::vector<uint32_t> digitStack;
	for (uint32_t i = 0; integerString.c_str()[i] != '\0'; i++)
	{
		char digitChar = integerString.c_str()[i];
		uint32_t digit = 0;
		if (!this->DigitFromChar(digit, digitChar))
			return false;
		
		digitStack.push_back(digit);
	}

	this->digitArray.clear();
	while (digitStack.size() > 0)
	{
		uint32_t digit = digitStack.back();
		digitStack.pop_back();
		this->digitArray.push_back(digit);
	}

	return true;
}

bool BigInteger::ToString(std::string& integerString) const
{
	integerString = "";

	std::vector<char> charStack;
	for (uint32_t digit : this->digitArray)
	{
		char digitChar = '?';
		if (!this->DigitToChar(digit, digitChar))
			return false;

		charStack.push_back(digitChar);
	}

	while (charStack.size() > 0)
	{
		char digitChar = charStack.back();
		charStack.pop_back();
		integerString += digitChar;
	}

	return true;
}

bool BigInteger::FromInteger(uint64_t integer, uint32_t desiredBase)
{
	if (desiredBase < 2)
		return false;

	this->base = desiredBase;
	this->digitArray.clear();
	while (integer > 0)
	{
		uint32_t digit = integer % this->base;
		this->digitArray.push_back(digit);
		integer -= digit;
		integer /= this->base;
	}

	return true;
}

bool BigInteger::ToInteger(uint64_t& integer) const
{
	if (this->base < 2)
		return false;

	integer = 0;
	uint64_t basePower = 1;
	for (uint32_t digit : this->digitArray)
	{
		uint64_t delta = uint64_t(digit) * basePower;
		uint64_t room = std::numeric_limits<uint64_t>::max() - integer;
		if (delta >= room)
			return false;

		integer += delta;
		basePower *= this->base;
	}

	return true;
}

bool BigInteger::FromBigInteger(const BigInteger& bigInteger, uint32_t desiredBase)
{
	if (desiredBase < 2)
		return false;

	this->base = desiredBase;

	if (this->base == bigInteger.base)
	{
		this->digitArray.clear();
		for (uint32_t digit : bigInteger.digitArray)
			this->digitArray.push_back(digit);

		return true;
	}

	uint64_t intermediateInteger = 0;
	if (bigInteger.ToInteger(intermediateInteger) && this->FromInteger(intermediateInteger, desiredBase))
		return true;

	// TODO: This will require addition, subtraction, division and binary exponentiation.

	return false;
}

bool BigInteger::ToBigInteger(BigInteger& bigInteger, uint32_t desiredBase)
{
	return bigInteger.FromBigInteger(*this, desiredBase);
}

bool BigInteger::DigitToChar(uint32_t digit, char& digitChar) const
{
	if (digit >= this->base)
		return false;

	if (0 <= digit && digit <= 9)
	{
		digitChar = '0' + char(digit);
		return true;
	}

	if (10 <= digit && digit <= 36)
	{
		digitChar = 'A' + char(digit - 10);
		return true;
	}

	return false;
}

bool BigInteger::DigitFromChar(uint32_t& digit, const char digitChar) const
{
	if ('0' <= digitChar && digitChar <= '9')
		digit = uint32_t(digitChar - '0');
	else if ('A' <= digitChar && digitChar <= 'Z')
		digit = uint32_t(digitChar - 'A') + 10;
	else if ('a' <= digitChar && digitChar <= 'z')
		digit = uint32_t(digitChar - 'a') + 10;
	else
		return false;

	return digit < this->base;
}