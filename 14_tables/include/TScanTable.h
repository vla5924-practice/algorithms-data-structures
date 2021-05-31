#pragma once

#include "TTable.h"
#include "TTabRecord.h"

template <typename TKey, typename TData>
class TScanTable : protected TTable<TKey, TData>
{
protected:
	TTabRecord<TKey, TData>** records;
public:
	TScanTable(int _tabSize);
	virtual TTabRecord<TKey, TData>* FindRecord(TKey key);
	virtual void InsertRecord(TKey key, TData* data);
	virtual void RemoveRecord(TKey key);
};

template <typename TKey, typename TData>
TScanTable<TKey, TData>::TScanTable(int _tabSize) : TTable(_tabSize) {}

template <typename TKey, typename TData>
TTabRecord<TKey, TData>* TScanTable<TKey, TData>::FindRecord(TKey key)
{
	for (int i = 0; i < this->dataCount; i++)
	{
		if (records[i]->key == key)
		{
			this->currPos = i;
			return records[i];
		}
	}
	return nullptr;
}

template <typename TKey, typename TData>
void TScanTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{
	if (!this->IsFull())
	{
		records[this->dataCount++] = new TTabRecord<TKey, TData>(key, data);
	}
}

template <typename TKey, typename TData>
void TScanTable<TKey, TData>::RemoveRecord(TKey key)
{
	if (!this->IsEmpty())
	{
		if (FindRecord(key) != nullptr)
		{
			delete records[this->currPos];
			records[this->currPos] = records[--this->dataCount];
		}
	}
}
