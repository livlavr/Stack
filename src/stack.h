#ifndef STACK_H_
#define STACK_H_

typedef int stack_elem;

enum stack_errors
{
    NO_ERRORS = 0,
    STACK_DID_NOT_INITIALIZED = 1,
    STACK_INITIALIZED = 2,
    STACK_POINTER_IS_NULL = 3,
    STACK_OVERFLOW = 4,
    STACK_UNDERFLOW = 5
};

struct stack_info
{
    size_t stack_born_line;
    char*  stack_name;
    size_t stack_last_usage_line;
    char* stack_last_usage_function;
    char* stack_last_usage_file;
};

struct stack
{
    stack_info* information;
    stack_elem* data;
    size_t size;
    size_t capacity;
    stack_errors initialized = STACK_DID_NOT_INITIALIZED;
    stack_errors error       = NO_ERRORS;
};

int stack_ctor(stack* stack, size_t capacity);
int stack_push(stack* stack, stack_elem value);
int stack_pop(stack* stack, stack_elem* value);
int stack_dtor(stack* stack);
// bool stack_ok(stack* stack);
int stack_resize(stack* stack, size_t new_size);

#endif
