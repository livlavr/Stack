#include <stdio.h>
#include <stdlib.h>

#include "error_types.h"
#include "stack_public.h"
#include "stack.h"
#include "../Custom-asserts/custom_asserts.h"

#include "stack_security.h"

int stack_public_ctor(stack** stack_pointer, int capacity, const char* file,
                       size_t line, const char* name)
{
    warning(capacity > 0, STACK_BAD_CAPACITY);

    *stack_pointer = (stack*)calloc(1, sizeof(stack));

    customAssert(stack_pointer, CALLOC_ERROR);

    (*stack_pointer)->error       = NO_ERRORS;
    (*stack_pointer)->initialized = STACK_DID_NOT_INITIALIZED;

    (*stack_pointer)->information = (stack_info*)calloc(1, sizeof(stack_info));

    customAssert((*stack_pointer)->information, CALLOC_ERROR);

    *((*stack_pointer)->information)               = {};
    (*stack_pointer)->information->stack_name      = name;
    (*stack_pointer)->information->stack_born_line = line;
    (*stack_pointer)->information->stack_born_file = file;

    stack_ctor(*stack_pointer, capacity, file, line);

    return 0;
}

int stack_public_dump(stack* stack_pointer, const char* file, size_t line, const char* function)
{
    return 0;   //return bacause of release version - //TODO make debug() wrap for dumps and canaries

    warning(stack_pointer, POINTER_IS_NULL);

    // stack_check(!stack_ok(stack_pointer), "STACK_DUMP" && !OK, file, line); - //BUG Vulnerability intentionally left for the task

    stack_pointer->information->stack_last_usage_line     = line;
    stack_pointer->information->stack_last_usage_file     = file;
    stack_pointer->information->stack_last_usage_function = function;

    stack_private_dump(stack_pointer);

    return 0;
}
