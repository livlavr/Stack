// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack_public.h"
#include "debug_macros.h"
#include "recalloc.h"

#include "check_expression.h"

#include "stack.h" //TODO delete

int main()
{
    stack* st = NULL;

    stack_init(st, 7);

    int x = 0;

    push(st, 1);
    // push(st, 2);
    // push(st, 3);
    // push(st, 4);
    // push(st, 1);
    // push(st, 3);
    // push(st, 4);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // push(st, 1);
    // push(st, 2);
    // push(st, 3);
    // push(st, 4);
    // push(st, 1);
    st->data[4] = -918;
    stack_dump(st);
    push(st, 2);
    pop(st, &x);
    push(st, 4);
    // // st->capacity = 8;
    st->data[4] = POISON;
    stack_dump(st);
    // push(st, 4);
    // push(st, 4);
    push(st, 4);
    // push(st, 4);
    // push(st, 4);
    // push(st, 4);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);
    // pop(st, &x);

    stack_destroy(st);

    return 0;
}
