#include <stdio.h>

#include "Stack.h"

int main() {
    Stack stack = {};

    DO StackInit(&stack, 1) OR DIE(&stack);

    DO StackAdd(&stack, 1) OR DIE(&stack);
    DO StackAdd(&stack, 2) OR DIE(&stack);
    DO StackAdd(&stack, 2) OR DIE(&stack);

    printf("added\n");

    int poped_elem = 0;

    DO StackPop(&stack, &poped_elem) OR DIE(&stack);
    printf("%d\n", poped_elem);
    DO StackPop(&stack, &poped_elem) OR DIE(&stack);
    printf("%d\n", poped_elem);
    DO StackPop(&stack, &poped_elem) OR DIE(&stack);
    printf("%d\n", poped_elem);
    DO StackPop(&stack, &poped_elem) OR DIE(&stack);
    printf("%d\n", poped_elem);

    *(stack.data - 1) = 123;

    DO StackVerefy(&stack) OR DIE(&stack);

    printf("poped\n");

    DO StackFree(&stack) OR DIE(&stack);

    return 0;
}