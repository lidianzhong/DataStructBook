#include<iostream>
using namespace std;

#ifndef __SQ_BIN_TREE_NODE_TAG_TYPE__
#define __SQ_BIN_TREE_NODE_TAG_TYPE__
enum SqBinTreeNodeTagType { EMPTY_NODE, DATA_NODE };
#endif 

#define DEFAULT_SIZE 100

// 顺序存储二叉树结点类模板
template<class ElemType>
struct SqBinTreeNode
{
	ElemType data;
	SqBinTreeNodeTagType tag;

	SqBinTreeNode() : tag(EMPTY_NODE) {}
	SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE) : data(item), tag(tg) {}

};


// 顺序存储二叉树类模板
template<class ElemType>
class SqBinaryTree
{

protected:
	int maxSize;
	SqBinTreeNode<ElemType>* elems;
	int root;


	// 辅助函数模板
	void InOrderHelp(int cur, void(*visit)(const ElemType&)) const;
	void PreOrderHelp(int cur, void(*visit)(const ElemType&)) const;
	void PostOrderHelp(int cur, void(*visit)(const ElemType&)) const;
	int HeightHelp(int cur) const;

public:
	SqBinaryTree();                                       // 无参数的构造函数模板
	virtual~SqBinaryTree();
	int GetRoot() const;                                  // 返回二叉树的根
	bool NodeEmpty(int cur) const;                        // 判断结点cur是否为空
	bool GetItem(int cur, ElemType& e) const;             // 返回结点cur的元素值 
	bool SetElem(int cur, const ElemType& e);             // 将结点cur的值置为e
	bool Empty() const;                                   // 判断二叉树是否为空
	void InOrder(void(*visit)(const ElemType&)) const;    // 二叉树的中序遍历
	void PreOrder(void(*visit)(const ElemType&)) const;   // 二叉树的先序遍历
	void PostOrder(void(*visit)(const ElemType&)) const;  // 二叉树的后序遍历
	void LevelOrder(void(*visit)(const ElemType&)) const; // 二叉树的层次遍历
	int NodeCount() const;                                // 求二叉树的结点个数
	int LeftChild(const int cur) const;                   // 返回二叉树结点cur的左孩子
	int RightChild(const int cur) const;                  // 返回二叉树结点cur的右孩子
	int Parent(const int cur) const;                      // 返回二叉树结点cur的双亲
	void InsertLeftChild(int cur, const ElemType& e);     // 插入左孩子
	void InsertRightChild(int cur, const ElemType& e);    // 插入右孩子 
	void DeleteLeftChild(int cur);                        // 删除左子树
	void DeleteRightChild(int cur);                       // 删除右子树
	int Height() const;                                   // 求二叉树的高
	SqBinaryTree(const ElemType& e, int size = DEFAULT_SIZE);
	SqBinaryTree(const SqBinaryTree<ElemType>& copy);
	SqBinaryTree(SqBinTreeNode<ElemType>es[], int r, int size = DEFAULT_SIZE) = delete;
	SqBinaryTree<ElemType>& operator=(const SqBinaryTree<ElemType>& copy) = delete;

};

template<class ElemType>
void SqBinaryTree<ElemType>::InOrderHelp(int cur, void(*visit)(const ElemType&)) const
{

	if (!NodeEmpty(cur))
	{
		InOrderHelp(LeftChild(cur), visit);
		(*visit)(elems[cur].data);
		InOrderHelp(RightChild(cur), visit);
	}

}

template<class ElemType>
void SqBinaryTree<ElemType>::PreOrderHelp(int cur, void(*visit)(const ElemType&)) const
{

	if (!NodeEmpty(cur))
	{
		(*visit)(elems[cur].data);
		PreOrderHelp(LeftChild(cur), visit);
		PreOrderHelp(RightChild(cur), visit);
	}

}

template<class ElemType>
void SqBinaryTree<ElemType>::PostOrderHelp(int cur, void(*visit)(const ElemType&)) const
{

	if (!NodeEmpty(cur))
	{
		PostOrderHelp(LeftChild(cur), visit);
		PostOrderHelp(RightChild(cur), visit);
		(*visit)(elems[cur].data);
	}

}

template<class ElemType>
int SqBinaryTree<ElemType>::HeightHelp(int cur) const
{
	if (NodeEmpty(cur)) return 0;

	int depth = 0;
	int leftdepth = HeightHelp(LeftChild(cur));
	int rightdepth = HeightHelp(RightChild(cur));

	depth = leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;

	return depth;
}

template<class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree()
{
	maxSize = DEFAULT_SIZE;
	elems = new SqBinTreeNode<ElemType>[maxSize];
	root = 1;
}

