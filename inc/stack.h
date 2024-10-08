#ifndef STACK_H_
#define STACK_H_

#include <cstdint>

#include "stack_private.h"
#include "stack_consts.h"
#include "stack_security.h"

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
    stack_elem   left_canary; //DEBUG
    stack_info*  information;
    stack_elem*  data_with_canaries;//DEBUG
    const char*  dump_file_name;
    stack_elem*  data;
    int          size;
    int          capacity;
    stack_errors initialized = STACK_DID_NOT_INITIALIZED;
    int          error       = NO_ERRORS;//DEBUG
    stack_elem   right_canary; //DEBUG
};

int stack_ctor     (stack* stack, int capacity, const char* file,
                    size_t line, const char* name);
int stack_dump     (stack* stack);
int set_dump_file  (stack *stack);
#endif
