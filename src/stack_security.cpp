#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack_security.h"
#include "stack_consts.h"
#include "stack_private.h"
#include "stack.h"
#include "debug_macros.h"
#include "color_print.h"

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
    color_print(RED_TEXT, BOLD, "YOUR ERROR CODE: ");
    binary_code_output(error);
    printf("\n");
    DESCRIPTION_OF_ERRORS(error);

    return error;
}

int stack_ok(stack* stack) //TODO valid test //check stack error in the beginning
{
    int new_error_code = NO_ERRORS;

    //TODO hash check

    if(stack->initialized == STACK_DID_NOT_INITIALIZED)
    {
        new_error_code += STACK_DID_NOT_INITIALIZED;

        stack->error = new_error_code;

        return stack_err_error(stack->error);
    }

    if(stack->capacity < stack->size)
    {
        new_error_code += STACK_OVERFLOW;
    }

    if(stack->capacity < 0)
    {
        new_error_code += STACK_BAD_CAPACITY;
    }

    if(stack->size < 0)
    {
        new_error_code += STACK_BAD_SIZE;
    }

    if(stack->left_canary != STRUCT_STACK_CANARY)
    {
        new_error_code += STACK_STRUCT_BAD_LEFT_CANARY;
    }

    if(stack->right_canary != STRUCT_STACK_CANARY)
    {
        new_error_code += STACK_STRUCT_BAD_RIGHT_CANARY;
    }

    if(stack->data_with_canaries[0] != STACK_CANARY)
    {
        new_error_code += STACK_BAD_LEFT_CANARY;
    }

    if(stack->data_with_canaries[CANARY_SIZE + stack->capacity] != STACK_CANARY)
    {
        new_error_code += STACK_BAD_RIGHT_CANARY;
    }

    if(new_error_code == NO_ERRORS)
    {
        stack->error = NO_ERRORS;

        return NO_ERRORS;
    }
    else
    {
        stack->error = new_error_code;

        return stack_err_error(stack->error);
    }
}
