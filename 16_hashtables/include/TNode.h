#pragma once

template<typename TKey, typename TData>
class TNode
{
protected:
    template<typename, typename> friend class THashTable;
    template<typename, typename> friend class TArrayHashTable;
    template<typename, typename> friend class TChain;
    TKey key;
    TNode<TKey, TData>* next;
public:
    TData data;
    TKey getKey() const { return key; }
    TNode(const TKey& key_, TData data_, TNode* next_ = nullptr)
        : key(key_), data(data_), next(next_){}
};
