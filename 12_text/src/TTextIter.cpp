#include "TTextIter.h"

TTextIter::TTextIter(TText& _text, TTextNode* _node, TStack<TTextNode*> _st)
    : text(_text), node(_node), st(_st)
{
}

TTextIter::TTextIter(const TTextIter& t)
    : text(t.text), node(t.node), st(t.st)
{
}

bool TTextIter::GoNext() 
{
    if (node->GetLevel() == 3)
    {
        if (node->GetNext() != nullptr)
        {
            node = node->GetNext();
        }
        else
        {
            node = st.Get();

            if (node->GetNext() != nullptr)
            {
                node = node->GetNext();
            }
            else
            {
                node = st.Get();
                if (node->GetNext() != nullptr)
                {
                    node = node->GetNext();
                }
                else
                {
                    node = nullptr;
                    return false;
                }
            }
        }
    }
    else
    {
        st.Put(node);
        node = node->GetDown();
    }
    return true;
}

bool TTextIter::GoNextChar()
{
    if (node->GetLevel() == 1)
    {
        st.Put(node);
        node = node->GetDown();
        st.Put(node);
        node = node->GetDown();
        return true;
    }

    if (node->GetLevel() == 2)
    {
        st.Put(node);
        node = node->GetDown();
        return true;
    }

    if (node->GetLevel() == 3 && node->GetNext() != nullptr)
    {
        node = node->GetNext();
        return true;
    }

    if (node->GetLevel() == 3 && node->GetNext() == nullptr)
    {
        if (st.IsEmpty())
        {
            throw "error"; 
        }

        TTextNode* temp = st.Get();

        if (temp->GetNext() != nullptr)
        {
            st.Put(temp->GetNext());
            node = temp->GetNext()->GetDown();
            return true;
        }

        return false;
    }
    return false;
}

bool TTextIter::IsEnd()
{
    if (node == nullptr)
        return true;
    if (node->GetLevel() == 1 || node->GetLevel() == 2)
        return false;

    if (node->GetLevel() == 3 && node->GetNext() != nullptr)
        return false;

    if (node->GetLevel() == 3 && node->GetNext() == nullptr)
    {
        if (st.IsEmpty())
            throw "error"; 

        TTextNode* prev = st.Get();
        if (prev->GetNext() != nullptr)
            return false;

        return true;
    }

    return true;
}

void TTextIter::ResetToString() {
    while (node->GetLevel() > 1)
    {
        if (st.IsEmpty())
            throw "error";
        node = st.Get();
    }
}

void TTextIter::ResetToWord()
{
    if (node->GetLevel() == 1)
    {
        st.Put(node);
        node = node->GetDown();
    }
    else if (node->GetLevel() == 3)
    {
        node = st.Get();
    }
}

TTextNode* TTextIter::Get()
{
    return node;
}
