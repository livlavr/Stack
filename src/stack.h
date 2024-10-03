#ifndef STACK_H_
#define STACK_H_

typedef int stack_elem;

enum stack_errors
{
    NO_ERRORS                     = 0,
    STACK_INITIALIZED             = 2,
    STACK_DID_NOT_INITIALIZED     = 1,
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

struct stack_info
{
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

int stack_ctor     (stack* stack, int capacity);
int stack_push     (stack* stack, stack_elem value);
int stack_pop      (stack* stack, stack_elem* value);
int stack_dtor     (stack* stack);
int stack_ok       (stack* stack, const char* function);
int stack_err_error(int ERROR);
int stack_resize   (stack* stack, int new_size);

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
    printf("JERK LOL <3<3<3\n");               \
    printf("\n")

#define CANARY_SIZE (int)(sizeof(uint64_t) / sizeof(stack_elem))

#endif
