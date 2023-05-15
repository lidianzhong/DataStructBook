#include <iostream>
using namespace std;

template<class ElemType>
class Matrix
{
protected:
	ElemType* elems; // 存储矩阵元素
	int rows, cols; // 矩阵行数和列数

public:
	Matrix(int rs, int cs);
	~Matrix();
	int GetRows() const;
	int GetCols() const;
	ElemType& operator() (int i, int j); // 重载函数运算符
	Matrix(const Matrix<ElemType>& copy); // 复制构造函数模板
	Matrix<ElemType>& operator=(const Matrix<ElemType>& copy); // 重载赋值运算符

};

template<class ElemType>
Matrix<ElemType>::Matrix(int rs, int cs)
{
	if (rs < 1 || cs < 1) throw"行数或列数无效"; // 抛出异常

	rows = rs;
	cols = cs;
	elems = new ElemType[rows * cols]; // 分配存储空间

}

template<class ElemType>
Matrix<ElemType>::~Matrix()
{
	delete[] elems;
}

template<class ElemType>
int Matrix<ElemType>::GetRows() const
{
	return rows;
}

template<class ElemType>
int Matrix<ElemType>::GetCols() const
{
	return cols;
}

template<class ElemType>
ElemType& Matrix<ElemType>::operator()(int i, int j)
{
	if (i < 1 || i > rows || j < 1 || j > cols) throw"下标出界";

	return elems[(i - 1) * rows + (j - 1)];
}

template<class ElemType>
Matrix<ElemType>::Matrix(const Matrix<ElemType>& copy)
{
	rows = copy.rows;
	cols = copy.cols;
	elems = new ElemType[rows * cols];
	for (int i = 0; i < rows * cols; i++)
	{
		elems[i] = copy.elems[i];
	}
}

template<class ElemType>
Matrix<ElemType>& Matrix<ElemType>::operator=(const Matrix<ElemType>& copy)
{
	if (this == &copy) return *this;
	delete[] elems;
	rows = copy.rows;
	cols = copy.cols;
	elems = new ElemType[rows * cols];
	for (int i = 0; i < rows * cols; i++)
	{
		elems[i] = copy.elems[i];
	}
	return *this;
}
