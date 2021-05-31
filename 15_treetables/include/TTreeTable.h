#pragma once

#include "TBinaryTree.h"
#include "TNode.h"

template <typename TKey, typename TData>
class TTreeTable
{
protected:
    size_t entriesCount;
    TBinaryTree<TKey, TData> tree;

public:
    TTreeTable() { entriesCount = 0; }
    ~TTreeTable() {}

    bool IsEmpty() const;
    TNode<TKey, TData>* Find(const TKey& needle) const;

    void Insert(const TKey& key, TData data);
    void Remove(const TKey& key);

    TNode<TKey, TData>* root() const;
};

template<typename TKey, typename TData>
TNode<TKey, TData>* TTreeTable<TKey, TData>::root() const
{
    return tree.root();
}

template<typename TKey, typename TData>
bool TTreeTable<TKey, TData>::IsEmpty() const
{
    return entriesCount == 0;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TTreeTable<TKey, TData>::Find(const TKey& needle) const
{
    return tree.Find(needle);
}

template<typename TKey, typename TData>
void TTreeTable<TKey, TData>::Insert(const TKey& key, TData data)
{
    if (Find(key) != nullptr)
        throw "duplicate";
    tree.Insert(key, data);
    entriesCount++;
}

template<typename TKey, typename TData>
void TTreeTable<TKey, TData>::Remove(const TKey& key)
{
    TNode<TKey, TData>* node = Find(key);
    if (node == nullptr)
        throw "not found";
    tree.Remove(node);
    entriesCount--;
}
