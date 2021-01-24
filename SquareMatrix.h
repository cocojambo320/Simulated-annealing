//
// Created by mikolaj on 19.12.2020.
//

#ifndef SIMULATED_ANNEALING_SQUAREMATRIX_H
#define SIMULATED_ANNEALING_SQUAREMATRIX_H


class SquareMatrix
{
private:
    int** ptr;
    int size;

    void init(int size);
public:
    SquareMatrix(int size);
    SquareMatrix(const SquareMatrix &matrix);
    ~SquareMatrix();
    int* operator[](int);
    SquareMatrix& operator = (const SquareMatrix& t);
    int getSize();
};


#endif //SIMULATED_ANNEALING_SQUAREMATRIX_H
