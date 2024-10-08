#ifndef STACK_PRIVATE_H_
#define STACK_PRIVATE_H_

typedef int stack_elem;

struct stack;

stack* create_stack_pointer();

int stack_private_ctor(stack* stack, int capacity, size_t line, const char* file);
int stack_push     (stack* stack, stack_elem  value, const char* file, size_t line);
int stack_pop      (stack* stack, stack_elem* value, const char* file, size_t line);
int stack_private_dump(stack* stack, size_t line,
                       const char* file, const char* function);
int stack_dtor     (stack* stack);

#define getname(a) #a

#define push(Stack, value)\
    stack_push(Stack, value, __FILE__, __LINE__)

#define pop(Stack, value)\
    stack_pop(Stack, value, __FILE__, __LINE__)

#endif
