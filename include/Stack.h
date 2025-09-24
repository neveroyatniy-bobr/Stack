#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>

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
void StackInit(Stack* stack, size_t capacity);

/// @brief Увиличивает вместимость стэка в GROW_FACTOR раз
/// @param stack Стэк
void StackExpantion(Stack* stack);

/// @brief Уменьшает вместимость стэка в GROW_FACTOR раз
/// @param stack Стэк
void StackContaction(Stack* stack);

/// @brief Функция освобождения всей памяти выделенной под стэк
/// @param stack Стэк
void StackFree(Stack* stack); 

/// @brief Добавляет элемент в стэк
/// @param stack Стэк
/// @param elem Элемент
void StackAdd(Stack* stack, stack_elem_t elem);

/// @brief Удаляет последний элемент из стэка
/// @param stack Стэк
/// @return Знвчение удаленного элемента
stack_elem_t StackPop(Stack* stack);

#endif // STACK_H_