#include<iostream>
using namespace std;

// �����ģ��
template<class ElemType>
struct Node
{
	ElemType data;
	Node<ElemType>* next;

	Node(); // �޲ι��캯��ģ��
	Node(ElemType item, Node<ElemType>* link = NULL); // ��֪����Ԫ�غͺ��ָ�뽨���ṹ

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

// ��ʽջ
template<class ElemType>
class LinkStack
{
protected:
	Node<ElemType>* top;
	int count;

public:
	LinkStack();
	virtual ~LinkStack();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const ElemType&)) const;
	bool Push(const ElemType& e);
	bool Top(ElemType& e) const;
	bool Pop(ElemType& e);
	LinkStack(const LinkStack<ElemType>& copy); // ���ƹ��캯��ģ��
	LinkStack<ElemType>& operator=(const LinkStack<ElemType>& copy); // ���ظ�ֵ�����

};

template<class ElemType>
LinkStack<ElemType>::LinkStack()
{
	top = NULL;
	count = 0;
}

template<class ElemType>
LinkStack<ElemType>::~LinkStack()
{
	Clear();
}

template<class ElemType>
int LinkStack<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool LinkStack<ElemType>::Empty() const
{
	return top == NULL;
}

template<class ElemType>
void LinkStack<ElemType>::Clear()
{
	ElemType tmpElem;
	while (!Empty()) {
		Pop(tmpElem);
	}
}

template<class ElemType>
void LinkStack<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	LinkStack<ElemType> tmpS; // ��ʱջ��tmpS��Ԫ��˳���뵱ǰջԪ��˳���෴
	for (Node<ElemType>* tmpPtr = top; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		tmpS.Push(tmpPtr->data);
	}
	
	for (Node<ElemType>* tmpPtr = tmpS.top; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
bool LinkStack<ElemType>::Push(const ElemType& e)
{
	Node<ElemType>* newTop = new Node<ElemType>(e, top);

	if (newTop == NULL) return false;
	
	top = newTop;
	count++;

	return true;
}

template<class ElemType>
bool LinkStack<ElemType>::Top(ElemType& e) const
{
	if (Empty()) return false;

	e = top->data;
	return true;
}

template<class ElemType>
bool LinkStack<ElemType>::Pop(ElemType& e)
{
	if (Empty()) return false;

	Node<ElemType>* old_top = top;
	e = old_top->data;
	top = old_top->next;
	count--;
	delete old_top;

	return true;
}

template<class ElemType>
LinkStack<ElemType>::LinkStack(const LinkStack<ElemType>& copy)
{
	top = new Node<ElemType>(copy.top->data);
	count = copy.count;

	Node<ElemType>* buttomPtr = top;
	for (Node<ElemType>* tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		buttomPtr->next = new Node<ElemType>(tmpPtr->data);
		buttomPtr = buttomPtr->next;
	}
}

template<class ElemType>
LinkStack<ElemType>& LinkStack<ElemType>::operator=(const LinkStack<ElemType>& copy)
{
	if (this == &copy) return *this;

	if (copy.Empty()) {
		top = NULL;
		count = 0;
	}
	else
	{
		Clear();
		top = new Node<ElemType>(copy.top->data);
		count = copy.count;

		Node<ElemType>* buttomPtr = top;
		for (Node<ElemType>* tmpPtr = copy.top->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
			buttomPtr->next = new Node<ElemType>(tmpPtr->data);
			buttomPtr = buttomPtr->next;
		}
	}

	return *this;
}
