//
// Created by MashPlant on 18-5-15.
//

#ifndef MST_GENERATOR_H
#define MST_GENERATOR_H


#include "BaseTest.h"

class GeneratorTest : public BaseTest
{
	std::function<double(int)> gen;

public:
	template<typename Func>
	GeneratorTest(int N, Func &&f) : BaseTest(N), gen(std::forward<Func>(f))
	{}

	void generate() override
	{
		for (int i = 0; i < N; ++i)
		{
			double x = gen(i), y = gen(i);
			input[i] = {x, y};
		}
	}
};


#endif //MST_GENERATOR_H
