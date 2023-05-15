#include<iostream>
using namespace std;

#ifndef __SQ_BIN_TREE_NODE_TAG_TYPE__
#define __SQ_BIN_TREE_NODE_TAG_TYPE__
enum SqBinTreeNodeTagType { EMPTY_NODE, DATA_NODE };
#endif 

#define DEFAULT_SIZE 100

// ˳��洢�����������ģ��
template<class ElemType>
struct SqBinTreeNode
{
	ElemType data;
	SqBinTreeNodeTagType tag;

	SqBinTreeNode() : tag(EMPTY_NODE) {}
	SqBinTreeNode(ElemType item, SqBinTreeNodeTagType tg = EMPTY_NODE) : data(item), tag(tg) {}

};


// ˳��洢��������ģ��
template<class ElemType>
class SqBinaryTree
{

protected:
	int maxSize;
	SqBinTreeNode<ElemType>* elems;
	int root;


	// ��������ģ��
	void InOrderHelp(int cur, void(*visit)(const ElemType&)) const;
	void PreOrderHelp(int cur, void(*visit)(const ElemType&)) const;
	void PostOrderHelp(int cur, void(*visit)(const ElemType&)) const;
	int HeightHelp(int cur) const;

public:
	SqBinaryTree();                                       // �޲����Ĺ��캯��ģ��
	virtual~SqBinaryTree();
	int GetRoot() const;                                  // ���ض������ĸ�
	bool NodeEmpty(int cur) const;                        // �жϽ��cur�Ƿ�Ϊ��
	bool GetItem(int cur, ElemType& e) const;             // ���ؽ��cur��Ԫ��ֵ 
	bool SetElem(int cur, const ElemType& e);             // �����cur��ֵ��Ϊe
	bool Empty() const;                                   // �ж϶������Ƿ�Ϊ��
	void InOrder(void(*visit)(const ElemType&)) const;    // ���������������
	void PreOrder(void(*visit)(const ElemType&)) const;   // ���������������
	void PostOrder(void(*visit)(const ElemType&)) const;  // �������ĺ������
	void LevelOrder(void(*visit)(const ElemType&)) const; // �������Ĳ�α���
	int NodeCount() const;                                // ��������Ľ�����
	int LeftChild(const int cur) const;                   // ���ض��������cur������
	int RightChild(const int cur) const;                  // ���ض��������cur���Һ���
	int Parent(const int cur) const;                      // ���ض��������cur��˫��
	void InsertLeftChild(int cur, const ElemType& e);     // ��������
	void InsertRightChild(int cur, const ElemType& e);    // �����Һ��� 
	void DeleteLeftChild(int cur);                        // ɾ��������
	void DeleteRightChild(int cur);                       // ɾ��������
	int Height() const;                                   // ��������ĸ�
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
	if (cur >= maxSize) return false; // ���������±귶Χ
	if (NodeEmpty(cur)) return false; // ���Ϊ����

	e = elems[cur].data;

	return true;
}

template<class ElemType>
bool SqBinaryTree<ElemType>::SetElem(int cur, const ElemType& e)
{
	if (cur >= maxSize) return false;
	if (NodeEmpty(cur)) return false; // ���Ϊ����

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
	// ��������ʵ�֣��൱�ڹ����������
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
	// ��������ʵ�֣��൱�ڹ����������
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

