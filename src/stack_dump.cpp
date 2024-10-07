#include <stdio.h>

#include "stack.h"
#include "debug_macros.h"
#include "check_expression.h"

static const stack_elem POISON = 109093; //DEBUG?

int stack_dump(stack* stack)
{
    check_expression(stack != NULL, POINTER_IS_NULL);

    check_expression(stack->initialized != STACK_DID_NOT_INITIALIZED, STACK_DID_NOT_INITIALIZED);

    const char* filename = stack->information->dump_filename;

    FILE* dump_file = fopen(filename, "a"); //TODO how could i make dump.txt in certain dir?

    if (dump_file == NULL)
    {
        printf("CAN'T FIND A \"");
        printf("%s", filename);
        printf("\" FILE\n");

        return DUMP_FILE_OPENING_ERROR;
    }

    fprintf(dump_file, "stack %s[%p] at %s : %lu : %s born at %s : %lu\n",
            stack->information->stack_name,
            stack, stack->information->stack_last_usage_file,
            stack->information->stack_last_usage_line,
            stack->information->stack_last_usage_function,
            stack->information->stack_born_file,
            stack->information->stack_born_line);
    fprintf(dump_file, "initialized = %d\n", stack->initialized);
    fprintf(dump_file, "capacity    = %d\n", stack->capacity);
    fprintf(dump_file, "size        = %d\n", stack->size);
    fprintf(dump_file, "error       = %d\n", stack->error);

    fprintf(dump_file, "CANARY      = %llu\n", stack->left_canary); //DEBUG

    fprintf(dump_file, "[canary][%p] = %d\n", &stack->data_with_canaries[0],
            stack->data_with_canaries[0]); //DEBUG


    for(size_t index = 0; index < (size_t)stack->capacity; index++)
    {
        if (stack->data[index] != POISON)
        {
            fprintf(dump_file, "*[%lu][%p] = %d\n", index,
                    stack->data + index, stack->data[index]);
        }
        else
        {
            fprintf(dump_file, "[%lu][%p] = %d [POISON]\n", index,
                    stack->data + index, stack->data[index]);
        }
    }

    fprintf(dump_file, "[canary][%p] = %d\n",
            &(stack->data_with_canaries[CANARY_SIZE + stack->capacity]),
            stack->data_with_canaries[CANARY_SIZE + stack->capacity]); //DEBUG

    fprintf(dump_file, "CANARY      = %llu\n", stack->right_canary); //DEBUG

    fprintf(dump_file, "\n");

    fclose(dump_file);

    return 0;
}
