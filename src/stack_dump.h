#ifndef STACK_DUMP_H_
#define STACK_DUMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "check_expression.h"

enum DUMP_AND_CTOR_ERRORS
{
    DUMP_FILE_OPENING_ERROR = 100
};

int stack_dump(stack* stack);
int stack_dump_file_cleaning();

#ifndef NDEBUG

    #define STACK_BORN_INFO(stack)                                     \
        stack.information = (stack_info*)calloc(1, sizeof(stack_info));\
        *(stack.information)               = {};                       \
        stack.information->stack_name      = #stack;                   \
        stack.information->stack_born_line = __LINE__;                 \
        stack.information->stack_born_file = __FILE__

    #define GET_LAST_INFO(stack)                                           \
        stack.information->stack_last_usage_line     = __LINE__;           \
        stack.information->stack_last_usage_function = __PRETTY_FUNCTION__;\
        stack.information->stack_last_usage_file     = __FILE__

    #define $STACK_DUMP(stack)\
        GET_LAST_INFO(stack); \
        stack_dump(&stack)

    #define $STACK_CTOR(stack, size)\
        STACK_BORN_INFO(stack);     \
        stack_ctor(&stack, size)

#endif
#endif

