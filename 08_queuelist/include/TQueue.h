#ifndef _TQUEUE_H_
#define _TQUEUE_H_

#include "TList.h"

template<typename ValType>
class TQueue
{
protected:
    TList<ValType> list;
public:
    TQueue();
    ~TQueue();
    bool IsEmpty(void) const;
    bool IsFull(void) const;
    void Put(const ValType& Val);
    ValType Get();

    static TQueue LoadFromFile(const char* pathToFile);
    void SaveToFile(const char* pathToFile);
    ValType GetMin();
    ValType GetMax();
};

template<typename ValType>
TQueue<ValType>::TQueue()
{
}

template<typename ValType>
TQueue<ValType>::~TQueue()
{
}

template<typename ValType>
bool TQueue<ValType>::IsEmpty(void) const
{
    return list.GetCount() == 0;
}

template<typename ValType>
bool TQueue<ValType>::IsFull(void) const
{
    return false;
}

template<typename ValType>
void TQueue<ValType>::Put(const ValType& Val)
{
    list.InsLast(val);
}

template<typename ValType>
ValType TQueue<ValType>::Get()
{
    ValType val = list.GetFirst()->data;
    list.DelFirst();
    return val;
}

template<typename T>
TQueue<T> TQueue<T>::LoadFromFile(const char* pathToFile)
{
    ifstream file(pathToFile);
    int count;
    file >> count;
    TQueue<T> queue;
    for (int i = 0; i < count; i++)
    {
        T f;
        file >> f;
        queue.list.InsLast(f);
    }
    file.close();
    return queue;
}

template<typename T>
void TQueue<T>::SaveToFile(const char* pathToFile)
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
ValType TQueue<ValType>::GetMin()
{
    if (list.GetCount() == 0)
        throw "Empty queue";
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
ValType TQueue<ValType>::GetMax()
{
    if (list.GetCount() == 0)
        throw "Empty queue";
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

#endif // !_TQUEUE_H_
