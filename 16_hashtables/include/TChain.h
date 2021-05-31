#pragma once

#include "TNode.h"

template<typename TKey, typename TData>
class TChain
{
public:
    using Node = TNode<TKey, TData>;
protected:
    template<typename, typename> friend class THashTable;
    Node* head;
public:
    TChain();
    ~TChain();
    void Add(const TKey& key, TData data = nullptr);
    bool Remove(const TKey& key);
};

template<typename TKey, typename TData>
TChain<TKey, TData>::TChain()
    : head(nullptr)
{
}

template<typename TKey, typename TData>
TChain<TKey, TData>::~TChain()
{
    if (!head)
        return;
    Node* temp = head;
    while (temp)
    {
        Node* node = temp;
        temp = temp->next;
        delete node;
    }
}

template<typename TKey, typename TData>
void TChain<TKey, TData>::Add(const TKey& key, TData data)
{
    head = new Node(key, data, head);
}

template<typename TKey, typename TData>
bool TChain<TKey, TData>::Remove(const TKey& key)
{
    if (head == nullptr)
        return false;
    if (head->key == key)
    {
        delete head;
        head = nullptr;
        return true;
    }
    Node* node;
    for (node = head; node->next != nullptr; node = node->next)
        ;
    if (node->next == nullptr)
        return false;
    Node* next = node->next->next;
    delete node->next;
    node->next = next;
    return true;
}
