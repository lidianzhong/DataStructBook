#include<iostream>
using namespace std;

// 循环队列类模板
template<class ElemType>
class SqQueue
{
protected:
	int front, rear;
	int count;
	int maxSize;
	ElemType* elems;

public:
	SqQueue(int size = DEFAULT_SiZE);
	virtual ~SqQueue();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*visit)(const ElemType&)) const;
	bool OutQueue(ElemType& e);
	bool GetHead(ElemType& e) const;
	bool InQueue(ElemType& e);
	SqQueue(const SqQueue<ElemType>& copy);                      // 复制构造函数模板
	SqQueue<ElemType>& operator=(const SqQueue<ElemType>& copy); // 重载赋值运算符

};

template<class ElemType>
SqQueue<ElemType>::SqQueue(int size)
{
	maxSize = size;
	elems = new ElemType[maxSize];
	rear = front = 0;
	count = 0;
}

template<class ElemType>
SqQueue<ElemType>::~SqQueue()
{
	delete[] elems;
}

template<class ElemType>
int SqQueue<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool SqQueue<ElemType>::Empty() const
{
	return count == 0;
}

template<class ElemType>
void SqQueue<ElemType>::Clear()
{
	rear = front = 0;
	count = 0;
}

template<class ElemType>
void SqQueue<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize) {
		(*visit) (elems[pos]);
	}
}

template<class ElemType>
bool SqQueue<ElemType>::OutQueue(ElemType& e)
{
	if (Empty()) return false;

	e = elems[front];
	front = (front + 1) % maxSize;
	count--;


	return true;
}

template<class ElemType>
bool SqQueue<ElemType>::GetHead(ElemType& e) const
{
	if (Empty()) return false;

	e = elems[front];

	return true;
}

template<class ElemType>
bool SqQueue<ElemType>::InQueue(ElemType& e)
{
	if (count == maxSize) return false;

	elems[rear] = e;
	rear = (rear + 1) % maxSize;
	count++;

	return true;

}

template<class ElemType>
SqQueue<ElemType>::SqQueue(const SqQueue<ElemType>& copy)
{
	maxSize = copy.maxSize;
	elems = new ElemType[maxSize];
	front = copy.front;
	rear = copy.rear;
	count = copy.count;

	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize) {
		elems[pos] = copy.elems[pos];
	}

}

template<class ElemType>
SqQueue<ElemType>& SqQueue<ElemType>::operator=(const SqQueue<ElemType>& copy)
{
	if (this == &copy) return *this;

	maxSize = copy.maxSize;
	delete[] elems;
	elems = new ElemType[maxSize];
	front = copy.front;
	rear = copy.rear;
	count = copy.count;

	for (int pos = front; pos != rear; pos = (pos + 1) % maxSize) {
		elems[pos] = copy.elems[pos];
	}

	return *this;
}
