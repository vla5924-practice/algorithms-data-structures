#ifndef _TMULTISTACK_H_
#define _TMULTISTACK_H_

#include <cmath>
#include "TStack.h"

template <class T>
class TMultiStack
{
protected:
	int size;
	int stackCount;
	TStack<T>* stacks;
	T** sData;
	T* data;

	void StackRelocation(int i);

public:
	TMultiStack(int size_ = 1, int stackCount = 1);
	~TMultiStack();

	T Get(int i);

	void Put(T d, int i);
	bool IsEmpty(int i) const;
	bool IsFull(int i) const;
	int GetSize();
	void Resize(int size_ = 1, int stackCount_ = 1);

	int GetMinCountStack();
};

template<class T>
void TMultiStack<T>::StackRelocation(int index)
{
	int freeSize = 0;
	for (int i = 0; i < stackCount; i++)
		freeSize += stacks[i].GetSize() - stacks[i].GetCount();
	if (freeSize == 0)
		throw "No free space";
	int count = static_cast<int>(std::floor(static_cast<double>(freeSize) / stackCount));
	int* sizes = new int[stackCount];
	for (int i = 0; i < stackCount - 1; i++)
		sizes[i] = stacks[i].GetCount() + count;
	int c = stacks[stackCount - 1].GetCount();
	sizes[stackCount - 1] = c + (freeSize - count * (stackCount - 1));
	T** newData = new T*[stackCount];
	int k = 0;
	for (int i = 0; i < stackCount; i++)
	{
		newData[i] = data + k;
		k = k + sizes[i];
	}
	for (int i = 0; i < stackCount; i++)
	{
		if (newData[i] == sData[i])
			stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
		else if (newData[i] < sData[i])
		{
			for (int j = 0; j < stacks[i].GetCount(); j++)
				newData[i][j] = sData[i][j];
			stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
		}
		else if (newData[i] > sData[i])
		{
			int k = i;
			for (; k < stackCount; k++)
				if (newData[k] <= sData[k])
					break;
			k--;
			for (int s = k; s <= i; s--)
			{
				for (int j = stacks[s].GetCount() - 1; j >= 0; j--)
					newData[s][j] = sData[s][j];
				stacks[s].SetData(newData[s], sizes[s], stacks[s].GetCount());
			}
		}
	}
	T** temp = sData;
	sData = newData;
	delete[] temp;
	delete[] sizes;
}

template<class T>
TMultiStack<T>::TMultiStack(int size_, int stackCount_)
{
	if (size_ <= 0 || stackCount_ <= 0)
		throw "Invalid parameters";
	size = size_;
	stackCount = stackCount_;
	data = new T[size];
	for (int i = 0; i < size; i++)
		data[i] = 0;
	int count = static_cast<int>(std::floor(static_cast<double>(size_) / stackCount));
	int* sizes = new int[stackCount];
	for (int i = 0; i < stackCount - 1; i++)
		sizes[i] = count;
	sizes[stackCount - 1] = size_ - count * (stackCount - 1);
	sData = new T*[stackCount];
	stacks = new TStack<T>[stackCount];
	int k = 0;
	for (int i = 0; i < stackCount; i++)
	{
		stacks[i].SetData(data + k, sizes[i], 0);
		sData[i] = data + k;
		k = k + sizes[i];
	}
}

template <class T>
TMultiStack<T>::~TMultiStack()
{
	if (data != nullptr)
	{
		delete[] data;
		data = nullptr;
	}
	if (stacks != nullptr)
	{
		delete[] stacks;
		stacks = nullptr;
	}
	size = 0;
	stackCount = 0;
}

template<class T>
void TMultiStack<T>::Put(T d, int i)
{
	if (i < 0 || i >= stackCount)
		throw "Invalid parameter";
	if (stacks[i].IsFull())
		StackRelocation(i);
	stacks[i].Put(d);
}

template<class T>
T TMultiStack<T>::Get(int i)
{
	if (i < 0 || i > stackCount)
		throw "Invalid parameter";
	if (stacks[i].IsEmpty())
		throw "No free space";
	return stacks[i].Get();
}

template<class T>
bool TMultiStack<T>::IsEmpty(int i) const
{
	if (i < 0 || i > stackCount)
		throw "Invalid parameter";
	return stacks[i].IsEmpty();
}

template<class T>
bool TMultiStack<T>::IsFull(int i) const
{
	if (i < 0 || i > stackCount)
		throw "Invalid parameter";
	return stacks[i].IsFull();
}

template <class T>
int TMultiStack<T>::GetSize()
{
	return size;
}

template<class T>
void TMultiStack<T>::Resize(int size_, int stackCount_)
{
	stacks[stackCount_].Resize(size_);
}

template<class T>
int TMultiStack<T>::GetMinCountStack()
{
	int min = 0;
	for (int i = 1; i < stackCount; i++)
		if (stacks[i].GetCount() < stacks[min].GetCount())
			min = i;
	return min;
}

#endif
