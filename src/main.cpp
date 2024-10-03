// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "recalloc.h"
#include "debug_macros.h"
#include "stack_dump.h"

int main() //TODO how to do MakeF see when .h is updated?
{
    stack_dump_file_cleaning();

    stack st = {};
    int x = 0;
    // $STACK_DUMP(st);
    $STACK_CTOR(st, 3);
    stack_push(&st, 1);
    stack_push(&st, 2);
    stack_push(&st, 3);
    stack_push(&st, 4);
    stack_push(&st, 1);
    stack_push(&st, 2);
    stack_pop(&st, &x);
    stack_push(&st, 4);
    stack_pop(&st, &x);
    stack_pop(&st, &x);
    stack_pop(&st, &x);
    stack_pop(&st, &x);
    stack_pop(&st, &x);
    // stack_pop(&st, &x);
    // *(st.data_with_canaries) = 0;
    // st.right_canary = 52;
    // st.data = NULL;
    // st.size = -10;
    // st.left_canary = 50;
    // st.capacity = -5;
    // stack_pop(&st, &x);
    stack_dtor(&st);

    return 0;
}
