#include <iostream>
#include <queue>

using namespace std;

// �����ֵܱ�ʾ�������ģ��
template <class ElemType>
struct ChildSiblingTreeNode
{
	ElemType data;
	ChildSiblingTreeNode<ElemType>* firstChild; // ָ���һ�����ӽ��
	ChildSiblingTreeNode<ElemType>* rightSibling; // ָ�����ֵܵ�ָ��

	ChildSiblingTreeNode(); // �޲����Ĺ��캯��
	ChildSiblingTreeNode(ElemType item, ChildSiblingTreeNode<ElemType>* fChild = NULL, ChildSiblingTreeNode<ElemType>* rSibling = NULL); // �в����Ĺ��캯��

};

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode() : firstChild(NULL), rightSibling(NULL) {}

template<class ElemType>
ChildSiblingTreeNode<ElemType>::ChildSiblingTreeNode(ElemType item, ChildSiblingTreeNode<ElemType>* fChild, ChildSiblingTreeNode<ElemType>* rSibling)
	: data(item), firstChild(fChild), rightSibling(rSibling) {}

// �����ֵܱ�ʾ����ģ��
template <class ElemType>
class ChildSiblingTree
{

protected:
	ChildSiblingTreeNode<ElemType>* root; // ָ�������ָ��

	// ��������ģ��

	// ������rΪ��������
	void DestoryHelp(ChildSiblingTreeNode<ElemType>* &r); 
	// �ȸ����������rΪ��������
	void PreRootOrderHelp(ChildSiblingTreeNode<ElemType>* r, void(*visit)(ElemType&)) const; 
	// ������������rΪ��������
	void PostRootOrderHelp(ChildSiblingTreeNode<ElemType>* r, void(*visit)(ElemType&)) const; 
	// ����rΪ���������Ľ�����
	int NodeCountHelp(const ChildSiblingTreeNode<ElemType>* r) const; 
	// ����rΪ���������ĸ߶�
	int HeightHelp(const ChildSiblingTreeNode<ElemType>* r) const;
	// ����rΪ�������Ķ�
	int DegreeHelp(const ChildSiblingTreeNode<ElemType>* r) const;
	// ɾ����rΪ������
	void DeleteHelp(ChildSiblingTreeNode<ElemType>* r);
	// ����cur��˫��
	ChildSiblingTreeNode<ElemType>* ParentHelp(ChildSiblingTreeNode<ElemType>* r, const ChildSiblingTreeNode<ElemType>* cur) const;
	// ������
	ChildSiblingTreeNode<ElemType>* CopyTreeHelp(const ChildSiblingTreeNode<ElemType>* r);
	// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr��������Ϊn�����������ظ����ָ��
	ChildSiblingTreeNode<ElemType>* CreateTreeHelp(const ElemType items[], const int parents[], int r, int n);

public:
	// �޲����Ĺ��캯��
	ChildSiblingTree();
	// ��������ģ��
	virtual~ChildSiblingTree();
	// �������ĸ�
	ChildSiblingTreeNode<ElemType>* GetRoot() const;
	// �ж����Ƿ�Ϊ��
	bool IsEmpty() const;
	// ��e���ؽ��Ԫ��ֵ
	bool GetElem(ChildSiblingTreeNode<ElemType>* cur, ElemType& e) const;
	// ��e���½��Ԫ��ֵ
	bool SetElem(ChildSiblingTreeNode<ElemType>* cur, const ElemType& e);
	// �����ȸ������
	void PreRootOrder(void(*visit)(ElemType&)) const;
	// ���ĺ�������
	void PostRootOrder(void(*visit)(ElemType&)) const;
	// ���Ĳ�α���
	void LevelOrder(void(*visit)(ElemType&)) const;
	// �����Ľ�����
	int NodeCount() const;
	// ���ؽ��cur�Ķ�
	int NodeDegree(ChildSiblingTreeNode<ElemType>* cur) const;
	// �������Ķ�
	int Degree()const;
	// ���������cur�ĵ�һ������
	ChildSiblingTreeNode<ElemType>* FirstChild(const ChildSiblingTreeNode<ElemType>* cur) const;
	// ���������cur�����ֵ�
	ChildSiblingTreeNode<ElemType>* RightSibling(const ChildSiblingTreeNode<ElemType>* cur) const;
	// ���������cur��˫��
	ChildSiblingTreeNode<ElemType>* Parent(const ChildSiblingTreeNode<ElemType>* cur) const;
	// ������Ԫ�ز���Ϊcur�ĵ�i������
	bool InsertChild(ChildSiblingTreeNode<ElemType>* cur, int i, const ElemType& e);
	// ɾ�������cur�ĵ�i������
	bool DeleteChild(ChildSiblingTreeNode<ElemType>* cur, int i);
	// �������ĸ߶�
	int Height() const;
	// ����������Ԫ��eΪ������
	ChildSiblingTree(const ElemType& e);
	// ���ƹ��캯��ģ��
	ChildSiblingTree(const ChildSiblingTree<ElemType>& copy);
	// ��������Ԫ��Ϊitems[],��Ӧ���˫��Ϊparents[],�����λ��Ϊr��������Ϊn����
	ChildSiblingTree(const ElemType items[], const int parents[], int r, int n);
	// ������rΪ������
	ChildSiblingTree(ChildSiblingTreeNode<ElemType>* r);
	// ��ֵ���������
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
