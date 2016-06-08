//
// Created by Dmitry Belousov on 04.06.2016.
//

#include <stdio.h>
#include <math.h>
#include "Experiment.h"


//////////////////OUT/////////////////////

void outRectMatrix(const char *fileName, const RectMatrix *matrix) {
    FILE *file = fopen(fileName, "w");

    unsigned n = matrix->n;
    unsigned m = matrix->m;
    type *it = matrix->matrix;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            fprintf(file, "%f ", *it++);
        fprintf(file, "\n");
    }

    fclose(file);
}

void outUTBMatrix(const char *fileName, const UTBMatrix *matrix) {
    FILE *file = fopen(fileName, "w");
//TODO
//    unsigned bs2 = matrix->bsize * matrix->bsize;
    unsigned n = matrix->size;
//    unsigned s = AP(bs2, bs2 * n, n);

    type *it = matrix->matrix;
    for (int i = 0; i < n; ++i)
        fprintf(file, "%f ", *it);

    fclose(file);
}

void outMatrix(const char *fileName, const void *matrix, int matrixType) {
    switch (matrixType) {
        case MATRIX_RECT: outRectMatrix(fileName, matrix); break;
        case MATRIX_UTB:  outUTBMatrix(fileName, matrix);  break;
    }
}


////////////////Experiment////////////////////

void doExperiment(const RectMatrix *A, const RectMatrix *B, const Stack *splits) {
    UTBMatrix *a = toUTBMatrix(A, splits);
    RBMatrix *b = toRBMatrix(B, splits);

    Result *result = mul(a, b); //TODO

    destroyUTBMatrix(a);
    destroyRBMatrix(b);

//    for (int i = 0; i <= splits->it; ++i)
//        printf("%d ", splits->values[i]);
//    printf("\n");
}

unsigned GCD(unsigned a, unsigned b) {
    while (a != b)
        if(a > b)
            a -= b;
        else
            b -= a;
    return a;
}

Stack* deviders(unsigned x) {
    Stack *seq = newStack(0);

    unsigned max = sqrt(x);
    for (int i = 2; i <= max; ++i) {
        if(x % i == 0) {
            push(seq, i);

            unsigned j = x / i;
            if(j != i)
                push(seq, j);
        }
    }

    fit_size(seq);
    return seq;
}

unsigned start(unsigned Size) {
    unsigned count_of_experiments = 0;

    ///original matrix:
    RectMatrix *ut = newUTMatrix(Size);
    RectMatrix *rect = newRectMatrix(Size, Size);

    ///reducing (dfs):
    Stack *tree = newStack(5);
    Stack *parents = newStack(5);

    //add first layer:
    Stack *childs = deviders(Size);
    push_stack(tree, childs);

    while(isEmpty(tree) == 0) {
        destroyStack(childs);

        //visit if childs were visited:
        while(isEmpty(tree) == 0 && top(tree) == top(parents)) {
            doExperiment(ut, rect, parents);
            ++count_of_experiments;

            pop(tree);
            pop(parents);
        }
        if(isEmpty(tree) != 0)
            break;

        childs = deviders(top(tree));

        //continue if can reduce:
        if(isEmpty(childs) == 0) {
            push(parents, top(tree));
            push_stack(tree, childs);
        }
        else {  //it's a leaf (stop reducing)
            push(parents, top(tree));
            doExperiment(ut, rect, parents);
            ++count_of_experiments;

            pop(parents);
            pop(tree);
        }
    }

    ///dealloc:
    destroyRectMatrix(ut);
    destroyRectMatrix(rect);
    destroyStack(tree);
    destroyStack(parents);

    printf("count_of_experiments: %d\n", count_of_experiments);

    return count_of_experiments;
}
