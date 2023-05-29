#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 100;

// 有向图的临界矩阵类模板
template<class ElemType>
class AdjMatrixDirGraph
{

protected:
	int vexNum, edgeNum; // 顶点个数和边数
	int** Matrix;        // 邻接矩阵
	ElemType* elems;     // 顶点元素
	mutable bool* tag;   // 指向标志数组的指针

	// 辅助函数模板

	// 销毁有向图，释放有向图占用的空间
	void DestroyHelp(); 
	// 从顶点v出发进行深度优先搜索图
	void DFS(int v, void(*visit)(const ElemType& e)) const;
	// 从顶点v出发进行广度优先搜索图
	void BFS(int v, void(*visit)(const ElemType&)) const;


public:
	AdjMatrixDirGraph(ElemType es[], int vertexNum = DEFAULT_SIZE); 
	AdjMatrixDirGraph(int vertexNum = DEFAULT_SIZE);
	~AdjMatrixDirGraph();

	// 深度优先遍历
	void DFSTraverse(void(*visit)(const ElemType&)) const;

	// 广度优先遍历
	void BFSTraverse(void(*visit)(const ElemType&)) const;

	// 求顶点的元素
	bool GetElem(int v, ElemType& e) const;

	// 设置顶点的元素值
	bool SetElem(int v, const ElemType& e);

	// 返回顶点个数
	int GetVexNum() const;

	// 返回边数
	int GetEdgeNum() const;

	// 返回顶点vd第一个邻接点
	int FirstAdjVex(int v) const;

	// 返回顶点v1的相对于v2的下一个邻接点
	int NextAdjVex(int v1, int v2) const;
	 
	// 插入顶点为v1和v2的边
	void InsertEdge(int v1, int v2);

	// 删除顶点为v1和v2的边
	void DeleteEdge(int v1, int v2);

	// 返回顶点v的标志
	bool GetTag(int v) const;

	// 设置顶点v的标志为val
	void SetTag(int v, bool val) const;

	// 复制构造函数模板
	AdjMatrixDirGraph(const AdjMatrixDirGraph<ElemType>& copy);

	// 重载赋值运算符
	AdjMatrixDirGraph<ElemType>& operator=(const AdjMatrixDirGraph<ElemType>& copy);
};

template<class ElemType>
void AdjMatrixDirGraph<ElemType>::DestroyHelp()
{
	delete[] elems;
	delete[] tag;

	for (int iPos = 0; iPos < vexNum + 1; iPos++)
	{
		// 释放邻接矩阵的行
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

	// 初始化elems数组
	for (int i = 0; i < vertexNum; i++)
		elems[i + 1] = es[i];

	// 初始化邻接矩阵
	memset(Matrix, 0, (vexNum + 1) * (vexNum + 1));

	// 初始化tag数组
	memset(tag, false, vexNum + 1);
}

template<class ElemType>
AdjMatrixDirGraph<ElemType>::AdjMatrixDirGraph(int vertexNum)
	: vexNum(vertexNum), edgeNum(0)
{

	Matrix = new int* [(vexNum + 1) * (vexNum + 1)];
	elems = new ElemType[vexNum + 1];

	tag = new bool[vexNum + 1];

	// 初始化邻接矩阵
	memset(Matrix, 0, (vexNum + 1) * (vexNum + 1));

	// 初始化tag数组
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
