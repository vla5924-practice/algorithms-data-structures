#ifndef _TBANDMATRIX_H_
#define _TBANDMATRIX_H_

#include <iostream>
#include <cstring>

template<typename ValType>
class TBandMatrix
{
	int rows;
	int cols;
	ValType* m;
public:
	TBandMatrix();
	TBandMatrix(const TBandMatrix& other);
	TBandMatrix(int rows_, int cols_);
	TBandMatrix(ValType* other, int rows, int cols);
	~TBandMatrix();

	TBandMatrix<ValType>& operator=(const TBandMatrix<ValType>& other);
	TBandMatrix<ValType> operator+(const TBandMatrix<ValType>& other);
	TBandMatrix<ValType> operator+(ValType d);
	TBandMatrix<ValType> operator-(const TBandMatrix<ValType>& other);
	TBandMatrix<ValType> operator-(ValType d);
	TBandMatrix<ValType> operator*(const TBandMatrix<ValType>& other);
	TBandMatrix<ValType> operator*(ValType d);
	ValType* operator[](int index);

	friend std::ostream& operator<<(std::ostream& s, const TBandMatrix& m)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
				s << m[i * cols + j] << " ";
			s << '\n';
		}
		return s;
	}
};

template<typename ValType>
TBandMatrix<ValType>::TBandMatrix()
{
	rows = 0;
	cols = 0;
	m = nullptr;
}

template<typename ValType>
TBandMatrix<ValType>::TBandMatrix(const TBandMatrix& other)
{
	rows = other.rows;
	cols = other.cols;
	int elements = rows * cols;
	if (elements == 0)
		m = nullptr;
	else
	{
		m = new ValType[elements];
		for (int i = 0; i < elements; i++)
			m[i] = other.m[i];
	}
}

template<typename ValType>
TBandMatrix<ValType>::TBandMatrix(int rows_, int cols_)
{
	if (rows < 0 || cols < 0)
		throw "Invalid sizes";
	rows = rows_;
	cols = cols_;
	int elements = rows * cols;
	m = elements > 0 ? new ValType[elements]() : nullptr;
}

template<typename ValType>
TBandMatrix<ValType>::TBandMatrix(ValType* other, int rows_, int cols_)
{
	if (rows < 0 || cols < 0)
		throw "Invalid sizes";
	rows = rows_;
	cols = cols_;
	int elements = rows * cols;
	if (elements == 0)
		m = nullptr;
	else
	{
		m = new ValType[elements];
		for (int i = 0; i < elements; i++)
			m[i] = other.m[i];
	}
}

template<typename ValType>
TBandMatrix<ValType>::~TBandMatrix()
{
	if (m != nullptr)
	{
		delete[] m;
		m = nullptr;
	}
	rows = 0;
	cols = 0;
}

template<typename ValType>
TBandMatrix<ValType> TBandMatrix<ValType>::operator+(const TBandMatrix<ValType>& other)
{
	if (rows != other.rows || cols != other.cols)
		throw "Unequal sizes";
	TBandMatrix<ValType> result(*this);
	int elements = rows * cols;
	for (int i = 0; i < elements; i++)
		result.m[i] += other.m[i];
	return result;
}

template<typename ValType>
TBandMatrix<ValType> TBandMatrix<ValType>::operator+(ValType d)
{
	if (rows == 0 || cols == 0)
		return TBandMatrix<ValType>();
	TBandMatrix<ValType> result(*this);
	int elements = rows * cols;
	for (int i = 0; i < elements; i++)
		result.m[i] += d;
	return result;
}

template<typename ValType>
TBandMatrix<ValType> TBandMatrix<ValType>::operator-(const TBandMatrix<ValType>& other)
{
	if (rows != other.rows || cols != other.cols)
		throw "Unequal sizes";
	TBandMatrix<ValType> result(*this);
	int elements = rows * cols;
	for (int i = 0; i < elements; i++)
		result.m[i] -= other.m[i];
	return result;
}

template<typename ValType>
TBandMatrix<ValType> TBandMatrix<ValType>::operator-(ValType d)
{
	if (rows == 0 || cols == 0)
		return TBandMatrix<ValType>();
	TBandMatrix<ValType> result(*this);
	int elements = rows * cols;
	for (int i = 0; i < elements; i++)
		result.m[i] -= d;
	return result;
}

template<typename ValType>
TBandMatrix<ValType> TBandMatrix<ValType>::operator*(const TBandMatrix<ValType>& other)
{
	if (rows != other.cols || cols != other.rows)
		throw "Result * undefined";
	TBandMatrix<ValType> result(rows, other.cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			for (int k = 0; k < result.cols; k++)
				result.m[i * cols + j] += m[i * result.cols + k] * other.m[k * other.cols + j];
	return result;
}

template<typename ValType>
TBandMatrix<ValType> TBandMatrix<ValType>::operator*(ValType d)
{
	if (rows == 0 || cols == 0)
		return TBandMatrix<ValType>();
	TBandMatrix<ValType> result(*this);
	int elements = rows * cols;
	for (int i = 0; i < elements; i++)
		result.m[i] *= d;
	return result;
}

template<typename ValType>
TBandMatrix<ValType>& TBandMatrix<ValType>::operator=(const TBandMatrix<ValType>& other)
{
	if (this == &other)
		return *this;
	if (rows != other.rows || cols != other.cols)
		delete[] m;
	rows = other.rows;
	cols = other.cols;
	int elements = rows * cols;
	if (elements == 0)
		m = nullptr;
	else
	{
		m = new ValType[elements];
		for (int i = 0; i < elements; i++)
			m[i] = other.m[i];
	}
	return *this;
}

template<typename ValType>
ValType* TBandMatrix<ValType>::operator[](int index)
{
	if (index < 0 || index > rows)
		throw "Invalid index";
	return m + index * cols;
}

#endif
