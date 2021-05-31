#pragma once

#include "TChain.h"

template <typename TKey, typename TData>
class THashTable
{
protected:
    size_t entriesCount;
    size_t chainsCount;
    TChain<TKey, TData>* chains;
    size_t Hash(const TKey& key) const;

public:
    THashTable(size_t chainsCount_ = 64);
    ~THashTable();

    bool IsEmpty() const;
    TNode<TKey, TData>* Find(const TKey& needle) const;

    void Insert(const TKey& key, TData data);
    void Remove(const TKey& key);
};

template<typename TKey, typename TData>
inline size_t THashTable<TKey, TData>::Hash(const TKey& key) const
{
    return key % chainsCount;
}

template<typename TKey, typename TData>
THashTable<TKey, TData>::THashTable(size_t chainsCount_)
    : chainsCount(chainsCount_)
{
    if (chainsCount == 0)
        chains = nullptr;
    else
        chains = new TChain<TKey, TData>[chainsCount];
}

template<typename TKey, typename TData>
THashTable<TKey, TData>::~THashTable()
{
    if (chains)
        delete[] chains;
}

template<typename TKey, typename TData>
bool THashTable<TKey, TData>::IsEmpty() const
{
    return entriesCount == 0;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* THashTable<TKey, TData>::Find(const TKey& needle) const
{
    size_t index = Hash(needle);
    for (TNode<TKey, TData>* i = chains[index].head; i != nullptr; i = i->next)
        if (i->getKey() == needle)
            return i;
    return nullptr;
}

template<typename TKey, typename TData>
void THashTable<TKey, TData>::Insert(const TKey& key, TData data)
{
    if (Find(key))
        throw "duplication";
    size_t index = Hash(key);
    chains[index].Add(key, data);
    entriesCount++;
}

template<typename TKey, typename TData>
void THashTable<TKey, TData>::Remove(const TKey& key)
{
    size_t index = Hash(key);
    if (!chains[index].Remove(key))
        throw "not found";
    entriesCount--;
}
