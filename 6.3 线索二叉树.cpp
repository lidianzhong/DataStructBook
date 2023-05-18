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
ThreadBinTreeNode<ElemType>::ThreadBinTreeNode() : data(0), leftChild(NULL), rightChild(NULL), leftTag(CHILD_PTR), rightTag(THREAD_PTR) {}


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
		pre->rightChild = pre;
		pre->rightTag = THREAD_PTR;
	}


	pre = cur;


	if (cur->rightTag == NULL)
		// 线索化右子树
		InThreadHelp(cur->rightChild, pre);

}


