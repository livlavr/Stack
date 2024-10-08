#ifndef STACK_PRIVATE_H_
#define STACK_PRIVATE_H_

typedef int stack_elem;

struct stack;

stack* create_stack_pointer();

int stack_private_ctor(stack* stack, int capacity, const char* file,
                       size_t line, const char* name);
int stack_push     (stack* stack, stack_elem  value, const char* file, size_t line);
int stack_pop      (stack* stack, stack_elem* value, const char* file, size_t line);
int stack_private_dump(stack* stack, size_t line,
                       const char* file, const char* function);
int stack_dtor     (stack* stack, const char* file, size_t line);

#define getname(a) #a

#define stack_init(stack_pointer, capacity)\
    stack_private_ctor(stack_pointer, capacity, __FILE__, __LINE__, #stack_pointer)

#define push(stack_pointer, value)\
    stack_push(stack_pointer, value, __FILE__, __LINE__)

#define pop(stack_pointer, value)\
    stack_pop(stack_pointer, value, __FILE__, __LINE__)

#define stack_destroy(stack_pointer)\
    stack_dtor(stack_pointer, __FILE__, __LINE__)

#endif
