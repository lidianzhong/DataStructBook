#include <iostream>
using namespace std;

template<class ElemType>
struct DblNode
{
	ElemType data;
	DblNode<ElemType>* back;
	DblNode<ElemType>* next;

	DblNode();
	DblNode(ElemType, DblNode <ElemType>* linkBack = NULL, DblNode<ElemType>* linkNext = NULL);


};

template<class ElemType>
DblNode<ElemType>::DblNode()
{
	next = NULL;
}

template<class ElemType>
DblNode<ElemType>::DblNode(ElemType item, DblNode<ElemType>* linkBack, DblNode<ElemType>* linkNext)
{
	data = item;
	back = linkBack;
	next = linkNext;
}

// 简单双向循环链表类模板
template<class ElemType>
class SimpleDblLinkList
{
protected:
	DblNode<ElemType>* head;

	DblNode<ElemType>* GetElemPtr(int position) const; // 返回指向第position个结点的指针

public:
	SimpleDblLinkList();
	virtual ~SimpleDblLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*visit) (const ElemType&)) const;
	bool GetElem(int position, ElemType& e) const;
	bool SetElem(int position, const ElemType& e);
	bool Delete(int position, ElemType& e);
	bool Insert(int position, const ElemType& e);
	SimpleDblLinkList(const SimpleDblLinkList<ElemType>& copy); // 复制构造函数模板
	SimpleDblLinkList<ElemType>& operator=(const SimpleDblLinkList<ElemType>& copy); // 重载赋值运算符


};

template<class ElemType>
DblNode<ElemType>* SimpleDblLinkList<ElemType>::GetElemPtr(int position) const
{
	if (position == 0) return head;

	DblNode<ElemType>* tmpPtr = head->next;

	int pos = 1;

	while (tmpPtr != head && pos < position) {
		tmpPtr = tmpPtr->next;
		pos++;
	}

	if (tmpPtr != head && pos == position) return tmpPtr;
	else return NULL;

}

template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList()
{
	head = new DblNode<ElemType>;
	head->next = head;
	head->back = head;
	
}

template<class ElemType>
SimpleDblLinkList<ElemType>::~SimpleDblLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int SimpleDblLinkList<ElemType>::Length() const
{
	int count = 0;
	for (DblNode<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) count++;
	return count;
}

template<class ElemType>
bool SimpleDblLinkList<ElemType>::Empty() const
{
	return head->next == head;
}

template<class ElemType>
void SimpleDblLinkList<ElemType>::Clear()
{
	ElemType tmp;
	Delete(1, tmp);
}

template<class ElemType>
void SimpleDblLinkList<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (DblNode<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) {
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
bool SimpleDblLinkList<ElemType>::GetElem(int position, ElemType& e) const
{
	if (position < 1 || position > Length()) return false;

	DblNode<ElemType>* tmpPtr;

	tmpPtr = GetElemPtr(position);
	e = tmpPtr->data;

	return true;
}

template<class ElemType>
bool SimpleDblLinkList<ElemType>::SetElem(int position, const ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	DblNode<ElemType>* tmpPtr;

	tmpPtr = GetElemPtr(position);
	tmpPtr->data = e;

	return true;
}

template<class ElemType>
bool SimpleDblLinkList<ElemType>::Delete(int position, ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	DblNode<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	tmpPtr->back->next = tmpPtr->next;
	tmpPtr->next->back = tmpPtr->back;
	e = tmpPtr->data;
	delete tmpPtr;

	return true;

}

template<class ElemType>
bool SimpleDblLinkList<ElemType>::Insert(int position, const ElemType& e)
{
	if (position < 1 || position > Length() + 1) return false;

	DblNode<ElemType>* tmpPtr, * nextPtr, * newPtr;
	tmpPtr = GetElemPtr(position - 1);
	nextPtr = tmpPtr->next;
	newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);
	tmpPtr->next = newPtr;
	nextPtr->back = newPtr;

	return true;

}

template<class ElemType>
SimpleDblLinkList<ElemType>::SimpleDblLinkList(const SimpleDblLinkList<ElemType>& copy)
{
	// 创建一个空的链表
	head = new DblNode<ElemType>;
	head->next = head;
	head->back = head;

	// 复制过程
	DblNode<ElemType>* curPtr = head;

	for (DblNode<ElemType>* tmpPtr = copy.head->next; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
		DblNode<ElemType>* newPtr = new DblNode<ElemType>(tmpPtr->data, curPtr, head);
		curPtr->next = newPtr;
		head->back = newPtr;
	}


}

template<class ElemType>
SimpleDblLinkList<ElemType>& SimpleDblLinkList<ElemType>::operator=(const SimpleDblLinkList<ElemType>& copy)
{
	if (this == &copy) return *this;

	// 释放当前所有已存在的结点
	DblNode<ElemType>* tmpPtr = head->next;
	while (tmpPtr != head) {
		DblNode<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		delete prevPtr;
	}

	// 复制要复制的链表
	DblNode<ElemType>* curPtr = head;

	for (DblNode<ElemType>* tmpPtr = copy.head->next; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
		DblNode<ElemType>* newPtr = new DblNode<ElemType>(tmpPtr->data, curPtr, head);
		curPtr->next = newPtr;
		head->back = newPtr;
	}

}
