//
// Created by mikolaj on 19.12.2020.
//


#include "SquareMatrix.h"
#include <algorithm>

SquareMatrix::SquareMatrix(int size)
{
    if(size >= 0)
        init(size);
}

SquareMatrix::SquareMatrix(const SquareMatrix &matrix)
{
    init(matrix.size);

    for (int i = 0; i < matrix.size; i++)
    {
        std::copy(matrix.ptr[i], matrix.ptr[i] + matrix.size, ptr[i]);
    }
}

void SquareMatrix::init(int size)
{
    this->size = size;

    ptr = new int* [size];

    for (int i = 0; i < size; i++)
    {
        ptr[i] = new int[size];
    }
}

SquareMatrix::~SquareMatrix()
{
    for (int i = 0; i < this->size; i++)
        delete[] ptr[i];

    delete[] ptr;
}

int* SquareMatrix::operator [] (int index)
{
    return ptr[index];
}

SquareMatrix& SquareMatrix::operator = (const SquareMatrix& t)
{
    return *this;
}

int SquareMatrix::getSize()
{
    return size;
}