#ifndef STACK_H_
#define STACK_H_

#include <cstdint>

#include "stack_private.h"

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
    NUMBER_OF_ERRORS              = 11
};

enum DUMP_AND_CTOR_ERRORS
{
    DUMP_FILE_OPENING_ERROR = 100
};

struct stack_info
{
    const char* dump_filename;
    size_t      stack_born_line;
    const char* stack_born_file;
    const char* stack_name;
    size_t      stack_last_usage_line;
    const char* stack_last_usage_function;
    const char* stack_last_usage_file;
};

struct stack
{
    uint64_t     left_canary; //DEBUG
    stack_info*  information;
    stack_elem*  data_with_canaries;//DEBUG
    stack_elem*  data;
    int          size;
    int          capacity;
    stack_errors initialized = STACK_DID_NOT_INITIALIZED;
    int          error = NO_ERRORS;//DEBUG
    uint64_t     right_canary; //DEBUG
};

#define DESCR_(error) \
    printf("%s ", #error);\
    binary_code_output(error);\
    printf("\n")

#define DESCRIPTION_OF_ERRORS                  \
    DESCR_(STACK_DID_NOT_INITIALIZED);         \
    DESCR_(STACK_DOUBLE_INITIALIZING);         \
    DESCR_(STACK_POINTER_IS_NULL);             \
    DESCR_(STACK_OVERFLOW);                    \
    DESCR_(STACK_UNDERFLOW);                   \
    DESCR_(STACK_BAD_CAPACITY);                \
    DESCR_(STACK_BAD_SIZE);                    \
    DESCR_(STACK_STRUCT_BAD_LEFT_CANARY);      \
    DESCR_(STACK_STRUCT_BAD_RIGHT_CANARY);     \
    DESCR_(STACK_BAD_LEFT_CANARY);             \
    DESCR_(STACK_BAD_RIGHT_CANARY);            \
    printf("JERK LOL <3<3<3\n");               \
    printf("\n")

#define CANARY_SIZE (int)(sizeof(uint64_t) / sizeof(stack_elem))

int stack_ctor     (stack* stack, int capacity);
int stack_dump     (stack* stack);
#endif
