#include<iostream>
#include "��/6.2 ��������.cpp"
using namespace std;

enum PointerTagType {CHILD_PTR, THREAD_PTR}; // ָ���־����

// �����������������ģ��
template<class ElemType>
struct ThreadBinTreeNode
{
	ElemType data; 
	ThreadBinTreeNode<ElemType>* leftChild;
	ThreadBinTreeNode<ElemType>* rightChild;
	PointerTagType leftTag, rightTag; // ���ұ�־

	// ���캯��ģ��
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


// ����������������ģ��
template<class ElemType>
class InThreadBinTree
{

protected:
	ThreadBinTreeNode<ElemType>* root;

	// ��������ģ��

	// ������������curΪ���Ķ�����
	void InThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre);

	// btΪ���Ķ�����ת�����µ�δ�����������������������������¶������ĸ�
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(BinTreeNode<ElemType>* r);

	//��������������
	ThreadBinTreeNode<ElemType>* CopyTreeHelp(const ThreadBinTreeNode<ElemType>* copy);

	// ������rΪ���Ķ�����
	void DestroyHelp(ThreadBinTreeNode<ElemType>*& r);

public:

	// �ɶ���������������������������ת�����캯��ģ��
	InThreadBinTree(const BinaryTree<ElemType>& bt);

	// ��������ģ��
	virtual~InThreadBinTree();

	// ���������������ĸ�
	ThreadBinTreeNode<ElemType>* GetRoot() const;

	// ����������������
	void InThread();

	// ���������������
	void InOrder(void(*visit)(const ElemType&)) const;

	// ���ƹ��캯��ģ��
	InThreadBinTree(const InThreadBinTree<ElemType>& copy);

	// ���ظ�ֵ�����
	InThreadBinTree<ElemType>& operator=(const InThreadBinTree<ElemType>& copy);

};

template<class ElemType>
void InThreadBinTree<ElemType>::InThreadHelp(ThreadBinTreeNode<ElemType>* cur, ThreadBinTreeNode<ElemType>*& pre)
{
	// �����ս�㷵��
	if (cur == NULL) return; 

	if (cur->leftTag == CHILD_PTR)
		// ������������
		InThreadHelp(cur->leftChild, pre);


	// �Ե�ǰcur���Ĳ���
	if (cur->leftChild == NULL) {
		// cur�����ӣ�������
		cur->leftChild = pre;
		cur->leftTag = THREAD_PTR;
	}

	// ��pre���Ĳ���
	if (pre != NULL && pre->rightChild == NULL) {
		// pre���Һ��ӣ�������
		pre->rightChild = pre;
		pre->rightTag = THREAD_PTR;
	}


	pre = cur;


	if (cur->rightTag == NULL)
		// ������������
		InThreadHelp(cur->rightChild, pre);

}


