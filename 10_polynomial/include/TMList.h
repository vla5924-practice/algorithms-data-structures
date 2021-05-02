#ifndef _TMLIST_H_
#define _TMLIST_H_

#include <iostream>
#include "TMonomial.h"

class TMList
{
protected:
    TMonomial* root;
    TMonomial* end;
    int count;
public:
    TMList();
    TMList(const TMList& other);
    ~TMList();

    TMList& operator=(const TMList& other);

    bool IsEmpty() const;
    void InsFirst(const TMonomial& e);
    void InsLast(const TMonomial& e);
    void InsAfter(TMonomial* insAfterThis, const TMonomial& e);

    TMonomial* GetFirst() const;
    TMonomial* GetLast() const;
    int GetCount() const;

    void DelFirst();
    void DelLast();
    void Del(TMonomial* e);

    friend std::ostream& operator<<(std::ostream& s, const TMList& list)
    {
        TMonomial* i = list.root;
        while (i != nullptr)
        {
            s << i->data << ' ';
            i = i->next;
        }
        return s;
    }
};

TMList::TMList()
    : root(nullptr), end(nullptr), count(0)
{
}

TMList::TMList(const TMList& other)
    : TMList()
{
    count = other.count;
    if (other.count == 0)
        return;
    root = new TMonomial(other.root, nullptr, nullptr);
    if (other.count == 1)
    {
        end = root;
        return;
    }
    TMonomial* i = other.root->next;
    TMonomial* j = root;
    TMonomial* k = root;
    while (i != nullptr)
    {
        j = new TMonomial(i, k, nullptr);
        k->next = j;
        k = j;
        i = i->next;
    }
    end = j;
}

TMList::~TMList()
{
    if (root == nullptr)
        return;
    TMonomial* i = root;
    TMonomial* j = i;
    while (i != nullptr)
    {
        i = i->next;
        delete j;
        j = i;
    }
    root = nullptr;
    end = nullptr;
    count = 0;
}

TMList& TMList::operator=(const TMList& other)
{
    if (root != nullptr)
    {
        TMonomial* i = root;
        TMonomial* j = i;
        while (i != nullptr)
        {
            i = i->next;
            delete j;
            j = i;
        }
        root = nullptr;
        end = nullptr;
    }
    count = other.count;
    if (other.count == 0)
        return *this;
    root = new TMonomial(other.root, nullptr, nullptr);
    if (other.count == 1)
    {
        end = root;
        return *this;
    }
    TMonomial* i = other.root->next;
    TMonomial* j = root;
    TMonomial* k = root;
    while (i != nullptr)
    {
        j = new TMonomial(i, k, nullptr);
        k->next = j;
        k = j;
        i = i->next;
    }
    end = j;
    return *this;
}

bool TMList::IsEmpty() const
{
    return count == 0;
}

void TMList::InsFirst(const TMonomial& e)
{
    TMonomial* newRoot = new TMonomial(e);
    if (root != nullptr)
        root->prev = newRoot;
    newRoot->prev = nullptr;
    newRoot->next = root;
    root = newRoot;
    if (count == 0)
        end = root;
    count += 1;
}

void TMList::InsLast(const TMonomial& e)
{
    TMonomial* newEnd = new TMonomial(e);
    if (end != nullptr)
        end->next = newEnd;
    newEnd->prev = end;
    newEnd->next = nullptr;
    end = newEnd;
    if (count == 0)
        root = end;
    count += 1;
}

void TMList::InsAfter(TMonomial* insAfterThis, const TMonomial& e)
{
    if (insAfterThis == end)
    {
        InsLast(e);
        return;
    }
    TMonomial* newElem = new TMonomial(e);
    newElem->prev = insAfterThis;
    insAfterThis->next = newElem;
    newElem->next->prev = newElem;
    count += 1;
}

TMonomial* TMList::GetFirst() const
{
    return root;
}

TMonomial* TMList::GetLast() const
{
    return end;
}

int TMList::GetCount() const
{
    return count;
}

void TMList::DelFirst()
{
    if (root == nullptr)
        return;
    TMonomial* temp = root;
    root = root->next;
    if (root != nullptr)
        root->prev = nullptr;
    delete temp;
    if (count == 1)
        end = nullptr;
    count -= 1;
}

void TMList::DelLast()
{
    if (end == nullptr)
        return;
    TMonomial* temp = end;
    end = end->prev;
    if (end != nullptr)
        end->next = nullptr;
    delete temp;
    if (count == 1)
        root = nullptr;
    count -= 1;
}

void TMList::Del(TMonomial* e)
{
    if (e == nullptr)
        return;
    if (e == root)
    {
        DelFirst();
        return;
    }
    if (e == end)
    {
        DelLast();
        return;
    }
    e->prev->next = e->next;
    e->next->prev = e->prev;
    delete e;
    count -= 1;
}

#endif
