#include <iostream>
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

// ˫������ģ��
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

// ����������ģ��
template <class ElemType>
class LinkList
{
protected:
	Node<ElemType> *head;	                        // ͷָ��

	mutable int curPosition;	                    // ��ǰλ�õ����
	mutable Node<ElemType> *curPtr;	                // ��ǰλ�õ�ָ��
	int count;	                                    // Ԫ�ظ���

	// ��������ģ��
	Node<ElemType> *GetElemPtr(int position) const;	// ����ָ���position������ָ��

public:
	LinkList();	
	virtual ~LinkList();	
    int Length() const;	
	bool Empty() const;	
	void Clear();	
	void Traverse(void (*Visit)(const ElemType &)) const;	
	bool GetElem(int position, ElemType &e) const;	
	bool SetElem(int position, const ElemType &e);	
	bool Delete(int position, ElemType &e);	
	bool Insert(int position, const ElemType& e); 
	bool InsertTail(const ElemType& e);
	Node<ElemType>* GetHead() const;
	LinkList(const LinkList<ElemType>& copy);                      // ���ƹ��캯��
	LinkList<ElemType>& operator=(const LinkList<ElemType>& copy); // ���ظ�ֵ�����
};



template<class ElemType>
Node<ElemType>* LinkList<ElemType>::GetElemPtr(int position) const
{
	if (curPosition > position) {
		// ��ǰλ����position֮�󣬴�ͷ��ʼ����
		curPosition = 0;
		curPtr = head;
	}

	for (; curPosition < position; curPosition++) {
		curPtr = curPtr->next;
	}

	return curPtr;

}

template<class ElemType>
LinkList<ElemType>::LinkList()
{
	head = new Node<ElemType>;
	curPosition = 0;
	curPtr = head;
	count = 0;
}

template<class ElemType>
LinkList<ElemType>::~LinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int LinkList<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool LinkList<ElemType>::Empty() const
{
	return head->next == NULL;
}

template<class ElemType>
void LinkList<ElemType>::Clear()
{
	ElemType tmpElem; // ��ʱԪ��ֵ
	while (!Empty()) {
		Delete(1, tmpElem);
	}
}

template<class ElemType>
Node<ElemType>* LinkList<ElemType>::GetHead() const
{
	return head;
}

template<class ElemType>
void LinkList<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) {
		(*visit) (tmpPtr->data);
	}
}

template<class ElemType>
bool LinkList<ElemType>::GetElem(int position, ElemType& e) const
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	e = tmpPtr->data;

	return true;

}

template<class ElemType>
bool LinkList<ElemType>::SetElem(int position, const ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	tmpPtr->data = e;

	return true;

}

template<class ElemType>
bool LinkList<ElemType>::Delete(int position, ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* nextPtr = tmpPtr->next;
	tmpPtr->next = nextPtr->next;
	e = nextPtr->data;

	// add
	if (position == Length())
	{
		// ɾ��β��㣬��ǰ����Ϊͷ���
		curPosition = 0;
		curPtr = head;
	}
	else
	{
		// ɾ����β��㣬��ǰ����Ϊ��position�����
		curPosition = position;
		curPtr = tmpPtr->next;
	}

	count--;

	delete nextPtr;

	return true;
}

template<class ElemType>
bool LinkList<ElemType>::Insert(int position, const ElemType& e)
{
	if (position < 1 || position > Length() + 1) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* newPtr;
	newPtr = new Node<ElemType>(e, tmpPtr->next);
	tmpPtr->next = newPtr;

	curPosition = position;
	curPtr = newPtr;
	count++;

	return true;
}

template<class ElemType>
bool LinkList<ElemType>::InsertTail(const ElemType& e)
{
	Node<ElemType>* tmpPtr = GetElemPtr(Length());
	tmpPtr->next = new Node<ElemType>(e);
	count++;

	return true;
}

template<class ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType>& copy)
{
	curPosition = 0;
	curPtr = head;
	count = copy.count;

	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != NULL; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data);
		tmpPtr = tmpPtr->next;
	}
}

template<class ElemType>
LinkList<ElemType>& LinkList<ElemType>::operator=(const LinkList<ElemType>& copy)
{
	if (this == &copy) return *this;

	curPosition = 0;
	curPtr = head;
	count = copy.count;

	// �ͷŵ�ǰ��������н��
	Node<ElemType>* tmpPtr = head->next;
	while (tmpPtr != NULL) {
		Node<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		delete prevPtr;
	}

	// ����Ҫ���Ƶ�����
	tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != NULL; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data);
		tmpPtr = tmpPtr->next;
	}

	return *this;

}

template<class ElemType>
class CircLinkList
{
protected:
	Node<ElemType>* head;
	mutable int curPosition;                                               // ��ǰλ�õ����
	mutable Node<ElemType>* curPtr;                                        // ��ǰλ�õ�ָ��
	int count;                                                             // Ԫ�ظ���

