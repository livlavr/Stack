#include <stdio.h>

#include "stack.h"
#include "debug_macros.h"
<<<<<<< HEAD
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
=======
#include "stack_consts.h"
#include "stack_security.h"
#include "../../Custom-asserts/custom_asserts.h"

int stack_private_dump(stack* stack_pointer)
{
    check_expression(stack_pointer != NULL, POINTER_IS_NULL);

    // stack_check(!stack_ok(stack_pointer), "STACK_DUMP" && !OK, file, line); //TODO turn on

    FILE* dumb_file = fopen(stack_pointer->dump_file_name, "a");

    if (dumb_file == NULL)
    {
        printf("CAN'T FIND A \"");
        printf("%s", stack_pointer->dump_file_name);
        printf("\" FILE\n");

        return FILE_OPENING_ERROR;
    }

    fprintf(dumb_file, "stack %s[%p] at %s : %lu : %s born in %s : %lu\n",
            stack_pointer->information->stack_name,
            stack_pointer, stack_pointer->information->stack_last_usage_file,
            stack_pointer->information->stack_last_usage_line,
            stack_pointer->information->stack_last_usage_function,
            stack_pointer->information->stack_born_file,
            stack_pointer->information->stack_born_line);
    fprintf(dumb_file, "initialized = %d\n", stack_pointer->initialized);
    fprintf(dumb_file, "capacity    = %d\n", stack_pointer->capacity);
    fprintf(dumb_file, "size        = %d\n", stack_pointer->size);
    fprintf(dumb_file, "hash        = %llu\n", stack_pointer->hash);
    fprintf(dumb_file, "data_hash   = %llu\n", stack_pointer->data_hash);
    fprintf(dumb_file, "error       = %d\n", stack_pointer->error);

    fprintf(dumb_file, "CANARY      = %d\n", stack_pointer->left_canary); //DEBUG

    fprintf(dumb_file, "[canary][%p] = %d\n", &stack_pointer->data_with_canaries[0],
            stack_pointer->data_with_canaries[0]); //DEBUG


    for(size_t index = 0; index < (size_t)stack_pointer->capacity; index++)
    {
        if (stack_pointer->data[index] != POISON)
        {
            fprintf(dumb_file, "*[%lu][%p] = %d\n", index,
                    stack_pointer->data + index, stack_pointer->data[index]);
        }
        else
        {
            fprintf(dumb_file, "[%lu][%p] = %d [POISON]\n", index,
                    stack_pointer->data + index, stack_pointer->data[index]);
        }
    }

    fprintf(dumb_file, "[canary][%p] = %d\n",
            &(stack_pointer->data_with_canaries[CANARY_SIZE + stack_pointer->capacity]),
            stack_pointer->data_with_canaries[CANARY_SIZE + stack_pointer->capacity]); //DEBUG

    fprintf(dumb_file, "CANARY      = %d\n", stack_pointer->right_canary); //DEBUG
>>>>>>> fix

    fprintf(dump_file, "\n");

    fclose(dump_file);

    return 0;
}
