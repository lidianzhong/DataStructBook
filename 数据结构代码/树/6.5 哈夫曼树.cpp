#include <iostream>
#include <string>
#include "线性表/2.4链表修改版.cpp"
using namespace std;

// 哈夫曼树结点类模板
template <class WeightType>
struct HuffmanTreeNode
{
	WeightType weight;		// 权数据元素
	unsigned int parent,leftChild,rightChild;	// 双亲和左右孩子结点下标

	// 构造函数模板
	HuffmanTreeNode();
	HuffmanTreeNode(WeightType w,int p = 0, int lChild = 0, int rChild = 0); // 已知权，双亲及左右孩子构造结构 
};

// 哈夫曼树类模板
template <class CharType, class WeightType>
class HuffmanTree
{

protected:
	HuffmanTreeNode<WeightType> *nodes;	// 存储结点信息，nodes[0]未用
	CharType* LeafChars;	// 存储叶子结点的字符信息,LeafChars[0]未用
	LinkList<char>* LeafCharCodes;	// 存储叶子结点的编码信息,LeafCharCodes[0]未用
	int curPos; // 译码时从根节点到叶节点的路径上的当前结点
	int num; // 叶结点个数

	// 辅助函数模板
	
	// 在nodes[1..cur]中选择parent为0且weight最小的两个结点，下标分别为r1和r2
	void Select(int cur, int &r1, int &r2);	
	// 由字符，权值和字符个数构造哈夫曼树
	void CreateHuffmanTree(CharType ch[], WeightType w[], int n);

public:
	// 由字符，权值和字符个数构造哈夫曼树
	HuffmanTree(CharType ch[], WeightType w[], int n); 
	// 析构函数
	virtual ~HuffmanTree();
	// 编码
	LinkList<CharType> EnCode(CharType ch);
	// 译码
	LinkList<CharType> DeCode(LinkList<char> strCode);
	// 复制构造函数模板
	HuffmanTree(const HuffmanTree<CharType, WeightType> &copy);
	// 赋值运算符重载模板
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
	// 求出最小的值
	int firstmin = INT_MAX, firstidx = -1;
	for (int pos = 1; pos <= cur; pos++) {
		if (nodes[pos].parent == 0 && nodes[pos].weight < firstmin) {
			firstmin = nodes[pos].weight;
			firstidx = pos;
		}
	}

	// 求出第二小的值
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
	num = n; // num为叶结点个数
	int m = 2 * n - 1; // m为结点个数

	nodes = new HuffmanTreeNode<WeightType>[m + 1];
	LeafChars = new CharType[n + 1];
	LeafCharCodes = new LinkList<char>[n + 1];

	for (int pos = 1; pos <= n; pos++) {
		// 存储叶结点信息
		nodes[pos].weight = w[pos - 1];
		LeafChars[pos] = ch[pos - 1];
	}

	for (int pos = n + 1; pos <= m; pos++) {
		// 建立哈夫曼树
		int r1, r2;
		Select(pos - 1, r1, r2); // nodes[1~pos-1]中选择双亲为0，权值最小的两个结点r1,r2

		// 合并以r1，r2为根的树
		nodes[r1].parent = nodes[r2].parent = pos;
		nodes[pos].leftChild = r1;
		nodes[pos].rightChild = r2;
		nodes[pos].weight = nodes[r1].weight + nodes[r2].weight;
	}

	for (int pos = 1; pos <= n; pos++) {
		// 求n个叶结点字符的编码
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
	throw "非法字符，无法编码!";
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

