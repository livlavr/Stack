#include <stdio.h>

#include "defined_dump_and_ctor.h"

int stack_dump_file_cleaning()
{
    FILE* dumb_file = fopen("dump.txt", "w");

    if (dumb_file == NULL)
    {
        printf("CAN'T FIND A \"dump.txt\" FILE\n");

        return DUMP_FILE_OPENING_ERROR;
    }

    fclose(dumb_file);
    return 0;
}

int stack_dump(stack* stack)
{
    FILE* dumb_file = fopen("dump.txt", "a"); //TODO how could i make dump.txt in certain dir?

    if (dumb_file == NULL)
    {
        printf("CAN'T FIND A \"dump.txt\" FILE\n");

        return DUMP_FILE_OPENING_ERROR;
    }

    fprintf(dumb_file, "stack %s[%p] at %s : %lu : %s born at %s : %lu\n", stack->information->stack_name,
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

    fprintf(dumb_file, "[canary][%p] = %d\n", &stack->data[-1], stack->data[-1]); //DEBUG


    for(size_t index = 0; index < stack->capacity; index++)
    {
        if (index < stack->size)
        {
            fprintf(dumb_file, "*[%d][%p] = %d\n", index, stack->data + index, stack->data[index]);
        }
        else
        {
            fprintf(dumb_file, "[%d][%p] = %d [POISON]\n", index, stack->data + index, stack->data[index]);
        }
    }

    fprintf(dumb_file, "[canary][%p] = %d\n", &(stack->data[stack->capacity]), stack->data[stack->capacity]); //DEBUG

    fprintf(dumb_file, "CANARY      = %d\n", stack->right_canary); //DEBUG


    fprintf(dumb_file, "\n");

    fclose(dumb_file);

    return 0;
}
