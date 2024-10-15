#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <cstdlib>

#include "stack_private.h"
#include "recalloc.h"
#include "Custom-asserts/custom_asserts.h"
#include "ab_test.h"
#include "debug_macros.h"

int stack_manipulations_example()
{
    stack* st = create_stack_pointer();
    STACK_CTOR(st, 10, "dump.txt");
    int x = 0;
    stack_push(st, 1);
    stack_push(st, 2);
    stack_push(st, 3);
    stack_push(st, 4);
    stack_push(st, 1);
    stack_push(st, 2);
    stack_pop(st, &x);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_push(st, 4);
    stack_pop(st, &x);
    stack_pop(st, &x);
    stack_pop(st, &x);
    stack_pop(st, &x);
    stack_pop(st, &x);

    stack_dtor(st);

    return 0;
}

char* scan_text(const char* filename, char* text)
{
    check_expression(filename != NULL, POINTER_IS_NULL);

    FILE* file      = fopen(filename, "r");
    struct stat buf = {};

    check_expression(file != NULL, FILE_OPEN_ERROR);

    int stat_value_check = stat(filename, &buf);

    check_expression(stat_value_check != -1, STAT_ERROR);

    size_t size_of_text = (size_t)buf.st_size + 1;
    text                = (char*)calloc(size_of_text, sizeof(char));

    check_expression(text != NULL, CALLOC_ERROR);

    size_t fread_value_check = fread(text, sizeof(char), size_of_text, file);

    check_expression(fread_value_check != 0, FILE_READ_ERROR);

    fclose(file);

    return text;
}

int ab_test()
{
    stack_manipulations_example();

    char* dump = NULL;
    char* test = NULL;
    dump = scan_text("dump.txt", dump);
    test = scan_text("test.txt", test);

    if(strlen(dump) == strlen(test))
    {
        printf(GREEN_TEXT "SUCCESS\n" DEFAULT_TEXT);
    }
    else
    {
        printf(YELLOW_TEXT "FAILED\n" DEFAULT_TEXT);
    }

    return 0;
}
