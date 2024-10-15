#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack_security.h"
#include "stack_consts.h"
#include "stack_public.h"
#include "stack.h"
#include "debug_macros.h"
#include "../Color-printf/color_printf.h"
#include "../Custom-asserts/custom_asserts.h"


void binary_code_output(int error)
{
    if((error >> 1) != 0)
    {
        binary_code_output(error >> 1);
        printf("%d", error % 2);
    }
    else
    {
        printf("%d", error % 2);
    }
}

int stack_err_error(int error)
{
    color_printf(RED_TEXT, BOLD, "YOUR ERROR CODE: ");
    binary_code_output(error);
    printf("\n");
    DESCRIPTION_OF_ERRORS(error);

    return error;
}

int stack_ok(stack* stack_pointer) //TODO valid test
{
    check_expression(stack_pointer != NULL, POINTER_IS_NULL);

    int new_error_code = NO_ERRORS;

    if(stack_pointer->hash != hash(stack_pointer)) //DEBUG
    {
        new_error_code |= STACK_BAD_HASH;
    }

    if(stack_pointer->data_hash != data_hash(stack_pointer->data_with_canaries,
       stack_pointer->capacity + 2 * CANARY_SIZE))//DEBUG
    {
        new_error_code |= STACK_BAD_DATA_HASH;
    }

    if(stack_pointer->initialized == STACK_DID_NOT_INITIALIZED)
    {
        new_error_code |= STACK_DID_NOT_INITIALIZED;

        stack_pointer->error = new_error_code;

        return stack_err_error(stack_pointer->error);
    }

    if(stack_pointer->capacity < stack_pointer->size)
    {
        new_error_code |= STACK_OVERFLOW;
    }

    if(stack_pointer->capacity < 0)
    {
        new_error_code |= STACK_BAD_CAPACITY;
    }

    if(stack_pointer->size < 0)
    {
        new_error_code |= STACK_BAD_SIZE;
    }

    if(stack_pointer->left_canary != STRUCT_STACK_CANARY)
    {
        new_error_code |= STACK_STRUCT_BAD_LEFT_CANARY;
    }

    if(stack_pointer->right_canary != STRUCT_STACK_CANARY)
    {
        new_error_code |= STACK_STRUCT_BAD_RIGHT_CANARY;
    }

    if(stack_pointer->data_with_canaries[0] != STACK_CANARY)
    {
        new_error_code |= STACK_BAD_LEFT_CANARY;
    }

    if(stack_pointer->data_with_canaries[CANARY_SIZE + stack_pointer->capacity] != STACK_CANARY)
    {
        new_error_code |= STACK_BAD_RIGHT_CANARY;
    }

    if(new_error_code == NO_ERRORS)
    {
        stack_pointer->error = NO_ERRORS;

        return NO_ERRORS;
    }
    else
    {
        stack_pointer->error = new_error_code;

        return stack_err_error(stack_pointer->error);
    }
}

uint64_t data_hash(stack_elem* data_with_canaries, int size)
{
    check_expression(data_with_canaries != NULL, POINTER_IS_NULL);

    uint64_t hash = 5381;
    int c = 0;

    char* ptr = (char*)data_with_canaries;
    uint64_t size_of_data = (uint64_t)((size_t)size * sizeof(stack_elem));
    for (uint64_t number_of_ptr = 0; number_of_ptr <= size_of_data; number_of_ptr++)
    {
        c = *(int*)ptr++;
        hash = ((hash << 5) + hash) + (uint64_t)c;
    }

    return hash;
}

uint64_t hash(stack *stack_pointer)
{
    check_expression(stack_pointer != NULL, STACK_POINTER_IS_NULL);

    uint64_t hash = 5381;
    int c = 0;

    char* ptr = (char*)stack_pointer;
    uint64_t right_canary_pointer = (uint64_t)&stack_pointer->right_canary;
    uint64_t hash_pointer = (uint64_t)&stack_pointer->hash;
    uint64_t size_of_hash = sizeof(uint64_t);
    uint64_t size_of_int  = sizeof(int);

    while ((uint64_t)ptr <= right_canary_pointer)
    {
        if((uint64_t)ptr <= hash_pointer - size_of_int || (uint64_t)ptr >= hash_pointer + size_of_hash)
        {
            c = *(int*)ptr++;
            hash = ((hash << 5) + hash) + (uint64_t)c;
        }
        else
        {
            ptr++;
        }
    }

    return hash;
}
