#ifndef STACK_SECURITY_H_
#define STACK_SECURITY_H_

#include "stack_public.h"
#include "stack_consts.h"
#include "color_printf.h"

#define DESCR_(error, big_error)                      \
    if((big_error / error & 1) == 1)                  \
    {                                                 \
        color_printf(RED_COLOR, BOLD, #error " ");    \
    }                                                 \
    else                                              \
    {                                                 \
        printf("%s ", #error);                        \
    }                                                 \
    binary_code_output(error);                        \
    printf("\n")                                      \

#define DESCRIPTION_OF_ERRORS(big_error)              \
    DESCR_(STACK_DID_NOT_INITIALIZED, big_error);     \
    DESCR_(STACK_DOUBLE_INITIALIZING, big_error);     \
    DESCR_(STACK_POINTER_IS_NULL, big_error);         \
    DESCR_(STACK_OVERFLOW, big_error);                \
    DESCR_(STACK_UNDERFLOW, big_error);               \
    DESCR_(STACK_BAD_CAPACITY, big_error);            \
    DESCR_(STACK_BAD_SIZE, big_error);                \
    DESCR_(STACK_STRUCT_BAD_LEFT_CANARY, big_error);  \
    DESCR_(STACK_STRUCT_BAD_RIGHT_CANARY, big_error); \
    DESCR_(STACK_BAD_LEFT_CANARY, big_error);         \
    DESCR_(STACK_BAD_RIGHT_CANARY, big_error);        \
    DESCR_(STACK_BAD_HASH, big_error);                \
    DESCR_(STACK_BAD_DATA_HASH, big_error);

#define CANARY_SIZE (int)(sizeof(stack_elem) / sizeof(stack_elem))//DEBUG

#define stack_check(condition, message, file, line) do                                                    \
{                                                                                                         \
    int condition_return = condition;                                                                     \
    if(!(condition_return))                                                                               \
    {                                                                                                     \
        color_printf(YELLOW_COLOR, BOLD, "ERROR %s : %s, file: %s, function: %s, line: %d\n", #condition, \
        #message, file, __FUNCTION__, line);                                                              \
        printf("\n");                                                                                     \
        return message;                                                                                   \
    }                                                                                                     \
} while(0)

enum stack_errors
{
    NO_ERRORS                     = 0,
    STACK_INITIALIZED             = 2,
    STACK_DID_NOT_INITIALIZED     = 1 << 0,
    STACK_DOUBLE_INITIALIZING     = 1 << 1,
    STACK_POINTER_IS_NULL         = 1 << 2,
    STACK_OVERFLOW                = 1 << 3,
    STACK_UNDERFLOW               = 1 << 4,
    STACK_BAD_CAPACITY            = 1 << 5,
    STACK_BAD_SIZE                = 1 << 6,
    STACK_STRUCT_BAD_LEFT_CANARY  = 1 << 7,
    STACK_STRUCT_BAD_RIGHT_CANARY = 1 << 8,
    STACK_BAD_LEFT_CANARY         = 1 << 9,
    STACK_BAD_RIGHT_CANARY        = 1 << 10,
    STACK_BAD_HASH                = 1 << 11,
    STACK_BAD_DATA_HASH           = 1 << 12
};

enum DUMP_AND_CTOR_ERRORS
{
    FILE_OPENING_ERROR = 100
};

int      stack_err_error    (int error);
int      stack_ok           (stack* stack_pointer);
void     binary_code_output (int error);
uint64_t hash               (stack *stack_pointer);
uint64_t data_hash          (stack_elem* data_with_canaries, int size);

#endif
