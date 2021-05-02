#ifndef _TSTACK_H_
#define _TSTACK_H_

template<typename T>
class TStack
{
protected:
    T* pMem;
    int MemSize;
    int Hi;
    bool myMem;
public:
    TStack(int Size = 0, bool myMem_ = false);
    ~TStack();
    int IsEmpty() const;
    int IsFull() const;
    void Put(const T& Val);
    T Get();

    void SetData(T* ptr, int size, int top);
    void Resize(int size);
    int GetSize();
    int GetCount();
};

template<typename T>
TStack<T>::TStack(int Size, bool myMem_)
{
    if (Size < 0)
        throw "Invalid size";
    MemSize = Size;
    Hi = 0;
    myMem = myMem_;
    pMem = nullptr;
    if (Size > 0 && myMem)
        pMem = new T[MemSize];
}

template<typename T>
TStack<T>::~TStack()
{
    if (pMem != nullptr && myMem)
        delete[] pMem;
    pMem = nullptr;
}

template<typename T>
int TStack<T>::IsEmpty(void) const
{
    return Hi == 0;
}

template<typename T>
int TStack<T>::IsFull(void) const
{
    return Hi == MemSize;
}

template<typename T>
void TStack<T>::Put(const T& Val)
{
    if (IsFull())
        throw "Stack is full";
    pMem[Hi] = Val;
    Hi++;
}

template<typename T>
T TStack<T>::Get(void)
{
    if (IsEmpty())
        throw "Stack is empty";
    Hi--;
    return pMem[Hi];
}

template<typename T>
void TStack<T>::SetData(T* ptr, int size, int top)
{
    pMem = ptr;
    Size = size;
    Hi = top;
}

template<typename T>
void TStack<T>::Resize(int size)
{
    if (size <= 0)
        throw "Invalid size";
    if (size == Size)
        return;
    T* temp = new T[size];
    Size = size > Size ? Size : size;
    for (int i = 0; i < Size; i++)
        temp[i] = pMem[i];
    if (data != nullptr)
        delete[] data;
    data = temp;
    Size = size;
    Hi = Hi > Size ? Size : Hi;
}

template<typename T>
int TStack<T>::GetSize()
{
    return MemSize;
}

template<typename T>
int TStack<T>::GetCount()
{
    return Hi;
}

#endif
