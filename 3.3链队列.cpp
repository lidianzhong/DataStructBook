#include<iostream>
using namespace std;

// 结点类模板
template<class ElemType>
struct Node
{
	ElemType data;
	Node<ElemType>* next;

	Node(); // 无参构造函数模板
	Node(ElemType item, Node<ElemType>* link = NULL); // 已知数据元素和后继指针建立结构

};

template<class ElemType>
Node<ElemType>::Node()
{
	next = NULL;
}

template<class ElemType>
Node<ElemType>::Node(ElemType item, Node<ElemType>* link)
{
	data = item;
	next = link;
}

template<class ElemType>
class LinkQueue
{
protected:
	Node<ElemType>* front, * rear;	
	int count;

public:
	LinkQueue();
	virtual~LinkQueue();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*visit) (const ElemType&)) const;
	bool QutQueue(ElemType &e);
	bool GetHead(ElemType& e) const;
	bool InQueue(const ElemType& e);
	LinkQueue(const LinkQueue<ElemType>& copy); // 复制构造函数模板
	LinkQueue<ElemType>& operator=(const LinkQueue<ElemType>& copy); // 重载赋值运算符
};

template<class ElemType>
LinkQueue<ElemType>::LinkQueue()
{
	// front指向的位置不存在元素，rear指向尾元素
	// 队头出队，队尾入队
	rear = front = new Node<ElemType>;
	count = 0;
}

template<class ElemType>
LinkQueue<ElemType>::~LinkQueue()
{
	Clear();
}

template<class ElemType>
int LinkQueue<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool LinkQueue<ElemType>::Empty() const
{
	return count == 0;
}

template<class ElemType>
void LinkQueue<ElemType>::Clear()
{
	ElemType tmpElem;
	while (!Empty()) {
		QutQueue(tmpElem);
	}
}

template<class ElemType>
void LinkQueue<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (Node<ElemType>* tmpPtr = front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
bool LinkQueue<ElemType>::QutQueue(ElemType& e)
{
	if (Empty()) return false;

	Node<ElemType>* tmpPtr = front->next;
	e = tmpPtr->data;
	front->next = tmpPtr->next;
	if (rear == tmpPtr) rear = front; // 表示出队前队列中只有一个元素，出队后为空队列
	delete tmpPtr;
	count--;

	return true;
}

template<class ElemType>
bool LinkQueue<ElemType>::GetHead(ElemType& e) const
{
	if (Empty()) return false;

	Node<ElemType>* tmpPtr = front->next;
	e = tmpPtr->data;

	return true;
}

template<class ElemType>
bool LinkQueue<ElemType>::InQueue(const ElemType& e)
{
	Node<ElemType>* tmpPtr = new Node<ElemType>(e);
	rear->next = tmpPtr;
	rear = tmpPtr;
	count++;
	
	return true;
}

template<class ElemType>
LinkQueue<ElemType>::LinkQueue(const LinkQueue<ElemType>& copy)
{
	rear = front = new Node<ElemType>;
	count = 0;
	for (Node<ElemType>* tmpPtr = copy.front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		InQueue(tmpPtr->data);
	}
}

template<class ElemType>
LinkQueue<ElemType>& LinkQueue<ElemType>::operator=(const LinkQueue<ElemType>& copy)
{
	if (this == &copy) return *this;

	Clear();
	for (Node<ElemType>* tmpPtr = copy.front->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		InQueue(tmpPtr->data);
	}

	return *this;

}
