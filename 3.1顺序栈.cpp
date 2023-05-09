#include <iostream>
using namespace std;

// 顺序栈
template<class ElemType>
class SqStack
{
protected:
	int count;
	int maxSize;
	ElemType* elems;

public:
	SqStack(int size = DEFAULT_SIZE);
	virtual~SqStack();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const ElemType&)) const;
	bool Push(const ElemType& e);
	bool Top(ElemType& e) const;
	bool Pop(ElemType& e);
	SqStack(const SqStack<ElemType>& copy); // 复制构造函数模板
	SqStack<ElemType>& operator=(const SqStack<ElemType>& copy); // 重载赋值运算符
};

template<class ElemType>
SqStack<ElemType>::SqStack(int size)
{
	maxSize = size;
	elems = new ElemType(maxSize);
	count = 0; // 初始化时数组0的位置是不放任何元素的
}

template<class ElemType>
SqStack<ElemType>::~SqStack()
{
	delete[] elems;
}

template<class ElemType>
int SqStack<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool SqStack<ElemType>::Empty() const
{
	return count == 0;
}

template<class ElemType>
void SqStack<ElemType>::Clear()
{
	count = 0;
}

template<class ElemType>
void SqStack<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (int pos = 1; pos <= Length(); pos++) {
		(*visit)(elems[pos - 1]);
	}
}

template<class ElemType>
bool SqStack<ElemType>::Push(const ElemType& e)
{
	if (count == maxSize) return false;

	elems[count++] = e;
	return true;
}

template<class ElemType>
bool SqStack<ElemType>::Top(ElemType& e) const
{
	if (Empty()) return false;
	
	e = elems[count - 1];

	return true;
}

template<class ElemType>
bool SqStack<ElemType>::Pop(ElemType& e)
{
	if (Empty()) return false;

	e = elems[count - 1];
	count--;

	return true;
}

template<class ElemType>
SqStack<ElemType>::SqStack(const SqStack<ElemType>& copy)
{
	maxSize = copy.maxSize;
	elems = new ElemType[maxSize];
	count = copy.count;

	for (int pos = 1; pos <= Length(); pos++) {
		elems[pos - 1] = copy.elems[pos - 1];
	}
}

template<class ElemType>
SqStack<ElemType>& SqStack<ElemType>::operator=(const SqStack<ElemType>& copy)
{
	if (this == &copy) return *this;

	maxSize = copy.maxSize;
	delete[] elems;
	elems = new ElemType[maxSize];
	count = copy.count;

	for (int pos = 1; pos <= Length(); pos++)
	{
		elems[pos - 1] = copy.elems[pos - 1];
	}

	return *this;
}
