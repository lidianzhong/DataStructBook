#include<iostream>
#include "��/6.2 ��������.cpp"
using namespace std;

enum PointerTagType { CHILD_PTR, THREAD_PTR }; // ָ���־����

// ������������������ģ��
template<class ElemType>
struct TriLKBinTreeNode
{
	ElemType data;
	TriLKBinTreeNode<ElemType>* leftChild;
	TriLKBinTreeNode<ElemType>* rightChild;
	TriLKBinTreeNode<ElemType>* parent;

	TriLKBinTreeNode();
	TriLKBinTreeNode(
		const ElemType& val,                       //
		TriLKBinTreeNode<ElemType>* lChild = NULL, //
		TriLKBinTreeNode<ElemType>* rChild = NULL, //
		TriLKBinTreeNode<ElemType>* pt = NULL);    //
};


template<class ElemType>
TriLKBinTreeNode<ElemType>::TriLKBinTreeNode()
	: data(0), leftChild(NULL), rightChild(NULL), parent(NULL) {}

template<class ElemType>
TriLKBinTreeNode<ElemType>::TriLKBinTreeNode(
	const ElemType& val,                //
	TriLKBinTreeNode<ElemType>* lChild, //
	TriLKBinTreeNode<ElemType>* rChild, //
	TriLKBinTreeNode<ElemType>* pt)     //
	: data(val), leftChild(lChild), rightChild(rChild), parent(pt) {}


// ���������������ģ��
template<class ElemType>
struct PostThreadBinTreeNode
{
	ElemType data;
	PostThreadBinTreeNode<ElemType>* leftChild;
	PostThreadBinTreeNode<ElemType>* rightChild;
	PostThreadBinTreeNode<ElemType>* parent;
	PointerTagType leftTag, rightTag;

	PostThreadBinTreeNode();
	PostThreadBinTreeNode(
		const ElemType& data,                            //
		PostThreadBinTreeNode<ElemType>* lChild = NULL, //
		PostThreadBinTreeNode<ElemType>* rChild = NULL, //
		PostThreadBinTreeNode<ElemType>* pt = NULL,     //
		PointerTagType leftTag = CHILD_PTR,             //
		PointerTagType rightTag = CHILD_PTR);           //
} ;

template<class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode()
	: data(0), leftChild(NULL), rightChild(NULL), parent(NULL), leftTag(CHILD_PTR), rightTag(CHILD_PTR) {}

template<class ElemType>
PostThreadBinTreeNode<ElemType>::PostThreadBinTreeNode(
	const ElemType& val,                     //
	PostThreadBinTreeNode<ElemType>* lChild, //
	PostThreadBinTreeNode<ElemType>* rChild, //
	PostThreadBinTreeNode<ElemType>* pt,     //
	PointerTagType leftTag,                  //
	PointerTagType rightTag)                 //
	: data(val), leftChild(lChild), rightChild(rChild), parent(pt) {}


// ����������������ģ��
template<class ElemType>
class PostThreadBinTree
{

protected:
	PostThreadBinTreeNode<ElemType>* root;
	
	// ��������ģ��

	// ������������curΪ���Ķ�����
	void PostThreadHelp(PostThreadBinTreeNode<ElemType>* cur, PostThreadBinTreeNode<ElemType>*& pre);

	// btΪ���Ķ�����ת�����µ�δ�������ĺ��������������������¶������ĸ�
	PostThreadBinTreeNode<ElemType>* CopyTreeHelp(TriLKBinTreeNode<ElemType>* r);

	//��������������
	PostThreadBinTreeNode<ElemType>* CopyTreeHelp(const PostThreadBinTreeNode<ElemType>* copy);

	// ������rΪ���Ķ�����
	void DestroyHelp(PostThreadBinTreeNode<ElemType>*& r);


public:

	// ��������ģ��
	virtual~PostThreadBinTree();

	// ���������������ĸ�
	PostThreadBinTreeNode<ElemType>* GetRoot() const;

	// ����������������
	void PostThread();

	// �������ĺ������
	void PostOrder(void(*visit)(const ElemType&)) const;

	// ���ƹ��캯��ģ��
	PostThreadBinTree(const PostThreadBinTree<ElemType>& copy);

	// ���ظ�ֵ�����
	PostThreadBinTree<ElemType>& operator=(const PostThreadBinTree<ElemType>& copy);


};

template<class ElemType>
void PostThreadBinTree<ElemType>::PostThreadHelp(PostThreadBinTreeNode<ElemType>* cur, PostThreadBinTreeNode<ElemType>*& pre)
{
	// ��
	if (cur->leftTag == CHILD_PTR)
		cur = cur->leftChild;

	// ��
	if (cur->rightTag == CHILD_PTR)
		cur = cur->rightChild;

	// ��(��cur��pre�Ĳ���)
	if (cur->leftChild == NULL) {
		cur->leftChild = pre;
		cur->leftTag = THREAD_PTR;
	}

	if (pre != NULL && pre->rightChild == NULL) {
		pre->rightChild = cur;
		pre->rightTag = THREAD_PTR;
	}


	// ��pre�ĸ���
	pre = cur;
}

