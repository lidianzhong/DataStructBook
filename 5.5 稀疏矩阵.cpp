#include <iostream>
#define DEFAULT_SIZE 100
using namespace std;

// ��Ԫ����ģ��
template<class ElemType>
struct Triple
{
	int row, col;
	ElemType value;

	// ���캯��ģ��
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


// ϡ�������Ԫ��˳�����ģ��
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
	TriSparseMatrix(const TriSparseMatrix<ElemType>& copy); // ���ƹ��캯��ģ��
	TriSparseMatrix<ElemType>& operator=(const TriSparseMatrix<ElemType>& copy); // ���ظ�ֵ�����

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
	if (r < 1 || r > rows || c < 1 || c > cols) return false; // �±귶Χ��

	int j; // ��ʾ����Ԫ����ϡ�������п��ܵ�λ��

	for (j = num - 1; j >= 0 && (r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--); // ���ַ�����
	
	if (j >= 0 && triElems[j].row == r && triElems[j].col == c) { // ���ҳɹ�

		if (v == 0) { // ���vΪ0���ͽ����λ�ñ�Ϊ0��Ȼ��ɾ�����λ��

			for (int i = j + 1; i < num; i++) triElems[i - 1] = triElems[i];

			num--;
		}
		else { // ���v��Ϊ0���͸�ֵv��value
			triElems[j].value = v;
		}

		return true;

	}
	else if (v != 0 && num < maxSize) { // û�ҵ������Ƿ����������ǾͲ��뵽ϡ��������
		for (int i = num - 1; i > j; i--) triElems[i + 1] = triElems[i];
		triElems[j + 1].row = r;
		triElems[j + 1].col = c;
		triElems[j + 1].value = v;
		num++;
		return true;
	}

	else return false; // �ߵ�����num < maxSize,�ڴ�����


}

template<class ElemType>
bool TriSparseMatrix<ElemType>::GetElem(int r, int c, ElemType& v)
{
	if (r < 1 || r > rows || c <1 || c > cols) return false; // �±귶Χ��

	int j;
	
	for (j = num - 1; j >= 0 && (r < triElems[j].row || r == triElems[j].row && c < triElems[j].col); j--); // ���ַ�����

	if (j >= 0 && triElems[j].row == r && triElems[j].col == c) { // ���ҳɹ�

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

// ��ӡTripe��Ԫ��
template<class ElemType>
void Print_Triple(const Triple<ElemType>& triElem) {
	cout << "row=" << triElem.row << "  col=" << triElem.col << "  value=" << triElem.value << endl;
}