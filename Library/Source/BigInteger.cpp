#include "BigInteger.h"
#include "Helpers.h"

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
		if (!AccumulateWithOverflowCheck(integer, delta))
			return false;

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

bool BigInteger::CalcRemainder(uint32_t modulus, uint32_t& remainder) const
{
	remainder = 0;
	for (uint32_t exp = 0; exp < (uint32_t)this->digitArray.size(); exp++)
	{
		uint32_t digit = this->digitArray[exp];
		remainder += (digit * BinaryExponentiation(this->base, exp, modulus)) % modulus;
	}

	return true;
}

bool BigInteger::Normalize()
{
	uint32_t i = 0;
	while (i < this->digitArray.size())
	{
		uint32_t digit = this->digitArray[i];
		if (digit >= this->base)
		{
			uint32_t remainder = digit % this->base;
			uint32_t quotient = (digit - remainder) / this->base;
			this->digitArray[i] = remainder;

			if (i + 1 == this->digitArray.size())
				this->digitArray.push_back(0);

			if (!AccumulateWithOverflowCheck(this->digitArray[i + 1], quotient))
				return false;
		}

		i++;
	}

	while (this->digitArray.back() == 0 && this->digitArray.size() > 1)
		this->digitArray.pop_back();

	return true;
}

bool BigInteger::IsLessThan(const BigInteger& bigInteger) const
{
	if (this->base != bigInteger.base)
		return false;

	if (this->digitArray.size() < bigInteger.digitArray.size())
		return true;

	if (this->digitArray.size() > bigInteger.digitArray.size())
		return false;

	if (this->digitArray.size() == 0)
		return false;

	for (uint32_t i = 0; i < (uint32_t)this->digitArray.size(); i++)
	{
		uint32_t j = uint32_t(this->digitArray.size()) - 1 - i;
		uint32_t digitA = this->digitArray[j];
		uint32_t digitB = bigInteger.digitArray[j];
		if (digitA < digitB)
			return true;
		else if (digitA > digitB)
			return false;
	}

	return false;
}

bool BigInteger::IsGreaterThan(const BigInteger& bigInteger) const
{
	return bigInteger.IsLessThan(*this);
}

bool BigInteger::IsEqualTo(const BigInteger& bigInteger) const
{
	if (this->base != bigInteger.base)
		return false;

	if (this->digitArray.size() != bigInteger.digitArray.size())
		return false;

	for (uint32_t i = 0; i < (uint32_t)this->digitArray.size(); i++)
	{
		uint32_t digitA = this->digitArray[i];
		uint32_t digitB = bigInteger.digitArray[i];
		if (digitA != digitB)
			return false;
	}

	return true;
}

bool BigInteger::IsZero() const
{
	return this->base > 1 && this->digitArray.size() == 1 && this->digitArray[0] == 0;
}

bool BigInteger::SetAsSum(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB)
{
	if (bigIntegerA.base != bigIntegerB.base)
		return false;

	this->base = bigIntegerA.base;

	uint32_t sizeA = (uint32_t)bigIntegerA.digitArray.size();
	uint32_t sizeB = (uint32_t)bigIntegerB.digitArray.size();

	if (sizeA > sizeB)
		this->digitArray.resize(sizeA);
	else
		this->digitArray.resize(sizeB);

	for (uint32_t i = 0; i < (uint32_t)this->digitArray.size(); i++)
		this->digitArray[i] = bigIntegerA[i] + bigIntegerB[i];

	if (!this->Normalize())
		return false;

	return true;
}

