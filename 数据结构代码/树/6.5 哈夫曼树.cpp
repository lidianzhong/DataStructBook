#include <iostream>
#include <string>
#include "���Ա�/2.4�����޸İ�.cpp"
using namespace std;

// �������������ģ��
template <class WeightType>
struct HuffmanTreeNode
{
	WeightType weight;		// Ȩ����Ԫ��
	unsigned int parent,leftChild,rightChild;	// ˫�׺����Һ��ӽ���±�

	// ���캯��ģ��
	HuffmanTreeNode();
	HuffmanTreeNode(WeightType w,int p = 0, int lChild = 0, int rChild = 0); // ��֪Ȩ��˫�׼����Һ��ӹ���ṹ 
};

// ����������ģ��
template <class CharType, class WeightType>
class HuffmanTree
{

protected:
	HuffmanTreeNode<WeightType> *nodes;	// �洢�����Ϣ��nodes[0]δ��
	CharType* LeafChars;	// �洢Ҷ�ӽ����ַ���Ϣ,LeafChars[0]δ��
	LinkList<char>* LeafCharCodes;	// �洢Ҷ�ӽ��ı�����Ϣ,LeafCharCodes[0]δ��
	int curPos; // ����ʱ�Ӹ��ڵ㵽Ҷ�ڵ��·���ϵĵ�ǰ���
	int num; // Ҷ������

	// ��������ģ��
	
	// ��nodes[1..cur]��ѡ��parentΪ0��weight��С��������㣬�±�ֱ�Ϊr1��r2
	void Select(int cur, int &r1, int &r2);	
	// ���ַ���Ȩֵ���ַ����������������
	void CreateHuffmanTree(CharType ch[], WeightType w[], int n);

public:
	// ���ַ���Ȩֵ���ַ����������������
	HuffmanTree(CharType ch[], WeightType w[], int n); 
	// ��������
	virtual ~HuffmanTree();
	// ����
	LinkList<CharType> EnCode(CharType ch);
	// ����
	LinkList<CharType> DeCode(LinkList<char> strCode);
	// ���ƹ��캯��ģ��
	HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);
	// ��ֵ���������ģ��
	HuffmanTree<CharType, WeightType>& operator=(const HuffmanTree<CharType, WeightType> &copy);

};

template<class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode() : parent(0), leftChild(0), rightChild(0) {}

template<class WeightType>
HuffmanTreeNode<WeightType>::HuffmanTreeNode(WeightType w, int p, int lChild, int rChild)
	: weight(0), parent(0), leftChild(lChild), rightChild(rChild) {}

template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::Select(int cur, int& r1, int& r2)
{
	// �����С��ֵ
	int firstmin = INT_MAX, firstidx = -1;
	for (int pos = 1; pos <= cur; pos++) {
		if (nodes[pos].parent == 0 && nodes[pos].weight < firstmin) {
			firstmin = nodes[pos].weight;
			firstidx = pos;
		}
	}

	// ����ڶ�С��ֵ
	int secondmin = INT_MAX, secondidx = -1;
	for (int pos = 1; pos <= cur; pos++) {
		if (nodes[pos].parent == 0 && nodes[pos].weight < secondmin && pos != firstidx) {
			secondmin = nodes[pos].weight;
			secondidx = pos;
		}
	}

	r1 = firstidx;
	r2 = secondidx;
}

