//
// Created by Dmitry Belousov on 28.05.2016.
//

#ifndef BMM_MATRIX_H
#define BMM_MATRIX_H

#include "../Helpers/Stack.h"

#define type double

#define AP(a1, an, n) (a1 + an) / 2 * n
#define randValue() 1

//input:
typedef struct {
    type *matrix;
    unsigned n;
    unsigned m;
} RectMatrix;

//block-matrix:
typedef struct {
    type *matrix;
    unsigned size;
    Stack *splits;
} UTBMatrix;

typedef struct {
    type *matrix;
    unsigned n;
    unsigned m;
    Stack *splits;
} RBMatrix;

typedef struct {
    RBMatrix *matrix;
    time_t exec_time;
} Result;


////////////Allocation/////////////////

RectMatrix* newUTMatrix(unsigned size);
RectMatrix* newRectMatrix(unsigned n, unsigned m);

RBMatrix* toRBMatrix(const RectMatrix *rectMatrix, const Stack *splits);
UTBMatrix* toUTBMatrix(const RectMatrix *utMatrix, const Stack *splits);


///////////Deallocation////////////////

void destroyRectMatrix(RectMatrix *rbMatrix);
void destroyRBMatrix(RBMatrix *rbMatrix);
void destroyUTBMatrix(UTBMatrix *utbMatrix);


//////////////Operation////////////////

Result* mul(const UTBMatrix *A, const RBMatrix *B);


#endif //BMM_MATRIX_H
