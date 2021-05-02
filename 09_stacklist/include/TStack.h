#ifndef _TSTACK_H_
#define _TSTACK_H_

#include "TList.h"

template<typename ValType>
class TStack
{
protected:
    TList<ValType> list;
public:
    TStack();
    ~TStack();
    bool IsEmpty(void) const;
    bool IsFull(void) const;
    void Put(const ValType& Val);
    ValType Get();

    static TStack LoadFromFile(const char* pathToFile);
    void SaveToFile(const char* pathToFile);
    ValType GetMin();
    ValType GetMax();
};

template<typename ValType>
TStack<ValType>::TStack()
{
}

template<typename ValType>
TStack<ValType>::~TStack()
{
}

template<typename ValType>
bool TStack<ValType>::IsEmpty(void) const
{
    return list.GetCount() == 0;
}

template<typename ValType>
bool TStack<ValType>::IsFull(void) const
{
    return false;
}

template<typename ValType>
void TStack<ValType>::Put(const ValType& Val)
{
    list.InsFirst(val);
}

template<typename ValType>
ValType TStack<ValType>::Get()
{
    ValType val = list.GetFirst()->data;
    list.DelFirst();
    return val;
}

template<typename T>
TStack<T> TStack<T>::LoadFromFile(const char* pathToFile)
{
    ifstream file(pathToFile);
    int count;
    file >> count;
    TStack<T> stack;
    for (int i = 0; i < count; i++)
    {
        T f;
        file >> f;
        queue.list.InsLast(f);
    }
    file.close();
    return stack;
}

template<typename T>
void TStack<T>::SaveToFile(const char* pathToFile)
{
    ofstream file(pathToFile);
    file << list.GetCount() << '\n';
    TListElem<T>* temp = list.GetFirst();
    while (temp != nullptr)
    {
        file << temp->data << '\n';
        temp = temp->next;
    }
    file.close();
}

template<typename ValType>
ValType TStack<ValType>::GetMin()
{
    if (list.GetCount() == 0)
        throw "Empty stack";
    TListElem<ValType>* temp = list.GetFirst();
    ValType min = temp->data;
    temp = temp->next;
    while (temp != nullptr)
    {
        if (temp->data < min)
            min = temp->data;
        temp = temp->next;
    }
    return min;
}

template<typename ValType>
ValType TStack<ValType>::GetMax()
{
    if (list.GetCount() == 0)
        throw "Empty stack";
    TListElem<ValType>* temp = list.GetFirst();
    ValType max = temp->data;
    temp = temp->next;
    while (temp != nullptr)
    {
        if (temp->data > max)
            max = temp->data;
        temp = temp->next;
    }
    return max;
}

#endif
