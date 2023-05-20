#include<iostream>
#include "��/6.2 ��������.cpp"
using namespace std;

enum PointerTagType {CHILD_PTR, THREAD_PTR}; // ָ���־����

// �����������������ģ��
template<class ElemType>
struct ThreadBinTreeNode
{
	ElemType data; 
	ThreadBinTreeNode<ElemType>* leftChild;
	ThreadBinTreeNode<ElemType>* rightChild;
	PointerTagType leftTag, rightTag; // ���ұ�־

	// ���캯��ģ��
	ThreadBinTreeNode();
	ThreadBinTreeNode(
		const ElemType& val,                        //
		ThreadBinTreeNode<ElemType>* lChild = NULL, //
		ThreadBinTreeNode<ElemType>* rChild = NULL, //
		PointerTagType leftTag = CHILD_PTR,         //
		PointerTagType rightTag = CHILD_PTR);       //

};

template<class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode() : data(0), leftChild(NULL), rightChild(NULL), leftTag(CHILD_PTR), rightTag(CHILD_PTR) {}


template<class ElemType>
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode(
	const ElemType& val,                 //
	ThreadBinTreeNode<ElemType>* lChild, //
	ThreadBinTreeNode<ElemType>* rChild, //
	PointerTagType leftTag,              //
	PointerTagType rightTag)             //
	: data(val), leftChild(lChild), rightChild(rChild) {};


// ����������������ģ��
template<class ElemType>
class InThreadBinTree
{

protected:
	ThreadBinTreeNode<ElemType>* root;

	// ��������ģ��

	// ������������curΪ���Ķ�����
	void InThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre);

	// btΪ���Ķ�����ת�����µ�δ�����������������������������¶������ĸ�
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(BinTreeNode<ElemType>* r);

	//��������������
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy);

	// ������rΪ���Ķ�����
	void DestroyHelp(ThreadBinTreeNode<ElemType>*& r);

public:

	// �ɶ���������������������������ת�����캯��ģ��
	InThreadBinTree(const BinaryTree<ElemType>& bt);

	// ��������ģ��
	virtual~InThreadBinTree();

	// ���������������ĸ�
	ThreadBinTreeNode<ElemType>* GetRoot() const;

	// ����������������
	void InThread();

	// ���������������
	void InOrder(void(*visit)(const ElemType&)) const;

	// ���ƹ��캯��ģ��
	InThreadBinTree(const InThreadBinTree<ElemType>& copy);

	// ���ظ�ֵ�����
	InThreadBinTree<ElemType>& operator=(const InThreadBinTree<ElemType>& copy);

};


template<class ElemType>
void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre)
{
	// �����ս�㷵��
	if (cur == NULL) return; 

	if (cur->leftTag == CHILD_PTR)
		// ������������
		InThreadHelp(cur->leftChild, pre);


	// �Ե�ǰcur���Ĳ���
	if (cur->leftChild == NULL) {
		// cur�����ӣ�������
		cur->leftChild = pre;
		cur->leftTag = THREAD_PTR;
	}

	// ��pre���Ĳ���
	if (pre != NULL && pre->rightChild == NULL) {
		// pre���Һ��ӣ�������
		pre->rightChild = cur;
		pre->rightTag = THREAD_PTR;
	}


	pre = cur;


	if (cur->rightTag == CHILD_PTR)
		// ������������
		InThreadHelp(cur->rightChild, pre);

}


template<class ElemType>
ThreadBinTreeNode<ElemType>* InThreadBinTree<ElemType>::CopyTreeHelp(BinTreeNode<ElemType>* r)
{
	if (r == NULL) return NULL;

	ThreadBinTreeNode<ElemType>* cur = new ThreadBinTreeNode<ElemType>(r->data);
	cur->leftChild = CopyTreeHelp(r->leftChild);
	cur->rightChild = CopyTreeHelp(r->rightChild);

	return cur;
}

template<class ElemType>
ThreadBinTreeNode<ElemType>* InThreadBinTree<ElemType>::CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy)
{
	if (copy == NULL) return NULL;

	ThreadBinTreeNode<ElemType>* cur = new ThreadBinTreeNode<ElemType>(copy->data);
	cur->leftTag = copy->leftTag;
	cur->rightTag = copy->rightTag;
	cur->leftChild = CopyTreeHelp(copy->leftChild);
	cur->rightChild = CopyTreeHelp(copy->rightChild);


	return cur;
}

template<class ElemType>
void InThreadBinTree<ElemType>::DestroyHelp(ThreadBinTreeNode<ElemType>*& r)
{
	if (r == NULL) return;
	
	DestroyHelp(r->leftChild);
	DestroyHelp(r->rightChild);
	delete r;
	r = NULL;
}

template<class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const BinaryTree<ElemType>& bt)
{
	root = CopyTreeHelp(bt.GetRoot());
}

template<class ElemType>
InThreadBinTree<ElemType>::~InThreadBinTree()
{
	DestroyHelp(root);
}

template<class ElemType>
ThreadBinTreeNode<ElemType>* InThreadBinTree<ElemType>::GetRoot() const
{
	return root;
}


template<class ElemType>
void InThreadBinTree<ElemType>::InThread()
{
	ThreadBinTreeNode<ElemType>* pre = NULL;
	InThreadHelp(root, pre);
	if (pre->rightChild == NULL) // preΪ�������������һ�����
		pre->rightTag = THREAD_PTR; // �����Һ��ӣ�����������
}


template<class ElemType>
void InThreadBinTree<ElemType>::InOrder(void(*visit)(const ElemType&)) const
{
	if (root == NULL) return;

	ThreadBinTreeNode<ElemType>* cur = root;
	while (cur->leftTag == CHILD_PTR) // ���������Ľ�㣬�˽��Ϊ�������еĵ�һ�����
		cur = cur->leftChild;
	while (cur != NULL)
	{
		(*visit)(cur->data);

		if (cur->rightTag == THREAD_PTR) {
			// ����Ϊ���������Ϊcur->rightChild
			cur = cur->rightChild;
		}
		else {
			// ����Ϊ���ӣ�cur�����������Ľ��Ϊ���
			cur = cur->rightChild;
			while (cur->leftTag == CHILD_PTR)
				cur = cur->leftChild; // ����ԭcur�����������Ľ��
		}
	}
}

template<class ElemType>
InThreadBinTree<ElemType>::InThreadBinTree(const InThreadBinTree<ElemType>& copy)
{
	root = CopyTreeHelp(copy.GetRoot());
}

template<class ElemType>
InThreadBinTree<ElemType>& InThreadBinTree<ElemType>::operator=(const InThreadBinTree<ElemType>& copy)
{
	if (this == &copy) return *this;

	root = CopyTreeHelp(copy.GetRoot());

	return *this;
}




