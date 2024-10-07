// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

#include "stack_private.h"
#include "ab_test.h"
#include "recalloc.h"
#include "stack.h"
#include "debug_macros.h"

int main() //TODO how to do MakeF see when .h is updated?
{
    // ab_test();
    stack* st = create_stack_pointer();
    STACK_CTOR(st, 10, "dump.txt");
    st = NULL;
    stack_push(st, 10);
    return 0;
}
