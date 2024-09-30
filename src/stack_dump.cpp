#include <stdio.h>

#include "stack_dump.h"

int stack_dump(stack* stack)
{
    printf("stack %s[%p] at %s:%lu born at %s:%lu\n", stack->information->stack_name,
            stack, stack->information->stack_last_usage_file,
            stack->information->stack_last_usage_line,
            stack->information->stack_born_file,
            stack->information->stack_born_line);
    printf("initialized = %d\n", stack->initialized);
    printf("capacity    = %lu\n", stack->capacity);
    printf("size        = %lu\n", stack->size);
    for(size_t index = 0; index < stack->capacity; index++)
    {
        if (index < stack->size)
        {
            printf("*[%lu] = %d\n", index, stack->data[index]);
        }
        else
        {
            printf("[%lu]\n", index);
        }
    }
    printf("\n");

    return 0;
}
