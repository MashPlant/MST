//
// Created by MashPlant on 18-5-5.
//

#ifndef MST_KDTREE_H
#define MST_KDTREE_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <type_traits>

template<typename Point, int K,
		typename Coordinate = double (Point::*)(int) const>
class KDTree
{
	constexpr static double eps = 1e-7;
	Point *first, *last;
	//std::vector<Point> pts;
	std::vector<int> split; // save the split result for nearest
	const Coordinate coordinate;

	double min[K], max[K];

	void build(Point *l, Point *r) // [0,n) indexed
	{
		if (l >= r) return;
		auto mid = l + (r - l) / 2;
		auto midIndex = mid - first;
		// get the variance of each dimension
		split[midIndex] = 0;
		double var = 0.0;
		for (int d = 0; d < K; ++d) // find the dimension with biggest variance
		{
			double ave = 0.0, tmpVar = 0.0;
			for (auto i = l; i < r; ++i)
				ave += (i->*coordinate)(d);
			ave /= r - l;
			for (auto i = l; i < r; ++i)
				tmpVar += pow((i->*coordinate)(d) - ave, 2);
			if (tmpVar > var)
				var = tmpVar, split[midIndex] = d;
		}
		// split at the dimension just found
		std::nth_element(l, mid, r, [=](const Point &lhs, const Point &rhs)
		{ return (lhs.*coordinate)(split[midIndex]) < (rhs.*coordinate)(split[midIndex]); });
		build(l, mid);
		build(mid + 1, r);
	}


	double ans;
	Point *which; // ans & which are only for function nearest, to reduce the number of parameter

	void nearest(const Point &pt, Point *l, Point *r)
	{
		if (l >= r) return;
		auto mid = l + (r - l) / 2;
		auto midIndex = mid - first;
		// the euclidean distance between pt and current root(pts[mid])
		double dis2 = 0.0;
		for (int d = 0; d < K; d++)
			dis2 += pow((mid->*coordinate)(d) - (pt.*coordinate)(d), 2);
		if (fabs(dis2) > eps && dis2 < ans)
			ans = dis2, which = mid;
		// the euclidean distance between pt and split plane
		double currOfPt = (pt.*coordinate)(split[midIndex]),
				currOfMid = (mid->*coordinate)(split[midIndex]);
		double r2 = pow(currOfMid - currOfPt, 2);
		if (currOfPt < currOfMid)
		{
			nearest(pt, l, mid);
			// draw a sphere with pt as center, current ans as radius
			// if it intersect with the split plane, the nearest point maybe in another subtree
			if (r2 <= ans)
				nearest(pt, mid + 1, r);
		}
		else
		{
			nearest(pt, mid + 1, r);
			if (r2 <= ans)
				nearest(pt, l, mid);
		}
	}

	bool found; // only for function any

	void anyGreater(const Point &pt, Point *l, Point *r)
	{
		if (l >= r) return;
		auto mid = l + (r - l) / 2;
		auto midIndex = mid - first;
		bool check = true;
		for (int d = 0; d < K && check; ++d)
			check &= (mid->*coordinate)(d) >= (pt.*coordinate)(d);
		if (check)
			return void(found = true);
		anyGreater(pt, mid + 1, r);
		if (!found && (pt.*coordinate)(split[midIndex]) <= (mid->*coordinate)(split[midIndex]))
			anyGreater(pt, l, mid);
	}

	void anyLess(const Point &pt, Point *l, Point *r)
	{
		if (l >= r) return;
		auto mid = l + (r - l) / 2;
		auto midIndex = mid - first;
		bool check = true;
		for (int d = 0; d < K && check; ++d)
			check &= (mid->*coordinate)(d) <= (pt.*coordinate)(d);
		if (check)
			return void(found = true);
		anyLess(pt, l, mid);
		if (!found && (pt.*coordinate)(split[midIndex]) >= (mid->*coordinate)(split[midIndex]))
			anyLess(pt, mid + 1, r);
	}

public:
	KDTree(Point *first, Point *last, Coordinate coordinate = &Point::operator[])
			: first(first), last(last), coordinate(coordinate), split(last - first)
	{
		build(first, last);
		for (int d = 0; d < K; ++d)
		{
			auto[minPoint, maxPoint] = std::minmax_element(first, last, [=](const Point &lhs, const Point &rhs)
			{ return (lhs.*coordinate)(d) < (rhs.*coordinate)(d); });
			min[d] = (const_cast<const Point *>(minPoint)->*coordinate)(d);
			max[d] = (const_cast<const Point *>(maxPoint)->*coordinate)(d);
		}
	}

	struct Result
	{
		const Point &point;
		double dis2;
	};

	Result nearest(const Point &point)
	{
		ans = std::numeric_limits<double>::max(), which = nullptr;
		nearest(point, first, last);
		return {*which, ans};
	}

	bool allGreater(const Point &point)
	{
		bool allEq = true;
		for (int i = 0; i < K; ++i)
		{
			double diff = min[i] - (point.*coordinate)(i);
			if (diff < 0)
				return false;
			else if (diff > 0)
				allEq = false;
		}
		return !allEq;
	}

	bool allLess(const Point &point)
	{
		bool allEq = true;
		for (int i = 0; i < K; ++i)
		{
			double diff = (point.*coordinate)(i) - max[i];
			if (diff < 0)
				return false;
			else if (diff > 0)
				allEq = false;
		}
		return !allEq;
	}

	bool anyGreater(const Point &point)
	{
		found = false;
		anyGreater(point, first, last);
		return found;
	}

	bool anyLess(const Point &point)
	{
		found = false;
		anyLess(point, first, last);
		return found;
	}

	template<typename Func>
	void forEach(Func f) const
	{
		for (auto it = first; it != last; ++it)
			f(*it);
	}
};


#endif //MST_KDTREE_H
