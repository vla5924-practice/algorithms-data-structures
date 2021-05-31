#pragma once

template <typename TKey, typename TData>
class TTabRecord
{
protected:
	TKey key;
	TData* pData;
public:
	TTabRecord(TKey _key, TData* _data);
	~TTabRecord();
	TData* GetData();
	TKey GetKey();
	TTabRecord* GetCopy();
};

template <typename TKey, typename TData>
TTabRecord<TKey, TData>::TTabRecord(TKey _key, TData* _pData)
{
	key = _key;
	pData = _pData;
}

template <typename TKey, typename TData>
TTabRecord<TKey, TData>::~TTabRecord()
{
	if (pData)
		delete pData;
}

template <typename TKey, typename TData>
TTabRecord<TKey, TData>* TTabRecord<TKey, TData>::GetCopy()
{
	TTabRecord<TKey, TData>* result;
	result->key = key;
	result->pData = new TData(pData);
	return result;
}

template <typename TKey, typename TData>
TData* TTabRecord<TKey, TData>::GetData()
{
	return pData;
}

template <typename TKey, typename TData>
TKey TTabRecord<TKey, TData>::GetKey()
{
	return key;
}
