//
// Created by MashPlant on 18-5-6.
//

#ifndef MST_YAOMST_H
#define MST_YAOMST_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "UFS.h"
#include "KDTree.h"
#include "Point2d.h"
#include "Mat22.h"
#include <iostream>

class YaoMST
{
	struct PointPair
	{
		Point2d oPoint;
		Point2d nPoint;
		int index;

		double oldAt(int pos) const
		{ return oPoint[pos]; }


		double newAt(int pos) const
		{ return nPoint[pos]; }
	};

	using Block = KDTree<PointPair, 2>;

	struct Cell
	{
		Block oBlock;
		Block nBlock;
		PointPair *originFirst, *originLast;
	};


	struct Edge
	{
		int from, to;
		double w;

		bool operator<(const Edge &rhs) const
		{ return w < rhs.w; }
	};

	int n;
	std::vector<Edge> edges;

	void addEdge(int from, int to, double w)
	{
		edges.push_back({from, to, w});
	}

public:
	constexpr static char Info[] =
			"Yao's MST method for 2d plane\n"
			"complexity : n^(5/3)*lg(n)";

	explicit YaoMST(const std::vector<Point2d> &points, double sFactor = 1.0 / 3.0)
	{
		n = static_cast<int>(points.size());
		const int s = static_cast<int>(pow(n, sFactor));
		const int step1 = n / s;
		const int step2 = step1 / s;
		const double sq3 = sqrt(3);
		const Mat22 trans[3] = {{sq3,  -1, 0,   2},
		                        {-sq3, 1,  sq3, 1},
		                        {-sq3, -1, 0,   2}};
		// three copy for points
		// origin for brute look up (faster)
		// oldTree for KDTree of old coordinate
		// newTree for KDTree of new coordinate
		// KDTree is designed to not manage memory, but use provided memory
		// to reduce memory fragmentation
		std::vector<PointPair> origin(points.size()), oldTree(points.size()), newTree(points.size());

		for (auto &tran : trans)
		{
			for (int i = 0; i < n; ++i)
			{
				origin[i].oPoint = points[i];
				origin[i].nPoint = tran * points[i];
				origin[i].index = i;
			}
			std::sort(origin.begin(), origin.end(), [](const PointPair &lhs, const PointPair &rhs)
			{ return lhs.nPoint.x < rhs.nPoint.x; });
			std::vector<Cell> cells;
			for (int i = 0; i < n; i += step1)
			{
				const int up = std::min(i + step1, n);
				std::sort(origin.begin() + i, origin.begin() + up, [](const PointPair &lhs, const PointPair &rhs)
				{ return lhs.nPoint.y > rhs.nPoint.y; });
			}
			oldTree = newTree = origin; // vector's operator= has been optimized, this will not allocate memory
			for (int i = 0; i < n; i += step1)
			{
				const int up = std::min(i + step1, n);
				for (int j = i; j < up; j += step2)
					cells.push_back(
							{Block(oldTree.data() + j, oldTree.data() + std::min(j + step2, up), &PointPair::oldAt),
							 Block(newTree.data() + j, newTree.data() + std::min(j + step2, up), &PointPair::newAt),
							 origin.data() + j, origin.data() + std::min(j + step2, up)});
			}
			for (auto &pointPair : origin)
			{
				double dis2 = std::numeric_limits<double>::max();
				int to = -1;
				auto checkMin = [&](int index, double newDis2)
				{
					if (newDis2 < dis2)
						to = index, dis2 = newDis2;
				};
				for (auto &cell : cells)
				{
					if (cell.nBlock.allGreater(pointPair))
					{
						const auto &result = cell.oBlock.nearest(pointPair);
						checkMin(result.point.index, result.dis2);
					}
					else if (!cell.nBlock.anyGreater(pointPair))
						continue;
					else
					{
						for (auto it = cell.originFirst; it != cell.originLast; ++it)
						{
							if (it->nPoint.y < pointPair.nPoint.y)
								break;
							if (it->index != pointPair.index && it->nPoint.x >= pointPair.nPoint.x)
								checkMin(it->index, (it->oPoint - pointPair.oPoint).length2());
						}
					}
					if (to != -1)
						addEdge(pointPair.index, to, sqrt(dis2));
				}
			}
		}
	}

	double operator()()
	{
		std::sort(edges.begin(), edges.end());
		int need = n;
		double ans = 0.0;
		UFS ufs(n);
		for (auto &edge : edges)
		{
			if (!ufs.connected(edge.from, edge.to))
			{
				ufs.connect(edge.from, edge.to);
				ans += edge.w;
				if (--need == 1)
					break;
			}
		}
		return ans;
	}


};

#endif //MST_YAOMST_H
