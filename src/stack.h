#ifndef STACK_H_
#define STACK_H_

typedef int stack_elem;

enum stack_errors
{
    NO_ERRORS = 0,
    STACK_INITIALIZED = 2,
    STACK_DID_NOT_INITIALIZED = 1,
    STACK_POINTER_IS_NULL = 10,
    STACK_OVERFLOW = 100,
    STACK_UNDERFLOW = 1000,
    STACK_BAD_CAPACITY = 10000,
    STACK_BAD_SIZE = 100000
};

struct stack_info
{
    size_t stack_born_line;
    const char* stack_born_file;
    const char*  stack_name;
    size_t stack_last_usage_line;
    const char* stack_last_usage_function;
    const char* stack_last_usage_file;
};

struct stack
{
    stack_info* information;
    stack_elem* data;
    int size;
    int capacity;
    stack_errors initialized = STACK_DID_NOT_INITIALIZED;
    int error       = NO_ERRORS;
};

int stack_ctor(stack* stack, size_t capacity);
int stack_push(stack* stack, stack_elem value);
int stack_pop(stack* stack, stack_elem* value);
int stack_dtor(stack* stack);
int stack_ok(stack* stack, const char* function);
int stack_err_error(int ERROR);
int stack_resize(stack* stack, size_t new_size);

#define DESCR_(ERROR) printf("%s - %d", #ERROR, ERROR)

#endif
