#ifndef DEBUG_MACROS_H_
#define DEBUG_MACROS_H_

#ifndef NDEBUG

    #define GREEN_TEXT   "\033[1;32m"
    #define YELLOW_TEXT  "\033[1;33m"
    #define DEFAULT_TEXT "\033[0m"
    #define BLUE_TEXT    "\033[36m"

    #define $DEBUG(variable, type_of_output) do                                     \
    {                                                                               \
        printf("< " #type_of_output " > - %s | "                                    \
               BLUE_TEXT   "file - %s | "                                              \
               YELLOW_TEXT "line - %d | "                                           \
               GREEN_TEXT  "function - %s\n"                                        \
               DEFAULT_TEXT, variable, #variable, __FILE__, __LINE__, __FUNCTION__);\
    }while(0)

#else

    #define $DEBUG(variable, type_of_output) ;

#endif
#endif
