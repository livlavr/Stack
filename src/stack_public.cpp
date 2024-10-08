#include <stdio.h>
#include <stdlib.h>

#include "stack_public.h"
#include "stack.h"
#include "check_expression.h"

stack* create_stack_pointer()
{
    stack* st = (stack*)calloc(1, sizeof(stack));

    warning(st != NULL, CALLOC_ERROR);

    *st = {};

    return st;
}

int stack_public_ctor(stack* stack, int capacity, const char* file,
                       size_t line, const char* name)
{
    check_expression(stack   != NULL, POINTER_IS_NULL);
    check_expression(capacity > 0, STACK_BAD_CAPACITY);

    stack->information = (stack_info*)calloc(1, sizeof(stack_info));

    warning(stack->information != NULL, CALLOC_ERROR);

    *(stack->information)               = {};
    stack->information->stack_name      = name;
    stack->information->stack_born_line = line;
    stack->information->stack_born_file = file;

    stack_ctor(stack, capacity, file, line);

    return 0;
}

int stack_public_dump(stack* stack, const char* file, size_t line, const char* function)
{
    check_expression(stack != NULL, POINTER_IS_NULL);

    // stack_check(!stack_ok(stack), "STACK_DUMP" && !OK, file, line);

    stack->information->stack_last_usage_line     = line;
    stack->information->stack_last_usage_file     = file;
    stack->information->stack_last_usage_function = function;

    stack_private_dump(stack);

    return 0;
}
