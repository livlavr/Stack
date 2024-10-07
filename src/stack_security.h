#ifndef STACK_SECURITY_H_
#define STACK_SECURITY_H_

#include "stack_private.h"
#include "stack_consts.h"

enum stack_errors
{
    NO_ERRORS                     = 0,
    STACK_INITIALIZED             = 2,
    STACK_DID_NOT_INITIALIZED     = 1,
    STACK_DOUBLE_INITIALIZING     = 2,
    STACK_POINTER_IS_NULL         = 10,
    STACK_OVERFLOW                = 100,
    STACK_UNDERFLOW               = 1000,
    STACK_BAD_CAPACITY            = 10000,
    STACK_BAD_SIZE                = 100000,
    STACK_STRUCT_BAD_LEFT_CANARY  = 1000000,
    STACK_STRUCT_BAD_RIGHT_CANARY = 10000000,
    STACK_BAD_LEFT_CANARY         = 100000000,
    STACK_BAD_RIGHT_CANARY        = 1000000000,
    NUMBER_OF_ERRORS              = 10

};

enum DUMP_AND_CTOR_ERRORS
{
    DUMP_FILE_OPENING_ERROR = 100
};

long int stack_err_error(long int error);
long int stack_ok       (stack* stack, const char* function);
long int stack_ctor_ok  (stack* stack);
void binary_code_output(uint32_t error);

#define DESCR_(ERROR) printf("%s - %d\n", #ERROR, ERROR)

#define DESCRIPTION_OF_ERRORS                  \
    DESCR_(STACK_DID_NOT_INITIALIZED);         \
    DESCR_(STACK_POINTER_IS_NULL);             \
    DESCR_(STACK_OVERFLOW);                    \
    DESCR_(STACK_UNDERFLOW);                   \
    DESCR_(STACK_BAD_CAPACITY);                \
    DESCR_(STACK_BAD_SIZE);                    \
    DESCR_(STACK_STRUCT_BAD_LEFT_CANARY);      \
    DESCR_(STACK_STRUCT_BAD_RIGHT_CANARY);     \
    DESCR_(STACK_BAD_LEFT_CANARY);             \
    DESCR_(STACK_BAD_RIGHT_CANARY);            \
    printf("\n")

#define CANARY_SIZE (int)(sizeof(uint64_t) / sizeof(stack_elem))//DEBUG

#endif
