#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "recalloc.h"
#include "defined_dump_and_ctor.h"

int stack_ctor(stack* stack, size_t capacity)
{
    stack->size        = 0;
    stack->capacity    = capacity;
    stack->data        = (stack_elem*)calloc(capacity, sizeof(stack_elem));
    stack->initialized = STACK_INITIALIZED;
    stack->error       = NO_ERRORS;

    return 0;
}

int stack_push(stack* stack, int value)
{
    if(stack->size == stack->capacity)
    {
        stack_resize(stack, stack->capacity * 2);
    }

    stack->data[stack->size] = value;
    stack->size++;

    struct stack stack_copy = *stack;
    $STACK_DUMP(stack_copy);

    return 0;
}

int stack_pop(stack* stack, stack_elem* value)
{
    if (stack->size * 4 <= stack->capacity)
    {
        stack->capacity = (size_t)ceil(stack->capacity / 2);
        //TODO If push and pop recently inited stack capacity will become less then user asked. Is it ok?
    }

    *value = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = 0;
    stack->size--;

    struct stack stack_copy = *stack;
    $STACK_DUMP(stack_copy);

    return 0;
}

int stack_dtor(stack* stack)
{
    stack->size     = 0;
    stack->capacity = 0;
    free(stack->data);
    stack->data = NULL;

    return 0;
}

int stack_resize(stack* stack, size_t new_size) //TODO DO_NOT_CALL_ME
{
    if(stack->capacity < new_size)
    {
        stack->data = (stack_elem*)recalloc(stack->data, stack->capacity,
                       new_size, sizeof(stack_elem));
        stack->capacity *= 2;
    }
    else
    {
        stack->data = (stack_elem*)realloc(stack->data, new_size * sizeof(stack_elem));
    }

    return 0;
}

// bool stack_ok(stack* stack) //TODO valid test
// {
//     if(stack->initialized == STACK_DID_NOT_INITIALIZED)
//     {
//         stack->error = STACK_DID_NOT_INITIALIZED;
//
//         return STACK_DID_NOT_INITIALIZED;
//     }
//
//     if(stack->capacity < stack->size)
//     {
//         stack->error =     STACK_OVERFLOW;
//
//         return STACK_OVERFLOW;
//     }
//
//     if(stack->data == NULL)
//     {
//         stack->error = STACK_POINTER_IS_NULL;
//
//         return STACK_POINTER_IS_NULL;
//     }
//
//     return true;
// }
