#pragma once

#include "TNode.h"

template <typename TKey, typename TData>
class TArrayHashTable
{
protected:
    size_t tabSize;
    size_t entriesCount;
    size_t hashStep;
    size_t freePos;
    size_t currPos;
    TNode<TKey, TData>** entries;
    TNode<TKey, TData>* specialMark;

    size_t GetNextPos(size_t _pos) { return (_pos + hashStep) % tabSize; }
    size_t Hash(const TKey& key);

public:
    TArrayHashTable(size_t _tabSize, size_t _hashStep);
    ~TArrayHashTable();

    bool IsEmpty() const { return entriesCount == 0; }
    bool IsFull() const { return entriesCount == tabSize; }
    TNode<TKey, TData>* Find(const TKey& needle);

    void Insert(const TKey& key, TData data);
    void Remove(const TKey& key);
};

template<typename TKey, class TData>
size_t TArrayHashTable<TKey, TData>::Hash(const TKey& key) 
{
    return key % tabSize + key % 3;
};

template<typename TKey, class TData>
TArrayHashTable<TKey, TData>::TArrayHashTable(size_t _tabSize, size_t _hashStep)
{
    tabSize = _tabSize;
    hashStep = _hashStep;
    freePos = 0;
    entries = new TNode<TKey, TData>*[tabSize];
    for (size_t i = 0; i < tabSize; i++)
        entries[i] = nullptr;
    specialMark = new TNode<TKey, TData>(TKey(), TData());
};

template<typename TKey, class TData>
TArrayHashTable<TKey, TData>::~TArrayHashTable()
{
    hashStep = 0;
    freePos = 0;
    for (int i = 0; i < tabSize; i++)
        if (entries[i] && entries[i] != specialMark)
            delete entries[i];

    delete[] entries;
    delete specialMark;
};

template<typename TKey, class TData>
TNode<TKey, TData>* TArrayHashTable<TKey, TData>::Find(const TKey& _key)
{
    TNode<TKey, TData>* node = nullptr;
    currPos = Hash(_key) % tabSize;
    freePos = -1;

    for (size_t i = 0; i < tabSize; i++)
    {
        if (!entries[currPos])
        {
            if (freePos == -1)
                freePos = currPos;
            break;
        }
        else if (entries[currPos] == specialMark)
        {
            if (freePos == -1)
                freePos = currPos;
        }
        else if (entries[currPos]->key == _key)
        {
            node = entries[currPos];
            break;
        }

        currPos = GetNextPos(currPos);
    }

    return node;
};

template<typename TKey, class TData>
void TArrayHashTable<TKey, TData>::Insert(const TKey& _key, TData _data)
{
    if (IsFull())
        throw "full table";
    if (Find(_key))
        throw "duplicate";
    if (freePos != -1)
    {
        currPos = freePos;
        entries[currPos] = new TNode<TKey, TData>(_key, _data);
        entriesCount++;
        freePos = -1;
    }
};

template<typename TKey, class TData>
void TArrayHashTable<TKey, TData>::Remove(const TKey& _key)
{
    if (IsEmpty())
        throw "empty table";
    if (!Find(_key))
        throw "not found";
    delete entries[currPos];
    entries[currPos] = specialMark;
    entriesCount--;
};
