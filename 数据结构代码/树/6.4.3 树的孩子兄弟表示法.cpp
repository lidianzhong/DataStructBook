#include <iostream>
#include <queue>

using namespace std;

// 孩子兄弟表示树结点类模板
template <class ElemType>
struct ChildSiblingTreeNode
{
	ElemType data;
	ChildSiblingTreeNode<ElemType>* firstChild; // 指向第一个孩子结点
	ChildSiblingTreeNode<ElemType>* rightSibling; // 指向右兄弟的指针

	ChildSiblingTreeNode(); // 无参数的构造函数
	ChildSiblingTreeNode(ElemType item, ChildSiblingTreeNode<ElemType>* fChild = NULL, ChildSiblingTreeNode<ElemType>* rSibling = NULL); // 有参数的构造函数

};

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode() : firstChild(NULL), rightSibling(NULL) {}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType item, ChildSiblingTreeNode<ElemType>* fChild, ChildSiblingTreeNode<ElemType>* rSibling)
	: data(item), firstChild(fChild), rightSibling(rSibling) {}

// 孩子兄弟表示树类模板
template <class ElemType>
class ChildSiblingTree
{

protected:
	ChildSiblingTreeNode<ElemType>* root; // 指向根结点的指针

	// 辅助函数模板

	// 销毁以r为根的子树
	void DestoryHelp(ChildSiblingTreeNode<ElemType>* &r); 
	// 先根次序遍历以r为根的子树
	void PreRootOrderHelp(ChildSiblingTreeNode<ElemType>* r, void(*visit)(ElemType&)) const; 
	// 后根次序遍历以r为根的子树
	void PostRootOrderHelp(ChildSiblingTreeNode<ElemType>* r, void(*visit)(ElemType&)) const; 
	// 求以r为根的子树的结点个数
	int NodeCountHelp(const ChildSiblingTreeNode<ElemType>* r) const; 
	// 求以r为根的子树的高度
	int HeightHelp(const ChildSiblingTreeNode<ElemType>* r) const;
	// 求以r为根的树的度
	int DegreeHelp(const ChildSiblingTreeNode<ElemType>* r) const;
	// 删除以r为根的树
	void DeleteHelp(ChildSiblingTreeNode<ElemType>* r);
	// 返回cur的双亲
	ChildSiblingTreeNode<ElemType>* ParentHelp(ChildSiblingTreeNode<ElemType>* r, const ChildSiblingTreeNode<ElemType>* cur) const;
	// 复制树
	ChildSiblingTreeNode<ElemType>* CopyTreeHelp(const ChildSiblingTreeNode<ElemType>* r);
	// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r，结点个数为n的树，并返回根结点指针
	ChildSiblingTreeNode<ElemType>* CreateTreeHelp(const ElemType items[], const int parents[], int r, int n);

public:
	// 无参数的构造函数
	ChildSiblingTree();
	// 析构函数模板
	virtual~ChildSiblingTree();
	// 返回树的根
	ChildSiblingTreeNode<ElemType>* GetRoot() const;
	// 判断树是否为空
	bool IsEmpty() const;
	// 用e返回结点元素值
	bool GetElem(ChildSiblingTreeNode<ElemType>* cur, ElemType& e) const;
	// 用e更新结点元素值
	bool SetElem(ChildSiblingTreeNode<ElemType>* cur, const ElemType& e);
	// 树的先根序遍历
	void PreRootOrder(void(*visit)(ElemType&)) const;
	// 树的后根序遍历
	void PostRootOrder(void(*visit)(ElemType&)) const;
	// 树的层次遍历
	void LevelOrder(void(*visit)(ElemType&)) const;
	// 求树的结点个数
	int NodeCount() const;
	// 返回结点cur的度
	int NodeDegree(ChildSiblingTreeNode<ElemType>* cur) const;
	// 返回树的度
	int Degree()const;
	// 返回树结点cur的第一个孩子
	ChildSiblingTreeNode<ElemType>* FirstChild(const ChildSiblingTreeNode<ElemType>* cur) const;
	// 返回树结点cur的右兄弟
	ChildSiblingTreeNode<ElemType>* RightSibling(const ChildSiblingTreeNode<ElemType>* cur) const;
	// 返回树结点cur的双亲
	ChildSiblingTreeNode<ElemType>* Parent(const ChildSiblingTreeNode<ElemType>* cur) const;
	// 将数据元素插入为cur的第i个孩子
	bool InsertChild(ChildSiblingTreeNode<ElemType>* cur, int i, const ElemType& e);
	// 删除树结点cur的第i个子树
	bool DeleteChild(ChildSiblingTreeNode<ElemType>* cur, int i);
	// 返回树的高度
	int Height() const;
	// 建立以数据元素e为根的树
	ChildSiblingTree(const ElemType& e);
	// 复制构造函数模板
	ChildSiblingTree(const ChildSiblingTree<ElemType>& copy);
	// 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r，结点个数为n的树
	ChildSiblingTree(const ElemType items[], const int parents[], int r, int n);
	// 建立以r为根的树
	ChildSiblingTree(ChildSiblingTreeNode<ElemType>* r);
	// 赋值运算符重载
	ChildSiblingTree<ElemType>& operator=(const ChildSiblingTree<ElemType>& copy);
};

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::CopyTreeHelp(const ChildSiblingTreeNode<ElemType>* r)
{
	if (r == NULL) return NULL;

	ChildSiblingTreeNode<ElemType>* newPtr = new ChildSiblingTreeNode<ElemType>(r->data);

	newPtr->firstChild = CopyTreeHelp(r->firstChild);
	newPtr->rightSibling = CopyTreeHelp(r->rightSibling);

	return newPtr;

}

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::CreateTreeHelp(const ElemType items[], const int parents[], int r, int n)
{
	bool isfirst = true;

	ChildSiblingTreeNode<ElemType>* newPtr = NULL, *tmpPtr = NULL;


	for (int pos = 0; pos < n; pos++) {
		if (parents[pos] == r) {
			if (isfirst) {
				tmpPtr = new ChildSiblingTreeNode<ElemType>(items[pos]);
				newPtr = tmpPtr;
				tmpPtr->firstChild = CreateTreeHelp(items, parents, pos, n);
				isfirst = false;
			}
			else {
				tmpPtr->rightSibling = new ChildSiblingTreeNode<ElemType>(items[pos]);
				tmpPtr = tmpPtr->rightSibling;
				tmpPtr->firstChild = CreateTreeHelp(items, parents, pos, n);
			}
		}
	}

	return newPtr;

}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree()
{
	root = NULL;
}

