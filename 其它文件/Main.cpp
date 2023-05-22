#include <iostream>
#include "数组和广义表/5.5 稀疏矩阵.cpp"
#include "数组和广义表/5.6 引用数法广义表.cpp"
#include "树/6.1 顺序存储二叉树.cpp"
#include "树/6.2 二叉链表.cpp"
#include "树/6.4.2 树的孩子双亲表示法.cpp"
#include "树/6.4.3 树的孩子兄弟表示法.cpp"

using namespace std;

template<class ElemType>
void Print(ElemType data)
{
	cout << data << ' ';
}


void test01()
{
	TriSparseMatrix<int> Matrix(5,6);
	Matrix.SetElem(1, 3, 2);
	Matrix.SetElem(2, 6, 8);
	Matrix.SetElem(3, 1, 1);
	Matrix.SetElem(3, 3, 3);
	Matrix.SetElem(5, 1, 4);
	Matrix.SetElem(3, 3, 6);


	int row = Matrix.GetRows();
	int col = Matrix.GetCols();
	int value;
	Matrix.GetElem(3, 3, value);

	cout << row << ' ' << col << ' ' << value << endl;
	cout << "num=" << Matrix.GetNum() << endl;
}

void test02()
{
	TriSparseMatrix<int> Matrix;
	Matrix.SetElem(5, 1, 4);
	Matrix.SetElem(1, 3, 2);
	Matrix.SetElem(2, 6, 8);
	Matrix.SetElem(3, 1, 1);
	Matrix.SetElem(3, 3, 3);
	Matrix.SetElem(3, 3, 6);

	Matrix.Traverse(Print_Triple);
}

void test03()
{
	RefGenList<char> list;
	RefGenList<char> list1;
	list.Input();
	list1 = list;
	list1.Show();
}

void test04()
{
	SqBinaryTree<char> tree('A');
	tree.InsertLeftChild(1,'B');
	tree.InsertLeftChild(2, 'D');
	tree.InsertRightChild(4, 'F');
	tree.InsertRightChild(1, 'C');
	tree.InsertRightChild(3, 'E');


	tree.PreOrder(Print);
	cout << endl;
	tree.InOrder(Print);
	cout << endl;
	tree.PostOrder(Print);
	cout << endl;
	tree.LevelOrder(Print);
}


void test05()
{
	BinTreeNode<char>* root;

	char pre[] = "ABCDEFGHI";
	char in[] = "DCBAGFHEI";

	CreateBinaryTreeHelp<char>(root, pre, in, 0, int(strlen(pre) - 1), 0, int(strlen(in) - 1));

	BinaryTree<char> tree(root);


	tree.LevelOrder(Print);
}

void test06()
{
	ChildParentTree<char> tree('A');
	tree.InsertChild(0, 1, 'B');
	tree.InsertChild(0, 2, 'C');
	tree.InsertChild(0, 3, 'D');
	tree.InsertChild(1, 1, 'E');
	tree.InsertChild(1, 2, 'F');
	tree.InsertChild(3, 1, 'G');
	tree.InsertChild(3, 2, 'H');

	cout << "树的先序遍历结果为：" << endl;
	tree.PreRootOrder(Print);
	cout << endl;

	cout << "树的后序遍历结果为：" << endl;
	tree.PostRootOrder(Print);
	cout << endl;

	cout << "树的层序遍历结果为：" << endl;
	tree.LevelOrder(Print);
	cout << endl;

	cout << "结点1的第一个孩子：" << tree.FirstChild(1) << endl;
	
	cout << "树的结点数量为：" << tree.NodeCount() << endl;

	cout << "树的高度为：" << tree.Height() << endl;

	cout << "树的度为：" << tree.Degree() << endl;

	cout << "------删除一个1结点--------";
	tree.DeleteChild(0, 1);
	cout << endl;

	cout << "树的先序遍历结果为：" << endl;
	tree.PreRootOrder(Print);
	cout << endl;

	cout << "树的后序遍历结果为：" << endl;
	tree.PostRootOrder(Print);
	cout << endl;

	cout << "树的层序遍历结果为：" << endl;
	tree.LevelOrder(Print);
	cout << endl;

	cout << "结点1的第一个孩子：" << tree.FirstChild(1) << endl;
}

void test07()
{
	char items[10] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H' };
	int parents[10] = { -1,0,0,0,1,1,3,3 };
	ChildSiblingTree<char> cstree(items, parents, 0, 8);

	cout << "树的先序遍历：" << endl;
	cstree.PreRootOrder(Print);
	cout << endl;

	cout << "树的后序遍历：" << endl;
	cstree.PostRootOrder(Print);
	cout << endl;

	cout << "树的层序遍历：" << endl;
	cstree.LevelOrder(Print);
	cout << endl;

	cout << "------------------------" << endl;
	cout << "删除树结点cur的第i个子树" << endl;
	cstree.DeleteChild(cstree.GetRoot(),1);

	cout << "删除后的树的先序遍历：" << endl;
	cstree.PreRootOrder(Print);
	cout << endl;

	cout << "删除后的树的后序遍历：" << endl;
	cstree.PostRootOrder(Print);
	cout << endl;


	cout << "删除后的树的层序遍历：" << endl;
	cstree.LevelOrder(Print);
	cout << endl;

	cout << "删除后的树的结点个数：" << endl;
	cout << cstree.NodeCount();
	cout << endl;

	cout << "删除后的树的度：" << endl;
	cout << cstree.Degree();
	cout << endl;

	cout << "删除后的树的高度：" << endl;
	cout << cstree.Height();
	cout << endl;
}

int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	// test05();
	//test06();

	test07();

	return 0;
}
