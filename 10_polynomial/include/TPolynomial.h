#ifndef _TPOLYNOMIAL_H_
#define _TPOLYNOMIAL_H_

#include <iostream>
#include "TMList.h"

class TPolynomial
{
    TMList m;

    bool IsDimMoreOrEqual(const TMonomial* m1, const TMonomial* m2) const;
    bool IsDimLessOrEqual(const TMonomial* m1, const TMonomial* m2) const;
    bool IsDimEqual(const TMonomial* m1, const TMonomial* m2) const;
    TMonomial* FindSameDim(const TMonomial* monomial) const;
    TMonomial* FindPrevOrdered(const TMonomial* monomial) const;
    void Add(const TMonomial* monomial);
    void AddNonzero(TMonomial* primary, const TMonomial* secondary);
    void Reduce();
public:
    TPolynomial();
    TPolynomial(const TMonomial& monomial);
    TPolynomial(const TPolynomial& other);
    TPolynomial(double number);
    ~TPolynomial();
    TPolynomial& operator=(const TPolynomial& other);
    TPolynomial operator+(const TPolynomial& other);
    TPolynomial operator+(const TMonomial& monomial);
    TPolynomial operator+(double number);
    TPolynomial operator-(const TPolynomial& other);
    TPolynomial operator-(const TMonomial& monomial);
    TPolynomial operator-(double number);
    TPolynomial operator*(const TPolynomial& other);
    TPolynomial operator*(const TMonomial& monomial);
    TPolynomial operator*(double number);
    TPolynomial& operator+=(const TPolynomial& other);
    TPolynomial& operator+=(const TMonomial& monomial);
    TPolynomial& operator+=(double number);
    TPolynomial& operator-=(const TPolynomial& other);
    TPolynomial& operator-=(const TMonomial& monomial);
    TPolynomial& operator-=(double number);
    TPolynomial& operator*=(const TPolynomial& other);
    TPolynomial& operator*=(const TMonomial& monomial);
    TPolynomial& operator*=(double number);
    friend std::ostream& operator<<(std::ostream& s, const TPolynomial& p);
};

#endif
