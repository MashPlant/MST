#include <iostream>
#include <random>
#include <iomanip>
#include <chrono>

#include "../src/Point2d.h"
#include "../src/YaoMST.h"
#include "../src/PrimMST.h"
#include "../src/KruskalMST.h"
#include "../src/PairingHeap.h"
#include "../src/DelaunayMST.h"
#include "../src/FibHeap.h"

const int N = 50000;
std::vector<Point2d> input;

template<typename MSTSolver>
void solve(const char *info)
{
	std::cout << info << std::endl;
	auto &now = std::chrono::system_clock::now;
	auto beg = now();
	MSTSolver solver(input);
	double ans = solver();
	std::cout << "use time : " << (now() - beg).count() << std::endl
	          << "result : " << ans << std::endl << std::endl;
}

int main()
{
	std::mt19937 mt;
	std::uniform_real_distribution<> dis(0, 10000.0);
	for (int i = 0; i < N; ++i)
		input.push_back({dis(mt), dis(mt)});
	solve<DelaunayMST>("delaunay triangulation mst method");
	solve<YaoMST>("yao mst method");
	solve<PrimMST<>>("naive prim method");
	solve<PrimMST<FibHeap>>("prim method with fibonacci heap\n"
	                        "works well on dense graph (O(E+VlgV))\n"
	                        "but still can't match delaunay because the geometry property is not used");
	solve<PrimMST<PairingHeap>>("prim method with pairing heap, as above");
	try
	{
		solve<PrimMST<BinaryHeap>>("prim method with binary heap\n"
		                           "perform worse on dense graph\n"
		                           "might cause MLE");
	}
	catch (const std::bad_alloc &)
	{ std::cout << "prim with binary heap failed to calculate mst because of n^2 memory use" << std::endl; }
	try
	{
		solve<KruskalMST>("naive kruskal method\n"
		                  "might cause MLE");
	}
	catch (const std::bad_alloc &)
	{ std::cout << "kruskal failed to calculate mst because of n^2 memory use" << std::endl; }
}

