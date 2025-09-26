#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>

enum error {
    OK                    = 0,
    POP_ON_EMPTY_STACK    = 1,
    STACK_NULL_PTR        = 2,
    STACK_EXPANTION_ERR   = 3,
    STACK_CONTRACTION_ERR = 4,
    STACK_INIT_ERR        = 5,
    STACK_DATA_NULL_PTR   = 6,
    STACK_OVERFLOW        = 7
};

typedef int stack_elem_t;

/// @brief Сруктура, хранящая стэк
struct Stack {
    size_t capacity;
    size_t size;
    stack_elem_t* data;
};

/// @brief Минимальная вместимость стэка
static const size_t MIN_CAPACITY = 16;
/// @brief Фактор увеличения вместимости стэка при переполнении
static const size_t GROW_FACTOR = 2;

/// @brief Функция иницивлизации стэка
/// @param stack Стэк
/// @param capacity начальный вместимость стэка
/// @return Код ошибки
error StackInit(Stack* stack, size_t capacity);

/// @brief Увиличивает вместимость стэка в GROW_FACTOR раз
/// @param stack Стэк
/// @return Код ошибки
error StackExpantion(Stack* stack);

/// @brief Уменьшает вместимость стэка в GROW_FACTOR раз
/// @param stack Стэк
/// @return Код ошибки
error StackContraction(Stack* stack);

/// @brief Функция освобождения всей памяти выделенной под стэк
/// @param stack Стэк
/// @return Код ошибки
error StackFree(Stack* stack);

/// @brief Добавляет элемент в стэк
/// @param stack Стэк
/// @param elem Элемент
/// @return Код ошибки
error StackAdd(Stack* stack, stack_elem_t elem);

/// @brief Удаляет последний элемент из стэка
/// @param stack Стэк
/// @return Код ошибки
error StackPop(Stack* stack, stack_elem_t* poped_elem);

error StackVerefy(Stack* stack);

void StackDump(Stack* stack);

#endif // STACK_H_