#include <stdio.h>
#include <stdlib.h>

#include "check_expression.h"
#include "stack_private.h"
#include "stack.h"

stack* create_stack_pointer()
{
    stack* st = (stack*)calloc(1, sizeof(stack));

    check_expression(st != NULL, CALLOC_ERROR);

    return st;
}

int stack_dump_file_cleaning(const char* dump_filename) //TODO file will be destroyed when second stack initialized
{
    FILE* dumb_file = fopen(dump_filename, "w");

    if (dumb_file == NULL)
    {
        printf("CAN'T FIND A \"");
        printf("%s", dump_filename);
        printf("\" FILE\n");

        return DUMP_FILE_OPENING_ERROR;
    }

    fclose(dumb_file);

    return 0;
}

int stack_private_ctor(stack* stack, int capacity, size_t line, const char* name_of_stack,
                       const char* file, const char* dump_filename)
{
    stack_dump_file_cleaning(dump_filename); //DEBUG

    stack->information = (stack_info*)calloc(1, sizeof(stack_info));

    check_expression(stack->information != NULL, CALLOC_ERROR);

    *(stack->information)               = {};
    stack->information->dump_filename   = dump_filename;
    stack->information->stack_name      = name_of_stack;
    stack->information->stack_born_line = line;
    stack->information->stack_born_file = file;

    stack_ctor(stack, capacity);

    return 0;
}

int stack_private_dump(stack* stack, size_t line, const char* file, const char* function)
{
    check_expression(stack              != NULL, POINTER_IS_NULL);

    check_expression(stack->information != NULL, POINTER_IS_NULL);

    stack->information->stack_last_usage_line     = line;
    stack->information->stack_last_usage_file     = file;
    stack->information->stack_last_usage_function = function;

    stack_dump(stack);

    return 0;
}
