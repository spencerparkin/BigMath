#pragma once

#include "BigInteger.h"
#include <string>

class Test
{
public:
	Test();
	virtual ~Test();

	virtual bool Perform() = 0;

	std::string name;
};

class Test64BitConversion : public Test
{
public:
	Test64BitConversion();
	virtual ~Test64BitConversion();

	virtual bool Perform() override;
};

class TestStringConversion : public Test
{
public:
	TestStringConversion();
	virtual ~TestStringConversion();

	virtual bool Perform() override;
};