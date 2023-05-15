#include <iostream>
using namespace std;

template<class ElemType>
class SymmetricMatrix
{
private:
	ElemType* elems; // 存储对称矩阵元素
	int size; // 对称矩阵大小

public:
	SymmetricMatrix(int sz);
	~SymmetricMatrix();
	ElemType& operator() (int i, int j); // 重载函数运算符

	// 禁用复制构造函数和重载赋值运算符
	SymmetricMatrix(const SymmetricMatrix<ElemType>& copy) = delete;
	SymmetricMatrix<ElemType>& operator=(const SymmetricMatrix<ElemType>& copy) = delete;
};

template<class ElemType>
SymmetricMatrix<ElemType>::SymmetricMatrix(int sz)
{
	if (sz < 1) throw "矩阵大小无效";

	size = sz;
	elems = new ElemType[size * (size + 1) / 2]; // 只存储上三角元素
}

template<class ElemType>
SymmetricMatrix<ElemType>::~SymmetricMatrix()
{
	delete[] elems;
}

template<class ElemType>
ElemType& SymmetricMatrix<ElemType>::operator()(int i, int j)
{
	if (i < 1 || i > size || j < 1 || j > size) throw "下标出界";
	if (i < j) swap(i, j); // 使得 i >= j，只访问上三角元素

	return elems[(i - 1) * i / 2 + j - 1];
}
