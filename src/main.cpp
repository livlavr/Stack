// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack_private.h"
#include "debug_macros.h"
#include "recalloc.h"

// #include "stack.h" //TODO delete

int main()
{
    stack* st = create_stack_pointer();
    stack_private_ctor(st, 10, __LINE__, __FILE__);
    int x = 0;
    push(st, 1);
    push(st, 2);
    push(st, 3);
    push(st, 4);
    push(st, 1);
    push(st, 2);
    pop(st, &x);
    push(st, 4);
    push(st, 4);
    push(st, 4);
    push(st, 4);
    push(st, 4);
    push(st, 4);
    push(st, 4);
    pop(st, &x);
    pop(st, &x);
    pop(st, &x);
    pop(st, &x);
    pop(st, &x);

    stack_dtor(st);

    return 0;
}
