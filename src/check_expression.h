#ifndef CHECK_EXPRESSION_H_
#define CHECK_EXPRESSION_H_

#include <cstdlib>

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
            printf("ERROR (%s) : (%s), file: %s, function: %s, line: %d\n", #condition, \
            #message, __FILE__, __FUNCTION__, __LINE__);                                   \
            return condition_return;                                                             \
        }                                                                        \
    } while(0)

    #define warning(condition, message) do                              \
    {                                                                            \
        if (!(condition))                                                        \
        {                                                                        \
            printf("ERROR (%s) : (%s), file: %s, function: %s, line: %d\n", #condition, \
            #message, __FILE__, __FUNCTION__, __LINE__);                                   \
            exit(0);                                                         \
        }                                                                        \
    } while(0)

#else

    #define check_expression(condition, message)

    #define warning(condition, message)

#endif
#endif
