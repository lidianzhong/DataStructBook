#include <iostream>
using namespace std;

template<class ElemType>
class DiagonalMatrix
{
protected:
	ElemType* elems; 
	int n;

public:
	DiagonalMatrix(int sz);
	~DiagonalMatrix();
	int GetSize() const;
	ElemType& operator() (int i, int j);
};

template<class ElemType>
DiagonalMatrix<ElemType>::DiagonalMatrix(int sz)
{
	if(n < 1) throw "矩阵大小无效";
	n = sz;
	elems = new ElemType[3 * n - 1];
}

template<class ElemType>
DiagonalMatrix<ElemType>::~DiagonalMatrix()
{
	delete[] elems;
}

template<class ElemType>
int DiagonalMatrix<ElemType>::GetSize() const
{
	return n;
}

template<class ElemType>
ElemType& DiagonalMatrix<ElemType>::operator()(int i, int j)
{
	if (i < 1 || i > n || j < 1 || j > n) throw "下标出界";
	if (i == j) return elems[3 * n + 1];
	else if (i == j + 1) return elems[3 * n];
	else if (i == j - 1) return elems[3 * n - 1];
	else return elems[0];
}
