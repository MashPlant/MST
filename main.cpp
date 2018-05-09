#include "Point2d.h"
#include "KDTree.h"
#include "Mat22.h"
#include <iostream>
#include <random>
#include "YaoMST.h"
#include "PrimMST.h"
#include "KruskalMST.h"
#include <iomanip>

using namespace std;

mt19937 mt;
uniform_real_distribution<> dis(0, 100);

int main()
{

	vector<Point2d> vec;
	for (int i = 0; i < 100000; ++i)
		vec.push_back({dis(mt), dis(mt)});


	{
		auto beg = clock();
		PrimMST<> p(vec);
		cout << fixed << setprecision(8) << p() << endl;
		cout << clock() - beg << endl;
	}

	{
		auto beg = clock();
		YaoMST y(vec, 0.1);
		cout << fixed << setprecision(8) << y() << endl;
		cout << clock() - beg << endl;
	}

//	{
//		auto beg = clock();
//		KruskalMST k(vec);
//		cout << k() << endl;
//		cout << clock() - beg << endl;
//	}


}
