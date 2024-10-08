#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack_security.h"
#include "stack_consts.h"
#include "stack_private.h"
#include "stack.h"
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
    color_print(RED_TEXT, BOLD, "YOUR ERROR CODE:");
    binary_code_output(error);
    printf("\n");
    DESCRIPTION_OF_ERRORS(error);

    return error;
}

int stack_ok(stack* stack, const char* function) //TODO valid test //check stack error in the beginning
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

int stack_ctor_ok(stack* stack)
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
