#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "string_utils.h"
#include "common_types.h"

char *copyStr(const char *source, const int line_length)
{
    if (source != NULL)
    {
        char *copy = malloc(sizeof(char) * line_length);
        if (copy == NULL)
        {
            return NULL;
        }
        strncpy(copy, source, line_length - 1);
        copy[line_length - 1] = '\0';
        return copy;
    }
    return NULL;
}

char getOnlyChar(const char *str)
{
    char foundChar = '\0';
    const char *ptr = str;
    if (str == NULL)
        return '\0';
    SKIP_SPACES(ptr)
    if (*ptr == '\0')
        return '\0';
    foundChar = *ptr;
    ptr++;
    while (*ptr)
    {
        if (!isspace(*ptr))
            return '\0';
        ptr++;
    }
    return foundChar;
}

BOOLEAN isTabOrSpace(char c)
{
    return c == ' ' || c == '\t' ? TRUE : FALSE;
}
