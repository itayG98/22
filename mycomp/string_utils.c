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

BOOLEAN isValidNumString(const char *str)
{
    BOOLEAN seenDigit = FALSE;
    BOOLEAN seenDot = FALSE;

    if (str == NULL)
        return FALSE;

    SKIP_SPACES(str);

    if (*str == '-' || *str == '+')
        str++;

    while (*str)
    {
        if (isdigit(*str))
        {
            seenDigit = TRUE;
        }
        else if (*str == '.' && !seenDot)
        {
            seenDot = TRUE;
        }
        else if (isspace(*str))
        {
            while (isspace(*str))
            {
                str++;
            }
            if (*str != '\0')
            {
                return FALSE;
            }
            break;
        }
        else
        {
            return FALSE;
        }
        str++;
    }

    return seenDigit;
}

BOOLEAN isSpacesString(const char *str)
{
    if (str == NULL || *str == '\0' || *str == '\n')
    {
        return TRUE;
    }
    while (*str != '\0')
    {
        if (*str != ' ' && *str != '\t')
        {
            return FALSE;
        }
        str++;
    }
    return TRUE;
}

BOOLEAN endsWithDelimiter(char *str, char delimiter)
{
    unsigned int len;
    if (str == NULL || strlen(str) == 0)
    {
        return FALSE;
    }
    len = strlen(str);
    return str[len - 1] == delimiter;
}

char *my_strsep(char **stringp, const char *delim)
{
    char *start;
    char *current;

    if (stringp == NULL || *stringp == NULL)
    {
        return NULL;
    }

    start = *stringp;
    current = start;

    while (*current && !strchr(delim, *current))
    {
        current++;
    }

    if (*current)
    {
        *current = '\0';
        *stringp = current + 1;
    }
    else
    {
        *stringp = NULL;
    }

    if (start == current && strchr(delim, *current))
    {
        return "";
    }

    return start;
}
