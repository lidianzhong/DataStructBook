#include <iostream>
using namespace std;

#ifndef __REF_GEN_LIST_NODE_TYPE__
#define __REF_GEN_LIST_NODE_TYPE__
enum RefGenListNodeType {HEAD, ATOM, LIST};
#endif

// �����������������ģ��
template<class ElemType>
struct RefGenListNode
{
	// ��־,HEAD(0):ͷ���,ATOM(1):ԭ�ӽṹ,LIST(2):����
	RefGenListNodeType tag;

	RefGenListNode<ElemType>* nextLink;    //ָ��ͬһ���е���һ�����ָ��

	union 
	{
		int ref;                           // tag=HEAD,��ͷ���,���������
		ElemType atom;                     // tag=ATOM,���ԭ�ӽ�������
		RefGenListNode<ElemType>* subLink; // tag=LISK,���ָ���ӱ��ָ��
	};

	// ���캯��ģ��
	RefGenListNode<ElemType>(RefGenListNodeType tg = HEAD, RefGenListNode<ElemType>* next = NULL);     // �ɱ�־tg��ָ��next�������������������

};

// �����������������ģ��
template<class ElemType>
class RefGenList
{

protected:
	RefGenListNode<ElemType>* head; // �������������ͷָ��

	// ���������������ո񣬻��з����Ʊ����ȡһ�ַ�
	char GetChar(); 

	// ��ʾ��hdΪͷ�����������������
	void ShowHelp(RefGenListNode<ElemType>* hd) const; 

	// ������hdΪ��ͷ�������������������
	int DepthHelp(const RefGenListNode<ElemType>* hd) const;

	// �ͷ���hdΪ��ͷ���������������ṹ
	void ClearHelp(RefGenListNode<ElemType>* hd);

	// ����destHeadΪͷ������������������Ƴ���sourceHeadΪͷ�����������������
	void CopyHelp(const RefGenListNode<ElemType>* sourceHead, RefGenListNode<ElemType>*& destHead);

	// ������firstΪ��Ԫ�ؽ����������������
	void CreateHelp(RefGenListNode<ElemType>*& first);


public:
	RefGenList();
	RefGenList(RefGenListNode<ElemType>* hd);
	~RefGenList();
	RefGenListNode<ElemType>* First() const; // �����������������ĵ�һ��Ԫ��
	RefGenListNode<ElemType>* Next(RefGenListNode<ElemType>* elemPtr) const; // ����elemPtrָ����������������Ԫ�صĺ��
	bool Empty() const;
	void Push(const ElemType& e);
	void Push(RefGenList<ElemType>& subList);
	int Depth() const;
	RefGenList(const RefGenList<ElemType>& copy);
	RefGenList<ElemType>& operator=(const RefGenList<ElemType>& copy);
	void Input();
	void Show() const;


};

template<class ElemType>
RefGenListNode<ElemType>::RefGenListNode(RefGenListNodeType tg, RefGenListNode<ElemType>* next)
{
	tag = tg;
	nextLink = next;
}

template<class ElemType>
char RefGenList<ElemType>::GetChar()
{
	char c = getchar();
	return c;
}

template<class ElemType>
void RefGenList<ElemType>::ShowHelp(RefGenListNode<ElemType>* hd) const
{
	// ��ӡ��hdΪͷ����ֵ
	cout << "| HEAD | " << hd->ref << " |--->";

	for (RefGenListNode<ElemType>* tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink) {

		if (tmpPtr->tag == ATOM) {

			cout << "| ATOM | " << tmpPtr->atom << " |--->";

		}
		else
		{
			// LIST
			cout << "| LIST | " << " " << " |--->";
			cout << '(';
			ShowHelp(tmpPtr->subLink);
			cout << ')';
		}

	}

	cout << "NULL";

}

template<class ElemType>
int RefGenList<ElemType>::DepthHelp(const RefGenListNode<ElemType>* hd) const
{
	if (hd->nextLink == NULL) return 1;

	int subMaxDepth = 0;
	for (RefGenListNode<ElemType>* tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink) {

		if (tmpPtr->tag == LIST) {

			int curSubDepth = DepthHelp(tmpPtr->subLink);
			if (subMaxDepth < curSubDepth) subMaxDepth = curSubDepth;
		}
	}

	return subMaxDepth + 1;
}

template<class ElemType>
void RefGenList<ElemType>::ClearHelp(RefGenListNode<ElemType>* hd)
{
	hd->ref--;
	if (hd->ref == 0) {

		// ������Ϊ0,�ͷŽ����ռ�ÿռ�
		RefGenListNode<ElemType>* tmpPre, * tmpPtr;
		for (tmpPre = hd, tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPre = tmpPtr, tmpPtr = tmpPtr->nextLink) {

			delete tmpPre;
			if (tmpPtr->tag == LIST) {

				// tmpPtrΪ�ӱ�
				ClearHelp(tmpPtr->subLink);
			}

		}

		delete tmpPre;
	}
}

