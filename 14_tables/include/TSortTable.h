#pragma once

#include "TScanTable.h"
#include "TTabRecord.h"

template <typename TKey, typename TData>
class TSortTable : protected TScanTable<TKey, TData>
{
protected:
	void SortData();

public:
	TSortTable(int _tabSize);
	TSortTable(const TScanTable<TKey, TData>* table);

	virtual TTabRecord<TKey, TData>* FindRecord(TKey key);
	virtual void InsertRecord(TKey key, TData* data);
	virtual void RemoveRecord(TKey key);
};

template <typename TKey, typename TData>
void TSortTable<TKey, TData>::SortData()
{
	TTabRecord<TKey, TData>* temp;
	for (int i = 1, j; i < this->dataCount; i++)
	{
		temp = this->records[i];
		for (j = i - 1; j > -1; j--)
		{
			if (this->records[j] > temp->GetKey())
			{
				this->records[j + 1] = this->records[j];
			}
			else
				break;
		}
		this->records[j + 1] = temp;
	}
}

template <typename TKey, typename TData>
TSortTable<TKey, TData>::TSortTable(int _tabSize) : TScanTable(_tabSize) {}

template <typename TKey, typename TData>
TSortTable<TKey, TData>::TSortTable(const TScanTable<TKey, TData>* table)
{
	this->dataCount = table->GetDataCount();
	this->tabSize = table->GetTabSize();
	this->currPos = 0;
	this->records = new TTabRecord<TKey, TData>[this->tabSize];
	for (int i = 0; i < this->dataCount; i++)
	{
		this->records[i] = table->records[i]->GetCopy();
	}
	this->SortData();
}

template <typename TKey, typename TData>
TTabRecord<TKey, TData>* TSortTable<TKey, TData>::FindRecord(TKey key)
{
	int i, i1 = 0, i2 = this->dataCount - 1;
	TTabRecord<TKey, TData>* rec = nullptr;
	while (i1 <= i2)
	{
		i = (i1 + i2) / 2;
		if (key == this->records[i]->key)
		{
			i1 = i + 1;
			i2 = i;
			rec = this->records[i];
		}
		else if (key > this->records[i]->key)
			i1 = i + 1;
		else
			i2 = i - 1;
		this->currPos = i2;;
		return rec;
	}
}

template <typename TKey, typename TData>
void TSortTable<TKey, TData>::InsertRecord(TKey key, TData* data)
{
	if (!this->IsFull())
	{
		TTabRecord<TKey, TData>* rec = FindRecord(key);
		for (int i = this->dataCount; i > this->currPos; i--)
		{
			this->records[i] = this->records[i - 1];
		}
		this->records[this->currPos] = new TTabRecord<TKey, TData>(key, data);
		this->dataCount++;
	}
}

template <typename TKey, typename TData>
void TSortTable<TKey, TData>::RemoveRecord(TKey key)
{
	if (!this->IsEmpty())
	{
		TTabRecord<TKey, TData>* rec = FindRecord(key);
		if (rec != nullptr)
		{
			delete this->records[this->currPos];
			for (int i = this->currPos; i < this->dataCount - 1; i++)
			{
				this->records[i] = this->records[i + 1];
			}
			this->dataCount--;
		}
	}
}
