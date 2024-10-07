#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack_security.h"
#include "stack_private.h"
#include "stack.h"

void binary_code_output(uint32_t error, char* error_string)
{
    if((error >> 1) != 0)
    {
        binary_code_output(error >> 1);
        printf("%u", error % 2);
    }
    else
    {
        printf("%u", error % 2);
    }
}

long int stack_err_error(long int error)
{
    printf("YOUR ERROR CODE: ");
    char* error_string = calloc(NUMBER_OF_ERRORS, sizeof(char));

    check_expression(error_string != NULL, CALLOC_ERROR);

    for(size_t number_of_char = 0, number_of_char < NUMBER_OF_ERRORS; number_of_char++)
    {
        error_string[number_of_char] = '0';
    }

    binary_code_output((uint32_t)error, error_string);
    printf("\n");
    DESCRIPTION_OF_ERRORS;

    return error;
}

long int stack_ok(stack* stack, const char* function) //TODO valid test //check stack error in the beginning
{
    if(stack->error != 0)
    {
        return stack_err_error(stack->error);
    }

    if(strcmp(function, "stack_ctor") && (stack->initialized == STACK_DID_NOT_INITIALIZED))
    {
        stack->error += STACK_DID_NOT_INITIALIZED;
        return stack_err_error(stack->error);
    }

    if(stack->capacity < stack->size)
    {
        stack->error += STACK_OVERFLOW;
    }

    // TODO move to popa
    if(!strcmp(function, "stack_pop") && stack->size == 0)
    {
        stack->error += STACK_UNDERFLOW;
    }
    if(stack->capacity < 0)
    {
        stack->error += STACK_BAD_CAPACITY;
    }

    if(stack->size < 0)
    {
        stack->error += STACK_BAD_SIZE;
    }

    if(stack->left_canary != STRUCT_STACK_CANARY)
    {
        stack->error += STACK_STRUCT_BAD_LEFT_CANARY;
    }

    if(stack->right_canary != STRUCT_STACK_CANARY)
    {
        stack->error += STACK_STRUCT_BAD_RIGHT_CANARY;
    }

    if(stack->data_with_canaries[0] != STACK_CANARY)
    {
        stack->error += STACK_BAD_LEFT_CANARY;
    }

    if(stack->data_with_canaries[CANARY_SIZE + stack->capacity] != STACK_CANARY)
    {
        stack->error += STACK_BAD_RIGHT_CANARY;
    }

    if(stack->error == 0)
    {
        return NO_ERRORS;
    }
    else
    {
        return stack_err_error(stack->error);
    }
}

long int stack_ctor_ok(stack* stack)
{
    if(stack->error != 0)
    {
        return stack_err_error(stack->error);
    }
    if(stack->initialized == STACK_INITIALIZED)
    {
        stack->error += STACK_DOUBLE_INITIALIZING;
    }
    if(stack->capacity < 0)
    {
        stack->error += STACK_BAD_CAPACITY;
    }
    if(stack->size < 0)
    {
        stack->error += STACK_BAD_SIZE;
    }
    return stack_err_error(stack->error);
}
