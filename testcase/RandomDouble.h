//
// Created by MashPlant on 18-5-15.
//

#ifndef MST_RANDOMDOUBLE_H
#define MST_RANDOMDOUBLE_H

#include <random>
#include "BaseTest.h"

class RandomDoubleTest : public BaseTest
{
public:
	using BaseTest::BaseTest;
	void generate() override
	{
		std::mt19937 mt;
		std::uniform_real_distribution<> dis(0, 10000.0);
		for (int i = 0; i < N; ++i)
			input[i].x = dis(mt), input[i].y = dis(mt);
	}
};

#endif //MST_RANDOMDOUBLE_H