template<class ElemType>
SqBinaryTree<ElemType>::~SqBinaryTree()
{
	delete[] elems;
}

template<class ElemType>
int SqBinaryTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
bool SqBinaryTree<ElemType>::NodeEmpty(int cur) const
{
	if (cur >= maxSize) return true;
	else if (elems[cur].tag == EMPTY_NODE) return true;
	else return false;
}

template<class ElemType>
bool SqBinaryTree<ElemType>::GetItem(int cur, ElemType& e) const
{
	if (cur >= maxSize) return false; // 超过数组下标范围
	if (NodeEmpty(cur)) return false; // 结点为虚结点

	e = elems[cur].data;

	return true;
}

template<class ElemType>
bool SqBinaryTree<ElemType>::SetElem(int cur, const ElemType& e)
{
	if (cur >= maxSize) return false;
	if (NodeEmpty(cur)) return false; // 结点为虚结点

	elems[cur].data = e;

	return true;
}

template<class ElemType>
bool SqBinaryTree<ElemType>::Empty() const
{
	return elems[root].tag == EMPTY_NODE;
}

template<class ElemType>
void SqBinaryTree<ElemType>::InOrder(void(*visit)(const ElemType&)) const
{
	InOrderHelp(root, visit);
}

template<class ElemType>
void SqBinaryTree<ElemType>::PreOrder(void(*visit)(const ElemType&)) const
{
	PreOrderHelp(root, visit);
}

template<class ElemType>
void SqBinaryTree<ElemType>::PostOrder(void(*visit)(const ElemType&)) const
{
	PostOrderHelp(root, visit);
}

template<class ElemType>
void SqBinaryTree<ElemType>::LevelOrder(void(*visit)(const ElemType&)) const
{
	// 借助队列实现，相当于广度优先搜索
	// Continue...
	int pos = 1;
	while (pos < maxSize)
	{
		if (elems[pos].tag == EMPTY_NODE) cout << " ^ ";
		else cout << ' ' << elems[pos].data << ' ';
		pos++;
	}
}

template<class ElemType>
int SqBinaryTree<ElemType>::NodeCount() const
{
	// 借助队列实现，相当于广度优先搜索
	// Continue...

	// int pos = 1, count = 0;
	// while (pos < maxSize)
	// {
	// 	if (elems[pos].tag == DATA_NODE) count++;
	// }

	//return count;
}

template<class ElemType>
int SqBinaryTree<ElemType>::LeftChild(const int cur) const
{
	return 2 * cur;
}

template<class ElemType>
int SqBinaryTree<ElemType>::RightChild(const int cur) const
{
	return 2 * cur + 1;
}

template<class ElemType>
int SqBinaryTree<ElemType>::Parent(const int cur) const
{
	return cur / 2;
}

template<class ElemType>
void SqBinaryTree<ElemType>::InsertLeftChild(int cur, const ElemType& e)
{
	if (LeftChild(cur) < maxSize && elems[LeftChild(cur)].tag == EMPTY_NODE)
	{
		elems[LeftChild(cur)].data = e;
		elems[LeftChild(cur)].tag = DATA_NODE;
	}
}

template<class ElemType>
void SqBinaryTree<ElemType>::InsertRightChild(int cur, const ElemType& e)
{
	if (RightChild(cur) < maxSize && elems[RightChild(cur)].tag == EMPTY_NODE)
	{
		elems[RightChild(cur)].data = e;
		elems[RightChild(cur)].tag = DATA_NODE;
	}
}

template<class ElemType>
void SqBinaryTree<ElemType>::DeleteLeftChild(int cur)
{

	if (LeftChild(cur) < maxSize && elems[LeftChild(cur)].tag == DATA_NODE)
	{
		elems[LeftChild(cur)].tag == EMPTY_NODE;
	}
}

template<class ElemType>
void SqBinaryTree<ElemType>::DeleteRightChild(int cur)
{
	if (RightChild(cur) < maxSize && elems[RightChild(cur)].tag == DATA_NODE)
	{
		elems[RightChild(cur)].tag == EMPTY_NODE;
	}
}

template<class ElemType>
int SqBinaryTree<ElemType>::Height() const
{
	int maxHeight = 0;


}

template<class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const ElemType& e, int size)
{
	maxSize = size;
	elems = new SqBinTreeNode<ElemType>[maxSize];
	root = 1;


	elems[root].tag = DATA_NODE;
	elems[root].data = e;

}

template<class ElemType>
SqBinaryTree<ElemType>::SqBinaryTree(const SqBinaryTree<ElemType>& copy)
{
	// Continue...
}

