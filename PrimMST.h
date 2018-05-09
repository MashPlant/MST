//
// Created by MashPlant on 18-5-7.
//

#ifndef MST_PRIMMST_H
#define MST_PRIMMST_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Point2d.h"
#include "HeapTraits.h"

template<typename HeapType = void>
class PrimMST
{

};

template<>
class PrimMST<void>
{
	std::vector<Point2d> pts;

public:
	PrimMST(const std::vector<Point2d> &points) : pts(points)
	{}

	double operator()()
	{
		const int n = static_cast<int>(pts.size());
		std::unique_ptr<bool[]> vis(new bool[n]{});
		std::unique_ptr<double[]> dis(new double[n]{});
		std::fill(dis.get(), dis.get() + n, std::numeric_limits<double>::max());
		double ans = 0;
		dis[0] = 0.0;
		for (int _ = 0; _ < n; ++_)
		{
			double mn = std::numeric_limits<double>::max();
			int id = -1;
			for (int i = 0; i < n; ++i)
				if (!vis[i] && mn > dis[i])
					mn = dis[i], id = i;
			ans += mn;
			vis[id] = true;
			for (int i = 0; i < n; ++i)
				if (!vis[i])
					dis[i] = std::min(dis[i], (pts[id] - pts[i]).length());
		}
		return ans;
	}
};

#endif //MST_PRIMMST_H
