#ifndef STACK_PRIVATE_H_
#define STACK_PRIVATE_H_

typedef int stack_elem;

struct stack;

stack* create_stack_pointer();

int stack_private_ctor(stack* stack, int capacity, size_t line, const char* file);
int stack_push     (stack* stack, stack_elem value);
int stack_pop      (stack* stack, stack_elem* value);
int stack_private_dump(stack* stack, size_t line,
                                        const char* file, const char* function);
int stack_dtor     (stack* stack);

#define getname(a) #a

#endif
