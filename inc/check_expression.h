#ifndef CHECK_EXPRESSION_H_
#define CHECK_EXPRESSION_H_

#include <cstdlib>
#include "color_print.h"

enum TYPE_OF_ERROR
{
    POINTER_IS_NULL = 1,
    DOUBLE_IS_NAN   = 2,
    FILE_OPEN_ERROR = 3,
    FILE_READ_ERROR = 4,
    STAT_ERROR      = 5,
    CALLOC_ERROR    = 6
};

#ifndef NDEBUG

    #define check_expression(condition, message) do                              \
    {                                                                            \
        int condition_return = condition;                                            \
        if (!(condition_return))                                                        \
        {                                                                        \
            color_print(YELLOW_TEXT, BOLD, "ERROR %s : %s, file: %s, function: %s, line: %d\n", #condition, \
            #message, __FILE__, __FUNCTION__, __LINE__);                                   \
            printf("\n");\
            return message;                                                       \
        }                                                                        \
    } while(0)

    #define warning(condition, message) do                              \
    {                                                                            \
        if (!(condition))                                                        \
        {                                                                        \
            color_print(RED_TEXT, BOLD, "ERROR %s : %s, file: %s, function: %s, line: %d\n", #condition, \
            #message, __FILE__, __FUNCTION__, __LINE__);                                   \
            printf("\n");\
            exit(0);                                                         \
        }                                                                        \
    } while(0)

#else

    #define check_expression(condition, message)

    #define warning(condition, message)

#endif
#endif
