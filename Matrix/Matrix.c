//
// Created by Dmitry Belousov on 28.05.2016.
//

#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "../Helpers/Stack.h"

////////////////Helpers///////////////////


////////////Allocation/////////////////

RectMatrix* newUTMatrix(unsigned size) {
    type *matrix = (type *)malloc(size * size * sizeof(type));

    for (unsigned i = 0, ii = 0; i < size; ++i, ii += size) {
        unsigned j = 0;
        for (; j < i; ++j)
            *(matrix + ii + j) = 0;

        for (; j < size; ++j)
            *(matrix + ii + j) = randValue();
    }

    RectMatrix *utMatrix = (RectMatrix *)malloc(sizeof(RectMatrix));
    utMatrix->matrix = matrix;
    utMatrix->n = size;
    utMatrix->m = size;

    return utMatrix;
}

RectMatrix* newRectMatrix(unsigned n, unsigned m) {
    type *matrix = (type *)malloc(n * m * sizeof(type));

    for (unsigned i = 0, ii = 0; i < n; ++i, ii += n)
        for (unsigned j = 0; j < m; ++j)
            *(matrix + ii + j) = randValue();

    RectMatrix *rectMatrix = (RectMatrix *)malloc(sizeof(RectMatrix));
    rectMatrix->matrix = matrix;
    rectMatrix->n = n;
    rectMatrix->m = m;

    return rectMatrix;
}

RBMatrix* toRBMatrix(const RectMatrix *rectMatrix, const Stack *splits) {
    RBMatrix *rbMatrix = NULL;

    if(rectMatrix && (splits && splits->it >= 0)) {
        unsigned n = rectMatrix->n;
        unsigned m = rectMatrix->m;

        unsigned firstBlock = *splits->values;

        if (n % firstBlock == 0 && m % firstBlock == 0) {
            size_t size = n * m * sizeof(type);
            type *matrix = (type *) malloc(size);
            memcpy(matrix, rectMatrix->matrix, size);

            rbMatrix = (RBMatrix *)malloc(sizeof(RBMatrix));
            rbMatrix->matrix = matrix;
            rbMatrix->n = n;
            rbMatrix->m = m;
            rbMatrix->splits = splits;
        }
    }

    return rbMatrix;
}

UTBMatrix* toUTBMatrix(const RectMatrix *utMatrix, const Stack *splits) {
    UTBMatrix *utb = NULL;
    if(utMatrix && (splits && splits->it >= 0)) {
        unsigned n = utMatrix->n;
        unsigned bsize = *splits->values; //largest block size

        if(n % bsize == 0) {
            unsigned bcount = n / bsize;    //count of blocks in row (collumn)
            unsigned bs2 = bsize * bsize;
            unsigned s = AP(bs2, bs2 * bcount, bcount); // count of elements

            type *from = utMatrix->matrix;
            type *to = (type *)malloc(s * sizeof(type));

            type *it = to;
            for (unsigned i = 0, len = bsize; i < n; i += bsize, len += bsize)
                for (unsigned bj = i; bj < len; ++bj)
                    for (unsigned bi = 0; bi < len; ++bi)
                        *it++ = *(from + bi * n + bj);

            utb = (UTBMatrix *)malloc(sizeof(UTBMatrix));
            utb->matrix = to;
            utb->size = n;
            utb->splits = splits;
        }
    }

    return utb;
}


///////////Deallocation////////////////

void destroyRectMatrix(RectMatrix *mtx) {
    if(mtx) {
        if(mtx->matrix)
            free(mtx->matrix);
        free(mtx);
    }
}

void destroyRBMatrix(RBMatrix *mtx) {
    if(mtx) {
        if(mtx->matrix)
            free(mtx->matrix);
        free(mtx);
    }
}

void destroyUTBMatrix(UTBMatrix *mtx) {
    if(mtx) {
        if(mtx->matrix)
            free(mtx->matrix);
        free(mtx);
    }
}


///////////Multiplication///////////////

Result* mul(const UTBMatrix *A, const RBMatrix *B) {

}