#ifndef STACK_DUMP_H_
#define STACK_DUMP_H_

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
#include "stack.h"

int stack_dump(stack* stack);

#ifndef NDEBUG

    #define STACK_BORN_INFO(stack)\
        stack.information.stack_name =                     \
            (char*)calloc(strlen(#stack) + 1, sizeof(char));\
        stack.information.stack_name = #stack;\
                                                \
        stack.information.stack_born_line = __LINE__

    #define GET_LAST_INFO(stack)                                     \
        stack.information.stack_last_usage_line = __LINE__;               \
                                                                     \
        stack.information.stack_last_usage_function =                     \
            (char*)calloc(strlen(__PRETTY_FUNCTION__) + 1, sizeof(char));\
        stack.information.stack_last_usage_function = __PRETTY_FUNCTION__;\
                                                                     \
        stack.information.stack_last_usage_file =                         \
            (char*)calloc(strlen(__FILE__) + 1, sizeof(char));           \
        stack.information.stack__last_usage_file = __FILE__

    #define $STACK_DUMP(stack)                                  \
        GET_LAST_INFO(stack);                                        \
        stack_dump(&stack)

    #define $STACK_CTOR(stack, size)\
        STACK_BORN_INFO(stack);\
        stack_ctor(&stack, size)

#endif
#endif

