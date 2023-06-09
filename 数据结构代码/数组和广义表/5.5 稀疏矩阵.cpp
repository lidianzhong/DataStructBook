#include <iostream>
#define DEFAULT_SIZE 100
using namespace std;

// 三元组类模板
template<class ElemType>
struct Triple
{
	int row, col;
	ElemType value;

	// 构造函数模板
	Triple();
	Triple(int r, int c, ElemType v);
};

template<class ElemType>
Triple<ElemType>::Triple()
{
	row = 0;
	col = 0;
	value = ElemType();
}

template<class ElemType>
Triple<ElemType>::Triple(int r, int c, ElemType v)
{
	row = r;
	col = c;
	value = v;
}


// 稀疏矩阵三元组顺序表类模板
template<class ElemType>
class TriSparseMatrix
{
protected:
	Triple<ElemType>* triElems;
	int maxSize;
	int rows, cols, num;

public:
	TriSparseMatrix(int rs = DEFAULT_SIZE, int cs = DEFAULT_SIZE, int size = DEFAULT_SIZE);
	~TriSparseMatrix();
	int GetRows() const;
	int GetCols() const;
	int GetNum() const;
	bool SetElem(int r, int c, const ElemType& v);
	bool GetElem(int r, int c, ElemType& v);
	void Traverse(void (*visit)(const Triple<ElemType>&)) const;
	TriSparseMatrix(const TriSparseMatrix<ElemType>& copy); // 复制构造函数模板
	TriSparseMatrix<ElemType>& operator=(const TriSparseMatrix<ElemType>& copy); // 重载赋值运算符

public:
	// 将稀疏矩阵sourse转置成稀疏矩阵dest的简单算法
	void SimpleTranspose(const TriSparseMatrix<ElemType>& sourse, TriSparseMatrix<ElemType>& dest);

	// 将稀疏矩阵source转置成稀疏矩阵dest的快速算法
	void FastTranspose(const TriSparseMatrix<ElemType>& sourse, TriSparseMatrix<ElemType>& dest);
};

template<class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(int rs, int cs, int size)
{
	rows = rs;
	cols = cs;
	num = 0;
	maxSize = size;
	triElems = new Triple<ElemType>[size];
}

template<class ElemType>
TriSparseMatrix<ElemType>::~TriSparseMatrix()
{
	delete[] triElems;
}

template<class ElemType>
int TriSparseMatrix<ElemType>::GetRows() const
{
	return rows;
}

template<class ElemType>
int TriSparseMatrix<ElemType>::GetCols() const
{
	return cols;
}

template<class ElemType>
int TriSparseMatrix<ElemType>::GetNum() const
{
	return num;
}

