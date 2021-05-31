﻿#ifndef _TSTACK_H_
#define _TSTACK_H_

#include <fstream>

template<typename ValType>
class TStack {
protected: // поля
    ValType* pMem; // указатель на массив элементов
    int MemSize; // размер памяти для СД
    int Hi; // индекс вершины стека (и количество элементов)
public:

    TStack(int Size = 100); //конструктор
    TStack(const TStack& s)
    {
        MemSize = s.MemSize;
        Hi = s.Hi;
        pMem = new ValType[MemSize];
        for (int i = 0; i < Hi; i++)
            pMem[i] = s.pMem[i];
    }
    ~TStack(); //деструктор
    int IsEmpty(void) const; // контроль пустоты
    int IsFull(void) const; // контроль переполнения
    void Put(const ValType& Val);// добавить значение
    ValType Get(void); // извлечь значение

    ValType GetMin();
    ValType GetMax();
};

template<typename ValType>
TStack<ValType>::TStack(int Size)
{
    if (Size <= 0)
        throw "Invalid size";
    MemSize = Size;
    Hi = 0;
    pMem = nullptr;
    pMem = new ValType[MemSize];
}

template<typename ValType>
TStack<ValType>::~TStack()
{
    if (pMem != nullptr)
        delete[] pMem;
    pMem = nullptr;
}

template<typename ValType>
int TStack<ValType>::IsEmpty(void) const
{
    return Hi == 0;
}

template<typename ValType>
int TStack<ValType>::IsFull(void) const
{
    return Hi == MemSize;
}

template<typename ValType>
void TStack<ValType>::Put(const ValType& Val)
{
    if (IsFull())
        throw "Stack is full";
    pMem[Hi] = Val;
    Hi++;
}

template<typename ValType>
ValType TStack<ValType>::Get(void)
{
    if (IsEmpty())
        throw "Stack is empty";
    Hi--;
    return pMem[Hi];
}

template<typename ValType>
ValType TStack<ValType>::GetMin()
{
    ValType min = pMem[0];
    for (int i = 1; i < Hi; i++)
        if (pMem[i] < min)
            min = pMem[i];
    return min;
}

template<typename ValType>
ValType TStack<ValType>::GetMax()
{
    ValType max = pMem[0];
    for (int i = 1; i < Hi; i++)
        if (pMem[i] > max)
            max = pMem[i];
    return max;
}

#endif
