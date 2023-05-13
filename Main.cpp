#include <iostream>
#include "5.5 œ° Ëæÿ’Û.cpp"

using namespace std;


void test01()
{
	TriSparseMatrix<int> Matrix;
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



int main()
{
	//test01();
	test02();


	return 0;
}
