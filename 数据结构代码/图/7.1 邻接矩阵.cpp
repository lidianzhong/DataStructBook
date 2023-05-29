#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 100;

// ����ͼ���ٽ������ģ��
template<class ElemType>
class AdjMatrixDirGraph
{

protected:
	int vexNum, edgeNum; // ��������ͱ���
	int** Matrix;        // �ڽӾ���
	ElemType* elems;     // ����Ԫ��
	mutable bool* tag;   // ָ���־�����ָ��

	// ��������ģ��

	// ��������ͼ���ͷ�����ͼռ�õĿռ�
	void DestroyHelp(); 
	// �Ӷ���v�������������������ͼ
	void DFS(int v, void(*visit)(const ElemType& e)) const;
	// �Ӷ���v�������й����������ͼ
	void BFS(int v, void(*visit)(const ElemType&)) const;


public:
	AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE); 
	AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE);
	~AdjMatrixDirGraph();

	// ������ȱ���
	void DFSTraverse(void(*visit)(const ElemType&)) const;

	// ������ȱ���
	void BFSTraverse(void(*visit)(const ElemType&)) const;

	// �󶥵��Ԫ��
	bool GetElem(int v, ElemType& e) const;

	// ���ö����Ԫ��ֵ
	bool SetElem(int v, const ElemType& e);

	// ���ض������
	int GetVexNum() const;

	// ���ر���
	int GetEdgeNum() const;

	// ���ض���vd��һ���ڽӵ�
	int FirstAdjVex(int v) const;

	// ���ض���v1�������v2����һ���ڽӵ�
	int NextAdjVex(int v1, int v2) const;
	 
	// ���붥��Ϊv1��v2�ı�
	void InsertEdge(int v1, int v2);

	// ɾ������Ϊv1��v2�ı�
	void DeleteEdge(int v1, int v2);

	// ���ض���v�ı�־
	bool GetTag(int v) const;

	// ���ö���v�ı�־Ϊval
	void SetTag(int v, bool val) const;

	// ���ƹ��캯��ģ��
	AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType>& copy);

	// ���ظ�ֵ�����
	AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType>& copy);
};

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::DestroyHelp()
{
	delete[] elems;
	delete[] tag;

	for (int iPos = 0; iPos < vexNum + 1; iPos++)
	{
		// �ͷ��ڽӾ������
		delete[] Matrix[iPos];
	}
	delete[] Matrix;
}

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::DFS(int v, void(*visit)(const ElemType& e)) const
{
	tag[v] = true;
	(*visit)(elems[v]);

	for (int i = 1; i < vexNum + 1; ++i) {
		if (Matrix[v][i] == 1 && tag[i] != true)
			DFS(i, visit);
	}
}

#include<queue>
template<class ElemType>
void AdjMatrixDirGraph<ElemType>::BFS(int v, void(*visit)(const ElemType&)) const
{
	queue<int> q;

	tag[v] = true;
	(*visit)(elems[v]);

	q.push(v);
	while (!q.empty()) {
		int curv = q.front();
		q.pop();
		(*visit)(elems[curv]);

		for(int i = 1; i < vexNum + 1; i++)
			if (Matrix[curv][i] == 1 && tag[i] != true) {
				tag[i] = true;
				q.push(i);
			}
	}

}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(ElemType es[], int vertexNum)
	: vexNum(vertexNum), edgeNum(0)
{

	Matrix = new int* [(vexNum + 1) * (vexNum + 1)];
	elems = new ElemType[vexNum + 1];
	tag = new bool[vexNum + 1];

	// ��ʼ��elems����
	for (int i = 0; i < vertexNum; i++)
		elems[i + 1] = es[i];

	// ��ʼ���ڽӾ���
	memset(Matrix, 0, (vexNum + 1) * (vexNum + 1));

	// ��ʼ��tag����
	memset(tag, false, vexNum + 1);
}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum)
	: vexNum(vertexNum), edgeNum(0)
{

	Matrix = new int* [(vexNum + 1) * (vexNum + 1)];
	elems = new ElemType[vexNum + 1];

	tag = new bool[vexNum + 1];

	// ��ʼ���ڽӾ���
	memset(Matrix, 0, (vexNum + 1) * (vexNum + 1));

	// ��ʼ��tag����
	memset(tag, false, vexNum + 1);
}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::~AdjMatrixDirGraph()
{
	DestroyHelp();
}

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::DFSTraverse(void(*visit)(const ElemType&)) const
{
	memset(tag, false, vexNum + 1);
	DFS(1, visit);
}

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::BFSTraverse(void(*visit)(const ElemType&)) const
{
	memset(tag, false, vexNum + 1);
	BFS(1, visit);
}

