#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "recalloc.h"
#include "defined_dump_and_ctor.h"

static const stack_elem POISON = 109093; //DEBUG?
static const size_t OK = 1; //DEBUG
static const stack_elem STRUCT_STACK_CANARY = 808; //DEBUG
static const stack_elem STACK_CANARY = 707; //DEBUG

int stack_ctor(stack* stack, size_t capacity)
{
    check_expression(!stack_ok(stack, __func__), "STACK_CTOR" && !OK);

    stack->left_canary = STRUCT_STACK_CANARY; //DEBUG
    stack->right_canary = STRUCT_STACK_CANARY; //DEBUG

    stack->size        = 0;
    stack->capacity    = capacity;
    stack->data        = (stack_elem*)calloc(capacity + 2, sizeof(stack_elem)); //DEBUG +2

    stack->data[0] = STACK_CANARY;//DEBUG
    stack->data[stack->capacity + 1] = STACK_CANARY;//DEBUG

    stack->data = stack->data + 1;//DEBUG

    for (size_t number_of_element = 0; number_of_element < stack->capacity; number_of_element++)
    {
        stack->data[number_of_element] = POISON;
    }
    stack->initialized = STACK_INITIALIZED;
    stack->error       = NO_ERRORS;

    struct stack stack_copy = *stack;
    $STACK_DUMP(stack_copy);

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

    struct stack stack_copy = *stack;
    $STACK_DUMP(stack_copy);

    check_expression(!stack_ok(stack, __func__), "STACK_PUSH" && !OK);

    return 0;
}

int stack_pop(stack* stack, stack_elem* value)
{
    check_expression(!stack_ok(stack, __func__), ("STACK_POP" && !OK));

    if (stack->size * 4 <= stack->capacity)
    {
        stack->capacity = (size_t)ceil(stack->capacity / 2);
        //TODO If push and pop recently inited stack capacity will become less then user asked. Is it ok?
    }

    *value = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = POISON;
    stack->size--;

    struct stack stack_copy = *stack;
    $STACK_DUMP(stack_copy);

    return 0;
}

int stack_dtor(stack* stack)
{
    check_expression(!stack_ok(stack, __func__), "STACK_DTOR" && !OK);

    stack->size     = 0;
    stack->capacity = 0;
    free(&stack->data[-1]);
    stack->data = NULL;

    return 0;
}

int stack_resize(stack* stack, size_t new_size) //TODO DO_NOT_CALL_ME
{
    check_expression(!stack_ok(stack, __func__), "STACK_RESIZE" && !OK);

    if(stack->capacity < new_size)
    {
        stack->data = (stack_elem*)recalloc(stack->data, stack->capacity,
                       new_size, sizeof(stack_elem));
        stack->capacity *= 2;

        for (size_t number_of_element = stack->size; number_of_element < stack->capacity; number_of_element++)
        {
            stack->data[number_of_element] = POISON;
        }
    }
    else
    {
        stack->data = (stack_elem*)realloc(stack->data, new_size * sizeof(stack_elem));
    }

    check_expression(!stack_ok(stack, __func__), "STACK_RESIZE" && !OK);

    return 0;
}

int stack_err_error(int ERROR)
{
    size_t power_of_error = 1;
    size_t number_of_insignificant_zeros = NUMBER_OF_ERRORS;
    while(power_of_error <= 10 * (NUMBER_OF_ERRORS - 1))
    {
        if(ERROR < power_of_error)
        {
            printf("YOUR ERROR CODE: ");
            for(size_t number_of_printed_zeros = 0; number_of_printed_zeros < number_of_insignificant_zeros; number_of_printed_zeros++)
            {
                printf("0");
            }
            printf("%d\n", ERROR);

            DESCRIPTION_OF_ERRORS;

            return ERROR;
        }

        power_of_error *= 10;
        number_of_insignificant_zeros--;
    }
    printf("%d\n", ERROR);

    DESCRIPTION_OF_ERRORS;

    return ERROR;
}

int stack_ok(stack* stack, const char* function) //TODO valid test //TODO add insignificant zeros
{
    if(stack->initialized == STACK_DID_NOT_INITIALIZED && function != "stack_ctor")
    {
        stack->error += STACK_DID_NOT_INITIALIZED;

        return stack->error;
    }

    if(stack->capacity < stack->size)
    {
        stack->error += STACK_OVERFLOW;
    }

    if(stack->size == 0 && function == "stack_pop")
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

    if(stack->data == NULL && function != "stack_ctor")
    {
        stack->error += STACK_POINTER_IS_NULL;
    }

    if(stack->left_canary != STRUCT_STACK_CANARY && function != "stack_ctor")
    {
        stack->error += STACK_STRUCT_BAD_LEFT_CANARY;
    }

    if(stack->right_canary != STRUCT_STACK_CANARY && function != "stack_ctor")
    {
        stack->error += STACK_STRUCT_BAD_RIGHT_CANARY;
    }

    // if(stack->data[-1] != STACK_CANARY && function != "stack_ctor")
    // {
    //     stack->error += STACK_BAD_LEFT_CANARY;
    // }
    // printf("%d", stack->data[stack->capacity - 2]);
    // if(stack->data[stack->capacity - 1] != STACK_CANARY && function != "stack_ctor")
    // {
    //     stack->error += STACK_BAD_RIGHT_CANARY;
    // }

    if(stack->error == 0)
    {
        return NO_ERRORS;
    }
    else
    {
        return stack_err_error(stack->error);
    }
}
