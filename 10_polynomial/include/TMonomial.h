#ifndef _TMONOMIAL_H_
#define _TMONOMIAL_H_

#include <iostream>

class TMonomial
{
    void CheckDims(const TMonomial& other) const
    {
        if (dim != other.dim)
            throw "Unequal dim";
        for (int i = 0; i < dim; i++)
            if (data[i] != other.data[i])
                throw "Unequal dim";
    }

public:
    int* data;
    int dim;
    double k;
    TMonomial* prev;
    TMonomial* next;

    TMonomial(double k_ = 0, 
              int dim_ = 0,
              TMonomial* prev_ = nullptr, 
              TMonomial* next_ = nullptr)
        : k(k_), dim(dim_), prev(prev_), next(next_)
    {
        if (dim < 0)
            throw "Unexpected dim";
        if (dim == 0)
            data = nullptr;
        else
        {
            data = new int[dim];
            for (int i = 0; i < dim; i++)
                data[i] = 1;
        }
    }

    TMonomial(const TMonomial& other)
    {
        k = other.k;
        dim = other.dim;
        next = other.next;
        prev = other.prev;
        if (dim == 0)
            data = nullptr;
        else
        {
            data = new int[dim];
            for (int i = 0; i < dim; i++)
                data[i] = other.data[i];
        }
    }

    TMonomial(const TMonomial* other, TMonomial* prev_, TMonomial* next_)
    {
        k = other->k;
        dim = other->dim;
        next = next_;
        prev = prev_;
        if (dim == 0)
            data = nullptr;
        else
        {
            data = new int[dim];
            for (int i = 0; i < dim; i++)
                data[i] = other->data[i];
        }
    }

    ~TMonomial()
    {
        if (data != nullptr)
            delete[] data;
        data = nullptr;
        dim = 0;
    }

    TMonomial operator+(const TMonomial& other) const
    {
        CheckDims(other);
        TMonomial res(*this);
        res.k += other.k;
        return res;
    }

    TMonomial operator-(const TMonomial& other) const
    {
        CheckDims(other);
        TMonomial res(*this);
        res.k -= other.k;
        return res;
    }

    TMonomial operator*(const TMonomial& other) const
    {
        if (dim > other.dim)
        {
            TMonomial res(*this);
            res.k *= other.k;
            for (int i = 0; i < other.dim; i++)
                res.data[i] += other.data[i];
            return res;
        }
        else
        {
            TMonomial res(other);
            res.k *= k;
            for (int i = 0; i < dim; i++)
                res.data[i] += data[i];
            return res;
        }
    }

    TMonomial operator*(double number) const
    {
        TMonomial res(*this);
        res.k *= number;
        return res;
    }

    TMonomial operator+() const
    {
        return *this;
    }

    TMonomial operator-() const
    {
        TMonomial res(*this);
        res.k = -res.k;
        return res;
    }

    int& operator[](int index)
    {
        if (index < 0 || index >= dim)
            throw "Index invalid";
        return data[index];
    }

    friend std::ostream& operator<<(std::ostream& s, const TMonomial& m)
    {
        if (m.k == 0)
            return s << "+0";
        if (m.k > 0)
            s << '+';
        s << m.k;
        for (int i = 0; i < m.dim; i++)
            s << "*x_" << i << '^' << m.data[i];
        return s;
    }
};

#endif
