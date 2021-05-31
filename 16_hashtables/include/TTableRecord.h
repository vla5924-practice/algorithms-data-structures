#pragma once

template <typename TKey, typename TData>
class TTableRecord
{
protected:
    TKey key;
public:
    TData data;
    TTableRecord();
    TTableRecord(const TKey& key_, TData data_);
    TKey getKey() const;
};

template<typename TKey, typename TData>
TTableRecord<TKey, TData>::TTableRecord()
    : data(nullptr)
{
}

template<typename TKey, typename TData>
TTableRecord<TKey, TData>::TTableRecord(const TKey& key_, TData data_)
    : key(key_), data(data_)
{
}

template<typename TKey, typename TData>
TKey TTableRecord<TKey, TData>::getKey() const
{
    return key;
}
