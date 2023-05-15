#include <iostream>
#include <stack>
using namespace std;

// 二叉树结点类模板
template <class ElemType>
struct BinTreeNode
{
	ElemType data;
	BinTreeNode<ElemType> *leftChild;
	BinTreeNode<ElemType> *rightChild;

	// 构造函数模板
	BinTreeNode() : leftChild(NULL), rightChild(NULL) {}
	BinTreeNode(const ElemType& val, BinTreeNode<ElemType>* lChild = NULL, BinTreeNode<ElemType>* rChild = NULL);

};


// 二叉树结点类模板的实现部分
template<class ElemType>
BinTreeNode<ElemType>::BinTreeNode(const ElemType& val, BinTreeNode<ElemType>* lChild, BinTreeNode<ElemType>* rChild)
{
	data = val;
	leftChild = lChild;
	rightChild = rChild;
}


// 二叉树类模板
template <class ElemType>
class BinaryTree
{
protected:
	BinTreeNode<ElemType>* root;

	// 辅助函数模板
	BinTreeNode<ElemType>* CopyTreeHelp(const BinTreeNode<ElemType>* r);                                       // 复制二叉树
	void DestroyHelp(BinTreeNode<ElemType>*& r);                                                               // 销毁以r为根的二叉树
	void PreOrderHelp(const BinTreeNode<ElemType>* r, void(*visit)(const ElemType&)) const;                    // 先序遍历以r为根的二叉树
	void InOrderHelp(const BinTreeNode<ElemType>* r, void(*visit)(const ElemType&)) const;                     // 中序遍历以r为根的二叉树
	void PostOrderHelp(const BinTreeNode<ElemType>* r, void(*visit)(const ElemType&)) const;                   // 后序遍历以r为根的二叉树
	int HeightHelp(const BinTreeNode<ElemType>* r) const;                                                      // 求以r为根的二叉树的高度
	int NodeCountHelp(const BinTreeNode<ElemType>* r) const;                                                   // 求以r为根的二叉树的结点个数
	BinTreeNode<ElemType>* ParentHelp(const BinTreeNode<ElemType>* r, const BinTreeNode<ElemType>* cur) const; // 返回cur的双亲


public:
	BinaryTree();
	virtual~BinaryTree();
	BinTreeNode<ElemType>* GetRoot() const;                                                                    // 返回二叉树的根
	bool IsEmpty() const;                                                                                      // 判断二叉树是否为空
	bool GetElem(const BinTreeNode<ElemType>* cur, ElemType& e) const;                                         // 用e返回结点元素值
	bool SetElem(BinTreeNode<ElemType>* cur, const ElemType& e);                                               // 将结点cur的值置为e
	void InOrder(void(*visit)(const ElemType&)) const;                                                         // 二叉树的中序遍历
	void PreOrder(void(*visit)(const ElemType&)) const;                                                        // 二叉树的先序遍历
	void PostOrder(void(*visit)(const ElemType&)) const;                                                       // 二叉树的后序遍历
	void NonRecurPreOrder(const BinaryTree<ElemType>& bt, void(*visit)(const ElemType&));                      // 二叉树的先序遍历-非递归
	void NonRecurInOrder(const BinaryTree<ElemType>& bt, void(*visit)(const ElemType&));                       // 二叉树的中序遍历-非递归
	void NonRecurPostOrder(const BinaryTree<ElemType>& bt, void(*visit)(const ElemType&));                     // 二叉树的后序遍历-非递归
	void LevelOrder(void(*visit)(const ElemType&)) const;                                                      // 二叉树的层次遍历
	int NodeCount() const;                                                                                     // 求二叉树的结点个数
	BinTreeNode<ElemType>* LeftChild(const BinTreeNode<ElemType>* cur) const;                                  // 返回二叉树结点cur的左孩子
	BinTreeNode<ElemType>* RightChild(const BinTreeNode<ElemType>* cur) const;                                 // 返回二叉树结点cur的右孩子
	BinTreeNode<ElemType>* Parent(const BinTreeNode<ElemType>* cur) const;                                     // 返回二叉树结点的双亲
	void InsertLeftChild(BinTreeNode<ElemType>* cur, const ElemType& e);                                       // 插入左孩子
	void InsertRightChild(BinTreeNode<ElemType>* cur, const ElemType& e);                                      // 插入右孩子
	void DeleteLeftChild(BinTreeNode<ElemType>* cur);                                                          // 删除左子树
	void DeleteRightChild(BinTreeNode<ElemType>* cur);                                                         // 删除右子树
	int Height() const;                                                                                        // 求二叉树的高
	BinaryTree(const ElemType& e);                                                                             // 建立以e为根的二叉树
	BinaryTree(const BinaryTree<ElemType>& copy);                                                              // 复制构造函数模板
	BinaryTree(BinTreeNode<ElemType>* r);                                                                      // 建立以r为根的二叉树
	BinaryTree<ElemType>& operator=(const BinaryTree<ElemType>& copy);                                         // 重载赋值运算符
};


