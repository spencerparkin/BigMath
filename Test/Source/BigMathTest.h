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

class TestComparison : public Test
{
public:
	TestComparison();
	virtual ~TestComparison();

	virtual bool Perform() override;
};

class TestAddition : public Test
{
public:
	TestAddition();
	virtual ~TestAddition();

	virtual bool Perform() override;
};

class TestSubtraction : public Test
{
public:
	TestSubtraction();
	virtual ~TestSubtraction();

	virtual bool Perform() override;
};

class TestSubtractionWithBarrow : public Test
{
public:
	TestSubtractionWithBarrow();
	virtual ~TestSubtractionWithBarrow();

	virtual bool Perform() override;
};

class TestProduct : public Test
{
public:
	TestProduct();
	virtual ~TestProduct();

	virtual bool Perform() override;
};

class TestDivision : public Test
{
public:
	TestDivision();
	virtual ~TestDivision();

	virtual bool Perform() override;
};

class TestRemainder : public Test
{
public:
	TestRemainder();
	virtual ~TestRemainder();

	virtual bool Perform() override;
};