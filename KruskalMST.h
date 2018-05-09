//
// Created by MashPlant on 18-5-8.
//

#ifndef MST_KRUSKALMST_H
#define MST_KRUSKALMST_H

#include <vector>
#include <algorithm>
#include "UFS.h"
#include "Point2d.h"

class KruskalMST
{
	struct Edge
	{
		int from, to;
		double w;

		bool operator<(const Edge &rhs) const
		{ return w < rhs.w; }
	};

	std::vector<Edge> edges;
	int n;
public:
	KruskalMST(const std::vector<Point2d> &points)
	{
		n = static_cast<int>(points.size());
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j)
				edges.push_back({i, j, (points[i] - points[j]).length()});
		std::sort(edges.begin(), edges.end());
	}

	double operator()()
	{
		double ans = 0.0;
		UFS ufs(n);
		for (auto &edge : edges)
		{
			if (!ufs.connected(edge.from, edge.to))
			{
				ufs.connect(edge.from, edge.to);
				ans += edge.w;
				if (--n == 1)
					break;
			}
		}
		return ans;
	}

};

#endif //MST_KRUSKALMST_H