template<class ElemType>
PostThreadBinTreeNode<ElemType>* PostThreadBinTree<ElemType>::CopyTreeHelp(TriLKBinTreeNode<ElemType>* r)
{
	if (r == NULL) return;

	PostThreadBinTreeNode<ElemType>* cur = new PostThreadBinTreeNode<ElemType>(r->data);

	cur->leftChild = CopyTreeHelp(r->leftChild);
	if (cur->leftChild) cur->leftChild->parent = cur;

	cur->rightChild = CopyTreeHelp(r->rightChild);
	if (cur->rightChild) cur->rightChild->parent = cur;

	return cur;

}

template<class ElemType>
PostThreadBinTreeNode<ElemType>* PostThreadBinTree<ElemType>::CopyTreeHelp(const PostThreadBinTreeNode<ElemType>* copy)
{
	if (copy == NULL) return;

	PostThreadBinTreeNode<ElemType>* cur = new PostThreadBinTreeNode<ElemType>(copy->data);
	cur->leftTag = copy->leftTag;
	cur->rightTag = copy->rightTag;

	cur->leftChild = CopyTreeHelp(copy->leftChild);
	if (cur->leftChild) cur->leftChild->parent = cur;

	cur->rightChild = CopyTreeHelp(copy->rightChild);
	if (cur->rightChild) cur->rightChild->parent = cur;

	return cur;
}

template<class ElemType>
void PostThreadBinTree<ElemType>::DestroyHelp(PostThreadBinTreeNode<ElemType>*& r)
{
	if (r == NULL) return;

	DestroyHelp(r->leftChild);
	DestroyHelp(r->rightChild);
	delete r;
	r = NULL;
}


template<class ElemType>
PostThreadBinTree<ElemType>::~PostThreadBinTree()
{
	DestroyHelp(root);
}

template<class ElemType>
PostThreadBinTreeNode<ElemType>* PostThreadBinTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
void PostThreadBinTree<ElemType>::PostThread()
{
	PostThreadBinTreeNode<ElemType>* pre = NULL;

	PostThreadHelp(root, pre);

	if (pre->rightChild == NULL)
		pre->rightTag = THREAD_PTR;

}

template<class ElemType>
void PostThreadBinTree<ElemType>::PostOrder(void(*visit)(const ElemType&)) const
{
	if (root == NULL) return;

	PostThreadBinTreeNode<ElemType>* cur = root; 

	// ���������whileѭ��������cur����������еĵ�һ�����
	while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR) {
		if (cur->leftTag == CHILD_PTR) cur = cur->leftChild; // ��������
		else cur = cur->rightChild;                          // �����ӣ��������Һ���
	}

	/*
		������һ��㣬���cur����ָ��Ϊ����������Ϊcur->rightChild������
		(1) �����cur�Ƕ������ĸ�������Ϊ��
		(2) ���cur����˫�׵��Һ��ӻ�����˫�׵�������˫��û��������������Ϊ˫�׽��
		(3) ���cur����˫�׵����ӣ�����˫������������������Ϊ˫�׵��������а���������г��ĵ�һ����㣬����˫�׵��������������µĽ��
	*/

	while (cur != NULL) {

		(*visit)(cur->data);

		PostThreadBinTreeNode<ElemType>* pt = cur->parent; // ��ǰ����˫��

		if (cur->rightTag == THREAD_PTR) {
			// ��ָ��Ϊ���������Ϊcur->rightChild
			cur = cur->rightChild;
		}
		else if (cur == root) {
			// ���cur�Ƕ������ĸ�������Ϊ��
			cur = NULL;
		}
		else if (pt->rightChild == cur || (pt->leftChild == cur && pt->rightTag == THREAD_PTR)) {
			// ���cur����˫�׵��Һ��ӻ�����˫�׵�������˫��û��������������Ϊ˫�׽��
			cur = pt;
		}
		else {
			// ���cur����˫�׵����ӣ�����˫������������������Ϊ˫�׵��������а���������г��ĵ�һ����㣬����˫�׵��������������µĽ��
			cur = pt->rightChild;

			while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR) {
				if (cur->leftTag == CHILD_PTR) cur = cur->leftChild; // ��������
				else cur = cur->rightChild;                          // �����ӣ��������Һ���
			}
		}


	}


}


template<class ElemType>
PostThreadBinTree<ElemType>::PostThreadBinTree(const PostThreadBinTree<ElemType>& copy)
{
	CopyTreeHelp(copy.GetRoot());
}


template<class ElemType>
PostThreadBinTree<ElemType>& PostThreadBinTree<ElemType>::operator=(const PostThreadBinTree<ElemType>& copy)
{
	if (this == &copy) return *this;

	DestroyHelp(root);

	CopyTreeHelp(copy.GetRoot());

	return *this;
}
