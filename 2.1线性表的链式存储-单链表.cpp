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

// 简单线性表类模板
template<class ElemType>
class SimpleLinkList
{
protected:
	Node<ElemType>* head;

	// 辅助函数模板
	Node<ElemType>* GetElemPtr(int position) const; // 返回指向第position个结点的指针

public:
	SimpleLinkList(); // 无参数的构造函数模板
	virtual ~SimpleLinkList(); // 析构函数模板
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (* visit)(const ElemType&)) const;
	bool GetElem(int position, ElemType& e) const;
	bool SetElem(int position, const ElemType& e);
	bool Delete(int position, ElemType& e);
	bool Insert(int position, const ElemType& e);
	SimpleLinkList(const SimpleLinkList<ElemType>& copy); // 复制构造函数模板
	SimpleLinkList<ElemType>& operator=(const SimpleLinkList<ElemType>& copy); // 重载赋值运算符

};

template<class ElemType>
Node<ElemType>* SimpleLinkList<ElemType>::GetElemPtr(int position) const
{
	Node<ElemType>* tmpPtr = head;
	int pos = 0;

	while (tmpPtr != NULL && pos < position) {
		tmpPtr = tmpPtr->next;
		pos++;
	}

	if (tmpPtr != NULL && pos == position) return tmpPtr;
	else return NULL;
}

template<class ElemType>
SimpleLinkList<ElemType>::SimpleLinkList()
{
	head = new Node<ElemType>;
}

template<class ElemType>
SimpleLinkList<ElemType>::~SimpleLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int SimpleLinkList<ElemType>::Length() const
{
	int count = 0;
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) count++;

	return count;
}

template<class ElemType>
bool SimpleLinkList<ElemType>::Empty() const
{
	return head->next == NULL;
}

template<class ElemType>
void SimpleLinkList<ElemType>::Clear()
{
	ElemType tmpElem; // 临时元素值
	while (!Empty()) {
		Delete(1, tmpElem);
	}
}

template<class ElemType>
void SimpleLinkList<ElemType>::Traverse( void (* visit)(const ElemType &)) const
{
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		(*visit) (tmpPtr->data);
	}
}

template<class ElemType>
bool SimpleLinkList<ElemType>::GetElem(int position, ElemType& e) const
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	e = tmpPtr->data;

	return true;
}

template<class ElemType>
bool SimpleLinkList<ElemType>::SetElem(int position, const ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	tmpPtr->data = e;

	return true;
}

template<class ElemType>
bool SimpleLinkList<ElemType>::Delete(int position, ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* nextPtr = tmpPtr->next;
	tmpPtr->next = nextPtr->next;
	e = nextPtr->data;
	delete nextPtr;

	return true;
}

template<class ElemType>
bool SimpleLinkList<ElemType>::Insert(int position, const ElemType& e)
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
SimpleLinkList<ElemType>::SimpleLinkList(const SimpleLinkList<ElemType>& copy)
{
	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != NULL; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data);
		tmpPtr = tmpPtr->next;
	}

}

template<class ElemType>
SimpleLinkList<ElemType>& SimpleLinkList<ElemType>::operator=(const SimpleLinkList<ElemType>& copy)
{
	if (this == &copy) return *this;

	// 释放当前对象的所有结点
	Node<ElemType>* tmpPtr = head->next;
	while (tmpPtr != NULL) {
		Node<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		delete prevPtr;
	}

	// 复制要复制的链表
	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != NULL; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data);
		tmpPtr = tmpPtr->next;
	}

	return *this;


}

// 单链表的数据排序
template<class ElemType>
void MergeLinkList(const SimpleLinkList<ElemType> la, const SimpleLinkList<ElemType> lb, SimpleLinkList<ElemType>& lc) {
	
	ElemType aElem, bElem;
	int aLength = la.Length(), bLength = lb.Length();
	int aPosition = 1, bPosition = 1;

	lc.Clear();
	while (aPosition <= aLength && bPosition <= bLength) {
		la.GetElem(aPosition, aElem);
		lb.GetElem(bPosition, bElem);
		if (aElem < bElem) {
			lc.Insert(lc.Length() + 1, aElem);
			aPosition++;
		}
		else {
			lc.Insert(lc.Length() + 1, bElem);
			bPosition++;
		}
	}

	while (aPosition <= aLength) {
		la.GetElem(aPosition, aElem);
		lc.Insert(lc.Length() + 1, aElem);
		aPosition++;
	}

	while (bPosition <= bLength) {
		lb.GetElem(bPosition, bElem);
		lc.Insert(lc.Length() + 1, bElem);
		bPosition++;
	}

}

// 单链表元素逆置
template<class ElemType>
void Reverse(SimpleLinkList<ElemType>& la) {

	ElemType aElem, bElem;
	for (int position = 1; position <= la.Length() / 2; position++) {
		la.GetElem(position, aElem);
		la.GetElem(la.Length() - position + 1, bElem);

		la.SetElem(position, bElem);
		la.SetElem(la.Length() - position + 1, aElem);
	}

}
