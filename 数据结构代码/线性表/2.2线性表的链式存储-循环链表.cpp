#include <iostream>
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
class SimpleCircLinkList
{
protected:
	Node <ElemType>* head;

	Node<ElemType>* GetElemPtr(int position) const;

public:
	SimpleCircLinkList();
	virtual ~SimpleCircLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*visit) (const ElemType&)) const;
	bool GetElem(int position, ElemType& e) const;
	bool SetElem(int position, const ElemType& e);
	bool Delete(int position, ElemType& e);
	bool Insert(int position, const ElemType& e);
	SimpleCircLinkList(const SimpleCircLinkList<ElemType>& copy); // 复制构造函数模板
	SimpleCircLinkList<ElemType>& operator=(const SimpleCircLinkList<ElemType>& copy); // 重载赋值运算符
};

template<class ElemType>
Node<ElemType>* SimpleCircLinkList<ElemType>::GetElemPtr(int position) const
{
	if (position == 0) return head;

	Node<ElemType>* tmpPtr = head->next;

	int pos = 1;

	while (tmpPtr != head && pos < position) {
		tmpPtr = tmpPtr->next;
		pos++;
	}

	if (tmpPtr != head && pos == position) return tmpPtr;
	else return NULL;

}

template<class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList()
{
	head = new Node<ElemType>;
	head->next = head;
}

template<class ElemType>
SimpleCircLinkList<ElemType>::~SimpleCircLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int SimpleCircLinkList<ElemType>::Length() const
{
	int count = 0;
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) count++;
	return count;
}

template<class ElemType>
bool SimpleCircLinkList<ElemType>::Empty() const
{
	return head->next = head;
}

template<class ElemType>
void SimpleCircLinkList<ElemType>::Clear()
{
	ElemType tmp;
	if (!Empty()) {
		Delete(1, tmp);
	}
}

template<class ElemType>
void SimpleCircLinkList<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) {
		(*visit) (tmpPtr->data);
	}
}

template<class ElemType>
bool SimpleCircLinkList<ElemType>::GetElem(int position, ElemType& e) const
{
	if(position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	e = tmpPtr->data;
	return true;
}

template<class ElemType>
bool SimpleCircLinkList<ElemType>::SetElem(int position, const ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	tmpPtr->data = e;

	return true;

}

template<class ElemType>
bool SimpleCircLinkList<ElemType>::Delete(int position, ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* nextPtr;
	nextPtr = tmpPtr->next;
	tmpPtr->next = nextPtr->next;
	e = nextPtr->data;
	delete nextPtr;
	return true;
}

template<class ElemType>
bool SimpleCircLinkList<ElemType>::Insert(int position, const ElemType& e)
{
	if (position < 1 || position > Length() + 1) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* newPtr;
	newPtr = new Node<ElemType>(e, tmpPtr->next);
	tmpPtr->next = newPtr;

	return true;
}

template<class ElemType>
SimpleCircLinkList<ElemType>::SimpleCircLinkList(const SimpleCircLinkList<ElemType>& copy)
{
	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != head; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data,head);
		tmpPtr = tmpPtr->next;
	}
}

template<class ElemType>
SimpleCircLinkList<ElemType>& SimpleCircLinkList<ElemType>::operator=(const SimpleCircLinkList<ElemType>& copy)
{
	if (this == &copy) return *this;

	// 释放当前对象的所有结点
	Node<ElemType>* tmpPtr = head->next;
	while (tmpPtr != head) {
		Node<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		delete prevPtr;
	}

	// 复制要复制的链表
	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != head; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data, head);
		tmpPtr = tmpPtr->next;
	}

	return *this;
}
