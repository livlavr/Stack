#ifndef STACK_PRIVATE_H_
#define STACK_PRIVATE_H_

typedef int stack_elem;

struct stack;

stack* create_stack_pointer();

int stack_private_ctor(stack* stack, int capacity, size_t line, const char* name_of_stack,
                       const char* file, const char* dump_filename);
int stack_push     (stack* stack, stack_elem value);
int stack_pop      (stack* stack, stack_elem* value);
int stack_private_dump(stack* stack, size_t line, const char* file, const char* function);
int stack_dtor     (stack* stack);
int stack_dump_file_cleaning(const char* dump_filename);

#define STACK_CTOR(stack, capacity, dump_filename)\
    stack_private_ctor(stack, capacity, __LINE__, #stack, __FILE__, dump_filename)

#endif
