#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "common_types.h"

/* MACRO to skip str pointer to the first non whitespace*/
#define SKIP_SPACES(str)                                                 \
    while ((*str == ' ' || *str == '\t') && *str != '\0' && *str != EOF) \
        str++;

/* MACRO to skip str pointer to the first non whitespace and increasing i parameter*/
#define SKIP_SPACES_WITH_i(str)                                                                \
    while (((str)[i] && ((str)[i] == ' ' || (str)[i] == '\t') && *str != '\0' && *str != EOF)) \
        (i)++;

/*Helper method to copy a string into new allocated memory*/
char *copyStr(const char *source, const int length);
/*Helper method to return a character if it is the only non-white character in a string*/
char getOnlyChar(const char *str);
/*Validation method before a string inserted into atof method*/
BOOLEAN isValidNumString(const char *str);
/*Helper method check wether a given string contains only white characters*/
BOOLEAN isSpacesString(const char *str);

/*
 * Splits a string into tokens based on a set of delimiters.
 * Unlike `strtok()`, consecutive delimiters return an empty string instead of skipping tokens.
  @param inputPtr: Pointer to the string to tokenize. The pointer is updated
 *             to point to the next segment of the string.
  @param delimiters: A string containing the delimiter characters.
  @return A pointer to the next token (or segment) in the string ,
  NULL if there are no more tokens or empty string if consecutive decimeters
 */
char *my_strsep(char **inputPtr, const char *delimiters);

/*
Return wether consecutive commas
*/
BOOLEAN checkConsecutiveCommas(char *params_str);
#endif