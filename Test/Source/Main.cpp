#include "BigMathTest.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	std::vector<Test*> testArray;
	testArray.push_back(new Test64BitConversion());
	testArray.push_back(new TestStringConversion());
	testArray.push_back(new TestComparison());
	testArray.push_back(new TestAddition());
	testArray.push_back(new TestSubtraction());
	testArray.push_back(new TestSubtractionWithBarrow());
	testArray.push_back(new TestProduct());
	testArray.push_back(new TestDivision());
	testArray.push_back(new TestRemainder());
	testArray.push_back(new TestBaseConversion());

	uint32_t passCount = 0;
	for (Test* test : testArray)
	{
		printf("===========================================\n");
		printf("Test: %s\n", test->name.c_str());

		bool passed = test->Perform();
		if (passed)
			passCount++;

		printf("Result: %s\n", (passed ? "PASSED" : "FAILED!!!"));
	}

	float successRate = float(passCount) / float(testArray.size());

	printf("===========================================\n");
	printf("All tests completed.\n");
	printf("Success rate: %1.2f%%\n", successRate * 100.0f);

	for (Test* test : testArray)
		delete test;

	testArray.clear();

	return 0;
}