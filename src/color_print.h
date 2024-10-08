#ifndef COLOR_PRINT_H
#define COLOR_PRINT_H

/// @brief An enum type
/// Output color variables
enum MY_COLOR
{
    DEFAULT_TEXT     = 0,  /**< Value for default output color */
    GREEN_TEXT  = 32, /**< Value for green output color */
    RED_TEXT    = 31, /**< Value for red output color */
    YELLOW_TEXT = 33  /**< Value for yellow output color */
};

/// @brief An enum type
/// Output format of text
enum FORMAT
{
    BOLD    = 1, /**< Value for bold text */
    REGULAR = 0 /**< Value for regular text */
};

/**
 * @brief Function print colorful text what sets with
            three parameters
 *
 * @param [in] color sets color (MY_COLOR) of text
 * @param [in] font sets font (FORMAT) of text
 * @param [in] format_line format line with % symbols (same as in printf)
 * next parameter is values that would insert in format_line
 */
int color_print(MY_COLOR color, FORMAT font, const char * format_line, ...);

/**
 * @brief Function change color of console text what sets with
            two parameters
 *
 * @param color (enum MY_COLOR)
 * @param font (enum FORMAT)
 */
void style_selector(MY_COLOR color, FORMAT font);

#endif
