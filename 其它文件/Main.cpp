#include <iostream>
#include "数组和广义表/5.5 稀疏矩阵.cpp"
#include "数组和广义表/5.6 引用数法广义表.cpp"
#include "树/6.1 顺序存储二叉树.cpp"
#include "树/6.2 二叉链表.cpp"

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

int main()
{
	// test01();
	// test02();
	// test03();
	// test04();
	test05();

	return 0;
}
