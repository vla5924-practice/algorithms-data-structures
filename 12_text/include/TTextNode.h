#pragma once
#include <iostream>

class TTextNode
{
protected:
    static TTextNode* firstFree;
    static TTextNode* textNodes;

    TTextNode* next;
    TTextNode* down;
    char c;
    int level;

public:
    TTextNode(int l = 3, char _c = 0);
    TTextNode(char* s, int l);
    TTextNode(const TTextNode& _node);
    ~TTextNode();

    TTextNode* GetNext();
    TTextNode* GetDown();
    char GetC();
    int GetLevel();

    void SetNext(TTextNode* _next);
    void SetDown(TTextNode* _down);
    void SetC(char _c);
    void SetLevel(int _l);

    static void InitMem(int _size = 10);
    static void FreeMem();

    void* operator new(size_t size);
    void operator delete(void* p);

    friend std::ostream& operator<<(std::ostream& o, const TTextNode& t)
    {
        if (t.level == 3)
        {
            o << t.c;
            if (t.next != nullptr)
                o << *(t.next);
        }
        else
        {
            if (t.down != nullptr)
                o << *(t.down);

            if (t.next != nullptr)
                o << *(t.next);
        }

        return o;
    }
};