	// ��������ģ��
	Node<ElemType>* GetElemPtr(int position) const;                        // ����ָ���position������ָ��

public:
	CircLinkList();
	virtual ~CircLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*Visit)(const ElemType&)) const;
	bool GetElem(int position, ElemType& e) const;
	bool SetElem(int position, const ElemType& e);
	bool Delete(int position, ElemType& e);
	bool Insert(int position, const ElemType& e);
	CircLinkList(const CircLinkList<ElemType>& copy);                      // ���ƹ��캯��
	CircLinkList<ElemType>& operator=(const CircLinkList<ElemType>& copy); // ���ظ�ֵ�����
};

template<class ElemType>
Node<ElemType>* CircLinkList<ElemType>::GetElemPtr(int position) const
{
	while (curPosition != position)
	{
		curPosition = (curPosition + 1) % (Length() + 1);
		curPtr = curPtr->next;
	}

	return curPtr;
}

template<class ElemType>
CircLinkList<ElemType>::CircLinkList()
{
	head = new Node<ElemType>;
	head->next = head;
	curPosition = 0;
	curPtr = head;
	count = 0;
}

template<class ElemType>
CircLinkList<ElemType>::~CircLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int CircLinkList<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool CircLinkList<ElemType>::Empty() const
{
	return head->next = head;
}

template<class ElemType>
void CircLinkList<ElemType>::Clear()
{
	ElemType tmpElem;
	if (!Empty()) {
		Delete(1, tmpElem);
	}

	curPosition = 0;
	curPtr = head;
	count = 0;
}

template<class ElemType>
void CircLinkList<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (Node<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr->next) {
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
bool CircLinkList<ElemType>::GetElem(int position, ElemType& e) const
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	e = tmpPtr->data;
	return true;
}

template<class ElemType>
bool CircLinkList<ElemType>::SetElem(int position, const ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	tmpPtr->data = e;

	return true;
}

template<class ElemType>
bool CircLinkList<ElemType>::Delete(int position, ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* nextPtr;
	nextPtr = tmpPtr->next;
	tmpPtr->next = nextPtr->next;
	e = nextPtr->data;

	if (position == Length())
	{
		// ɾ��β��㣬��ǰ����Ϊͷ���
		curPosition = 0;
		curPtr = head;
	}
	else
	{
		// ɾ����β��㣬��ǰ����Ϊ��position�����
		curPosition = position;
		curPtr = tmpPtr->next;
	}

	count--;

	delete nextPtr;
	return true;
}

template<class ElemType>
bool CircLinkList<ElemType>::Insert(int position, const ElemType& e)
{
	if (position < 1 || position > Length() + 1) return false;

	Node<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position - 1);
	Node<ElemType>* newPtr;
	newPtr = new Node<ElemType>(e, tmpPtr->next);
	tmpPtr->next = newPtr;

	curPosition = position;
	curPtr = newPtr;
	count++;

	return true;
}

template<class ElemType>
CircLinkList<ElemType>::CircLinkList(const CircLinkList<ElemType>& copy)
{

	curPosition = 0;
	curPtr = head;
	count = copy.count;

	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != head; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data, head);
		tmpPtr = tmpPtr->next;
	}
}

template<class ElemType>
CircLinkList<ElemType>& CircLinkList<ElemType>::operator=(const CircLinkList<ElemType>& copy)
{
	if (this == &copy) return *this;

	curPosition = 0;
	curPtr = head;
	count = copy.count;

	// �ͷŵ�ǰ��������н��
	Node<ElemType>* tmpPtr = head->next;
	while (tmpPtr != head) {
		Node<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		delete prevPtr;
	}

	// ����Ҫ���Ƶ�����
	Node<ElemType>* tmpPtr = head;

	for (Node<ElemType>* curPtr = copy.GetElemPtr(1); curPtr != head; curPtr = curPtr->next) {
		tmpPtr->next = new Node<ElemType>(curPtr->data, head);
		tmpPtr = tmpPtr->next;
	}

	return *this;
}


// ��˫��ѭ��������ģ��
template<class ElemType>
class DblLinkList
{
protected:
	DblNode<ElemType>* head;

	mutable int curPosition;
	mutable DblNode<ElemType>* curPtr;
	int count;

	DblNode<ElemType>* GetElemPtr(int position) const; // ����ָ���position������ָ��

public:
	DblLinkList();
	virtual ~DblLinkList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void (*visit) (const ElemType&)) const;
	bool GetElem(int position, ElemType& e) const;
	bool SetElem(int position, const ElemType& e);
	bool Delete(int position, ElemType& e);
	bool Insert(int position, const ElemType& e);
	DblLinkList(const DblLinkList<ElemType>& copy); // ���ƹ��캯��ģ��
	DblLinkList<ElemType>& operator=(const DblLinkList<ElemType>& copy); // ���ظ�ֵ�����


};

