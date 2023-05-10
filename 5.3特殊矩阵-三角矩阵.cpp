#include <iostream>
using namespace std;

template<class ElemType>
class LowerTriangularMatrix
{
protected:
	ElemType* elems; // 存储下三角矩阵元素
	int n; // 下三角矩阵阶数

public:
	LowerTriangularMatrix(int sz);
	~LowerTriangularMatrix();
	int GetSize() const;
	ElemType& operator() (int i, int j);
};

template<class ElemType>
LowerTriangularMatrix<ElemType>::LowerTriangularMatrix(int sz)
{
	if (sz < 1) throw "矩阵大小无效";
	n = sz;
	elems = new ElemType[n * (n + 1) / 2]; // 只存储下三角元素
}

template<class ElemType>
LowerTriangularMatrix<ElemType>::~LowerTriangularMatrix()
{
	delete[] elems;
}

template<class ElemType>
int LowerTriangularMatrix<ElemType>::GetSize() const
{
	return n;
}

template<class ElemType>
ElemType& LowerTriangularMatrix<ElemType>::operator()(int i, int j)
{
	if(i < 1 || i > n || j < 1 || j > n) throw "下标出界";
	if (i > j) return elems[i * (i - 1) / 2 + j];
	else return elems[0];
}
