#include <iostream>
using namespace std;

template<class ElemType>
class SymmetricMatrix
{
private:
	ElemType* elems; // �洢�Գƾ���Ԫ��
	int size; // �Գƾ����С

public:
	SymmetricMatrix(int sz);
	~SymmetricMatrix();
	ElemType& operator() (int i, int j); // ���غ��������

	// ���ø��ƹ��캯�������ظ�ֵ�����
	SymmetricMatrix(const SymmetricMatrix<ElemType>& copy) = delete;
	SymmetricMatrix<ElemType>& operator=(const SymmetricMatrix<ElemType>& copy) = delete;
};

template<class ElemType>
SymmetricMatrix<ElemType>::SymmetricMatrix(int sz)
{
	if (sz < 1) throw "�����С��Ч";

	size = sz;
	elems = new ElemType[size * (size + 1) / 2]; // ֻ�洢������Ԫ��
}

template<class ElemType>
SymmetricMatrix<ElemType>::~SymmetricMatrix()
{
	delete[] elems;
}

template<class ElemType>
ElemType& SymmetricMatrix<ElemType>::operator()(int i, int j)
{
	if (i < 1 || i > size || j < 1 || j > size) throw "�±����";
	if (i < j) swap(i, j); // ʹ�� i >= j��ֻ����������Ԫ��

	return elems[(i - 1) * i / 2 + j - 1];
}
