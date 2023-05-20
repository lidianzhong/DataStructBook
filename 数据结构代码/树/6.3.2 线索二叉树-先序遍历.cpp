#include<iostream>
#include "树/6.2 二叉链表.cpp"
using namespace std;

enum PointerTagType { CHILD_PTR, THREAD_PTR }; // 指针标志类型

// 线索化二叉树结点类模板
template<class ElemType>
struct ThreadBinTreeNode
{
	ElemType data;
	ThreadBinTreeNode<ElemType>* leftChild;
	ThreadBinTreeNode<ElemType>* rightChild;
	PointerTagType leftTag, rightTag; // 左右标志

	// 构造函数模板
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


// 先序线索二叉树类模板
template<class ElemType>
class PreThreadBinTree
{

protected:
	ThreadBinTreeNode<ElemType>* root;

	// 辅助函数模板

	// 先序线索化以cur为根的二叉树
	void PreThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre);

	// bt为根的二叉树转化成新的未线索化的先序线索二叉树，返回新二叉树的根
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(BinTreeNode<ElemType>* r);

	//复制线索二叉树
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy);

	// 销毁以r为根的二叉树
	void DestroyHelp(ThreadBinTreeNode<ElemType>*& r);

public:

	// 由二叉树构造先序线索二叉树——转换构造函数模板
	PreThreadBinTree(const BinaryTree<ElemType>& bt);

	// 析构函数模板
	virtual~PreThreadBinTree();

	// 返回线索二叉树的根
	ThreadBinTreeNode<ElemType>* GetRoot() const;

	// 先序线索化二叉树
	void PreThread();

	// 二叉树的先序遍历
	void PreOrder(void(*visit)(const ElemType&)) const;

	// 复制构造函数模板
	PreThreadBinTree(const PreThreadBinTree<ElemType>& copy);

	// 重载赋值运算符
	PreThreadBinTree<ElemType>& operator=(const PreThreadBinTree<ElemType>& copy);

};





template<class ElemType>
void PreThreadBinTree<ElemType>::PreThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre)
{
	// 遇到空结点就返回
	if (cur == NULL) return;

	// 根
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

	// pre 更新
	pre = cur;

	// 左
	if (cur->leftTag == CHILD_PTR)
	{
		PreThreadHelp(cur->leftChild, pre);
	}
	

	// 右
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

	ThreadBinTreeNode<ElemType>* cur = root; // 根结点为先序遍历的第一个结点

	while (cur != NULL)
	{
		(*visit)(cur->data);

		if (cur->rightTag == THREAD_PTR) {
			// 如果右链为线索，后继为cur->rightChild
			cur = cur->rightChild;
		}
		else {
			// 右链为孩子
			if (cur->leftTag == CHILD_PTR) {
				// cur有左孩子，则左孩子为后继
				cur = cur->leftChild;
			}
			else {
				// cur无左孩子，则右孩子为后继
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




