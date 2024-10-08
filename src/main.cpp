// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack_private.h"
#include "recalloc.h"
#include "debug_macros.h"

int main() //TODO how to do MakeF see when .h is updated?
{
    stack_dump_file_cleaning();

    stack* st = create_stack();
    stack_private_ctor(st, 10, __LINE__, __FILE__);
    int x = 0;
    stack_push(st, 1);
    stack_push(st, 2);
    stack_push(st, 3);
    stack_push(st, 4);
    stack_push(st, 1);
    stack_push(st, 2);
    stack_pop(st, &x);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_pop(st, &x);
    stack_pop(st, &x);
    stack_pop(st, &x);
    stack_pop(st, &x);
    stack_pop(st, &x);

    stack_dtor(st);

    return 0;
}