template<class ElemType>
void RefGenList<ElemType>::CopyHelp(const RefGenListNode<ElemType>* sourceHead, RefGenListNode<ElemType>*& destHead)
{
	destHead = new RefGenListNode<ElemType>(HEAD);
	RefGenListNode<ElemType>* destPtr = destHead;
	destHead->ref = 1;
	for (RefGenListNode<ElemType>* tmpPtr = sourceHead->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink) { // ɨ���������������sourceHead�Ķ���

		destPtr = destPtr->nextLink = new RefGenListNode<ElemType>(tmpPtr->tag); // �����½��

		if (tmpPtr->tag == LIST) {
			// �ӱ�
			CopyHelp(tmpPtr->subLink, destPtr->subLink); // �����ӱ�
		}
		else
		{
			// ԭ�ӽ��
			destPtr->atom = tmpPtr->atom; // ����ԭ�ӽ��
		}

	}
}

template<class ElemType>
void RefGenList<ElemType>::CreateHelp(RefGenListNode<ElemType>*& first)
{
	char ch = GetChar();
	switch (ch)
	{

	case  ')':
		return;

	case '(':
		// ��ͷΪ�ӱ�
		first = new RefGenListNode<ElemType>(LIST);

		RefGenListNode<ElemType>* subHead;
		subHead = new RefGenListNode<ElemType>(HEAD);
		subHead->ref = 1;
		first->subLink = subHead;
		CreateHelp(subHead->nextLink);

		ch = GetChar();
		if (ch != ',') cin.putback(ch);
		CreateHelp(first->nextLink);
		break;

	default:
		// ��ͷΪԭ��
		cin.putback(ch);
		ElemType amData;
		cin >> amData;
		first = new RefGenListNode<ElemType>(ATOM);
		first->atom = amData;
		
		ch = GetChar();
		if (ch != ',') cin.putback(ch);
		CreateHelp(first->nextLink);
		break;
	}
}

template<class ElemType>
RefGenList<ElemType>::RefGenList()
{
	head = new RefGenListNode<ElemType>(HEAD);
	head->ref = 1;
}

template<class ElemType>
RefGenList<ElemType>::RefGenList(RefGenListNode<ElemType>* hd)
{
	head = hd;
	head->ref = 1;
}

template<class ElemType>
RefGenList<ElemType>::~RefGenList()
{
	ClearHelp(head);
}

template<class ElemType>
RefGenListNode<ElemType>* RefGenList<ElemType>::First() const
{

	return head->nextLink;
}

template<class ElemType>
RefGenListNode<ElemType>* RefGenList<ElemType>::Next(RefGenListNode<ElemType>* elemPtr) const
{
	return elemPtr->nextLink;
}

template<class ElemType>
bool RefGenList<ElemType>::Empty() const
{
	return head->nextLink == NULL;
}

template<class ElemType>
void RefGenList<ElemType>::Push(const ElemType& e)
{
	RefGenListNode<ElemType>* newPtr = new RefGenListNode<ElemType>(ATOM);
	newPtr->atom = e;
	newPtr->nextLink = head->nextLink;

	head->nextLink = newPtr;

}

template<class ElemType>
void RefGenList<ElemType>::Push(RefGenList<ElemType>& subList)
{
	RefGenListNode<ElemType>* newPtr = new RefGenListNode<ElemType>(LIST);
	newPtr->nextLink = head->nextLink;

	newPtr->subLink = subList.head;

	head->nextLink = newPtr;
}

template<class ElemType>
int RefGenList<ElemType>::Depth() const
{
	return DepthHelp(head);
}

template<class ElemType>
RefGenList<ElemType>::RefGenList(const RefGenList<ElemType>& copy)
{
	CopyHelp(copy.head, head);
}

template<class ElemType>
RefGenList<ElemType>& RefGenList<ElemType>::operator=(const RefGenList<ElemType>& copy)
{
	if (this == &copy) return *this;

	ClearHelp(head);

	CopyHelp(copy.head, head);

	return *this;
}

template<class ElemType>
void RefGenList<ElemType>::Input()
{
	head = new RefGenListNode<ElemType>(HEAD);
	head->ref = 1;
	GetChar();
	RefGenList<ElemType>::CreateHelp(head->nextLink);  // ������head->nextLinkΪ��ͷ���������������

}

template<class ElemType>
void RefGenList<ElemType>::Show() const
{
	ShowHelp(head);
}

