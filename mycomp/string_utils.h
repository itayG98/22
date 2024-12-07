#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "common_types.h"

/* MACRO to skip str pointer to the firsst non whitespace*/
#define SKIP_SPACES(str)                                                 \
    while ((*str == ' ' || *str == '\t') && *str != '\0' && *str != EOF) \
        str++;

/* MACRO to skip str pointer to the first non whitespace and increasing i parameter*/
#define SKIP_SPACES_WITH_i(str)                                                                \
    while (((str)[i] && ((str)[i] == ' ' || (str)[i] == '\t') && *str != '\0' && *str != EOF)) \
        (i)++;

/*Helper method to copy a string into new allocated memory*/
char *copyStr(const char *source, const int length);
/*Helper method to return a charecter if it is the only non-white charecter in a string*/
char getOnlyChar(const char *str);
/*Helper method to wether a charecter is white charecter*/
BOOLEAN isTabOrSpace(char c);
/*Validation method before a string inserted into atof method*/
BOOLEAN isValidNumString(const char *str);
/*Helper method check wether a given string contains only white charecters*/
BOOLEAN isSpacesString(const char *str);
/*
 * Helper method to tokenize a string.
 * Unlike `strtok()`, consecutive delimiters return an empty string instead of skipping tokens.
 */
char *my_strsep(char **stringp, const char *delim);
#endif