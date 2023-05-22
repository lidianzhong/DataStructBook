#include <iostream>
#include "����͹����/5.5 ϡ�����.cpp"
#include "����͹����/5.6 �������������.cpp"
#include "��/6.1 ˳��洢������.cpp"
#include "��/6.2 ��������.cpp"
#include "��/6.4.2 ���ĺ���˫�ױ�ʾ��.cpp"
#include "��/6.4.3 ���ĺ����ֵܱ�ʾ��.cpp"

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

	cout << "��������������Ϊ��" << endl;
	tree.PreRootOrder(Print);
	cout << endl;

	cout << "���ĺ���������Ϊ��" << endl;
	tree.PostRootOrder(Print);
	cout << endl;

	cout << "���Ĳ���������Ϊ��" << endl;
	tree.LevelOrder(Print);
	cout << endl;

	cout << "���1�ĵ�һ�����ӣ�" << tree.FirstChild(1) << endl;
	
	cout << "���Ľ������Ϊ��" << tree.NodeCount() << endl;

	cout << "���ĸ߶�Ϊ��" << tree.Height() << endl;

	cout << "���Ķ�Ϊ��" << tree.Degree() << endl;

	cout << "------ɾ��һ��1���--------";
	tree.DeleteChild(0, 1);
	cout << endl;

	cout << "��������������Ϊ��" << endl;
	tree.PreRootOrder(Print);
	cout << endl;

	cout << "���ĺ���������Ϊ��" << endl;
	tree.PostRootOrder(Print);
	cout << endl;

	cout << "���Ĳ���������Ϊ��" << endl;
	tree.LevelOrder(Print);
	cout << endl;

	cout << "���1�ĵ�һ�����ӣ�" << tree.FirstChild(1) << endl;
}

void test07()
{
	char items[10] = { 'A','B', 'C', 'D', 'E', 'F', 'G', 'H' };
	int parents[10] = { -1,0,0,0,1,1,3,3 };
	ChildSiblingTree<char> cstree(items, parents, 0, 8);

	cout << "�������������" << endl;
	cstree.PreRootOrder(Print);
	cout << endl;

	cout << "���ĺ��������" << endl;
	cstree.PostRootOrder(Print);
	cout << endl;

	cout << "���Ĳ��������" << endl;
	cstree.LevelOrder(Print);
	cout << endl;

	cout << "------------------------" << endl;
	cout << "ɾ�������cur�ĵ�i������" << endl;
	cstree.DeleteChild(cstree.GetRoot(),1);

	cout << "ɾ������������������" << endl;
	cstree.PreRootOrder(Print);
	cout << endl;

	cout << "ɾ��������ĺ��������" << endl;
	cstree.PostRootOrder(Print);
	cout << endl;


	cout << "ɾ��������Ĳ��������" << endl;
	cstree.LevelOrder(Print);
	cout << endl;

	cout << "ɾ��������Ľ�������" << endl;
	cout << cstree.NodeCount();
	cout << endl;

	cout << "ɾ��������Ķȣ�" << endl;
	cout << cstree.Degree();
	cout << endl;

	cout << "ɾ��������ĸ߶ȣ�" << endl;
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