template<class CharType, class WeightType>
void HuffmanTree<CharType, WeightType>::CreateHuffmanTree(CharType ch[], WeightType w[], int n)
{
	num = n; // numΪҶ������
	int m = 2 * n - 1; // mΪ������

	nodes = new HuffmanTreeNode<WeightType>[m + 1];
	LeafChars = new CharType[n + 1];
	LeafCharCodes = new LinkList<char>[n + 1];

	for (int pos = 1; pos <= n; pos++) {
		// �洢Ҷ�����Ϣ
		nodes[pos].weight = w[pos - 1];
		LeafChars[pos] = ch[pos - 1];
	}

	for (int pos = n + 1; pos <= m; pos++) {
		// ������������
		int r1, r2;
		Select(pos - 1, r1, r2); // nodes[1~pos-1]��ѡ��˫��Ϊ0��Ȩֵ��С���������r1,r2

		// �ϲ���r1��r2Ϊ������
		nodes[r1].parent = nodes[r2].parent = pos;
		nodes[pos].leftChild = r1;
		nodes[pos].rightChild = r2;
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;
	}

	for (int pos = 1; pos <= n; pos++) {
		// ��n��Ҷ����ַ��ı���
		LinkList<char> charCode;
		for (unsigned int child = pos, parent = nodes[child].parent; parent != 0; child = parent, parent = nodes[child].parent)
		{
			if (nodes[parent].leftChild == child)
				charCode.Insert(1, '0');
			else charCode.Insert(1, '1');
		}
		LeafCharCodes[pos] = charCode;
	}

	curPos = m;
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(CharType ch[], WeightType w[], int n)
{
	CreateHuffmanTree(ch, w, n);
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::~HuffmanTree()
{
	delete[] nodes;
	delete[] LeafChars;
	delete[] LeafCharCodes;
}

template<class CharType, class WeightType>
LinkList<CharType> HuffmanTree<CharType, WeightType>::EnCode(CharType ch)
{
	for (int pos = 1; pos <= num; pos++) {
		if (LeafChars[pos] == ch) return LeafCharCodes[pos];
	}
	throw "�Ƿ��ַ����޷�����!";
}

template<class CharType, class WeightType>
LinkList<CharType> HuffmanTree<CharType, WeightType>::DeCode(LinkList<char> strCode)
{
	LinkList<CharType>charList;

	for (Node<char>* tmpPtr = strCode.GetHead()->next; tmpPtr != NULL; tmpPtr = tmpPtr->next)
	{
		if (tmpPtr->data == '0') curPos = nodes[curPos].leftChild;
		else curPos = nodes[curPos].rightChild;

		if (nodes[curPos].leftChild == 0 && nodes[curPos].rightChild == 0) {
			charList.Insert(charList.Length() + 1, LeafChars[curPos]);
			curPos = 2 * num - 1;
		}
	}

	return charList;
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>::HuffmanTree(const HuffmanTree<CharType, WeightType>& copy)
{
	curPos = copy.curPos;
	num = copy.num;
	nodes = new HuffmanTreeNode<WeightType>[2 * num + 1];
	LeafChars = new CharType[num + 1];
	LeafCharCodes = new LinkList<char>[num + 1];

	for (int pos = 1; pos <= 2 * num - 1; pos++) {
		nodes[pos] = copy.nodes[pos];
	}

	for (int pos = 1; pos <= 2 * num; pos++) {
		LeafChars[pos] = copy.LeafChars[pos];
		LeafCharCodes[pos] = copy.LeafCharCodes[pos];
	}
}

template<class CharType, class WeightType>
HuffmanTree<CharType, WeightType>& HuffmanTree<CharType, WeightType>::operator=(const HuffmanTree<CharType, WeightType>& copy)
{
	if (this == &copy) return;

	delete[] nodes;
	delete[] LeafChars;
	delete[] LeafCharCodes;

	curPos = copy.curPos;
	num = copy.num;
	nodes = new HuffmanTreeNode<WeightType>[2 * num + 1];
	LeafChars = new CharType[num + 1];
	LeafCharCodes = new LinkList<char>[num + 1];

	for (int pos = 1; pos <= 2 * num - 1; pos++) {
		nodes[pos] = copy.nodes[pos];
	}

	for (int pos = 1; pos <= 2 * num; pos++) {
		LeafChars[pos] = copy.LeafChars[pos];
		LeafCharCodes[pos] = copy.LeafCharCodes[pos];
	}

	return *this;
}