template<class ElemType>
DblNode<ElemType>* DblLinkList<ElemType>::GetElemPtr(int position) const
{
	if (curPosition < position)
	{
		for (; curPosition < position; curPosition++) curPtr = curPtr->next;
	}
	else if(curPosition > position)
	{
		for (; curPosition > position; curPosition--) curPtr = curPtr->back;
	}

	return curPtr;

}

template<class ElemType>
DblLinkList<ElemType>::DblLinkList()
{
	head = new DblNode<ElemType>;
	head->next = head;
	head->back = head;

	curPosition = 0;
	curPtr = head;
	count = 0;

}

template<class ElemType>
DblLinkList<ElemType>::~DblLinkList()
{
	Clear();
	delete head;
}

template<class ElemType>
int DblLinkList<ElemType>::Length() const
{
	return count;
}

template<class ElemType>
bool DblLinkList<ElemType>::Empty() const
{
	return head->next == head;
}

template<class ElemType>
void DblLinkList<ElemType>::Clear()
{
	ElemType tmp;
	Delete(1, tmp);

	curPosition = 0;
	curPtr = head;
	count = 0;
}

template<class ElemType>
void DblLinkList<ElemType>::Traverse(void(*visit)(const ElemType&)) const
{
	for (DblNode<ElemType>* tmpPtr = head->next; tmpPtr != head; tmpPtr = tmpPtr->next) {
		(*visit)(tmpPtr->data);
	}
}

template<class ElemType>
bool DblLinkList<ElemType>::GetElem(int position, ElemType& e) const
{
	if (position < 1 || position > Length()) return false;

	DblNode<ElemType>* tmpPtr;

	tmpPtr = GetElemPtr(position);
	e = tmpPtr->data;

	return true;
}

template<class ElemType>
bool DblLinkList<ElemType>::SetElem(int position, const ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	DblNode<ElemType>* tmpPtr;

	tmpPtr = GetElemPtr(position);
	tmpPtr->data = e;

	return true;
}

template<class ElemType>
bool DblLinkList<ElemType>::Delete(int position, ElemType& e)
{
	if (position < 1 || position > Length()) return false;

	DblNode<ElemType>* tmpPtr;
	tmpPtr = GetElemPtr(position);
	tmpPtr->back->next = tmpPtr->next;
	tmpPtr->next->back = tmpPtr->back;
	e = tmpPtr->data;

	// add
	if (position == Length())
	{
		curPosition = 0;
		curPtr = head;
	}
	else
	{
		curPosition = position;
		curPtr = tmpPtr->next;
	}

	count--;

	delete tmpPtr;

	return true;

}

template<class ElemType>
bool DblLinkList<ElemType>::Insert(int position, const ElemType& e)
{
	if (position < 1 || position > Length() + 1) return false;

	DblNode<ElemType>* tmpPtr, * nextPtr, * newPtr;
	tmpPtr = GetElemPtr(position - 1);
	nextPtr = tmpPtr->next;
	newPtr = new DblNode<ElemType>(e, tmpPtr, nextPtr);
	tmpPtr->next = newPtr;
	nextPtr->back = newPtr;

	curPosition = position;
	curPtr = newPtr;
	count++;

	return true;

}

template<class ElemType>
DblLinkList<ElemType>::DblLinkList(const DblLinkList<ElemType>& copy)
{
	// ����һ���յ�����
	head = new DblNode<ElemType>;
	head->next = head;
	head->back = head;

	// ���ƹ���
	DblNode<ElemType>* curPtr = head;

	for (DblNode<ElemType>* tmpPtr = copy.head->next; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
		DblNode<ElemType>* newPtr = new DblNode<ElemType>(tmpPtr->data, curPtr, head);
		curPtr->next = newPtr;
		head->back = newPtr;
	}


}

template<class ElemType>
DblLinkList<ElemType>& DblLinkList<ElemType>::operator=(const DblLinkList<ElemType>& copy)
{
	if (this == &copy) return *this;

	// �ͷŵ�ǰ�����Ѵ��ڵĽ��
	DblNode<ElemType>* tmpPtr = head->next;
	while (tmpPtr != head) {
		DblNode<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->next;
		delete prevPtr;
	}

	// ����Ҫ���Ƶ�����
	DblNode<ElemType>* curPtr = head;

	for (DblNode<ElemType>* tmpPtr = copy.head->next; tmpPtr != copy.head; tmpPtr = tmpPtr->next) {
		DblNode<ElemType>* newPtr = new DblNode<ElemType>(tmpPtr->data, curPtr, head);
		curPtr->next = newPtr;
		head->back = newPtr;
	}

}