template<class ElemType>
bool TriSparseMatrix<ElemType>::SetElem(int r, int c, const ElemType& v)
{
	if (r < 1 || r > rows || c < 1 || c > cols) return false; // 下标范围错

	int j; // 表示查找元素在稀疏数组中可能的位置

	for (j = num - 1; j >= 0 && (r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--); // 二分法查找
	
	if (j >= 0 && triElems[j].row == r && triElems[j].col == c) { // 查找成功

		if (v == 0) { // 如果v为0，就将这个位置变为0，然后删掉这个位置

			for (int i = j + 1; i < num; i++) triElems[i - 1] = triElems[i];

			num--;
		}
		else { // 如果v不为0，就赋值v给value
			triElems[j].value = v;
		}

		return true;

	}
	else if (v != 0 && num < maxSize) { // 没找到，但是符合条件，那就插入到稀疏数组中
		for (int i = num - 1; i > j; i--) triElems[i + 1] = triElems[i];
		triElems[j + 1].row = r;
		triElems[j + 1].col = c;
		triElems[j + 1].value = v;
		num++;
		return true;
	}

	else return false; // 走到这是num < maxSize,内存满了


}

template<class ElemType>
bool TriSparseMatrix<ElemType>::GetElem(int r, int c, ElemType& v)
{
	if (r < 1 || r > rows || c <1 || c > cols) return false; // 下标范围错

	int j;
	
	for (j = num - 1; j >= 0 && (r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--); // 二分法查找

	if (j >= 0 && triElems[j].row == r && triElems[j].col == c) { // 查找成功

		v = triElems[j].value;
		return true;
}
	else {
		return false;
	}

	
}

template<class ElemType>
void TriSparseMatrix<ElemType>::Traverse(void(*visit)(const Triple<ElemType>&)) const
{
	for (int pos = 0; pos < num; pos++)
		(*visit)(triElems[pos]);
}

template<class ElemType>
TriSparseMatrix<ElemType>::TriSparseMatrix(const TriSparseMatrix<ElemType>& copy)
{
	maxSize = copy.maxSize;
	rows = copy.rows;
	cols = copy.cols;
	num = copy.num;

	for (int pos = 0; pos < GetNum(); pos++) {
		triElems[pos] = copy.triElems[pos];
	}
}

template<class ElemType>
TriSparseMatrix<ElemType>& TriSparseMatrix<ElemType>::operator=(const TriSparseMatrix<ElemType>& copy)
{
	if (this == &copy) return *this;

	delete[] triElems;
	triElems = new Triple<ElemType>[copy.maxSize];


	maxSize = copy.maxSize;
	rows = copy.rows;
	cols = copy.cols;
	num = copy.num;

	for (int pos = 0; pos < GetNum(); pos++) {
		triElems[pos] = copy.triElems[pos];
	}

}

template<class ElemType>
void TriSparseMatrix<ElemType>::SimpleTranspose(const TriSparseMatrix<ElemType>& sourse, TriSparseMatrix<ElemType>& dest)
{
	dest.rows = sourse.cols;
	dest.cols = sourse.rows;
	dest.num = sourse.num;
	dest.maxSize = sourse.maxSize;
	delete[] dest.triElems;
	dest.triElems = new Triple<ElemType>[dest.maxSize];


	if (dest.num > 0)
	{
		int destPos = 0;
		for (int col = 1; col <= sourse.cols; col++) { // col:1 ~ cols

			for (int soursePos = 1; soursePos < sourse.num; soursePos++) { // sourse 的 col

				if (sourse.triElems[soursePos].col == col) { // find col

					dest.triElems[destPos].row = sourse.triElems[soursePos].col;
					dest.triElems[destPos].col = sourse.triElems[soursePos].row;
					dest.triElems[destPos].value = sourse.triElems[soursePos].value;

					destPos++;

				}

			}

		}
	}

}

template<class ElemType>
void TriSparseMatrix<ElemType>::FastTranspose(const TriSparseMatrix<ElemType>& sourse, TriSparseMatrix<ElemType>& dest)
{

	dest.rows = sourse.cols;
	dest.cols = sourse.rows;
	dest.num = sourse.num;
	dest.maxSize = sourse.maxSize;
	delete[] dest.triElems;
	dest.triElems = new Triple<ElemType>[dest.maxSize];

	int* cNum = new int(sourse.cols);
	int* cPos = new int(sourse.cols);

	if (dest.num > 0)
	{
		for (int col = 1; col <= sourse.cols; col++) cNum[col] = 0;     // 初始化cNum

		for (int soursePos = 1; soursePos <= sourse.num; soursePos++) { // 得到cNum数组
			cNum[sourse.triElems[soursePos].col]++; 
		}

		cPos[1] = 0;
		for (int col = 2; col <= sourse.cols; col++) {                  // 得到cPos数组
			cPos[col] = cPos[col - 1] + cNum[col - 1];
		}


		for (int soursePos = 1; soursePos <= sourse.num; soursePos++) {
			int icol = sourse.triElems[soursePos].col;
			dest.triElems[cPos[icol]].col = sourse.triElems[soursePos].row;
			dest.triElems[cPos[icol]].row = sourse.triElems[soursePos].col;
			dest.triElems[cPos[icol]].value = sourse.triElems[soursePos].value;

			cPos[icol]++;

		}

	}

	delete[] cNum;
	delete[] cPos;

}



// 打印Tripe三元组
template<class ElemType>
void Print_Triple(const Triple<ElemType>& triElem) {
	cout << "row=" << triElem.row << "  col=" << triElem.col << "  value=" << triElem.value << endl;
}