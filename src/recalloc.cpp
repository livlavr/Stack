#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_types.h"
#include "stack_public.h"
#include "stack.h"
#include "recalloc.h"
#include "debug_macros.h"
#include "stack_security.h"

void* recalloc(void* const ptr, size_t old_size, size_t new_size, size_t size_of_type)
{
    char* new_ptr = NULL;

    if(ptr == NULL || old_size == 0)
    {
        new_ptr = (char*)calloc(new_size, size_of_type);

        if(new_ptr == NULL)
        {
            return NULL;
        }
        else
        {
            return (void*)new_ptr;
        }
    }

    if(new_size < old_size)
    {
        new_ptr = (char*)realloc(ptr, new_size * size_of_type);

        if(new_ptr == NULL)
        {
            return NULL;
        }
        else
        {
            return (void*)new_ptr;
        }
    }

    new_ptr = (char*)realloc(ptr, new_size * size_of_type);

    if(new_ptr == NULL)
    {
        return NULL;
    }
    memset(new_ptr + (old_size) * size_of_type, 0, (new_size - (old_size + CANARY_SIZE)) * size_of_type);//DEBUG

    return (void*)new_ptr;
};
