#include "TText.h"
#include "TTextIter.h"

TText::TText(char* s)
{
    root = new TTextNode(s, 1);
}

TText::~TText()
{
    TTextNode::FreeMem();
}

TTextIter TText::GetRoot()
{
    TStack<TTextNode*> A(100);
    TTextIter B(*this, root, A);
    return B;
}

TTextIter TText::Find(char c)
{
    TTextIter iter = GetRoot();

    while (iter.GoNextChar())
    {
        if (iter.Get()->GetC() == c)
        {
            return iter;
        }
    }
    return iter;
}

TTextIter TText::FindWord(char* c)
{
    TStack<TTextNode*> A(100);
    TTextIter iter(*this, root, A);

    while (iter.GoNext())
    {
        if (iter.Get()->GetLevel() == 2)
        {
            TTextIter resuls = iter;
            bool control = true;
            int i = 0;
            size_t n = strlen(c);

            while (iter.GoNext() && i < n)
            {
                if (iter.Get()->GetLevel() == 2)
                {
                    control = false;
                    break;
                }

                if (iter.Get()->GetC() != c[i])
                {
                    control = false;
                    break;
                }
                i++;
            }

            if (control)
            {
                return resuls;
            }
        }
    }
    return iter;
}

TTextIter TText::Find(char* s)
{
    TStack<TTextNode*> A(100);
    TTextIter iter(*this, root, A);
    size_t n = strlen(s);

    while (iter.GoNextChar())
    {
        TTextIter cur = iter;
        int i = 0;
        bool control = true;
        bool next = true;
        while (i < n)
        {
            if (!next)
            {
                control = false;
                break;
            }
            if (s[i] != cur.Get()->GetC()) {
                control = false;
                break;
            }
            next = cur.GoNextChar();
            i++;
        }

        if (control)
        {
            return iter;
        }
    }
    throw "not found";
}

void TText::Insert(char* c, TTextIter i)
{
    TTextNode* node = new TTextNode(c, i.Get()->GetLevel());
    TTextNode* next = i.Get()->GetNext();
    node->SetNext(next);
    i.Get()->SetNext(node);
}

inline void TText::InsertData(char* c, TTextIter i)
{
    if (strlen(c) == 1) 
    {
        Insert(c, i);
    }
    else 
    {
        int level = 2;
        int space = 0;

        for (int q = 0; q < strlen(c); q++)
        {
            if (c[q] == ' ') 
            {
                level = 1;
                break;
            }
        }

        TTextIter osn = i;
        TTextNode* next = i.Get()->GetNext();

        if (next->GetC() == ' ' || next->GetC() == '.') 
        {
            i.GoNextChar(); 
            size_t size = strlen(c);
            char* t = new char[size + 1];
            t[size + 1] = '\0';

            for (size_t j = 0; j < size; j++)
            {
                t[j] = c[j];
            }
            t[size] = ' ';

            TTextNode* node = new TTextNode(t, level);

            next->SetNext(node);
            i.Get()->SetNext(node);
        }
        else 
        {
            int cc = 0;
            char symbol = ' ';
            TTextNode* cc_node = i.Get()->GetNext();
            while ((cc_node->GetC() != '.') && (cc_node->GetC() != ' ') && (cc_node->GetC() != '\n'))
            {
                cc++;
                cc_node = cc_node->GetNext();
            }
            if (cc_node->GetC() == '.')
                symbol = '.';
            if (cc_node->GetC() == '\n')
                symbol = '\n';
            char* temp = new char[strlen(c) + cc + 3];
            temp[strlen(c) + cc + 3] = '\0';
            temp[0] = ' ';
            int j = 1;
            int k = 0;
            for (j; j < strlen(c) + 1; j++, k++)
                temp[j] = c[k];
            temp[j] = ' ';

            TTextNode* temp_node = i.Get()->GetNext();
            for (j = j + 1; j < strlen(c) + cc + 2; j++)
            {
                temp[j] = temp_node->GetC();
                temp_node = temp_node->GetNext();
            }
            temp[strlen(c) + cc + 2] = symbol;
            osn.GoNext();
            this->Delete(cc, osn);
            TTextNode* node = new TTextNode(temp, level);
            next->SetNext(node);
            i.Get()->SetNext(node);
        }
    }
}

void TText::Delete(int count, TTextIter i)
{
    if (count == 0)
        return;

    TStack<TTextNode*> stacks[3];
    int del = 0;
    int level = i.Get()->GetLevel();
    
    if (level < 3)
        i.GoNextChar();

    if (level >= 1 && level <= 3)
    {
        stacks[level - 1].Put(i.Get());
        if (level == 3)
            del++;
    }

    TTextIter iter = i;
    while (iter.GoNext() && del < count)
    {
        level = iter.Get()->GetLevel();
        if (level >= 1 && level <= 3)
        {
            stacks[level - 1].Put(iter.Get());
            if (level == 3)
                del++;
        }
    }

    if (del < count)
        throw "error";

    if (stacks[0].IsEmpty() && stacks[1].IsEmpty())
    {
        TTextIter prev = i;
        prev.ResetToWord();
        while (prev.Get()->GetNext() != i.Get() && prev.Get()->GetDown() != i.Get())
            prev.GoNext();
        TTextNode* last = stacks[2].Get();
        if (prev.Get()->GetLevel() == 2)
            prev.Get()->SetDown(last->GetNext());
        else
            prev.Get()->SetNext(last->GetNext());
        delete last;
        return;
    }

    TTextIter prev = i;
    prev.ResetToWord();

    while (prev.Get()->GetNext() != i.Get() && prev.Get()->GetDown() != i.Get())
        prev.GoNext();

    if (prev.Get()->GetNext() == i.Get())
        prev.Get()->SetNext(nullptr);
    else
        prev.Get()->SetDown(nullptr);

    if (stacks[0].IsEmpty()) 
    {
        TTextNode* last_word = stacks[1].Get();
        TTextNode* last_letter = stacks[2].Get();
        TTextIter cur = i;
        cur.ResetToWord();
        cur.Get()->SetNext(last_word);
        last_word->SetDown(last_letter->GetNext());
        delete last_letter;
        for (int i = 1; i < 3; i++)
        {
            while (!stacks[i].IsEmpty())
                delete stacks[i].Get();
        }
    }
    else 
    {
        TTextNode* last_string = stacks[0].Get();
        TTextNode* last_word = stacks[1].Get();
        TTextNode* last_letter = stacks[2].Get();
        TTextIter cur = i;
        cur.ResetToString();
        cur.Get()->SetNext(last_string);
        cur.ResetToWord();
        cur.Get()->SetNext(last_word);
        last_word->SetDown(last_letter->GetNext());
        delete last_letter;

        for (int i = 0; i < 3; i++)
        {
            while (!stacks[i].IsEmpty())
            {
                TTextNode* temp = stacks[i].Get();
                delete temp;
            }
        }
    }
}

char* TText::Copy(int count, TTextIter i)
{
    if (count < 0)
    {
        throw "error";
    }

    char* res = new char[count + 1];
    TTextIter iter = i;

    while (iter.Get()->GetLevel() < 3)
    {
        iter.GoNext();
    }

    if (count > 0)
    {
        res[0] = iter.Get()->GetC();
        int j = 1;

        while (iter.GoNextChar() && j < count)
        {
            res[j] = iter.Get()->GetC();
            j++;
        }
    }

    res[count] = '\0';
    return res;
}
