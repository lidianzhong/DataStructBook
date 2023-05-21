#include<iostream>
#include "���Ա�/2.4�����޸İ�.cpp"
#include <queue>
using namespace std;

#define DEFAULT_SIZE 100

enum StatusCode { SUCESS, FAIL, UNDER_FLOW, OVER_FLOW, RANGE_ERROR, DUPLICATE_ERROR, NOT_PRESENT, ENTRY_INSERTED, ENTRY_FOUND, VISITED, UNVISITED };

// ����˫�׷���ʾ�������ģ��
template<class ElemType>
struct ChildParentTreeNode
{
	ElemType data;
	LinkList<int> childLKlist;
	int parent;

	ChildParentTreeNode();
	ChildParentTreeNode(ElemType item, int pt = -1);
};

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode() : data(0), parent(-1), childLKlist(LinkList<int>()) {}

template<class ElemType>
ChildParentTreeNode<ElemType>::ChildParentTreeNode(ElemType item, int pt) : data(item), childLKlist(LinkList<int>()), parent(pt) {}


// ����˫�ױ�ʾ������ģ��
template<class ElemType>
class ChildParentTree
{

protected:
	ChildParentTreeNode<ElemType>* nodes;
	int maxSize;
	int root, num;

	// ��������ģ��

	// �ȸ������
	void PreRootOrderHelp(int r, void(*visit)(const ElemType&)) const;

	// ��������
	void PostRootOrderHelp(int r, void(*visit)(const ElemType&)) const;

	// ������rΪ�������ĸ�
	int HeightHelp(int r) const;

	// ɾ����rΪ������
	void DeleteHelp(int r);

public:
	ChildParentTree();
	virtual~ChildParentTree();
	int GetRoot() const;
	bool Empty() const;
	StatusCode GetElem(int cur, ElemType& e) const;
	StatusCode SetElem(int cur, const ElemType& e);
	void PreRootOrder(void(*visit)(const ElemType&)) const;                                       // �����������
	void PostRootOrder(void(*visit)(const ElemType&)) const;                                      // ���ĺ������
	void LevelOrder(void(*visit)(const ElemType&)) const;                                         // ���Ĳ������
	int NodeCount() const;                                                                        // �������Ľ�����
	int NodeDegree(int cur) const;                                                                // ���ؽ��cur�Ķ�
	int Degree() const;                                                                           // �������Ķ�
	int FirstChild(int cur) const;                                                                // ���ؽ��cur�ĵ�һ������
	int RightSibling(int cur) const;                                                              // ���ؽ��cur�����ֵ�
	int Parent(int cur) const;                                                                    // ���ؽ��cur��˫��
	bool InsertChild(int cur, int i, const ElemType& e);                                          // ������Ԫ�ز���Ϊcur�ĵ�i������
	bool DeleteChild(int cur, int i);                                                             // ɾ��cur�ĵ�i������
	int Height() const;                                                                           // �������ĸ�
	ChildParentTree(const ElemType& e, int size = DEFAULT_SIZE);                                  // ����������Ԫ��eΪ������
	ChildParentTree(const ChildParentTree<ElemType>& copy);                                       // ���ƹ��캯��ģ��
	ChildParentTree(ElemType items[], int parents[], int r, int n, int size = DEFAULT_SIZE);      // ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr,������Ϊn����
	ChildParentTree<ElemType>& operator=(const ChildParentTree<ElemType>& copy);                  // ���ظ�ֵ�����
};

template<class ElemType>
void ChildParentTree<ElemType>::PreRootOrderHelp(int r, void(*visit)(const ElemType&)) const
{
	if (r == -1) return;

	(*visit)(nodes[r].data);

	for (Node<int>* tmpPtr = nodes[r].childLKlist.GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		PreRootOrderHelp(tmpPtr->data, visit);
	}

}

template<class ElemType>
void ChildParentTree<ElemType>::PostRootOrderHelp(int r, void(*visit)(const ElemType&)) const
{
	if (root == -1) return;

	for (Node<int>* tmpPtr = nodes[r].childLKlist.GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) 
	{
		PostRootOrderHelp(tmpPtr->data,visit);
	}

	(*visit)(nodes[r].data);
}

template<class ElemType>
int ChildParentTree<ElemType>::HeightHelp(int r) const
{
	int height = 0;

	for (Node<int>* tmpPtr = nodes[r].childLKlist.GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		height = HeightHelp(tmpPtr->data) > height ? HeightHelp(tmpPtr->data) : height;
	}

	return height + 1;
}

template<class ElemType>
void ChildParentTree<ElemType>::DeleteHelp(int r)
{
	LinkList<int>* childlist = &nodes[r].childLKlist;

	for (Node<int>* tmpPtr = childlist->GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		DeleteHelp(tmpPtr->data);
	}

	// ����Ҫɾ���Ľ���������е�λ��
	int pos = 0;
	for (Node<int>* tmpPtr = childlist->GetHead()->next; tmpPtr != NULL && tmpPtr->data <= r; tmpPtr = tmpPtr->next)
		pos++;

	// ��������
	int tmpElem;
	childlist->Delete(pos, tmpElem);

}

template<class ElemType>
ChildParentTree<ElemType>::ChildParentTree() : maxSize(DEFAULT_SIZE), root(-1), num(0) 
{
	nodes = new ChildParentTreeNode<ElemType>[maxSize];
}

template<class ElemType>
ChildParentTree<ElemType>::~ChildParentTree()
{
	for (int i = 0; i < num; i++)
		if (nodes[i].childLKlist.Empty()) {
			nodes[i].childLKlist.Clear();
		}

	delete[] nodes;
}

template<class ElemType>
int ChildParentTree<ElemType>::GetRoot() const
{
	return root;
}

