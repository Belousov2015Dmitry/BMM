//
// Created by Dmitry Belousov on 04.06.2016.
//

#ifndef BMM_EXPERIMENT_H
#define BMM_EXPERIMENT_H

#include "../Matrix/Matrix.h"


#define MATRIX_RECT 1
#define MATRIX_RRB  1
#define MATRIX_UT   1
#define MATRIX_UTB  4

void outMatrix(const char *fileName, const void *matrix, const int matrixType);

unsigned start(unsigned Size);

///TODO: evaluate despersion

#endif //BMM_EXPERIMENT_H
