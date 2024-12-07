#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "common_types.h"

#define SKIP_SPACES(str)                                                 \
    while ((*str == ' ' || *str == '\t') && *str != '\0' && *str != EOF) \
        str++;

#define SKIP_SPACES_WITH_i(str)                                                                \
    while (((str)[i] && ((str)[i] == ' ' || (str)[i] == '\t') && *str != '\0' && *str != EOF)) \
        (i)++;

char *copyStr(const char *source, const int line_length);
char getOnlyChar(const char *str);
BOOLEAN isTabOrSpace(char c);
BOOLEAN isValidNumString(const char *str);
BOOLEAN isSpacesString(const char *str);
BOOLEAN endsWithDelimiter(char *str, char delimiter);
char *my_strsep(char **stringp, const char *delim);
#endif