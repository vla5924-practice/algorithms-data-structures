#pragma once

template <typename TKey, typename TData>
class TNode
{
protected:
    template<typename, typename> friend class TBinaryTree;
    TKey key;
    TNode<TKey, TData>* left;
    TNode<TKey, TData>* right;
    TNode<TKey, TData>* parent;
public:
    TData data;
    TNode(TKey key_, TData data_, TNode* parent_ = nullptr, TNode* left_ = nullptr, TNode* right_ = nullptr)
        : key(key_), data(data_), parent(parent_), left(left_), right(right_) {}
    TKey getKey() const { return key; };
};
