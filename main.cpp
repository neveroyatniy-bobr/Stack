#include <stdio.h>

#include "Stack.h"

int main() {
    Stack stack = {};

    StackInit(&stack, 1);

    StackAdd(&stack, 1);
    StackAdd(&stack, 2);
    StackAdd(&stack, 3);

    printf("added\n");

    printf("%d\n", StackPop(&stack));
    printf("%d\n", StackPop(&stack));
    printf("%d\n", StackPop(&stack));

    printf("poped\n");

    StackFree(&stack);

    return 0;
}