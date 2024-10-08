// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack_public.h"
#include "debug_macros.h"
#include "recalloc.h"

#include "stack.h" //TODO delete

int main()
{
    stack* st = create_stack_pointer();
    // stack_public_dump(st, __FILE__, __LINE__, __FUNCTION__);
    stack_init(st, 10);
    int x = 0;
    push(st, 1);
    push(st, 2);
    push(st, 3);
    push(st, 4);
    push(st, 1);
    // pop(st, &x);
    // pop(st, &x);
    pop(st, &x);
    pop(st, &x);
    pop(st, &x);
    pop(st, &x);
    pop(st, &x);
    push(st, 1);
    push(st, 2);
    push(st, 3);
    push(st, 4);
    push(st, 1);
    // st->capacity = -50;
    push(st, 2);
    pop(st, &x);
    push(st, 4);
    // st->capacity = 8;
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

    stack_destroy(st);

    return 0;
}
