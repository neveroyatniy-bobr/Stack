#include <stdio.h>

#include "Stack.h"

int main() {
    Stack stack = {};

    StackInit(&stack, 1);

    StackAdd(&stack, 1);
    StackAdd(&stack, 2);
    StackAdd(&stack, 3);

    printf("added\n");

    int poped_elem = 0;

    StackPop(&stack, &poped_elem);
    printf("%d\n", poped_elem);
    StackPop(&stack, &poped_elem);
    printf("%d\n", poped_elem);
    StackPop(&stack, &poped_elem);
    printf("%d\n", poped_elem);
    StackPop(&stack, &poped_elem);
    printf("%d\n", poped_elem);

    printf("poped\n");

    StackFree(&stack);

    return 0;
}