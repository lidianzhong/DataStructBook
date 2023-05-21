#include<iostream>
#include <queue>
using namespace std;

#define DEFAULT_SIZE 100

enum StatusCode { SUCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED };

// 双亲法表示树结点类模板
template<class ElemType>
struct ParentTreeNode
{
	ElemType data;
	int parent;

	ParentTreeNode();
	ParentTreeNode(ElemType item, int pt = -1);

};

template<class ElemType>
ParentTreeNode<ElemType>::ParentTreeNode() : data(0), parent(-1) {}

template<class ElemType>
ParentTreeNode<ElemType>::ParentTreeNode(ElemType item, int pt)
	: data(item), parent(pt) {}


// 双亲法表示树类模板
template<class ElemType>
class ParentTree
{

protected:
	ParentTreeNode<ElemType>* nodes; // 存储树结点
	int maxSize;                     // 树结点最大个数
	int root, num;                   // 根的位置及结点数

	// 辅助函数模板

	// 先根序遍历
	void PreRootOrderHelp(int r, void(*visit)(const ElemType&)) const;

	// 后根序遍历
	void PostRootOrderHelp(int r, void(*visit)(const ElemType&)) const;

	// 返回以r为根的树的高
	int HeightHelp(int r) const; 

	// 删除以r为根的树
	void DeleteHelp(int r);

public:
	ParentTree();
	virtual~ParentTree();
	int GetRoot() const;
	bool Empty() const;
	StatusCode GetElem(int cur, ElemType& e) const;
	StatusCode SetElem(int cur, const ElemType& e);
	void PreRootOrder(void(*visit)(const ElemType&)) const;                             // 树的先序遍历
	void PostRootOrder(void(*visit)(const ElemType&)) const;                            // 树的后序遍历
	void LevelOrder(void(*visit)(const ElemType&)) const;                               // 树的层序遍历
	int NodeCount() const;                                                              // 返回树的结点个数
	int NodeDegree(int cur) const;                                                      // 返回结点cur的度
	int Degree() const;                                                                 // 返回树的度
	int FirstChild(int cur) const;                                                      // 返回结点cur的第一个孩子
	int RightSibling(int cur) const;                                                    // 返回结点cur的右兄弟
	int Parent(int cur) const;                                                          // 返回结点cur的双亲
	bool InsertChild(int cur, int i, const ElemType& e);                                // 将数据元素插入为cur的第i个孩子
	bool DeleteChild(int cur, int i);                                                   // 删除cur的第i颗子树
	int Height() const;                                                                 // 返回树的高
	ParentTree(const ElemType& e, int size = DEFAULT_SIZE);                             // 建立以数据元素e为根的树
	ParentTree(const ParentTree<ElemType>& copy);                                       // 复制构造函数模板
	ParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE); // 建立数据元素为items[],对应结点双亲为parents[],根结点位置为r,结点个数为n的树
	ParentTree<ElemType>& operator=(const ParentTree<ElemType>& copy);                  // 重载赋值运算符
};

template<class ElemType>
void ParentTree<ElemType>::PreRootOrderHelp(int r, void(*visit)(const ElemType&)) const
{
	if (r == -1) return;

	(*visit)(nodes[r].data);

	for (int i = 0; i < num; i++) 
		if (nodes[i].parent == r)
			PreRootOrderHelp(i, visit);

}

template<class ElemType>
void ParentTree<ElemType>::PostRootOrderHelp(int r, void(*visit)(const ElemType&)) const
{
	if (r == -1) return;

	for (int i = 0; i < num; i++)
		if (nodes[i].parent == r)
			PostRootOrderHelp(i, visit);

	(*visit)(nodes[r].data);

}

template<class ElemType>
int ParentTree<ElemType>::HeightHelp(int r) const
{
	int height = 0;

	for (int i = 0; i < num; i++)
		if (nodes[i].parent == r)
			height = HeightHelp(i) > height ? HeightHelp(i) : height;

	return height + 1;

}

template<class ElemType>
void ParentTree<ElemType>::DeleteHelp(int r)
{
	for (int i = 0; i < num; i++)
		if (nodes[i].parent == r)
			DeleteHelp(i);

	for (int i = r; i < num - 1; i++)
		nodes[i] = nodes[i + 1];
}

template<class ElemType>
ParentTree<ElemType>::ParentTree() : maxSize(DEFAULT_SIZE), root(-1), num(0) 
{
	nodes = new ParentTreeNode<ElemType>[DEFAULT_SIZE];
}

template<class ElemType>
ParentTree<ElemType>::~ParentTree()
{
	delete[] nodes;
}

template<class ElemType>
int ParentTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
bool ParentTree<ElemType>::Empty() const
{
	return num == 0;
}

template<class ElemType>
StatusCode ParentTree<ElemType>::GetElem(int cur, ElemType& e) const
{
	if (cur < 0 || cur >= num) return RANGE_ERROR;

	e = nodes[cur].data;

	return SUCESS;
}

