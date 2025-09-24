#include "Stack.h"

#include <assert.h>
#include <stdio.h>

void StackInit(Stack* stack, size_t capacity) {
    assert(stack != NULL);

    stack->capacity = (capacity >= MIN_CAPACITY ? capacity : MIN_CAPACITY);

    stack->size = 0;

    stack->data = (stack_elem_t*)calloc(stack->capacity, sizeof(stack_elem_t));
}

void StackExpantion(Stack* stack) {
    assert(stack != NULL);

    stack_elem_t* data = (stack_elem_t*)realloc(stack->data, stack->capacity * GROW_FACTOR * sizeof(*(stack->data)));
    if (data != NULL) {
        stack->data = data;
    }

    stack->capacity *= GROW_FACTOR;
}

void StackContaction(Stack* stack) {
    assert(stack != NULL);

    stack_elem_t* data = (stack_elem_t*)realloc(stack->data, stack->capacity / GROW_FACTOR * sizeof(*(stack->data)));
    if (data != NULL) {
        stack->data = data;
    }

    stack->capacity *= GROW_FACTOR;
}

void StackFree(Stack* stack) {
    assert(stack != NULL);

    free(stack->data);
    
    stack->capacity = 0;
    stack->size = 0;
    stack->data = NULL;
}

void StackAdd(Stack* stack, stack_elem_t elem) {
    assert(stack != NULL);

    if (stack->size == stack->capacity / GROW_FACTOR) {
        StackExpantion(stack);
    }

    stack->data[stack->size] = elem;
    stack->size++;
}

stack_elem_t StackPop(Stack* stack) {
    assert(stack != NULL);

    stack_elem_t poped_elem = stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;
    stack->size--;

    if (stack->size == stack->capacity / GROW_FACTOR) {
        StackContaction(stack);
    }

    return poped_elem;
}