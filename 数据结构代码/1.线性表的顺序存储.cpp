#include<iostream>
using namespace std;

#define DEFAULT_SIZE 100

// 顺序表类模板
template<class elemType>
class SqList
{
protected:
	int count;
	int maxSize;
	elemType* elems; // 存储元素

public:
	SqList(int size = DEFAULT_SIZE);
	virtual ~SqList();
	int Length() const;
	bool Empty() const;
	void Clear();
	void Traverse(void(*visit)(const elemType&)) const;
	bool GetElem(int position, elemType& e) const;
	bool SetElem(int position, const elemType& e);
	bool Delete(int position, elemType& e);
	bool Insert(int position, const elemType& e);
	SqList(const SqList<elemType>& copy); // 复制构造函数模板
	SqList<elemType>& operator=(const SqList<elemType>& copy); // 重载赋值运算符

};

template<class elemType>
SqList<elemType>::SqList(int size)
{
	maxSize = size;
	elems = new elemType[maxSize];
	count = 0;
}

template<class elemType>
SqList<elemType>::~SqList()
{
	delete[] elems; //释放存储空间
}

template<class elemType>
int SqList<elemType>::Length() const
{
	return count;
}

template<class elemType>
bool SqList<elemType>::Empty() const
{
	return count == 0;
}

template<class elemType>
void SqList<elemType>::Clear()
{
	count = 0;
}

template<class elemType>
void SqList<elemType>::Traverse(void(*visit)(const elemType&)) const
{
	for (int pos = 1; pos <= Length(); pos++) {
		// 对线性表的每个元素调用函数(*visit)
		(*visit)(elems[pos - 1]);
	}
}

template<class elemType>
bool SqList<elemType>::GetElem(int position, elemType& e) const
{
	if (position < 1 || position > Length()) return false;

	e = elems[position - 1];
	return true;
}

template<class elemType>
bool SqList<elemType>::SetElem(int position, const elemType& e)
{
	if (position < 1 || position > Length()) return false;

	elems[position - 1] = e;
	return true;
}

template<class elemType>
bool SqList<elemType>::Delete(int position, elemType& e)
{
	elemType tmp;
	if (position < 1 || position > Length()) return false;

	GetElem(position, e);
	for (int pos = position + 1; pos <= Length(); pos++) {
		// 被删除的元素依次左移
		GetElem(pos, tmp); SetElem(pos - 1, tmp);
	}

	count--;
	return true;
}

template<class elemType>
bool SqList<elemType>::Insert(int position, const elemType& e)
{
	elemType tmp;
	if (count >= maxSize || position < 1 || position > Length() + 1) return false;

	count++; // 插入后元素个数将自增1

	for (int pos = Length(); pos >= position; pos--) {
		GetElem(pos, tmp); SetElem(pos + 1, tmp);
	}

	SetElem(position, e);
	return true;
}

template<class elemType>
SqList<elemType>::SqList(const SqList<elemType>& copy)
// 由线性表copy构造新线性表，复制构造函数
{
	maxSize = copy.maxSize;
	elems = new elemType[maxSize];
	count = copy.count;

	for (int pos = 1; pos <= Length(); pos++) {
		elems[pos - 1] = copy.elems[pos - 1];
	}
}

template<class elemType>
SqList<elemType>& SqList<elemType>::operator=(const SqList<elemType>& copy)
{
	if (&copy != this)
	{
		maxSize = copy.maxSize;
		if (elems != NULL) delete[] elems;
		elems = new elemType[maxSize];
		count = copy.count;

		for (int pos = 1; pos <= Length(); pos++) {
			elems[pos - 1] = copy.elems[pos - 1];
		}
	}

	return *this;
}


// 设计顺序表存储的两个集合求差集的算法
template<class elemType>
void Difference(const SqList<elemType>& la, const SqList<elemType>& lb, SqList<elemType>& lc) {
	// 方法：在la中取出元素，在lb中进行查找，如果未在lb中出现，就插入到lc中

	elemType aElem, bElem;

	lc.Clear();

	for (int aPos = 1; aPos <= la.Length(); aPos++) {
		la.GetElem(aPos, aElem);
		bool isExist = false;

		for (int bPos = 1; bPos <= lb.Length(); bPos++) {
			lb.GetElem(bPos, bElem);
			if (aElem == bElem) {
				isExist = true;
				break;
			}
		}

		if (!isExist) {
			lc.Insert(lc.Length() + 1, aElem);
		}
	}

}

// 顺序表左奇右偶的调整
void Adjust(SqList<int>& la) {
	int lPosition = 1, rPosition = la.Length();

	int aElem, bElem;

	while (lPosition < rPosition) {
		la.GetElem(lPosition, aElem); la.GetElem(rPosition, bElem);

		if (aElem % 2 == 1) lPosition++;
		else if (bElem % 2 == 0) rPosition--;
		else
		{
			la.SetElem(lPosition++, bElem);
			la.SetElem(rPosition--, aElem);
		}
	}

}

