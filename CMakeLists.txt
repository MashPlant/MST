cmake_minimum_required(VERSION 3.10)
project(MST)

set(CMAKE_CXX_STANDARD 17)

add_executable(MST main.cpp FibHeap.h KDTree.h Point2d.h Mat22.h YaoMST.h UFS.h PrimMST.h KruskalMST.h HeapTraits.h)