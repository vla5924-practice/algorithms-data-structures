#ifndef _TLIST_H_
#define _TLIST_H_

#include <iostream>

template<typename T>
class TListElem
{
public:
    T data;
    TListElem* prev;
    TListElem* next;

    TListElem(T data_, TListElem<T>* prev_, TListElem<T>* next_)
        : data(data_), prev(prev_), next(next_) {};
};

template<typename T>
class TListIterator
{
    TListElem<T>* e;
public:
    TListIterator(TListElem<T>* e_) { e = e_; }
    TListIterator(const TListIterator<T>& other) { e = other.e; }

    bool HaveData() { return e != nullptr; }
    T GetData() { return e->data; }
    T* GetDataPtr() { return &(e->data); }

    bool HaveNext() { return e != nullptr && e->next != nullptr; }
    bool HavePrev() { return e != nullptr && e->prev != nullptr; }

    void GoNext() { e = e->next; }
    void GoPrev() { e = e->prev; }

    TListIterator<T> GetNext() { return e->next; }
    TListIterator<T> GetPrev() { return e->prev; }
};

template<typename T>
class TList
{
protected:
    TListElem<T>* root;
    TListElem<T>* end;
    int count;
public:
    TList();
    TList(const TList<T>& other);
    ~TList();

    TList<T>& operator=(const TList<T>& other);

    bool IsEmpty();
    void InsFirst(T d);
    void InsLast(T d);
    void InsAfter(TListElem<T>* e, T d);
    void InsBefore(TListElem<T>* e, T d);

    TListElem<T>* GetFirst();
    TListElem<T>* GetLast();
    int GetCount();

    void DelFirst();
    void DelLast();
    void Del(TListElem<T>* e);

    template<typename T_>
    friend std::ostream& operator<<(std::ostream& s, const TList<T_>& list)
    {
        TListElem<T_>* i = list.root;
        while (i != nullptr)
        {
            s << i->data << ' ';
            i = i->next;
        }
        return s;
    }

    static TList LoadFromFile(const char* pathToFile);
    void SaveToFile(const char* pathToFile);
    TList<T> GetDiv(T k);
    
    TListIterator<T> GetFirstIterator();
    TListIterator<T> GetLastIterator();
};

template<typename T>
TList<T>::TList()
    : root(nullptr), end(nullptr), count(0)
{
}

template<typename T>
TList<T>::TList(const TList<T>& other)
    : TList()
{
    count = other.count;
    if (other.count == 0)
        return;
    root = new TListElem<T>(other.root->data, nullptr, nullptr);
    if (other.count == 1)
    {
        end = root;
        return;
    }
    TListElem<T>* i = other.root->next;
    TListElem<T>* j = root;
    TListElem<T>* k = root;
    while (i != nullptr)
    {
        j = new TListElem<T>(i->data, k, nullptr);
        k->next = j;
        k = j;
        i = i->next;
    }
    end = j;
}

template<typename T>
TList<T>::~TList()
{
    if (root == nullptr)
        return;
    TListElem<T>* i = root;
    TListElem<T>* j = i;
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

template<typename T>
TList<T>& TList<T>::operator=(const TList<T>& other)
{
    if (root != nullptr)
    {
        TListElem<T>* i = root;
        TListElem<T>* j = i;
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
    root = new TListElem<T>(other.root->data, nullptr, nullptr);
    if (other.count == 1)
    {
        end = root;
        return *this;
    }
    TListElem<T>* i = other.root->next;
    TListElem<T>* j = root;
    TListElem<T>* k = root;
    while (i != nullptr)
    {
        j = new TListElem<T>(i->data, k, nullptr);
        k->next = j;
        k = j;
        i = i->next;
    }
    end = j;
    return *this;
}

template<typename T>
bool TList<T>::IsEmpty()
{
    return count == 0;
}

template<typename T>
void TList<T>::InsFirst(T d)
{
    TListElem<T>* newRoot = new TListElem<T>(d, nullptr, root);
    if (root != nullptr)
        root->prev = newRoot;
    root = newRoot;
    if (count == 0)
        end = root;
    count += 1;
}

template<typename T>
void TList<T>::InsLast(T d)
{
    TListElem<T>* newEnd = new TListElem<T>(d, end, nullptr);
    if (end != nullptr)
        end->next = newEnd;
    end = newEnd;
    if (count == 0)
        root = end;
    count += 1;
}

template<typename T>
void TList<T>::InsAfter(TListElem<T>* e, T d)
{
    if (e == end)
    {
        InsLast(d);
        return;
    }
    TListElem<T>* newElem = new TListElem<T>(d, e, e->next);
    e->next = newElem;
    newElem->next->prev = newElem;
    count += 1;
}

template<typename T>
void TList<T>::InsBefore(TListElem<T>* e, T d)
{
    if (e == root)
    {
        InsFirst(d);
        return;
    }
    TListElem<T>* newElem = new TListElem<T>(d, e->prev, e);
    e->prev = newElem;
    newElem->prev->next = newElem;
    count += 1;
}

template<typename T>
TListElem<T>* TList<T>::GetFirst()
{
    return root;
}

template<typename T>
TListElem<T>* TList<T>::GetLast()
{
    return end;
}

template<typename T>
int TList<T>::GetCount()
{
    return count;
}

template<typename T>
void TList<T>::DelFirst()
{
    if (root == nullptr)
        return;
    TListElem<T>* temp = root;
    root = root->next;
    if (root != nullptr)
        root->prev = nullptr;
    delete temp;
    if (count == 1)
        end = nullptr;
    count -= 1;
}

template<typename T>
void TList<T>::DelLast()
{
    if (end == nullptr)
        return;
    TListElem<T>* temp = end;
    end = end->prev;
    if (end != nullptr)
        end->next = nullptr;
    delete temp;
    if (count == 1)
        root = nullptr;
    count -= 1;
}

template<typename T>
void TList<T>::Del(TListElem<T>* e)
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

template<typename T>
TList<T> TList<T>::LoadFromFile(const char* pathToFile)
{
    ifstream file(pathToFile);
    int count;
    file >> count;
    TList<T> list;
    for (int i = 0; i < count; i++)
    {
        T f;
        file >> f;
        list.InsLast(f);
    }
    file.close();
    return list;
}

template<typename T>
void TList<T>::SaveToFile(const char* pathToFile)
{
    ofstream file(pathToFile);
    file << count << '\n';
    TListElem<T>* temp = root;
    while (temp != nullptr)
    {
        file << temp->data << '\n';
        temp = temp->next;
    }
    file.close();
}

template<typename T>
TList<T> TList<T>::GetDiv(T k)
{
    TList<T> result;
    TListElem<T>* temp = root;
    while (temp != nullptr)
    {
        if (temp->data % k == 0)
            result.InsLast(temp->data);
        temp = temp->next;
    }
    return result;
}

template<typename T>
TListIterator<T> TList<T>::GetFirstIterator()
{
    return TListIterator<T>(root);
}

template<typename T>
TListIterator<T> TList<T>::GetLastIterator()
{
    return TListIterator<T>(end);
}

#endif
