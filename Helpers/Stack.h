//
// Created by Dmitry Belousov on 06.06.2016.
//

#ifndef BMM_STACK_H
#define BMM_STACK_H

#define stype unsigned

#define DO_NOT_RESIZE 0
#define DEFAULT_SIZE  0

typedef struct {
    stype *values;
    int it;
    int size;
} Stack;

Stack* newStack(unsigned initialSize);
void destroyStack(Stack *stack);

void push(Stack *stack, stype value);
void push_stack(Stack *stack, Stack *value);
stype pop(Stack *stack);
stype top(const Stack *stack);
void make_empty(Stack *stack, int size);
void fit_size(Stack *stack);

#define isEmpty(stack) stack == NULL || stack->it < 0

#endif //BMM_STACK_H
