#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <ctime>

#include "stack_private.h"
#include "stack.h"
#include "recalloc.h"
#include "debug_macros.h"
#include "check_expression.h"
#include "stack_consts.h"
#include "stack_security.h"

static int stack_resize(stack* stack, int new_size);

static int stack_resize(stack* stack, int new_size) //TODO DO_NOT_CALL_ME
{
    check_expression(!stack_ok(stack, __func__), "STACK_RESIZE" && !OK);

    if(stack->capacity < new_size)
    {
        stack->data_with_canaries = (stack_elem*)recalloc(stack->data_with_canaries, (size_t)(stack->capacity + 2 * CANARY_SIZE),
                       (size_t)(new_size + 2 * CANARY_SIZE), sizeof(stack_elem));//DEBUG

        warning(stack->data_with_canaries != NULL, CALLOC_ERROR);

        stack->data = stack->data_with_canaries + CANARY_SIZE;//DEBUG CANARY_SIZE

        stack->capacity = new_size;

        for (int number_of_element = stack->size; number_of_element < stack->capacity; number_of_element++)
        {
            stack->data[number_of_element] = POISON;//DEBUG
        }

        stack->data_with_canaries[stack->capacity + CANARY_SIZE] = STACK_CANARY;//DEBUG
    }
    else
    {
        stack->data_with_canaries = (stack_elem*)realloc(stack->data_with_canaries,
                                    (size_t)(new_size + 2 * CANARY_SIZE) * sizeof(stack_elem));//DEBUG +2
        stack->data = stack->data_with_canaries + CANARY_SIZE;//DEBUG CANARY_SIZE

        stack->capacity = new_size;

        stack->data_with_canaries[stack->capacity + CANARY_SIZE] = STACK_CANARY;//DEBUG
    }

    check_expression(!stack_ok(stack, __func__), "STACK_RESIZE" && !OK);

    return 0;
}

int set_dump_file(stack *stack)
{
    check_expression(stack != NULL, POINTER_IS_NULL);

    char *buffer            = (char *)calloc(SIZE_OF_BUFFER, sizeof(char));

    warning(buffer != NULL, CALLOC_ERROR);

    const time_t timer      = time(NULL);
    tm *now                 = localtime(&timer);
    const char *time   = asctime(now);
    size_t time_char_length = strlen(time) - 1;
    const char *folder_name = "dumps/";

    strcpy(buffer, folder_name);
    strncpy(buffer + strlen(folder_name), time, time_char_length);
    strcat(buffer, ".txt");

    stack->dump_file_name   = buffer;

    return 0;
}

int stack_ctor(stack* stack, int capacity)
{
    set_dump_file(stack);

    stack->left_canary  = STRUCT_STACK_CANARY;  //DEBUG
    stack->right_canary = STRUCT_STACK_CANARY; //DEBUG

    stack->size               = 0;
    stack->capacity           = capacity;
    stack->data_with_canaries = (stack_elem*)calloc((size_t)(capacity + 2 * CANARY_SIZE), sizeof(stack_elem)); //DEBUG CANARY_SIZE

    warning(stack->data_with_canaries != NULL, CALLOC_ERROR);

    stack->data               = stack->data_with_canaries + CANARY_SIZE; //DEBUG

    stack->data_with_canaries[0]                      = STACK_CANARY;//DEBUG
    stack->data_with_canaries[CANARY_SIZE + stack->capacity] = STACK_CANARY;//DEBUG

    for (int number_of_element = 0; number_of_element < stack->capacity; number_of_element++)
    {
        stack->data[number_of_element] = POISON;
    }
    stack->initialized = STACK_INITIALIZED;
    stack->error       = NO_ERRORS;

    stack_private_dump(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__);

    check_expression(!stack_ok(stack, __func__), "STACK_CTOR" && !OK);

    return 0;
}

int stack_push(stack* stack, int value)
{
    check_expression(!stack_ok(stack, __func__), "STACK_PUSH" && !OK);

    if(stack->size == stack->capacity)
    {
        stack_resize(stack, stack->capacity * 2);
    }

    stack->data[stack->size] = value;
    stack->size++;

    stack_private_dump(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__);

    check_expression(!stack_ok(stack, __func__), "STACK_PUSH" && !OK);

    return 0;
}

int stack_pop(stack* stack, stack_elem* value)
{
    check_expression(!stack_ok(stack, __func__), ("STACK_POP" && !OK));

    if (stack->size * 4 <= stack->capacity)
    {
        stack_resize(stack, (int)ceil(stack->capacity / 2));
        //TODO If push and pop recently inited stack capacity will become less then user asked. Is it ok?
    }

    *value = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = POISON; //DEBUG
    stack->size--;

    stack_private_dump(stack, __LINE__, __FILE__, __PRETTY_FUNCTION__);

    check_expression(!stack_ok(stack, "stack_pop_end"), ("STACK_POP" && !OK));

    return 0;
}

int stack_dtor(stack* stack)
{
    check_expression(!stack_ok(stack, __func__), "STACK_DTOR" && !OK);

    stack->size     = 0;
    stack->capacity = 0;
    free(stack->data_with_canaries);
    stack->data = NULL;

    return 0;
}
