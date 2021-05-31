#pragma once
#include <stack>

#include "TNode.h"

template <typename TKey, typename TData>
class TBinaryTree
{
protected:
    TNode<TKey, TData>* root_;

public:
    TBinaryTree();
    ~TBinaryTree();

    TNode<TKey, TData>* root() const;

    TNode<TKey, TData>* Find(const TKey& needle) const;
    TNode<TKey, TData>* findMin(TNode<TKey, TData>* root_) const;
    TNode<TKey, TData>* findNext(TNode<TKey, TData>* node) const;

    void Insert(const TKey& key, TData data);
    void Remove(const TKey& key);
    void Remove(TNode<TKey, TData>* node);
};

template<typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTree<TKey, TData>::findMin(TNode<TKey, TData>* root_) const
{
    if (root_ == nullptr)
        return nullptr;
    TNode<TKey, TData>* current = root_;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTree<TKey, TData>::findNext(TNode<TKey, TData>* node) const
{
    if (node == nullptr)
        return nullptr;
    TNode<TKey, TData>* result = nullptr;
    TNode<TKey, TData>* current = node;
    if (current->right != nullptr)
    {
        result = findMin(current->right);
        return result;
    }
    result = current->parent;
    TNode<TKey, TData>* temp = current;
    while ((result != nullptr) && (temp == result->right))
    {
        temp = result;
        result = result->parent;
    }
    return result;
}

template<typename TKey, typename TData>
TBinaryTree<TKey, TData>::TBinaryTree()
    : root_(nullptr)
{
}

template<typename TKey, typename TData>
TBinaryTree<TKey, TData>::~TBinaryTree()
{
    if (!root_)
        return;
    std::stack<TNode<TKey, TData>*> mainStack, helpStack;
    helpStack.push(root_);
    while (!helpStack.empty())
    {
        TNode<TKey, TData>* node = helpStack.top();
        helpStack.pop();
        if (!node->left)
            helpStack.push(node->left);
        if (!node->right)
            helpStack.push(node->right);
        mainStack.push(node);
    }
    while (!mainStack.empty())
    {
        TNode<TKey, TData>* node = mainStack.top();
        mainStack.pop();
        delete node;
    }
}

template<typename TKey, typename TData>
inline TNode<TKey, TData>* TBinaryTree<TKey, TData>::root() const
{
    return root_;
}

template<typename TKey, typename TData>
TNode<TKey, TData>* TBinaryTree<TKey, TData>::Find(const TKey& needle) const
{
    TNode<TKey, TData>* node = root_;
    while (node && node->key != needle)
    {
        if (needle < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

template<typename TKey, typename TData>
void TBinaryTree<TKey, TData>::Insert(const TKey& key, TData data)
{
    TNode<TKey, TData>* node = new TNode<TKey, TData>(key, data);
    if (root_ == nullptr)
    {
        root_ = node;
        return;
    }
    TNode<TKey, TData>* temp = root_;
    TNode<TKey, TData>* parent = nullptr;
    while (temp != nullptr)
    {
        parent = temp;
        if (node->key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    node->parent = parent;
    if (node->key < parent->key)
        parent->left = node;
    else
        parent->right = node;
}

template<typename TKey, typename TData>
void TBinaryTree<TKey, TData>::Remove(const TKey& key)
{
    TNode<TKey, TData>* node = Find(key);
    Remove(node);
}

template<typename TKey, typename TData>
void TBinaryTree<TKey, TData>::Remove(TNode<TKey, TData>* node)
{
    TNode<TKey, TData>* z = node;
    TNode<TKey, TData>* y = nullptr;
    TNode<TKey, TData>* x = nullptr;
    if ((z->left != nullptr) && (z->right != nullptr))
        y = findNext(z); // z has 2 parents
    else
        y = z; // z has 0 or 1 parent
    if (y->left != nullptr)
        x = y->left;
    else
        x = y->right;
    if (x != nullptr)
        x->parent = y->parent;
    if (y->parent != nullptr)
    {
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    if (y != z)
    {
        z->key = y->key;
        // delete z->data;
        z->data = y->data;
        delete y; // (?)
    }
    else
        delete z; // (?)
}
