//
// Created by Dmitry Belousov on 06.06.2016.
//


#include <stdlib.h>
#include <string.h>
#include "Stack.h"

Stack *newStack(unsigned initialSize) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    stack->it = -1;
    stack->size = initialSize ? initialSize : 10;
    stack->values = (stype *)malloc(stack->size * sizeof(stype));

    return stack;
}

void destroyStack(Stack *stack) {
    if(stack) {
        if(stack->values)
            free(stack->values);
        free(stack);
    }
}

void push(Stack *stack, stype value) {
    if(stack) {
        if(stack->it >= stack->size - 1) {
            stack->size += 5;
            stack->values = (stype *) realloc(stack->values, stack->size * sizeof(stype));
        }
        *(stack->values + ++stack->it) = value;
    }
}

void push_stack(Stack *stack, Stack *value) {
    if(stack && (value && value->it >= 0)) {
        unsigned newIt = stack->it + 1 + value->it;

        if(newIt >= stack->size - 1) {
            stack->size += value->it + 1;
            stack->values = (stype *) realloc(stack->values, stack->size * sizeof(stype));
        }
        memcpy(stack->values + stack->it + 1, value->values, (value->it + 1) * sizeof(stype));
        stack->it = newIt;
    }
}


stype pop(Stack *stack) {
    return stack && stack->it >= 0 ? *(stack->values + stack->it--) : INT_MAX;
}

stype top(const Stack *stack) {
    return stack && stack->it >= 0 ? *(stack->values + stack->it) : INT_MAX;
}

void make_empty(Stack *stack, int size) {
    if(stack) {
        stack->it = -1;

        if(size > 0) {
            stack->size = size;

        }
        stack->size = size > 0 ? size : 5;
        stack->it = -1;
        stack->values = (stype *) realloc(stack->values, stack->size * sizeof(stype));
    }
}

void fit_size(Stack *stack) {
    if(stack) {
        unsigned it = stack->it;
        stack->size = it >= 0 ? it + 1 : 5;
        stack->values = (stype *) realloc(stack->values, stack->size * sizeof(stype));
    }
}










