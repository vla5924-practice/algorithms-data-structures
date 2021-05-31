#include "TTextNode.h"

#include <cstring>

TTextNode* TTextNode::firstFree = nullptr;
TTextNode* TTextNode::textNodes = nullptr;

TTextNode::TTextNode(int l, char _c)
{
    next = nullptr;
    down = nullptr;
    c = _c;
    level = l;
}

TTextNode::TTextNode(char* s, int l) : TTextNode()
{
    if (l < 1 || l > 3)
        throw "invalid level";

    if (l == 1) {
        next = nullptr;
        c = 0;
        level = l;
        size_t size = strlen(s); 

        if (size > 0)
        {
            size_t start = 0;
            TTextNode* curr = new TTextNode(2);
            this->SetDown(curr);

            for (size_t i = 0; i < size; i++)
            {
                if (s[i] == ' ' || i == size - 1) 
                {
                    if (start != 0)
                    {
                        curr->SetNext(new TTextNode(2)); 
                        curr = curr->GetNext(); 
                    }

                    TTextNode* lcur = new TTextNode(3, s[start]); 
                    curr->SetDown(lcur); 

                    for (size_t j = start + 1; j <= i; j++)
                    {
                        lcur->SetNext(new TTextNode(3, s[j]));
                        lcur = lcur->GetNext();
                    }
                    lcur->SetNext(nullptr);
                    start = i + 1;
                }
            }
            curr->SetNext(nullptr);
        }
        return;
    }

    if (l == 2) {
        next = nullptr;
        c = 0;
        level = l;
        size_t size = strlen(s); 
        if (size > 0)
        {
            TTextNode* lcur = new TTextNode(3, s[0]);
            this->SetDown(lcur);

            for (size_t i = 1; i < size; i++)
            {
                lcur->SetNext(new TTextNode(3, s[i]));
                lcur = lcur->GetNext();
            }
            lcur->SetNext(nullptr);
        }
        return;
    }

    if (l == 3)
    {
        c = s[0]; 
        level = l; 
        next = nullptr;
        down = nullptr;
        return;
    }
}

TTextNode::TTextNode(const TTextNode& _node)
{
    next = nullptr;
    down = nullptr;
    c = _node.c;
    level = _node.level;
}

TTextNode::~TTextNode() 
{
}

TTextNode* TTextNode::GetNext()
{
    return next;
}

TTextNode* TTextNode::GetDown()
{
    return down;
}

char TTextNode::GetC()
{
    return c;
}

int TTextNode::GetLevel()
{
    return level;
}

void TTextNode::SetNext(TTextNode* _next)
{
    next = _next;
}

void TTextNode::SetDown(TTextNode* _down)
{
    down = _down;
}

void TTextNode::SetC(char _c)
{
    c = _c;
}

void TTextNode::SetLevel(int _l)
{
    if (_l < 1 || _l > 3)
        throw "invalid level";
    level = _l;
}

void TTextNode::InitMem(int _size) 
{
    if (_size <= 0)
        throw "invalid size";

    if (firstFree == nullptr && textNodes == nullptr)
    {
        textNodes = new TTextNode[_size];
        firstFree = textNodes;
    }
    else if (firstFree != nullptr && textNodes == nullptr)
    {
        throw "bad memory initialized";
    }
    else
    {
        TTextNode* temp = new TTextNode[_size];
        for (int i = 0; i < _size; i++)
            temp[i] = (textNodes[i]);
        textNodes = new TTextNode[_size * 2];
        firstFree = textNodes;
        for (int i = 0; i < _size; i++)
            textNodes[i] = temp[i];
        delete[] temp;
    }
}

void TTextNode::FreeMem() 
{
    if (textNodes != nullptr)
        delete[] textNodes;
    textNodes = nullptr;
    firstFree = nullptr;
}

void* TTextNode::operator new(size_t size)
{
    if (firstFree == nullptr)
        InitMem();

    TTextNode* node = firstFree;
    firstFree = firstFree->next;
    node->next = 0;
    return node;
}

void TTextNode::operator delete(void* p)
{
    TTextNode* node = reinterpret_cast<TTextNode*>(p);

    if (firstFree == nullptr && textNodes == nullptr)
        return;

    node->next = nullptr;
    node->down = nullptr;
    node->c = 0;
    node->level = 3;
    node->next = firstFree;
    firstFree = node;
}
