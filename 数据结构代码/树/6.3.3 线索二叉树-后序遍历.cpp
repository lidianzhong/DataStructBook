#include<iostream>
#include "树/6.2 二叉链表.cpp"
using namespace std;

enum PointerTagType { CHILD_PTR, THREAD_PTR }; // 指针标志类型

// 三叉链表二叉树结点类模板
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


// 线索二叉树结点类模板
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


// 后序线索二叉树类模板
template<class ElemType>
class PostThreadBinTree
{

protected:
	PostThreadBinTreeNode<ElemType>* root;
	
	// 辅助函数模板

	// 先序线索化以cur为根的二叉树
	void PostThreadHelp(PostThreadBinTreeNode<ElemType>* cur, PostThreadBinTreeNode<ElemType>*& pre);

	// bt为根的二叉树转化成新的未线索化的后序线索二叉树，返回新二叉树的根
	PostThreadBinTreeNode<ElemType>* CopyTreeHelp(TriLKBinTreeNode<ElemType>* r);

	//复制线索二叉树
	PostThreadBinTreeNode<ElemType>* CopyTreeHelp(const PostThreadBinTreeNode<ElemType>* copy);

	// 销毁以r为根的二叉树
	void DestroyHelp(PostThreadBinTreeNode<ElemType>*& r);


public:

	// 析构函数模板
	virtual~PostThreadBinTree();

	// 返回线索二叉树的根
	PostThreadBinTreeNode<ElemType>* GetRoot() const;

	// 后序线索化二叉树
	void PostThread();

	// 二叉树的后序遍历
	void PostOrder(void(*visit)(const ElemType&)) const;

	// 复制构造函数模板
	PostThreadBinTree(const PostThreadBinTree<ElemType>& copy);

	// 重载赋值运算符
	PostThreadBinTree<ElemType>& operator=(const PostThreadBinTree<ElemType>& copy);


};

template<class ElemType>
void PostThreadBinTree<ElemType>::PostThreadHelp(PostThreadBinTreeNode<ElemType>* cur, PostThreadBinTreeNode<ElemType>*& pre)
{
	// 左
	if (cur->leftTag == CHILD_PTR)
		cur = cur->leftChild;

	// 右
	if (cur->rightTag == CHILD_PTR)
		cur = cur->rightChild;

	// 根(对cur和pre的操作)
	if (cur->leftChild == NULL) {
		cur->leftChild = pre;
		cur->leftTag = THREAD_PTR;
	}

	if (pre != NULL && pre->rightChild == NULL) {
		pre->rightChild = cur;
		pre->rightTag = THREAD_PTR;
	}


	// 对pre的更改
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

	// 这个最外层的while循环结束后，cur到达后序序列的第一个结点
	while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR) {
		if (cur->leftTag == CHILD_PTR) cur = cur->leftChild; // 移向左孩子
		else cur = cur->rightChild;                          // 无左孩子，则移向右孩子
	}

	/*
		对于任一结点，如果cur的右指针为线索，则后继为cur->rightChild，否则
		(1) 若结点cur是二叉树的根，其后继为空
		(2) 结点cur是其双亲的右孩子或是其双亲的左孩子且双亲没有右子树，则后继为双亲结点
		(3) 结点cur是其双亲的左孩子，且其双亲有右子树，则其后继为双亲的右子树中按后序遍历列出的第一个结点，即其双亲的右子树中最左下的结点
	*/

	while (cur != NULL) {

		(*visit)(cur->data);

		PostThreadBinTreeNode<ElemType>* pt = cur->parent; // 当前结点的双亲

		if (cur->rightTag == THREAD_PTR) {
			// 右指针为线索，后继为cur->rightChild
			cur = cur->rightChild;
		}
		else if (cur == root) {
			// 结点cur是二叉树的根，其后继为空
			cur = NULL;
		}
		else if (pt->rightChild == cur || (pt->leftChild == cur && pt->rightTag == THREAD_PTR)) {
			// 结点cur是其双亲的右孩子或是其双亲的左孩子且双亲没有右子树，则后继为双亲结点
			cur = pt;
		}
		else {
			// 结点cur是其双亲的左孩子，且其双亲有右子树，则其后继为双亲的右子树中按后序遍历列出的第一个结点，即其双亲的右子树中最左下的结点
			cur = pt->rightChild;

			while (cur->leftTag == CHILD_PTR || cur->rightTag == CHILD_PTR) {
				if (cur->leftTag == CHILD_PTR) cur = cur->leftChild; // 移向左孩子
				else cur = cur->rightChild;                          // 无左孩子，则移向右孩子
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
