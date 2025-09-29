#include "Stack.h"

#include <assert.h>
#include <stdio.h>

inline static size_t min(size_t a, size_t b) {
    return a <= b ? a : b;
}

void PrintStackError(Error error) {
    switch (error)
    {
        case OK:
            fprintf(stderr, "Выполнено без ошибок\n");
            break;
        case POP_ON_EMPTY_STACK:
            fprintf(stderr, "Попытка удалить элемент из пустого стэка\n");
            break;
        case STACK_NULL_PTR:
            fprintf(stderr, "Нулевой указатель на стэк\n");
            break;
        case STACK_EXPANTION_ERR:
            fprintf(stderr, "Ошибка увеличения памяти для стэка\n");
            break;
        case STACK_CONTRACTION_ERR:
            fprintf(stderr, "Ошибка уменьшения памяти для стэка\n");
            break;
        case STACK_INIT_ERR:
            fprintf(stderr, "Ошибка выделения памяти на стэк\n");
            break;
        case STACK_DATA_NULL_PTR:
            fprintf(stderr, "Нулевой указатель на данные стэка\n");
            break;
        case STACK_OVERFLOW:
            fprintf(stderr, "Переполнение стэка\n");
            break;
        case POPED_ELEM_NULL_PTR:
            fprintf(stderr, "Нулевой указатель на удаленный элемент\n");
            break;
        default:
            fprintf(stderr, "Непредвиденная ошибка\n");
            break;
    }
}

Error StackInit(Stack* stack, size_t capacity) {
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

    StackCheck(stack);

    return OK;
}

Error StackExpantion(Stack* stack) {
    StackCheck(stack);

    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    stack_elem_t* data = (stack_elem_t*)realloc(stack->data, stack->capacity * GROW_FACTOR * sizeof(*(stack->data)));
    if (data == NULL) {
        return STACK_EXPANTION_ERR;
    }
    stack->data = data;

    stack->capacity *= GROW_FACTOR;

    StackCheck(stack);

    return OK;
}

Error StackContraction(Stack* stack) {
    StackCheck(stack);

    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    stack_elem_t* data = (stack_elem_t*)realloc(stack->data, stack->capacity / GROW_FACTOR * sizeof(*(stack->data)));
    if (data == NULL) {
        return STACK_CONTRACTION_ERR;
    }
    stack->data = data;

    stack->capacity /= GROW_FACTOR;

    StackCheck(stack);

    return OK;
}

Error StackFree(Stack* stack) {
    StackCheck(stack);

    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    free(stack->data);

    stack->capacity = 0;
    stack->size = 0;
    stack->data = NULL;

    return OK;
}

Error StackAdd(Stack* stack, stack_elem_t elem) {
    StackCheck(stack);

    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    if (stack->size == stack->capacity / GROW_FACTOR) {
        StackExpantion(stack);
    }

    stack->data[stack->size] = elem;
    stack->size++;

    StackCheck(stack);

    return OK;
}

Error StackPop(Stack* stack, stack_elem_t* poped_elem) {
    StackCheck(stack);

    if (poped_elem == NULL) {
        return POPED_ELEM_NULL_PTR;
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

    StackCheck(stack);

    return OK;
}

Error StackVerefy(Stack* stack) {
    if (stack == NULL) {
        return STACK_NULL_PTR;
    }

    if (stack->data == NULL) {
        return STACK_DATA_NULL_PTR;
    }

    if (stack->size > stack->capacity) {
        return STACK_OVERFLOW;
    }

    return OK;
}

void StackDump(Stack* stack, Error error_code) {
    PrintStackError(error_code);

    fprintf(stderr, "capacity = %lu\n", stack->capacity);
    fprintf(stderr, "size     = %lu\n", stack->size);
    fprintf(stderr, "data     = %p\n", stack->data);

    if (stack->data == NULL) {
        return;
    }

    for (size_t i = 0; i < min(stack->size, stack->capacity); i++) {
        fprintf(stderr, "data[%lu] = %d\n", i, stack->data[i]);
    }
}

bool Die(Stack* stack, Error error_code) {
    StackDump(stack, error_code);
    return 0;
}