#include <stdio.h>
#include <stdlib.h>

#include "stack_private.h"
#include "stack.h"
#include "check_expression.h"

stack* create_stack_pointer()
{
    stack* st = (stack*)calloc(1, sizeof(stack));

    warning(st != NULL, CALLOC_ERROR);

    return st;
}

int stack_private_ctor(stack* stack, int capacity, size_t line, const char* file)
{
    check_expression(stack != NULL, POINTER_IS_NULL);

    stack->information = (stack_info*)calloc(1, sizeof(stack_info));

    warning(stack->information != NULL, CALLOC_ERROR);

    *(stack->information)               = {};
    stack->information->stack_name      = getname(stack);
    stack->information->stack_born_line = line;
    stack->information->stack_born_file = file;

    stack_ctor(stack, capacity);

    return 0;
}

int stack_private_dump(stack* stack, size_t line,
                       const char* file, const char* function)
{
    check_expression(stack != NULL, POINTER_IS_NULL);

    stack->information->stack_last_usage_line     = line;
    stack->information->stack_last_usage_file     = file;
    stack->information->stack_last_usage_function = function;

    stack_dump(stack);

    return 0;
}
