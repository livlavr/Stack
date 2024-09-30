// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "recalloc.h"
#include "debug_macros.h"
#include "stack_dump.h"

int main()
{
    stack st = {};
    int x = 0;
    stack_dump(&st);
    stack_ctor(&st, 10);
    stack_dump(&st);
    stack_push(&st, 0);
    stack_push(&st, 1);
    stack_push(&st, 2);
    stack_push(&st, 3);
    stack_push(&st, 4);
    stack_push(&st, 5);
    stack_pop(&st, &x);
    stack_pop(&st, &x);
    // printf("%d\n", x);
    // stack_pop(&st, &x);
    // printf("%d\n", x);
    stack_push(&st, 2);
    stack_push(&st, 3);
    stack_push(&st, 4);
    stack_push(&st, 5);
    stack_push(&st, 2);
    stack_push(&st, 3);
    stack_push(&st, 3);
    stack_dump(&st);
    // stack_dtor(&st);
    return 0;
}
