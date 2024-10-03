#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"
#include "recalloc.h"
#include "stack_dump.h"
#include "debug_macros.h"

static const stack_elem POISON              = 109093; //DEBUG?
static const size_t     OK                  = 1; //DEBUG
static const uint64_t   STRUCT_STACK_CANARY = 808; //DEBUG //TODO rand values
static const uint64_t   STACK_CANARY        = 707; //DEBUG //TODO rand values and int <- ull conversion

static int stack_ok       (stack* stack, const char* function);
static int stack_err_error(int ERROR);
static int stack_resize   (stack* stack, int new_size);

static int stack_resize(stack* stack, int new_size) //TODO DO_NOT_CALL_ME
{
    check_expression(!stack_ok(stack, __func__), "STACK_RESIZE" && !OK);

    if(stack->capacity < new_size)
    {
        stack->data_with_canaries = (stack_elem*)recalloc(stack->data_with_canaries, (size_t)(stack->capacity + 2 * CANARY_SIZE),
                       (size_t)(new_size + 2 * CANARY_SIZE), sizeof(stack_elem));//DEBUG
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

static int stack_err_error(int ERROR) //TODO sep in other file
{
    int power_of_error = 1;
    size_t number_of_insignificant_zeros = NUMBER_OF_ERRORS;
    printf("YOUR ERROR CODE: ");
    while(power_of_error <= pow(10, (NUMBER_OF_ERRORS - 1)))
    {
        if(ERROR < power_of_error)
        {
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

static int stack_ok(stack* stack, const char* function) //TODO valid test //TODO add insignificant zeros
{
    //TODO double initialization
    if(strcmp(function, "stack_ctor") && (stack->initialized == STACK_DID_NOT_INITIALIZED))
    {
        stack->error += STACK_DID_NOT_INITIALIZED;
        return stack_err_error(stack->error);;
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

    if(strcmp(function, "stack_ctor") && stack->data == NULL)
    {
        stack->error += STACK_POINTER_IS_NULL;
    }

    if(strcmp(function, "stack_ctor") && stack->left_canary != STRUCT_STACK_CANARY)
    {
        stack->error += STACK_STRUCT_BAD_LEFT_CANARY;
    }

    if(strcmp(function, "stack_ctor") && stack->right_canary != STRUCT_STACK_CANARY)
    {
        stack->error += STACK_STRUCT_BAD_RIGHT_CANARY;
    }

    if(strcmp(function, "stack_ctor") && stack->data_with_canaries[0] != STACK_CANARY)
    {
        stack->error += STACK_BAD_LEFT_CANARY;
    }

    if(strcmp(function, "stack_ctor") && stack->data_with_canaries[CANARY_SIZE + stack->capacity] != STACK_CANARY)
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

int stack_ctor(stack* stack, int capacity)
{
    check_expression(!stack_ok(stack, __func__), "STACK_CTOR" && !OK);

    stack->left_canary  = STRUCT_STACK_CANARY;  //DEBUG
    stack->right_canary = STRUCT_STACK_CANARY; //DEBUG

    stack->size               = 0;
    stack->capacity           = capacity;
    stack->data_with_canaries = (stack_elem*)calloc((size_t)(capacity + 2 * CANARY_SIZE), sizeof(stack_elem)); //DEBUG CANARY_SIZE
    stack->data               = stack->data_with_canaries + CANARY_SIZE; //DEBUG

    stack->data_with_canaries[0]                      = STACK_CANARY;//DEBUG
    stack->data_with_canaries[CANARY_SIZE + stack->capacity] = STACK_CANARY;//DEBUG

    for (int number_of_element = 0; number_of_element < stack->capacity; number_of_element++)
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
        stack_resize(stack, (int)ceil(stack->capacity / 2));
        //TODO If push and pop recently inited stack capacity will become less then user asked. Is it ok?
    }

    *value = stack->data[stack->size - 1];
    stack->data[stack->size - 1] = POISON; //DEBUG
    stack->size--;

    struct stack stack_copy = *stack;
    $STACK_DUMP(stack_copy);

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
