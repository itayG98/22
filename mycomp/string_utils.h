#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "common_types.h"

#define SKIP_SPACES(line)                                                    \
    while ((*line == ' ' || *line == '\t') && *line != '\0' && *line != EOF) \
        line++;

#define SKIP_SPACES_WITH_i(line)                                                                    \
    while (((line)[i] && ((line)[i] == ' ' || (line)[i] == '\t') && *line != '\0' && *line != EOF)) \
        (i)++;

#define IS_EMPTY(str) (!(*str) || (str) == NULL || *(str) == '\0')

char *copyStr(const char *source, const int line_length);
char getOnlyChar(const char *str);
BOOLEAN isTabOrSpace(char c);
BOOLEAN isValidNumString(const char *str);
BOOLEAN isSpacesString(const char *str);
BOOLEAN endsWithDelimiter(char *str, char delimiter);
char *my_strsep(char **stringp, const char *delim);
#endif