template<class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::CopyTreeHelp(const BinTreeNode<ElemType>* r)
{
	if (r == NULL) return NULL;

	root = new BinTreeNode<ElemType>(r->data);
	root->leftChild = CopyTreeHelp(r->leftChild);
	root->rightChild = CopyTreeHelp(r->rightChild);
}

template<class ElemType>
void BinaryTree<ElemType>::DestroyHelp(BinTreeNode<ElemType>*& r)
{
}

template<class ElemType>
void BinaryTree<ElemType>::PreOrderHelp(const BinTreeNode<ElemType>* r, void(*visit)(const ElemType&)) const
{
	if (r != NULL)
	{
		(*visit)(r->data);
		PreOrderHelp(r->leftChild, visit);
		PreOrderHelp(r->rightChild, visit);
	}
}

template<class ElemType>
void BinaryTree<ElemType>::InOrderHelp(const BinTreeNode<ElemType>* r, void(*visit)(const ElemType&)) const
{
	if (r != NULL)
	{
		InOrderHelp(r->leftChild, visit);
		(*visit)(r->data);
		InOrderHelp(r->rightChild, visit);
	}
}

template<class ElemType>
void BinaryTree<ElemType>::PostOrderHelp(const BinTreeNode<ElemType>* r, void(*visit)(const ElemType&)) const
{
	if (r != NULL)
	{
		PostOrderHelp(r->leftChild, visit);
		PostOrderHelp(r->rightChild, visit);
		(*visit)(r->data);
	}
}

template<class ElemType>
int BinaryTree<ElemType>::HeightHelp(const BinTreeNode<ElemType>* r) const
{
	return 0;
}

template<class ElemType>
int BinaryTree<ElemType>::NodeCountHelp(const BinTreeNode<ElemType>* r) const
{
	return 0;
}

template<class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::ParentHelp(const BinTreeNode<ElemType>* r, const BinTreeNode<ElemType>* cur) const
{
	if (r == NULL) return NULL;

	if (r->leftChild == cur || r->rightChild == cur) return const_cast<BinTreeNode<ElemType>*>(r);
	else 
	{
		BinTreeNode<ElemType>* destPtr;
		destPtr = ParentHelp(r->leftChild, cur);
		if (destPtr != NULL) return destPtr;
		destPtr = ParentHelp(r->rightChild, cur);
		return destPtr;
	}

}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree()
{
	root = NULL;
}

template<class ElemType>
BinaryTree<ElemType>::~BinaryTree()
{
	DestroyHelp(root);
}

template<class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
bool BinaryTree<ElemType>::IsEmpty() const
{
	return root == NULL;
}

template<class ElemType>
bool BinaryTree<ElemType>::GetElem(const BinTreeNode<ElemType>* cur, ElemType& e) const
{
	if (cur == NULL) return false;

	e = cur->data;
	return true;
}

template<class ElemType>
bool BinaryTree<ElemType>::SetElem(BinTreeNode<ElemType>* cur, const ElemType& e)
{
	if (cur == NULL) return false;

	cur->data = e;
	return true;
}

template<class ElemType>
void BinaryTree<ElemType>::InOrder(void(*visit)(const ElemType&)) const
{
	InOrderHelp(root, visit);
}

template<class ElemType>
void BinaryTree<ElemType>::PreOrder(void(*visit)(const ElemType&)) const
{
	PreOrderHelp(root, visit);
}

template<class ElemType>
void BinaryTree<ElemType>::PostOrder(void(*visit)(const ElemType&)) const
{
	PostOrderHelp(root, visit);
}

