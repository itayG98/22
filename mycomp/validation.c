#include <string.h>
#include <stdlib.h>
#include "validation.h"

BOOLEAN vld_read_comp(char *line)
{
    char var[2];
    double real, imaginary;
    int numParams = sscanf(line, "%1s, %lf, %lf", var, &real, &imaginary);
    if (numParams == 3)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN vld_print_comp(char *line)
{
    char var[2];
    int numParams = sscanf(line, "%1s", var);
    if (numParams == 1)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN vld_add_comp(char *line)
{
    char var1[2], var2[2];
    int numParams = sscanf(line, "%1s, %1s", var1, var2);
    if (numParams == 2)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN vld_sub_comp(char *line)
{
    char var1[2], var2[2];
    int numParams = sscanf(line, "%1s, %1s", var1, var2);
    if (numParams == 2)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN vld_mult_comp_real(char *line)
{
    char var[2];
    double real;
    int numParams = sscanf(line, "%1s, %lf", var, &real);
    if (numParams == 2)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN vld_mult_comp_img(char *line)
{
    char var[2];
    double img;
    int numParams = sscanf(line, "%1s, %lf", var, &img);
    if (numParams == 2)
    {
        return TRUE;
    }
    return FALSE;
}

BOOLEAN vld_mult_comp_comp(char *line)
{
    char var1[2], var2[2];

    int numParams = sscanf(line, "%1s, %1s", var1, var2);

    if (numParams == 2)
    {
        return TRUE;
    }

    return FALSE;
}

BOOLEAN vld_abs_comp(char *line)
{
    char var[2];

    int numParams = sscanf(line, "%1s", var);

    if (numParams == 1)
    {
        return TRUE;
    }

    return FALSE;
}
