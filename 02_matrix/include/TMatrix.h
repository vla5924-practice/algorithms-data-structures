#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include "TVector.h"

template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
  using TVector<TVector<ValType>>::pVector;
  using TVector<TVector<ValType>>::Size;
public:
  TMatrix(int s = 10);
  TMatrix(const TMatrix& mt);                    // копирование
  TMatrix(const TVector<TVector<ValType>>& mt);  // преобразование типа
  bool operator==(const TMatrix& mt) const;      // сравнение
  bool operator!=(const TMatrix& mt) const;      // сравнение
  TMatrix& operator= (const TMatrix& mt);        // присваивание
  TMatrix  operator+ (const TMatrix& mt);        // сложение
  TMatrix  operator- (const TMatrix& mt);        // вычитание

  // ввод / вывод
  friend std::istream& operator>>(std::istream& in, TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend std::ostream& operator<<(std::ostream& out, const TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << std::endl;
    return out;
  }
};

template<typename ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType>>(s)
{
  for (int i = 0; i < Size; i++)
    pVector[i] = TVector<ValType>(Size - i, i);
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt)
  : TVector<TVector<ValType>>(mt)
{
}

template<typename ValType>
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt)
  : TVector<TVector<ValType>>(mt)
{
  for (int i = 0; i < Size; i++)
    if (mt[i].GetSize() != Size - i)
      throw "Matrix is non-convertible";
}

template<typename ValType>
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  if (Size != mt.Size)
    return false;
  for (int i = 0; i < mt.Size; i++)
    if (pVector[i] != mt.pVector[i])
      return false;
  return true;
}

template<typename ValType>
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
  return !(*this == mt);
}

template<typename ValType>
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
  if (this != &mt)
  {
    if (Size != mt.Size)
    {
      Size = mt.Size;
      delete[] pVector;
      pVector = new TVector<ValType>[mt.Size];
    }
    for (int i = 0; i < mt.Size; i++)
      pVector[i] = mt.pVector[i];
  }
  return *this;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix& mt)
{
  if (Size != mt.Size)
    throw "Matrices have different sizes";
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] = result.pVector[i] + mt.pVector[i];
  return result;
}

template<typename ValType>
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix& mt)
{
  if (Size != mt.Size)
    throw "Matrices have different sizes";
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] = result.pVector[i] - mt.pVector[i];
  return result;
}

#endif
