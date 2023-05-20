#include<iostream>
#include "��/6.2 ��������.cpp"
using namespace std;

enum PointerTagType { CHILD_PTR, THREAD_PTR }; // ָ���־����

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
class PreThreadBinTree
{

protected:
	ThreadBinTreeNode<ElemType>* root;

	// ��������ģ��

	// ������������curΪ���Ķ�����
	void PreThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre);

	// btΪ���Ķ�����ת�����µ�δ�����������������������������¶������ĸ�
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(BinTreeNode<ElemType>* r);

	//��������������
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy);

	// ������rΪ���Ķ�����
	void DestroyHelp(ThreadBinTreeNode<ElemType>*& r);

public:

	// �ɶ���������������������������ת�����캯��ģ��
	PreThreadBinTree(const BinaryTree<ElemType>& bt);

	// ��������ģ��
	virtual~PreThreadBinTree();

	// ���������������ĸ�
	ThreadBinTreeNode<ElemType>* GetRoot() const;

	// ����������������
	void PreThread();

	// ���������������
	void PreOrder(void(*visit)(const ElemType&)) const;

	// ���ƹ��캯��ģ��
	PreThreadBinTree(const PreThreadBinTree<ElemType>& copy);

	// ���ظ�ֵ�����
	PreThreadBinTree<ElemType>& operator=(const PreThreadBinTree<ElemType>& copy);

};





template<class ElemType>
void PreThreadBinTree<ElemType>::PreThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre)
{
	// �����ս��ͷ���
	if (cur == NULL) return;

	// ��
	if (cur->leftChild == NULL)
	{
		cur->leftChild = pre;
		cur->leftTag = THREAD_PTR;
	}

	if (pre != NULL && pre->rightChild == NULL)
	{
		pre->rightChild = cur;
		pre->rightTag = THREAD_PTR;
	}

	// pre ����
	pre = cur;

	// ��
	if (cur->leftTag == CHILD_PTR)
	{
		PreThreadHelp(cur->leftChild, pre);
	}
	

	// ��
	if (cur->rightTag == CHILD_PTR)
	{
		PreThreadHelp(cur->rightChild, pre);
	}



}

template<class ElemType>
ThreadBinTreeNode<ElemType>* PreThreadBinTree<ElemType>::CopyTreeHelp(BinTreeNode<ElemType>* r)
{
	if (r == NULL) return NULL;

	ThreadBinTreeNode<ElemType>* cur = new ThreadBinTreeNode<ElemType>(r->data);
	cur->leftChild = CopyTreeHelp(r->leftChild);
	cur->rightChild = CopyTreeHelp(r->rightChild);

	return cur;
}

template<class ElemType>
ThreadBinTreeNode<ElemType>* PreThreadBinTree<ElemType>::CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy)
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
void PreThreadBinTree<ElemType>::DestroyHelp(ThreadBinTreeNode<ElemType>*& r)
{
	if (r == NULL) return;

	DestroyHelp(r->leftChild);
	DestroyHelp(r->rightChild);
	delete r;
	r = NULL;
}

template<class ElemType>
PreThreadBinTree<ElemType>::PreThreadBinTree(const BinaryTree<ElemType>& bt)
{
	root = CopyTreeHelp(bt.GetRoot());
}

template<class ElemType>
PreThreadBinTree<ElemType>::~PreThreadBinTree()
{
	DestroyHelp(root);
}

template<class ElemType>
ThreadBinTreeNode<ElemType>* PreThreadBinTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
void PreThreadBinTree<ElemType>::PreThread()
{
	ThreadBinTreeNode<ElemType>* pre = NULL;
	PreThreadHelp(root, pre);
	if (pre->rightChild == NULL)
		pre->rightTag = THREAD_PTR;
}

template<class ElemType>
void PreThreadBinTree<ElemType>::PreOrder(void(*visit)(const ElemType&)) const
{
	if (root == NULL) return;

	ThreadBinTreeNode<ElemType>* cur = root; // �����Ϊ��������ĵ�һ�����

	while (cur != NULL)
	{
		(*visit)(cur->data);

		if (cur->rightTag == THREAD_PTR) {
			// �������Ϊ���������Ϊcur->rightChild
			cur = cur->rightChild;
		}
		else {
			// ����Ϊ����
			if (cur->leftTag == CHILD_PTR) {
				// cur�����ӣ�������Ϊ���
				cur = cur->leftChild;
			}
			else {
				// cur�����ӣ����Һ���Ϊ���
				cur = cur->rightChild;
			}
		}


	}
}





template<class ElemType>
PreThreadBinTree<ElemType>::PreThreadBinTree(const PreThreadBinTree<ElemType>& copy)
{
	root = CopyTreeHelp(copy.GetRoot());
}

template<class ElemType>
PreThreadBinTree<ElemType>& PreThreadBinTree<ElemType>::operator=(const PreThreadBinTree<ElemType>& copy)
{
	if (this == &copy) return *this;

	root = CopyTreeHelp(copy.GetRoot());

	return *this;
}




