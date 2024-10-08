#ifndef STACK_PUBLIC_H_
#define STACK_PUBLIC_H_

typedef int stack_elem;

struct stack;

stack* create_stack_pointer();

int stack_public_ctor(stack* stack, int capacity, const char* file,
                       size_t line, const char* name);
int stack_push     (stack* stack, stack_elem  value, const char* file, size_t line);
int stack_pop      (stack* stack, stack_elem* value, const char* file, size_t line);
int stack_public_dump(stack* stack, const char* file, size_t line, const char* function);
int stack_dtor     (stack* stack, const char* file, size_t line);

#define getname(a) #a

// #define get_stack_pointer() create_stack_pointer()

#define stack_init(stack_pointer, capacity)\
    stack_public_ctor(stack_pointer, capacity, __FILE__, __LINE__, #stack_pointer)

#define push(stack_pointer, value)\
    stack_push(stack_pointer, value, __FILE__, __LINE__)

#define pop(stack_pointer, value)\
    stack_pop(stack_pointer, value, __FILE__, __LINE__)

#define stack_destroy(stack_pointer)\
    stack_dtor(stack_pointer, __FILE__, __LINE__)

#define stack_dump(stack_pointer)\
    stack_public_dump(stack_pointer, __FILE__, __LINE__, __FUNCTION__)

#endif
