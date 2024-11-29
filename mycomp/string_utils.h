#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "common_types.h"

#define SKIP_SPACES(line)                 \
    while (*line == ' ' || *line == '\t') \
    {                                     \
        line++;                           \
    }

char *copyStr(const char *source, const int line_length);
char getOnlyChar(const char *str);
BOOLEAN isTabOrSpace(char c);
#endif