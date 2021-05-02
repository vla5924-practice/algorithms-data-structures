#include "TPolynomial.h"

bool TPolynomial::IsDimMoreOrEqual(const TMonomial* m1, const TMonomial* m2) const
{
    if (m1->dim != m2->dim)
        return m1->dim >= m2->dim;
    for (int i = 0; i < m1->dim; i++)
        if (m1->data[i] < m2->data[i])
            return false;
    return true;
}

bool TPolynomial::IsDimLessOrEqual(const TMonomial* m1, const TMonomial* m2) const
{
    if (m1->dim != m2->dim)
        return m1->dim <= m2->dim;
    for (int i = 0; i < m1->dim; i++)
        if (m1->data[i] > m2->data[i])
            return false;
    return true;
}

bool TPolynomial::IsDimEqual(const TMonomial* m1, const TMonomial* m2) const
{
    if (m1->dim != m2->dim)
        return false;
    for (int i = 0; i < m1->dim; i++)
        if (m1->data[i] != m2->data[i])
            return false;
    return true;
}

TMonomial* TPolynomial::FindSameDim(const TMonomial* monomial) const
{
    for (TMonomial* i = m.GetFirst(); i != nullptr; i = i->next)
        if (IsDimEqual(i, monomial))
            return i;
    return nullptr;
}

TMonomial* TPolynomial::FindPrevOrdered(const TMonomial* monomial) const
{
    if (!m.IsEmpty())
    {
        TMonomial* first = m.GetFirst();
        if (IsDimMoreOrEqual(monomial, first))
            return nullptr;
    }
    TMonomial* i = m.GetFirst();
    TMonomial* temp = i;
    for (; i->next != nullptr; i = i->next)
    {
        temp = i;
        TMonomial* next = temp->next;
        if(IsDimLessOrEqual(next, monomial))
            return temp;
    }
    if (temp->next == nullptr)
        return temp;
    else
        return i;
}

void TPolynomial::Add(const TMonomial* monomial)
{
    TMonomial* prevOrdered = FindPrevOrdered(monomial);
    if (prevOrdered != nullptr)
        m.InsAfter(prevOrdered, *monomial);
    else
        m.InsFirst(*monomial);
}

void TPolynomial::AddNonzero(TMonomial* primary, const TMonomial* secondary)
{
    if (primary)
    {
        if (secondary)
            *primary = *primary + *secondary;
        if (primary->data == 0)
            m.Del(primary);
        return;
    }
    if (secondary && secondary->k)
        Add(secondary);
}

void TPolynomial::Reduce()
{
    for (TMonomial* i = m.GetFirst(); i != nullptr; i = i->next)
    {
        TMonomial* control = i;
        if (control->k == 0)
        {
            m.Del(i);
            continue;
        }
        for (TMonomial* j = i->next; i != nullptr; j = j->next)
        {
            TMonomial* monomial = j;
            if (monomial->k == control->k)
            {
                control->k += monomial->k;
                m.Del(j);
            }
        }
    }
}

TPolynomial::TPolynomial()
{
}

TPolynomial::TPolynomial(const TMonomial& monomial)
{
    m.InsFirst(monomial);
}

TPolynomial::TPolynomial(double number)
{
    m.InsFirst(TMonomial(number));
}

TPolynomial::TPolynomial(const TPolynomial& other)
{
    m = other.m;
}

TPolynomial::~TPolynomial()
{
}

TPolynomial& TPolynomial::operator=(const TPolynomial& other)
{
    if (this == &other)
        return *this;
    m = other.m;
    return *this;
}

TPolynomial TPolynomial::operator+(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomial* i = other.m.GetFirst(); i != nullptr; i = i->next)
    {
        TMonomial* monomial = result.FindSameDim(i);
        result.AddNonzero(monomial, i);
    }
    return result;
}

TPolynomial TPolynomial::operator+(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomial* i = result.FindSameDim(&monomial);
    result.AddNonzero(i, &monomial);
    return result;
}

TPolynomial TPolynomial::operator+(double number)
{
    if (number == 0)
        return *this;
    return *this + TMonomial(number);
}

TPolynomial TPolynomial::operator-(const TPolynomial& other)
{
    TPolynomial result(*this);
    for (TMonomial* i = other.m.GetFirst(); i != nullptr; i = i->next)
    {
        TMonomial* monomial = result.FindSameDim(i);
        result.AddNonzero(monomial, &-(*i));
    }
    return result;
}

TPolynomial TPolynomial::operator-(const TMonomial& monomial)
{
    TPolynomial result(*this);
    TMonomial* i = result.FindSameDim(&monomial);
    result.AddNonzero(i, &-monomial);
    return result;
}

TPolynomial TPolynomial::operator-(double number)
{
    if (number == 0)
        return *this;
    return *this - TMonomial(number);
}

TPolynomial TPolynomial::operator*(const TPolynomial& other)
{
    TPolynomial result;
    for (TMonomial* i = m.GetFirst(); i != nullptr; i = i->next)
    {
        for (TMonomial* j = other.m.GetFirst(); j != nullptr; j = j->next)
        {
            TMonomial monomial = (*i) * (*j);
            if (monomial.k)
                result.Add(&monomial);
        }
    }
    result.Reduce();
    return result;
}

TPolynomial TPolynomial::operator*(const TMonomial& monomial)
{
    if (monomial.k == 0.)
        return TPolynomial();
    TPolynomial result(*this);
    for (TMonomial* i = m.GetFirst(); i != nullptr; i = i->next)
    {
        TMonomial res = (*i) * monomial;
        if (res.k)
            result.Add(&res);
    }
    result.Reduce();
    return result;
}

TPolynomial TPolynomial::operator*(double number)
{
    if (number == 0)
        return TPolynomial();
    TPolynomial result(*this);
    for (TMonomial* i = result.m.GetFirst(); i != nullptr; i = i->next)
    {
        i->k *= number;
    }
    return result;
}

TPolynomial& TPolynomial::operator+=(const TPolynomial& other)
{
    *this = *this + other;
    return *this;
}

TPolynomial& TPolynomial::operator+=(const TMonomial& monomial)
{
    *this = *this + monomial;
    return *this;
}

TPolynomial& TPolynomial::operator+=(double number)
{
    *this = *this + number;
    return *this;
}

TPolynomial& TPolynomial::operator-=(const TPolynomial& other)
{
    *this = *this - other;
    return *this;
}

TPolynomial& TPolynomial::operator-=(const TMonomial& monomial)
{
    *this = *this - monomial;
    return *this;
}

TPolynomial& TPolynomial::operator-=(double number)
{
    *this = *this - number;
    return *this;
}

TPolynomial& TPolynomial::operator*=(const TPolynomial& other)
{
    *this = *this * other;
    return *this;
}

TPolynomial& TPolynomial::operator*=(const TMonomial& monomial)
{
    *this = *this * monomial;
    return *this;
}

TPolynomial& TPolynomial::operator*=(double number)
{
    *this = *this * number;
    return *this;
}

std::ostream& operator<<(std::ostream& s, const TPolynomial& p)
{
    if (p.m.IsEmpty())
        return s << '0';
    for (TMonomial* i = p.m.GetFirst(); i != nullptr; i = i->next)
        s << *i;
    return s;
}
