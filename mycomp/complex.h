#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct
{
    double real;
    double imaginary;
} Complex;

typedef enum
{
    PRINT_COMP,
    ADD_COMP,
    ADD_COMP,
    SUB_COMP,
    MULT_COMP_REAL,
    MULT_COMP_IMG,
    MULT_COMP_COMP,
    ABS_COMP,
    STOP,
    INVALID_OPERATION
} Operation;

Operation get_operation_type(const char *operation_str);

#endif