template<class ElemType>
StatusCode ParentTree<ElemType>::SetElem(int cur, const ElemType& e)
{
	if (cur < 0 || cur >= num) return RANGE_ERROR;

	nodes[cur].data = e;

	return SUCESS;
}

template<class ElemType>
void ParentTree<ElemType>::PreRootOrder(void(*visit)(const ElemType&)) const
{
	PreRootOrderHelp(root, visit);
}

template<class ElemType>
void ParentTree<ElemType>::PostRootOrder(void(*visit)(const ElemType&)) const
{
	PostRootOrderHelp(root, visit);
}

template<class ElemType>
void ParentTree<ElemType>::LevelOrder(void(*visit)(const ElemType&)) const
{
	if (root == -1) return;

	queue<int> q;
	q.push(0);

	while (q.empty()) {
		int r = q.front();
		(*visit)(nodes[r].data);
		q.pop();

		for (int i = 0; i < num; i++)
			if (nodes[i].parent == r)
				q.push(i);
	}

}

template<class ElemType>
int ParentTree<ElemType>::NodeCount() const
{
	return num;
}

template<class ElemType>
int ParentTree<ElemType>::NodeDegree(int cur) const
{
	int count = 0;
	for (int i = 0; i < num; i++)
		if (nodes[i].parent == cur)
			count++;

	return count;
}

template<class ElemType>
int ParentTree<ElemType>::Degree() const
{
	if (root == -1) return 0;

	int count = 0;
	int* arr = new int[num + 1];
	memset(arr, 0, sizeof(arr));

	for (int i = 1; i < num; i++) {
		arr[nodes[i].parent]++;
	}

	for (int i = 0; i < num; i++)
		if (arr[i] > count) 
			count = arr[i];

	return count;

}

template<class ElemType>
int ParentTree<ElemType>::FirstChild(int cur) const
{
	for (int i = 0; i < num; i++)
		if (nodes[i].parent == cur)
			return i;

	return -1;
}

template<class ElemType>
int ParentTree<ElemType>::RightSibling(int cur) const
{
	for (int i = 0; i < num; i++)
		if (i > cur && nodes[i].parent == nodes[cur].parent)
			return i;

	return -1;
}

template<class ElemType>
int ParentTree<ElemType>::Parent(int cur) const
{
	return nodes[cur].parent;
}

template<class ElemType>
bool ParentTree<ElemType>::InsertChild(int cur, int i, const ElemType& e)
{
	if (cur < 0 || cur >= num) return false;

	if (i <= 0 || (cur + i - 2 > 0 && nodes[cur + i - 2].parent != cur)) return false;

	for (int i = num; i > cur + i - 1; i--)
		nodes[i] = nodes[i - 1];
	nodes[cur + i - 1] = ParentTreeNode<ElemType>(e, cur);

	num++;

	return true;
}

template<class ElemType>
bool ParentTree<ElemType>::DeleteChild(int cur, int i)
{
	if (cur < 0 || cur >= num) return false;

	if (i > 0 || cur + i - 1 >= num || nodes[cur + i - 1].parent != cur) return false;

	DeleteHelp(cur + i - 1);
}

template<class ElemType>
int ParentTree<ElemType>::Height() const
{
	HeightHelp(root);
}

template<class ElemType>
ParentTree<ElemType>::ParentTree(const ElemType& e, int size)
{
	maxSize = size;
	nodes = new ParentTreeNode<ElemType>[maxSize];
	root = 0;
	nodes[root] = ParentTreeNode<ElemType>(e, -1);
	num = 1;
}

template<class ElemType>
ParentTree<ElemType>::ParentTree(const ParentTree<ElemType>& copy)
{
	maxSize = copy.maxSize;
	root = copy.root;
	num = copy.num;

	nodes = new ParentTreeNode<ElemType>[maxSize];
	for (int i = 0; i < num; i++)
		nodes[i] = copy.nodes[i];

}

template<class ElemType>
ParentTree<ElemType>::ParentTree(ElemType items[], int parents[], int r, int n, int size)
{
	maxSize = size;
	nodes = new ParentTreeNode<ElemType>[maxSize];
	root = r;
	num = n;
	for (int i = 0; i < num; i++) {
		nodes[root + i] = ParentTreeNode<ElemType>(items[i], parents[i]);
	}
}

template<class ElemType>
ParentTree<ElemType>& ParentTree<ElemType>::operator=(const ParentTree<ElemType>& copy)
{
	if (&copy == this) return *this;

	maxSize = copy.maxSize;
	root = copy.root;
	num = copy.num;

	delete[] nodes;

	nodes = new ParentTreeNode<ElemType>[maxSize];
	for (int i = 0; i < num; i++)
		nodes[i] = copy.nodes[i];

	return *this;

}


