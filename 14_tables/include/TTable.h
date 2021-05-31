#pragma once

#include "TTabRecord.h"

template <typename TKey, typename TData>
class TTable
{
protected:
	int tabSize;
	int dataCount;
	int currPos;
public:
	TTable(int _tabSize);

	bool IsEmpty() const;
	bool IsFull() const;
	int GetDataCount() const;
	int GetTabSize() const;

	virtual TTabRecord<TKey, TData>* FindRecord(TKey key) = 0;
	virtual void InsertRecord(TKey key, TData* data) = 0;
	virtual void RemoveRecord(TKey key) = 0;

	virtual bool Reset();
	virtual bool GetNext();
	virtual bool IsTabEnded() const;

	virtual TKey GetKey() const = 0;
	virtual TData* GetData() const = 0;
};

template <typename TKey, typename TData>
TTable<TKey, TData>::TTable(int _tabSize)
{
	dataCount = currPos = 0;
	tabSize = _tabSize;
}

template <typename TKey, typename TData>
bool TTable<TKey, TData>::IsEmpty() const
{
	return dataCount == 0;
}

template <typename TKey, typename TData>
bool TTable<TKey, TData>::IsFull() const
{
	return dataCount == tabSize;
}

template <typename TKey, typename TData>
int TTable<TKey, TData>::GetDataCount() const
{
	return dataCount;
}

template <typename TKey, typename TData>
int TTable<TKey, TData>::GetTabSize() const
{
	return tabSize;
}

template <typename TKey, typename TData>
bool TTable<TKey, TData>::Reset()
{
	currPos = 0;
	return IsTabEnded();
}

template <typename TKey, typename TData>
bool TTable<TKey, TData>::GetNext()
{
	if (!IsTabEnded())
		currPos++;
	return IsTabEnded();
}

template <typename TKey, typename TData>
bool TTable<TKey, TData>::IsTabEnded() const
{
	return currPos >= tabSize;
}