template<class ElemType>
bool ChildParentTree<ElemType>::Empty() const
{
	return num == 0;
}

template<class ElemType>
StatusCode ChildParentTree<ElemType>::GetElem(int cur, ElemType& e) const
{
	if (cur < 0 || cur >= num) return RANGE_ERROR;

	e = nodes[cur].data;

	return SUCESS;
}

template<class ElemType>
StatusCode ChildParentTree<ElemType>::SetElem(int cur, const ElemType& e)
{
	if (cur < 0 || cur >= num) return RANGE_ERROR;

	nodes[cur].data = e;

	return SUCESS;
}

template<class ElemType>
void ChildParentTree<ElemType>::PreRootOrder(void(*visit)(const ElemType&)) const
{
	PreRootOrderHelp(root,visit);
}

template<class ElemType>
void ChildParentTree<ElemType>::PostRootOrder(void(*visit)(const ElemType&)) const
{
	PostRootOrderHelp(root, visit);
}

template<class ElemType>
void ChildParentTree<ElemType>::LevelOrder(void(*visit)(const ElemType&)) const
{
	if (root == -1) return;

	queue<int> q;
	q.push(root);

	while (!q.empty()) {
		int r = q.front();
		(*visit)(nodes[r].data);
		q.pop();

		for (Node<int>* tmpPtr = nodes[r].childLKlist.GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next) 
		{
			q.push(tmpPtr->data);
		}

	}
}

template<class ElemType>
int ChildParentTree<ElemType>::NodeCount() const
{
	return num;
}

template<class ElemType>
int ChildParentTree<ElemType>::NodeDegree(int cur) const
{
	int weight = 0;

	for (Node<int>* tmpPtr = nodes[cur].childLKlist.GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		weight = NodeDegree(tmpPtr->data) > weight ? NodeDegree(tmpPtr->data) : weight;
	}

	return weight + 1;

}

template<class ElemType>
int ChildParentTree<ElemType>::Degree() const
{
	if (root == -1) return 0;

	int degree = 1;

	for (int i = 0; i < num; i++) {
		int newdegree = nodes[i].childLKlist.Length();
		if (newdegree > degree)
			degree = newdegree;
	}

	return degree;
}

template<class ElemType>
int ChildParentTree<ElemType>::FirstChild(int cur) const
{
	if (nodes[cur].childLKlist.Empty()) return -1;

	int e;
	nodes[cur].childLKlist.GetElem(1, e);
	
	return e;
}

template<class ElemType>
int ChildParentTree<ElemType>::RightSibling(int cur) const
{
	int pt = nodes[cur].parent;
	for (Node<int>* tmpPtr = nodes[pt].childLKlist.GetHead()->next; tmpPtr != NULL || tmpPtr->data > cur; tmpPtr = tmpPtr->next)
		return tmpPtr->data;

	return -1;
}

template<class ElemType>
int ChildParentTree<ElemType>::Parent(int cur) const
{
	return nodes[cur].parent;
}

template<class ElemType>
bool ChildParentTree<ElemType>::InsertChild(int cur, int i, const ElemType& e)
{
	if (cur < 0 || cur >= num) return false;

	if (i <= 0 || i > nodes[cur].childLKlist.Length() + 1) return false;

	nodes[cur].childLKlist.InsertTail(num);

	nodes[num] = ChildParentTreeNode<ElemType>(e, cur);

	num++;

}

template<class ElemType>
bool ChildParentTree<ElemType>::DeleteChild(int cur, int i)
{
	if (cur < 0 || cur >= num) return false;
	if (i <= 0 || i > nodes[cur].childLKlist.Length() + 1) return false;


	Node<int>* tmpPtr = nodes[cur].childLKlist.GetHead();
	for (int j = 0; j < i - 1; j++) tmpPtr = tmpPtr->next;
	nodes[tmpPtr->next->data].childLKlist.Clear();

	tmpPtr->next = tmpPtr->next->next;
}

template<class ElemType>
int ChildParentTree<ElemType>::Height() const
{
	return HeightHelp(root);
}

template<class ElemType>
ChildParentTree<ElemType>::ChildParentTree(const ElemType& e, int size)
{
	maxSize = size;
	nodes = new ChildParentTreeNode<ElemType>[maxSize];
	root = 0;
	nodes[root] = ChildParentTreeNode<ElemType>(e, -1);
	num = 1;
}

template<class ElemType>
ChildParentTree<ElemType>::ChildParentTree(const ChildParentTree<ElemType>& copy)
{
	maxSize = copy.maxSize;
	root = copy.root;
	num = copy.num;


	nodes = new ChildParentTreeNode<ElemType>[maxSize];
	for (int i = 0; i < num; i++)
		nodes[i] = copy.nodes[i];
}

template<class ElemType>
ChildParentTree<ElemType>::ChildParentTree(ElemType items[], int parents[], int r, int n, int size)
{
	maxSize = size;
	nodes = new ChildParentTreeNode<ElemType>[maxSize];
	root = r;
	num = n;
	for (int i = 0; i < num; i++) {
		nodes[root + i] = ChildParentTreeNode<ElemType>(items[i], parents[i]);
	}

	for (int i = 1; i < num; i++) {
		int pt = nodes[i].parent;
		nodes[pt].childLKlist.InsertTail(i);
	}
}

template<class ElemType>
ChildParentTree<ElemType>& ChildParentTree<ElemType>::operator=(const ChildParentTree<ElemType>& copy)
{
	if (&copy == this) return *this;

	maxSize = copy.maxSize;
	root = copy.root;
	num = copy.num;

	delete[] nodes;

	nodes = new ChildParentTreeNode<ElemType>[maxSize];
	for (int i = 0; i < num; i++)
		nodes[i] = copy.nodes[i];

	return *this;
}