bool BigInteger::SetAsDifference(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB)
{
	if (bigIntegerA.base != bigIntegerB.base)
		return false;

	if (bigIntegerA.digitArray.size() == 0 || bigIntegerB.digitArray.size() == 0)
		return false;

	if (bigIntegerA.IsLessThan(bigIntegerB))
		return false;

	BigInteger bigIntegerACopy;
	if (!bigIntegerACopy.FromBigInteger(bigIntegerA, bigIntegerA.base))
		return false;

	this->base = bigIntegerA.base;

	this->digitArray.clear();
	for (uint32_t i = 0; i < (uint32_t)bigIntegerACopy.digitArray.size(); i++)
	{
		uint32_t digitA = bigIntegerACopy[i];
		uint32_t digitB = bigIntegerB[i];

		if (digitA < digitB)
		{
			uint32_t j = 0;
			for (j = i + 1; j < bigIntegerACopy.digitArray.size(); j++)
				if (bigIntegerACopy[j] != 0)
					break;

			if (j == bigIntegerACopy.digitArray.size())
				return false;

			while (j > i)
			{
				bigIntegerACopy.digitArray[j]--;
				bigIntegerACopy.digitArray[j - 1] += this->base;
				j--;
			}

			digitA = bigIntegerACopy[i];
		}

		this->digitArray.push_back(digitA - digitB);
	}

	if (!this->Normalize())
		return false;

	return true;
}

bool BigInteger::SetAsProduct(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB)
{
	if (bigIntegerA.base != bigIntegerB.base)
		return false;

	if (bigIntegerA.digitArray.size() == 0 || bigIntegerB.digitArray.size() == 0)
		return false;

	this->base = bigIntegerA.base;

	this->digitArray.resize(bigIntegerA.digitArray.size() + bigIntegerB.digitArray.size());
	for (uint32_t& digit : this->digitArray)
		digit = 0;

	for (uint32_t i = 0; i < bigIntegerA.digitArray.size(); i++)
	{
		uint32_t digitA = bigIntegerA[i];

		for (uint32_t j = 0; j < bigIntegerB.digitArray.size(); j++)
		{
			uint32_t digitB = bigIntegerB[j];

			uint32_t k = i + j;
			uint32_t& digit = this->digitArray[k];
			if (!AccumulateWithOverflowCheck(digit, digitA * digitB))
				return false;
		}
	}

	if (!this->Normalize())
		return false;

	return true;
}

bool BigInteger::SetAsQuotient(const BigInteger& bigIntegerA, const BigInteger& bigIntegerB, BigInteger& remainder)
{
	if (bigIntegerA.base != bigIntegerB.base)
		return false;

	if (bigIntegerB.IsZero())
		return false;

	this->base = bigIntegerA.base;
	remainder.base = bigIntegerA.base;

	if (bigIntegerA.IsLessThan(bigIntegerB))
	{
		this->digitArray.resize(1);
		this->digitArray[0] = 0;

		if (!remainder.FromBigInteger(bigIntegerA, bigIntegerA.base))
			return false;

		return true;
	}

	uint32_t degreeA = bigIntegerA.digitArray.size() - 1;
	uint32_t degreeB = bigIntegerB.digitArray.size() - 1;
	uint32_t degree = degreeA - degreeB;
	uint32_t coeficient = this->base - 1;

	BigInteger monomial, nextNumerator;
	monomial.base = this->base;

	while (true)
	{
		monomial.digitArray.resize(degree + 1);
		for (uint32_t i = 0; i < (uint32_t)monomial.digitArray.size(); i++)
			monomial.digitArray[i] = (i < degree) ? 0 : coeficient;

		BigInteger product;
		if (!product.SetAsProduct(bigIntegerB, monomial))
			return false;

		if (nextNumerator.SetAsDifference(bigIntegerA, product))
			break;

		if (coeficient > 1)
			coeficient--;
		else
		{
			coeficient = this->base - 1;
			if (degree > 0)
				degree--;
			else
				return false;
		}
	}

	BigInteger nextQuotient;
	if (!nextQuotient.SetAsQuotient(nextNumerator, bigIntegerB, remainder))
		return false;

	if (!this->SetAsSum(monomial, nextQuotient))
		return false;

	return true;
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

uint32_t BigInteger::operator[](uint32_t i) const
{
	if (i >= this->digitArray.size())
		return 0;

	return this->digitArray[i];
}