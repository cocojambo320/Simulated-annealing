//
// Created by mikolaj on 19.12.2020.
//

#include "Path.h"

Path::Path(int size) {
    this->size = size;
    ptr = new int[size];
}

Path::Path( const Path& src) {
    this->size = src.size;
    ptr = new int[size];
    std::copy(src.ptr, src.ptr + size, ptr);
}

Path::~Path() {
    delete[] ptr;
}

int Path::cost(Graph *graph)
{
    int cost = 0;

    for (int i = 0; i < size - 1; i++)
    {
        cost += graph->getWeight(ptr[i], ptr[i + 1]);
    }

    cost += graph->getWeight(ptr[size - 1], ptr[0]);

    return cost;
}

int& Path::operator [] (int index)
{
    return ptr[index];
}

Path& Path::operator=(const Path& src) {
    if(src.size == size)
        std::copy(src.ptr, src.ptr + size, ptr);
    else
    {
        delete[] ptr;
        size = src.size;
        ptr = new int[size];
        std::copy(src.ptr, src.ptr + size, ptr);
    }
    return *this;
}

int Path::getSize() {
    return size;
}