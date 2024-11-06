#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <ctime>

#include "../Custom-asserts/custom_asserts.h"

#include "stack_security.h"
#include "stack_public.h"
#include "debug_macros.h"
#include "stack_consts.h"
#include "recalloc.h"
#include "stack.h"

static int stack_resize(stack* stack_pointer, int new_size, const char* file, size_t line)
{
    check_expression(stack_pointer, POINTER_IS_NULL);

    stack_check(!stack_ok(stack_pointer), "STACK_RESIZE" && !OK, file, line);

    if(stack_pointer->capacity < new_size)
    {
        stack_pointer->data_with_canaries = (stack_elem*)recalloc(stack_pointer->data_with_canaries, (size_t)(stack_pointer->capacity + 2 * CANARY_SIZE),
                       (size_t)(new_size + 2 * CANARY_SIZE), sizeof(stack_elem));//DEBUG

        warning(stack_pointer->data_with_canaries, CALLOC_ERROR);

        stack_pointer->data = stack_pointer->data_with_canaries + CANARY_SIZE;//DEBUG CANARY_SIZE

        stack_pointer->capacity = new_size;

        for(int number_of_element = stack_pointer->size; number_of_element < stack_pointer->capacity; number_of_element++)
        {
            stack_pointer->data[number_of_element] = POISON;//DEBUG
        }

        stack_pointer->data_with_canaries[stack_pointer->capacity + CANARY_SIZE] = STACK_CANARY;//DEBUG
    }
    else
    {
        stack_pointer->data_with_canaries = (stack_elem*)realloc(stack_pointer->data_with_canaries,
                                    (size_t)(new_size + 2 * CANARY_SIZE) * sizeof(stack_elem));//DEBUG +2
        stack_pointer->data = stack_pointer->data_with_canaries + CANARY_SIZE;//DEBUG CANARY_SIZE

        stack_pointer->capacity = new_size;

        stack_pointer->data_with_canaries[stack_pointer->capacity + CANARY_SIZE] = STACK_CANARY;//DEBUG
    }

    stack_pointer->data_hash = data_hash(stack_pointer->data_with_canaries, stack_pointer->capacity + 2 * CANARY_SIZE);
    stack_pointer->hash      = hash(stack_pointer);

    stack_check(!stack_ok(stack_pointer), "STACK_RESIZE" && !OK, file, line);

    return 0;
}

static inline void stack_resize_down(stack* stack_pointer, const char* file, size_t line)
{
    if(stack_pointer->size * 4 <= stack_pointer->capacity)
    {
        stack_resize(stack_pointer, (int)ceil(stack_pointer->capacity / 2), file, line);
    }
}

static inline void stack_resize_up(stack* stack_pointer, const char* file, size_t line)
{
    if(stack_pointer->size == stack_pointer->capacity)
    {
        stack_resize(stack_pointer, stack_pointer->capacity * 2, file, line);
    }
}

int set_dump_file(stack *stack_pointer)
{
    check_expression(stack_pointer, POINTER_IS_NULL);

    char *buffer            = (char *)calloc(SIZE_OF_BUFFER, sizeof(char));

    warning(buffer, CALLOC_ERROR);

    const time_t timer      = time(NULL);
    tm *now                 = localtime(&timer);
    const char *time        = asctime(now);
    size_t time_char_length = strlen(time) - 1;
    const char *folder_name = "dumps/";

    strcpy(buffer, folder_name);
    strncpy(buffer + strlen(folder_name), time, time_char_length);
    strcat(buffer, ".txt");

    stack_pointer->dump_file_name = buffer;

    return 0;
}

