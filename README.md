OOP大作业

实现论文 

*ON CONSTRUCTING MINIMUM SPANNING TREES IN k-DIMENSIONAL SPACES AND RELATED PROBLEMS*      
by ANDREW CHI-CHIH YAO

从而能在*o*($n^2$)的时间内计算出一个二维平面上的图的最小生成树

当然了,利用delaunay triangulation可以在$\Theta$($nlgn$)的时间内计算出最小生成树,这比姚期智提供的算法在理论和实践上都优秀的多

如何编译运行:

首先确保你的编译器支持C++ 17

```
mkdir build
cmake ..
make
./MST
```