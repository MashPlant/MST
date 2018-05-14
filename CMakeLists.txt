cmake_minimum_required(VERSION 3.10)
project(MST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(MST testcase/main.cpp src/FibHeap.h src/KDTree.h src/Point2d.h src/Mat22.h src/YaoMST.h src/UFS.h src/PrimMST.h src/KruskalMST.h src/HeapTraits.h src/MemPool.h src/PairingHeap.h src/DelaunayMST.h)