template<class ElemType>
ChildSiblingTree<ElemType>::~ChildSiblingTree()
{
	DeleteHelp(root);
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
bool ChildSiblingTree<ElemType>::IsEmpty() const
{
	return root == NULL;
}

template<class ElemType>
bool ChildSiblingTree<ElemType>::GetElem(ChildSiblingTreeNode<ElemType>* cur, ElemType& e) const
{
	if (cur == NULL) return false;

	e = cur->data;

	return true;
}

template<class ElemType>
bool ChildSiblingTree<ElemType>::SetElem(ChildSiblingTreeNode<ElemType>* cur, const ElemType& e)
{
	if (cur == NULL) return false;

	cur->data = e;

	return true;
}

template<class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrder(void(*visit)(ElemType&)) const
{
	PreRootOrderHelp(root, visit);
}

template<class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrder(void(*visit)(ElemType&)) const
{
	PostRootOrderHelp(root, visit);
}

template<class ElemType>
void ChildSiblingTree<ElemType>::LevelOrder(void(*visit)(ElemType&)) const
{
	if (IsEmpty()) return;

	queue<ChildSiblingTreeNode<ElemType>*> q;
	
	q.push(root);

	while (!q.empty()) {

		ChildSiblingTreeNode<ElemType>* curPtr = q.front();

		(*visit)(curPtr->data);
		q.pop();

		if (curPtr->firstChild != NULL)
			q.push(curPtr->firstChild);

		if (curPtr->firstChild != NULL)
		{
			for (ChildSiblingTreeNode<ElemType>* tmpPtr = curPtr->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
			{
				q.push(tmpPtr);
			}

		}

	}



}

template<class ElemType>
int ChildSiblingTree<ElemType>::NodeCount() const
{
	return NodeCountHelp(root);
}

template<class ElemType>
int ChildSiblingTree<ElemType>::NodeDegree(ChildSiblingTreeNode<ElemType>* cur) const
{

	int count = 0;

	for (ChildSiblingTreeNode<ElemType>* tmpPtr = cur->firstChild; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
	{
		count++;
	}

	return count;
}

template<class ElemType>
int ChildSiblingTree<ElemType>::Degree() const
{
	return DegreeHelp(root);
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::FirstChild(const ChildSiblingTreeNode<ElemType>* cur) const
{
	return cur->firstChild;
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::RightSibling(const ChildSiblingTreeNode<ElemType>* cur) const
{
	return cur->rightSibling;
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::Parent(const ChildSiblingTreeNode<ElemType>* cur) const
{
	return ParentHelp(root,cur);
}

template<class ElemType>
bool ChildSiblingTree<ElemType>::InsertChild(ChildSiblingTreeNode<ElemType>* cur, int i, const ElemType& e)
{
	if (cur == NULL || i <= 0 || i > NodeDegree(cur) + 1) return false;


	if (i == 1) {
		cur->firstChild = new ChildSiblingTreeNode<ElemType>(e, NULL, cur->firstChild);
	}
	else {
		ChildSiblingTreeNode<ElemType>* tmpPtr = cur->firstChild;
		for (int pos = 0; pos < i - 2; pos++) {
			tmpPtr = tmpPtr->rightSibling;
		}
		tmpPtr->rightSibling = new ChildSiblingTreeNode<ElemType>(e, NULL, tmpPtr->rightSibling);
	}

	return true;
}

template<class ElemType>
bool ChildSiblingTree<ElemType>::DeleteChild(ChildSiblingTreeNode<ElemType>* cur, int i)
{
	if (cur == NULL || i <= 0 || i > NodeDegree(cur) + 1) return false;

	if (i == 1) {
		ChildSiblingTreeNode<ElemType>* tmpPtr = cur->firstChild;
		cur->firstChild = tmpPtr->rightSibling;
		DestoryHelp(cur->firstChild);
	}
	else {
		ChildSiblingTreeNode<ElemType>* prevPtr = cur->firstChild;
		for (int pos = 0; pos < i - 2; pos++) prevPtr = prevPtr->rightSibling;
		ChildSiblingTreeNode<ElemType>* tmpPtr = prevPtr->rightSibling;
		prevPtr->rightSibling = tmpPtr->rightSibling;
		DestoryHelp(tmpPtr);
	}

	return true;
}

template<class ElemType>
int ChildSiblingTree<ElemType>::Height() const
{
	return HeightHelp(root);
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType& e)
{
	root = new ChildSiblingTreeNode<ElemType>(e);
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ChildSiblingTree<ElemType>& copy)
{
	root = CopyTreeHelp(copy.GetRoot());
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(const ElemType items[], const int parents[], int r, int n)
{
	if (n >= 1)
	{
		root = new ChildSiblingTreeNode<ElemType>(items[0]);
		root->firstChild = CreateTreeHelp(items, parents, 0, n);
	}
}

template<class ElemType>
ChildSiblingTree<ElemType>::ChildSiblingTree(ChildSiblingTreeNode<ElemType>* r)
{
	root = r;
}

template<class ElemType>
ChildSiblingTree<ElemType>& ChildSiblingTree<ElemType>::operator=(const ChildSiblingTree<ElemType>& copy)
{
	if (&copy == this) return *this;

	delete[] root;

	CopyTreeHelp(root);

	return *this;
}

template<class ElemType>
void ChildSiblingTree<ElemType>::DestoryHelp(ChildSiblingTreeNode<ElemType>*& r)
{
	if (r == NULL) return;


	for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
	{
		DestoryHelp(r->firstChild);
	}


	ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild;

	while (tmpPtr != NULL) {
		ChildSiblingTreeNode<ElemType>* prevPtr = tmpPtr;
		tmpPtr = tmpPtr->rightSibling;
		delete prevPtr;
	}

}

template<class ElemType>
void ChildSiblingTree<ElemType>::PreRootOrderHelp(ChildSiblingTreeNode<ElemType>* r, void(*visit)(ElemType&)) const
{
	if (r == NULL) return;

	(*visit)(r->data);

	PreRootOrderHelp(r->firstChild, visit);

	if (r->firstChild != NULL)
	{
		for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
		{
			PreRootOrderHelp(tmpPtr, visit);
		}

	}



}

template<class ElemType>
void ChildSiblingTree<ElemType>::PostRootOrderHelp(ChildSiblingTreeNode<ElemType>* r, void(*visit)(ElemType&)) const
{
	if (r == NULL) return;


	PreRootOrderHelp(r->firstChild, visit);

	if (r->firstChild != NULL)
	{
		for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
		{
			PreRootOrderHelp(tmpPtr, visit);
		}

	}

	(*visit)(r->data);

}

template<class ElemType>
int ChildSiblingTree<ElemType>::NodeCountHelp(const ChildSiblingTreeNode<ElemType>* r) const
{
	if (r == 0) return 0;

	int count = 0;

	if (r->firstChild != NULL)
	{
		for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
		{
			count += NodeCountHelp(tmpPtr);
		}
	}

	return count + NodeCountHelp(r->firstChild) + 1;

}

template<class ElemType>
int ChildSiblingTree<ElemType>::HeightHelp(const ChildSiblingTreeNode<ElemType>* r) const
{
	if (r == NULL) return 0;

	int height = HeightHelp(r->firstChild);

	if (r->firstChild != NULL)
	{
		for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
		{
			int tmpheight = HeightHelp(tmpPtr);
			height = tmpheight > height ? tmpheight : height;
		}
	}

	return height + 1;

}

template<class ElemType>
int ChildSiblingTree<ElemType>::DegreeHelp(const ChildSiblingTreeNode<ElemType>* r) const
{
	if (r == NULL) return 0;

	int degree = 0;

	if (r->firstChild != NULL)
	{
		degree++;
		for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
		{
			degree++;
		}
	}

	int firstdegree = DegreeHelp(r->firstChild);
	degree = firstdegree > degree ? firstdegree : degree;

	if (r->firstChild != NULL)
	{
		for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild->rightSibling; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
		{
			int rightdegree = DegreeHelp(tmpPtr);
			degree = rightdegree > degree ? rightdegree : degree;
		}
	}

	return degree;

}

template<class ElemType>
void ChildSiblingTree<ElemType>::DeleteHelp(ChildSiblingTreeNode<ElemType>* r)
{
	DestoryHelp(r);
	delete r;
	r = NULL;
}

template<class ElemType>
ChildSiblingTreeNode<ElemType>* ChildSiblingTree<ElemType>::ParentHelp(ChildSiblingTreeNode<ElemType>* r, const ChildSiblingTreeNode<ElemType>* cur) const
{

	for (ChildSiblingTreeNode<ElemType>* tmpPtr = r->firstChild; tmpPtr != NULL; tmpPtr = tmpPtr->rightSibling)
	{
		if (tmpPtr == cur) return r;
		ParentHelp(tmpPtr, cur);
	}

	return NULL;

}
