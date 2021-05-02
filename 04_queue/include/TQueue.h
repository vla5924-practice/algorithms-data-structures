#ifndef _TQUEUE_H_
#define _TQUEUE_H_

#include <fstream>

template<typename ValType>
class TQueue 
{
protected: // поля
  ValType* pMem; // указатель на массив элементов
  int MemSize; // размер памяти для СД
  int DataCount; // количество элементов
  int Hi, Li;
  int GetNextIndex(int index); // получить следующий индекс
public:
  TQueue(int Size); //конструктор
  ~TQueue(); //деструктор
  int IsEmpty(void) const; // контроль пустоты
  int IsFull(void) const; // контроль переполнения
  void Put(const ValType& Val);// добавить значение
  ValType Get(void); // извлечь значение

  ValType GetMin();
  ValType GetMax();

  static TQueue loadFromFile(const char* pathToFile);
  void saveToFile(const char* pathToFile);
};

template<typename ValType>
int TQueue<ValType>::GetNextIndex(int index)
{
  return (index + 1) % MemSize;
}

template<typename ValType>
TQueue<ValType>::TQueue(int Size)
{
  if (Size <= 0)
    throw "Invalid size";
  MemSize = Size;
  DataCount = 0;
  Li = 0;
  Hi = MemSize - 1;
  pMem = nullptr;
  pMem = new ValType[MemSize];
}

template<typename ValType>
TQueue<ValType>::~TQueue()
{
  if (pMem != nullptr)
    delete[] pMem;
  pMem = nullptr;
}

template<typename ValType>
int TQueue<ValType>::IsEmpty(void) const
{
  return DataCount == 0;
}

template<typename ValType>
int TQueue<ValType>::IsFull(void) const
{
  return DataCount == MemSize;
}

template<typename ValType>
void TQueue<ValType>::Put(const ValType& Val)
{
  if (IsFull())
    throw "Queue is full";
  Hi = GetNextIndex(Hi);
  pMem[Hi] = Val;
  DataCount++;
}

template<typename ValType>
ValType TQueue<ValType>::Get(void)
{
  if (IsEmpty())
    throw "Queue is empty";
  ValType temp = pMem[Li];
  Li = GetNextIndex(Li);
  DataCount--;
  return temp;
}

template<typename ValType>
ValType TQueue<ValType>::GetMin()
{
    ValType min = pMem[Li];
    for (int i = 0, j = Li; i < DataCount; i++)
    {
        if (pMem[i] < min)
            min = pMem[i];
        j = GetNextIndex(j);
    }
    return min;
}

template<typename ValType>
ValType TQueue<ValType>::GetMax()
{
    ValType max = pMem[Li];
    for (int i = 0, j = Li; i < DataCount; i++)
    {
        if (pMem[i] > max)
            max = pMem[i];
        j = GetNextIndex(j);
    }
    return max;
}

template<typename ValType>
TQueue<ValType> TQueue<ValType>::loadFromFile(const char* pathToFile)
{
    ifstream file(pathToFile);
    int size, DataCount;
    file >> size;
    TQueue<ValType> queue(size);
    for (int i = 0; i < DataCount; i++)
    {
        ValType f;
        file >> f;
        queue.Put(f);
    }
    file.close();
    return queue;
}

template<typename ValType>
void TQueue<ValType>::saveToFile(const char* pathToFile)
{
    ofstream file(pathToFile);
    file << MemSize << '\n';
    for (int i = 0, j = Li; i < DataCount; i++)
    {
        file << pMem[j] << '\n';
        j = GetNextIndex(j);
    }
    file.close();
}

#endif
