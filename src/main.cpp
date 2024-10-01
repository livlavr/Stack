// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "recalloc.h"
#include "debug_macros.h"
#include "defined_dump_and_ctor.h"

int main()
{
    stack_dump_file_cleaning();

    stack st = {};
    int x = 0;
    $STACK_CTOR(st, 10);
    stack_push(&st, 1);
    stack_pop(&st, &x);
    stack_push(&st, 1);
    st.capacity = -10;
    stack_pop(&st, &x);
    stack_push(&st, 1);
    stack_push(&st, 1);
    stack_push(&st, 1);

    return 0;
}
