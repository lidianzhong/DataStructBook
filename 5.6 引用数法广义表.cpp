#include <iostream>
using namespace std;

#ifndef __REF_GEN_LIST_NODE_TYPE__
#define __REF_GEN_LIST_NODE_TYPE__
enum RefGenListNodeType {HEAD, ATOM, LIST};
#endif

// 引用数法广义表结点类模板
template<class ElemType>
struct RefGenListNode
{
	// 标志,HEAD(0):头结点,ATOM(1):原子结构,LIST(2):表结点
	RefGenListNodeType tag;

	RefGenListNode<ElemType>* nextLink;    //指向同一层中的下一个结点指针

	union 
	{
		int ref;                           // tag=HEAD,表头结点,存放引用数
		ElemType atom;                     // tag=ATOM,存放原子结点的数据
		RefGenListNode<ElemType>* subLink; // tag=LISK,存放指向子表的指针
	};

	// 构造函数模板
	RefGenListNode<ElemType>(RefGenListNodeType tg = HEAD, RefGenListNode<ElemType>* next = NULL);     // 由标志tg和指针next构造引用数法广义表结点

};

// 引用数数法广义表类模板
template<class ElemType>
class RefGenList
{

protected:
	RefGenListNode<ElemType>* head; // 引用数法广义表头指针

	// 从输入流中跳过空格，换行符及制表符获取一字符
	char GetChar(); 

	// 显示以hd为头结点的引用数法广义表
	void ShowHelp(RefGenListNode<ElemType>* hd) const; 

	// 计算以hd为表头的引用数法广义表的深度
	int DepthHelp(const RefGenListNode<ElemType>* hd) const;

	// 释放以hd为表头的引用数法广义表结构
	void ClearHelp(RefGenListNode<ElemType>* hd);

	// 将以destHead为头结点的引用数法广义表复制成以sourceHead为头结点的引用数法广义表
	void CopyHelp(const RefGenListNode<ElemType>* sourceHead, RefGenListNode<ElemType>*& destHead);

	// 创建以first为首元素结点的引用数法广义表
	void CreateHelp(RefGenListNode<ElemType>*& first);


public:
	RefGenList();
	RefGenList(RefGenListNode<ElemType>* hd);
	~RefGenList();
	RefGenListNode<ElemType>* First() const; // 返回引用数法广义表的第一个元素
	RefGenListNode<ElemType>* Next(RefGenListNode<ElemType>* elemPtr) const; // 返回elemPtr指向的引用数法广义表元素的后继
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
	// 打印以hd为头结点的值
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

		// 引用数为0,释放结点所占用空间
		RefGenListNode<ElemType>* tmpPre, * tmpPtr;
		for (tmpPre = hd, tmpPtr = hd->nextLink; tmpPtr != NULL; tmpPre = tmpPtr, tmpPtr = tmpPtr->nextLink) {

			delete tmpPre;
			if (tmpPtr->tag == LIST) {

				// tmpPtr为子表
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
	for (RefGenListNode<ElemType>* tmpPtr = sourceHead->nextLink; tmpPtr != NULL; tmpPtr = tmpPtr->nextLink) { // 扫描引用数法广义表sourceHead的顶层

		destPtr = destPtr->nextLink = new RefGenListNode<ElemType>(tmpPtr->tag); // 生成新结点

		if (tmpPtr->tag == LIST) {
			// 子表
			CopyHelp(tmpPtr->subLink, destPtr->subLink); // 复制子表
		}
		else
		{
			// 原子结点
			destPtr->atom = tmpPtr->atom; // 复制原子结点
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
		// 表头为子表
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
		// 表头为原子
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
	RefGenList<ElemType>::CreateHelp(head->nextLink);  // 创建以head->nextLink为表头的引用数法广义表

}

template<class ElemType>
void RefGenList<ElemType>::Show() const
{
	ShowHelp(head);
}