int stack_ctor(stack* stack_pointer, int capacity, const char* file, size_t line)
{
    check_expression(stack_pointer, POINTER_IS_NULL);

    check_expression(capacity > 0, STACK_BAD_CAPACITY);

    set_dump_file(stack_pointer);

    stack_pointer->left_canary  = STRUCT_STACK_CANARY;  //DEBUG
    stack_pointer->right_canary = STRUCT_STACK_CANARY; //DEBUG

    stack_pointer->size               = 0;
    stack_pointer->capacity           = capacity;
    stack_pointer->data_with_canaries = (stack_elem*)calloc((size_t)(capacity + 2 * CANARY_SIZE), sizeof(stack_elem)); //DEBUG CANARY_SIZE

    warning(stack_pointer->data_with_canaries, CALLOC_ERROR);

    stack_pointer->data               = stack_pointer->data_with_canaries + CANARY_SIZE; //DEBUG

    stack_pointer->data_with_canaries[0]                      = STACK_CANARY;//DEBUG
    stack_pointer->data_with_canaries[CANARY_SIZE + stack_pointer->capacity] = STACK_CANARY;//DEBUG

    for(int number_of_element = 0; number_of_element < stack_pointer->capacity; number_of_element++)
    {
        stack_pointer->data[number_of_element] = POISON;
    }
    stack_pointer->initialized = STACK_INITIALIZED;
    stack_pointer->error       = NO_ERRORS;

    stack_pointer->data_hash = data_hash(stack_pointer->data_with_canaries, stack_pointer->capacity + 2 * CANARY_SIZE);
    stack_pointer->hash      = hash(stack_pointer);

    // stack_public_dump(stack_pointer, file, line, __func__);

    stack_check(!stack_ok(stack_pointer), "STACK_CTOR" && !OK, file, line);

    return 0;
}

int stack_push(stack* stack_pointer, stack_elem value, const char* file, size_t line)
{
    check_expression(stack_pointer, POINTER_IS_NULL);

    stack_check(!stack_ok(stack_pointer), "STACK_PUSH" && !OK, file, line);

    stack_resize_up(stack_pointer, file, line);

    stack_pointer->data[stack_pointer->size] = value;
    stack_pointer->size++;

    stack_pointer->data_hash = data_hash(stack_pointer->data_with_canaries, stack_pointer->capacity + 2 * CANARY_SIZE);
    stack_pointer->hash      = hash(stack_pointer);

    // stack_public_dump(stack_pointer, file, line, __func__);

    stack_check(!stack_ok(stack_pointer), "STACK_PUSH" && !OK, file, line);

    return 0;
}

int stack_pop(stack* stack_pointer, stack_elem* value, const char* file, size_t line)
{
    check_expression(stack_pointer, POINTER_IS_NULL);

    stack_check(!stack_ok(stack_pointer), ("STACK_POP" && !OK), file, line);

    if(stack_pointer->size == 0)
    {
        stack_pointer->error += STACK_UNDERFLOW;

        stack_check(!stack_err_error(stack_pointer->error), ("STACK_POP" && !OK), file, line);
    }

    stack_resize_down(stack_pointer, file, line);

    *value = stack_pointer->data[stack_pointer->size - 1];
    stack_pointer->data[stack_pointer->size - 1] = POISON; //DEBUG
    stack_pointer->size--;

    stack_pointer->data_hash = data_hash(stack_pointer->data_with_canaries, stack_pointer->capacity + 2 * CANARY_SIZE);
    stack_pointer->hash      = hash(stack_pointer);

    // stack_public_dump(stack_pointer, file, line, __func__);

    stack_check(!stack_ok(stack_pointer), ("STACK_POP" && !OK), file, line);

    return 0;
}

int stack_dtor (stack* stack_pointer, const char* file, size_t line)
{
    check_expression(stack_pointer, POINTER_IS_NULL);

    stack_check(!stack_ok(stack_pointer), "STACK_DTOR" && !OK, file, line);

    free(stack_pointer->information);
    free(stack_pointer->data_with_canaries);
    stack_pointer->information = NULL;
    stack_pointer->dump_file_name = NULL;
    stack_pointer->data_with_canaries = NULL;
    stack_pointer->data = NULL;

    return 0;
}
