#include <stdio.h>
#include "complex.h"

Operation get_operation_type(const char *operation_str)
{
    if (strcmp(operation_str, "print_comp") == 0)
        return PRINT_COMP;
    if (strcmp(operation_str, "add_comp") == 0)
        return ADD_COMP;
    if (strcmp(operation_str, "sub_comp") == 0)
        return SUB_COMP;
    if (strcmp(operation_str, "mult_comp_real") == 0)
        return MULT_COMP_REAL;
    if (strcmp(operation_str, "mult_comp_img") == 0)
        return MULT_COMP_IMG;
    if (strcmp(operation_str, "mult_comp_comp") == 0)
        return MULT_COMP_COMP;
    if (strcmp(operation_str, "abs_comp") == 0)
        return ABS_COMP;
    if (strcmp(operation_str, "stop") == 0)
        return STOP;
    return INVALID_OPERATION;
}