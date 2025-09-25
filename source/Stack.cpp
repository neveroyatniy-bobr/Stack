#include "Stack.h"

#include <assert.h>
#include <stdio.h>

error StackInit(Stack* stack, size_t capacity) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    stack->capacity = (capacity >= MIN_CAPACITY ? capacity : MIN_CAPACITY);

    stack->size = 0;

    stack_elem_t* data = (stack_elem_t*)calloc(stack->capacity, sizeof(stack_elem_t));
    if (data == NULL) {
        return STACK_INIT_ERR;
    }
    stack->data = data;

    return OK;
}

error StackExpantion(Stack* stack) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    stack_elem_t* data = (stack_elem_t*)realloc(stack->data, stack->capacity * GROW_FACTOR * sizeof(*(stack->data)));
    if (data == NULL) {
        return STACK_EXPANTION_ERR;
    }
    stack->data = data;

    stack->capacity *= GROW_FACTOR;

    return OK;
}

error StackContraction(Stack* stack) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    stack_elem_t* data = (stack_elem_t*)realloc(stack->data, stack->capacity / GROW_FACTOR * sizeof(*(stack->data)));
    if (data == NULL) {
        return STACK_CONTRACTION_ERR;
    }
    stack->data = data;

    stack->capacity *= GROW_FACTOR;

    return OK;
}

error StackFree(Stack* stack) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    free(stack->data);
    
    stack->capacity = 0;
    stack->size = 0;
    stack->data = NULL;

    return OK;
}

error StackAdd(Stack* stack, stack_elem_t elem) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    if (stack->size == stack->capacity / GROW_FACTOR) {
        StackExpantion(stack);
    }

    stack->data[stack->size] = elem;
    stack->size++;

    return OK;
}

error StackPop(Stack* stack, stack_elem_t* poped_elem) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    if (stack->size == 0) {
        return POP_ON_EMPTY_STACK;
    }

    *poped_elem = stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;
    stack->size--;

    if (stack->size == stack->capacity / GROW_FACTOR) {
        StackContraction(stack);
    }

    return OK;
}