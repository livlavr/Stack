#ifndef STACK_SECURITY_H_
#define STACK_SECURITY_H_

#include "stack_private.h"

static const size_t     OK                  = 1;   //DEBUG
static const stack_elem STRUCT_STACK_CANARY = 808; //DEBUG //TODO rand values
static const stack_elem STACK_CANARY        = 707; //DEBUG //TODO rand values

long int stack_err_error(long int error);
long int stack_ok       (stack* stack, const char* function);
long int stack_ctor_ok  (stack* stack);
void binary_code_output(uint32_t number_of_error, char* error_string);

#endif
