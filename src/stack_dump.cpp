#include <stdio.h>

#include "stack.h"
#include "debug_macros.h"
#include "stack_consts.h"
#include "stack_security.h"
#include "check_expression.h"

int stack_private_dump(stack* stack)
{
    check_expression(stack != NULL, POINTER_IS_NULL);

    // stack_check(!stack_ok(stack), "STACK_DUMP" && !OK, file, line); //TODO

    FILE* dumb_file = fopen(stack->dump_file_name, "a"); //TODO how could i make dump.txt in certain dir?

    if (dumb_file == NULL)
    {
        printf("CAN'T FIND A \"");
        printf("%s", stack->dump_file_name);
        printf("\" FILE\n");

        return FILE_OPENING_ERROR;
    }

    fprintf(dumb_file, "stack %s[%p] at %s : %lu : %s born at %s : %lu\n",
            stack->information->stack_name,
            stack, stack->information->stack_last_usage_file,
            stack->information->stack_last_usage_line,
            stack->information->stack_last_usage_function,
            stack->information->stack_born_file,
            stack->information->stack_born_line);
    fprintf(dumb_file, "initialized = %d\n", stack->initialized);
    fprintf(dumb_file, "capacity    = %d\n", stack->capacity);
    fprintf(dumb_file, "size        = %d\n", stack->size);
    fprintf(dumb_file, "error       = %d\n", stack->error);

    fprintf(dumb_file, "CANARY      = %d\n", stack->left_canary); //DEBUG

    fprintf(dumb_file, "[canary][%p] = %d\n", &stack->data_with_canaries[0],
            stack->data_with_canaries[0]); //DEBUG


    for(size_t index = 0; index < (size_t)stack->capacity; index++)
    {
        if (stack->data[index] != POISON)
        {
            fprintf(dumb_file, "*[%lu][%p] = %d\n", index,
                    stack->data + index, stack->data[index]);
        }
        else
        {
            fprintf(dumb_file, "[%lu][%p] = %d [POISON]\n", index,
                    stack->data + index, stack->data[index]);
        }
    }

    fprintf(dumb_file, "[canary][%p] = %d\n",
            &(stack->data_with_canaries[CANARY_SIZE + stack->capacity]),
            stack->data_with_canaries[CANARY_SIZE + stack->capacity]); //DEBUG

    fprintf(dumb_file, "CANARY      = %d\n", stack->right_canary); //DEBUG

    fprintf(dumb_file, "\n");

    fclose(dumb_file);

    return 0;
}
