#include <array>
#include "BaseTest.h"

int main()
{
	std::mt19937 mt;
	std::uniform_real_distribution<> dis(0, 100);
	std::array tests =
			{
					TestFactory::createTest<TestFactory::RandomDouble>(10000),
					TestFactory::createTest<TestFactory::DistinctInt>(10000),
					TestFactory::createTest<TestFactory::Generator>(10000, [&](int)
					{ return dis(mt); })
			};
	for (auto &test : tests)
		test->solveAll();
}