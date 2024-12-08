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

#include <stdio.h>
#include <string.h>

char *my_strsep(char **inputPtr, const char *delimiters)
{
    char *tokenStart; /* Pointer to the start of the token */
    char *scanner;    /* Pointer to scan through the string */
    if (inputPtr == NULL || *inputPtr == NULL)
    {
        return NULL;
    }
    tokenStart = *inputPtr;
    scanner = tokenStart;
    while (*scanner && !strchr(delimiters, *scanner))
    {
        scanner++;
    }
    if (*scanner)
    {
        *scanner = '\0';         /* Null-terminate the current token */
        *inputPtr = scanner + 1; /* Move inputPtr to the next character */
    }
    else
    {
        *inputPtr = NULL;
    }
    /* Handle case where tokenStart equals scanner but starts with a delimiter */
    if (tokenStart == scanner && strchr(delimiters, *scanner))
    {
        return ""; /* Return an empty string for an empty token */
    }
    return tokenStart;
}
