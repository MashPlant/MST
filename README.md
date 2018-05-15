OOP大作业

实现论文 

*ON CONSTRUCTING MINIMUM SPANNING TREES IN k-DIMENSIONAL SPACES AND RELATED PROBLEMS*      
by ANDREW CHI-CHIH YAO

从而能在![equation](http://www.sciweavers.org/upload/Tex2Img_1526423123/eqn.png)的时间内计算出一个二维平面上的图的最小生成树.

当然了,利用delaunay三角剖分可以在![equation](http://www.sciweavers.org/upload/Tex2Img_1526423205/eqn.png)的时间内计算出最小生成树,这比姚期智的算法在理论和实践上都优秀的多.

# 实现了哪些算法
    *姚期智的算法
    *delaunay三角剖分
    *朴素的prim算法
    *二叉堆优化的prim算法
    *斐波那契堆和配对堆优化的prim算法
    *kruskal算法

姚期智的算法的算法理论复杂度为![equation](http://www.sciweavers.org/upload/Tex2Img_1526423923/eqn.png),这是通过取参数![equation](http://www.sciweavers.org/upload/Tex2Img_1526423974/eqn.png)达到的.但是这样的取值下常数过于巨大(也可能是我实现的太烂),所以我改成了![equation](http://www.sciweavers.org/upload/Tex2Img_1526424059/eqn.png).其实这样复杂度已经和平方没什么区别了,只比朴素的prim快两倍左右.

二叉堆优化的prim算法和kruskal算法在稠密图,尤其是完全图中表现很差,复杂度为![equation](http://www.sciweavers.org/upload/Tex2Img_1526423607/eqn.png),而且可能导致MLE.

斐波那契堆和配对堆优化的prim算法在一般的图上有很好表现,均为![equation](http://www.sciweavers.org/upload/Tex2Img_1526423757/eqn.png),但是因为没有利用任何几何性质,所以比delaunay三角剖分还是慢的多.

# 如何编译运行:

首先确保你的编译器支持C++ 17.

```
mkdir build
cd build
cmake ..
make
./MST
```