template<class ElemType>
void BinaryTree<ElemType>::NonRecurPreOrder(const BinaryTree<ElemType>& bt, void(*visit)(const ElemType&))
{
	BinTreeNode<ElemType>* cur = bt.GetRoot();
	stack<BinTreeNode<ElemType>*>s; 

	while (cur != NULL)
	{
		(*visit)(cur->data);
		s.push(cur);

		if (cur->leftChild != NULL)
		{
			cur = cur->leftChild;
		}
		else if (!s.empty())
		{
			while (!s.empty())
			{
				cur = s.top();
				s.pop();
				cur = cur->rightChild;
				if(cur != NULL) break;
			}
		}
		else
		{
			cur = NULL;
		}

	}
}

template<class ElemType>
void BinaryTree<ElemType>::NonRecurInOrder(const BinaryTree<ElemType>& bt, void(*visit)(const ElemType&))
{
	BinTreeNode<ElemType>* cur = bt.root;
	stack<BinTreeNode<ElemType>*> s;

	while (cur != NULL && !s.empty())
	{
		if (cur != NULL)
		{
			s.push(cur);
			cur = cur->leftChild;
		}
		else
		{
			cur = s.top();
			s.pop();
			(*visit)(cur->data);
			cur = cur->rightChild;
		}

	}

}

template<class ElemType>
void BinaryTree<ElemType>::NonRecurPostOrder(const BinaryTree<ElemType>& bt, void(*visit)(const ElemType&))
{
	BinTreeNode<ElemType>* cur = bt.root;
	stack<BinTreeNode<ElemType>*> s;

	BinTreeNode<ElemType>* prev = NULL;

	while (cur != NULL && !s.empty())
	{
		if (cur != NULL)
		{
			s.push(cur);
			cur = cur->leftChild;
		}
		else
		{
			cur = s.top();
			if (cur->rightChild == NULL || cur->rightChild == prev)
			{
				(*visit)(cur->data);
				prev = cur;
				s.pop();
				cur = NULL;
			}
			else 
			{
				cur = cur->rightChild;
			}
		}
	}


}

template<class ElemType>
void BinaryTree<ElemType>::LevelOrder(void(*visit)(const ElemType&)) const
{
}

template<class ElemType>
int BinaryTree<ElemType>::NodeCount() const
{
	return NodeCountHelp(root);
}

template<class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::LeftChild(const BinTreeNode<ElemType>* cur) const
{
	if (cur == NULL) return NULL;
	return cur->leftChild;
}

template<class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::RightChild(const BinTreeNode<ElemType>* cur) const
{
	if (cur == NULL) return NULL;
	return cur->rightChild;
}

template<class ElemType>
BinTreeNode<ElemType>* BinaryTree<ElemType>::Parent(const BinTreeNode<ElemType>* cur) const
{
	if (cur == NULL || cur == root) return NULL;

	return ParentHelp(root, cur);

}

template<class ElemType>
void BinaryTree<ElemType>::InsertLeftChild(BinTreeNode<ElemType>* cur, const ElemType& e)
{
	cur->leftChild = new BinTreeNode<ElemType>(e);
}

template<class ElemType>
void BinaryTree<ElemType>::InsertRightChild(BinTreeNode<ElemType>* cur, const ElemType& e)
{
	cur->rightChild = new BinTreeNode<ElemType>(e);
}

template<class ElemType>
void BinaryTree<ElemType>::DeleteLeftChild(BinTreeNode<ElemType>* cur)
{
	cur->leftChild = NULL;
}

template<class ElemType>
void BinaryTree<ElemType>::DeleteRightChild(BinTreeNode<ElemType>* cur)
{
	cur->rightChild = NULL;
}

template<class ElemType>
int BinaryTree<ElemType>::Height() const
{
	return HeightHelp(root);
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(const ElemType& e)
{
	root = new BinTreeNode<ElemType>(e);
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(const BinaryTree<ElemType>& copy)
{
	CopyTreeHelp(copy.root);
}

template<class ElemType>
BinaryTree<ElemType>::BinaryTree(BinTreeNode<ElemType>* r)
{
	root = new BinTreeNode<ElemType>(r->data, r->leftChild, r->rightChild);
}

template<class ElemType>
BinaryTree<ElemType>& BinaryTree<ElemType>::operator=(const BinaryTree<ElemType>& copy)
{
	if (this == &copy) return *this;

	DestroyHelp(root);
	CopyTreeHelp(copy.root);

	return *this;
}
