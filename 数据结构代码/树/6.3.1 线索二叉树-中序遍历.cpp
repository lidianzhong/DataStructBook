#include<iostream>
#include "树/6.2 二叉链表.cpp"
using namespace std;

enum PointerTagType {CHILD_PTR, THREAD_PTR}; // 指针标志类型

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


// 中序线索二叉树类模板
template<class ElemType>
class InThreadBinTree
{

protected:
	ThreadBinTreeNode<ElemType>* root;

	// 辅助函数模板

	// 中序线索化以cur为根的二叉树
	void InThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre);

	// bt为根的二叉树转化成新的未线索化的中序线索二叉树，返回新二叉树的根
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(BinTreeNode<ElemType>* r);

	//复制线索二叉树
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy);

	// 销毁以r为根的二叉树
	void DestroyHelp(ThreadBinTreeNode<ElemType>*& r);

public:

	// 由二叉树构造中序线索二叉树——转换构造函数模板
	InThreadBinTree(const BinaryTree<ElemType>& bt);

	// 析构函数模板
	virtual~InThreadBinTree();

	// 返回线索二叉树的根
	ThreadBinTreeNode<ElemType>* GetRoot() const;

	// 中序线索化二叉树
	void InThread();

	// 二叉树的中序遍历
	void InOrder(void(*visit)(const ElemType&)) const;

	// 复制构造函数模板
	InThreadBinTree(const InThreadBinTree<ElemType>& copy);

	// 重载赋值运算符
	InThreadBinTree<ElemType>& operator=(const InThreadBinTree<ElemType>& copy);

};


template<class ElemType>
void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre)
{
	// 遇到空结点返回
	if (cur == NULL) return; 

	if (cur->leftTag == CHILD_PTR)
		// 线索化左子树
		InThreadHelp(cur->leftChild, pre);


	// 对当前cur结点的操作
	if (cur->leftChild == NULL) {
		// cur无左孩子，加线索
		cur->leftChild = pre;
		cur->leftTag = THREAD_PTR;
	}

	// 对pre结点的操作
	if (pre != NULL && pre->rightChild == NULL) {
		// pre无右孩子，加线索
		pre->rightChild = cur;
		pre->rightTag = THREAD_PTR;
	}


	pre = cur;


	if (cur->rightTag == CHILD_PTR)
		// 线索化右子树
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
	if (pre->rightChild == NULL) // pre为中序序列中最后一个结点
		pre->rightTag = THREAD_PTR; // 如无右孩子，则加线索标记
}


template<class ElemType>
void InThreadBinTree<ElemType>::InOrder(void(*visit)(const ElemType&)) const
{
	if (root == NULL) return;

	ThreadBinTreeNode<ElemType>* cur = root;
	while (cur->leftTag == CHILD_PTR) // 查找最左侧的结点，此结点为中序序列的第一个结点
		cur = cur->leftChild;
	while (cur != NULL)
	{
		(*visit)(cur->data);

		if (cur->rightTag == THREAD_PTR) {
			// 右链为线索，后继为cur->rightChild
			cur = cur->rightChild;
		}
		else {
			// 右链为孩子，cur右子树最左侧的结点为后继
			cur = cur->rightChild;
			while (cur->leftTag == CHILD_PTR)
				cur = cur->leftChild; // 查找原cur右子树最左侧的结点
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