template<class ElemType>
bool AdjMatrixDirGraph<ElemType>::GetElem(int v, ElemType& e) const
{
	if (v < 1 || v >= vexNum + 1) return false;

	e = elems[v];

	return true;
}

template<class ElemType>
bool AdjMatrixDirGraph<ElemType>::SetElem(int v, const ElemType& e)
{
	if (v < 1 || v >= vexNum + 1) return false;
	
	elems[v] = e;

	return true;
}

template<class ElemType>
int AdjMatrixDirGraph<ElemType>::GetVexNum() const
{
	return vexNum;
}

template<class ElemType>
int AdjMatrixDirGraph<ElemType>::GetEdgeNum() const
{
	return edgeNum;
}

template<class ElemType>
int AdjMatrixDirGraph<ElemType>::FirstAdjVex(int v) const
{
	for(int i = 1; i < vexNum + 1; i++)
		if (Matrix[v][i] == 1) 
			return i;

	return -1;
}

template<class ElemType>
int AdjMatrixDirGraph<ElemType>::NextAdjVex(int v1, int v2) const
{
	for (int i = v2 + 1; i < vexNum + 1; i++)
		if (Matrix[v1][i] == 1)
			return i;

	return -1;
}

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::InsertEdge(int v1, int v2)
{
	Matrix[v1][v2] == 1;
	edgeNum++;
}

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::DeleteEdge(int v1, int v2)
{
	Matrix[v1][v2] == 0;
	edgeNum--;
}

template<class ElemType>
bool AdjMatrixDirGraph<ElemType>::GetTag(int v) const
{
	return tag[v];
}

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::SetTag(int v, bool val) const
{
	tag[v] = val;
}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType>& copy)
{
	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	Matrix = new int* [(vexNum + 1) * (vexNum + 1)];
	elems = new ElemType[vexNum + 1];
	tag = new bool[vexNum + 1];

	for (int i = 1; i < vexNum + 1; i++)
		for (int j = 1; j < vexNum + 1; j++)
			Matrix[i][j] = copy.Matrix[i][j];

	for (int i = 1; i < vexNum + 1; i++)
		elems[i] = copy.elems[i];

	for (int i = 1; i < vexNum + 1; i++)
		tag[i] = copy.tag[i];

}

template<class ElemType>
AdjMatrixDirGraph<ElemType>& AdjMatrixDirGraph<ElemType>::operator=(const AdjMatrixDirGraph<ElemType>& copy)
{
	if (this == &copy) return;

	DestroyHelp();

	vexNum = copy.vexNum;
	edgeNum = copy.edgeNum;

	Matrix = new int* [(vexNum + 1) * (vexNum + 1)];
	elems = new ElemType[vexNum + 1];
	tag = new bool[vexNum + 1];

	for (int i = 1; i < vexNum + 1; i++)
		for (int j = 1; j < vexNum + 1; j++)
			Matrix[i][j] = copy.Matrix[i][j];

	for (int i = 1; i < vexNum + 1; i++)
		elems[i] = copy.elems[i];

	for (int i = 1; i < vexNum + 1; i++)
		tag[i] = copy.tag[i];

	return *this;

}
