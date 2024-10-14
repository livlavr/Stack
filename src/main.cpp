// #define NDEBUG
#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
#include "stack_private.h"
#include "ab_test.h"
#include "recalloc.h"
#include "stack.h"
=======
#include "stack_public.h"
>>>>>>> fix
#include "debug_macros.h"
#include "recalloc.h"

#include "../../Custom-asserts/custom_asserts.h"

#include "stack.h" //TODO delete

int main()
{
<<<<<<< HEAD
    // ab_test();
    stack* st = create_stack_pointer();
    STACK_CTOR(st, 10, "dump.txt");
    st = NULL;
    stack_push(st, 10);
=======
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

>>>>>>> fix
    return 0;
}
