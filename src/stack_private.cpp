#include <stdio.h>
#include <stdlib.h>

#include "stack_private.h"
#include "stack.h"

stack* create_stack()
{
    stack* st = (stack*)calloc(1, sizeof(stack));
    return st;
}

int stack_private_ctor(stack* stack, int capacity, size_t line, const char* file)
{
    stack->information = (stack_info*)calloc(1, sizeof(stack_info));
    *(stack->information)               = {};
    stack->information->stack_name      = getname(stack);
    stack->information->stack_born_line = line;
    stack->information->stack_born_file = file;

    stack_ctor(stack, capacity);

    return 0;
}

int stack_private_dump(stack* stack, size_t line, const char* file, const char* function)
{
    stack->information->stack_last_usage_line     = line;
    stack->information->stack_last_usage_file     = file;
    stack->information->stack_last_usage_function = function;

    stack_dump(stack);

    return 0;
}
