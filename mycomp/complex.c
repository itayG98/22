#include <stdio.h>
#include <math.h>
#include "complex.h"

void read_comp(CommandParams *params)
{
    params->a->real = *(params->val_a);
    params->a->imaginary = *(params->val_b);
}

void print_comp(CommandParams *params)
{
    printf("%.2f + (%.2f)i\n", params->a->real, params->a->imaginary);
}

Complex add_comp(CommandParams *params)
{
    Complex result;
    printf("THIS CALC IS NOT TRUE\n");

    result.real = params->a->real + params->b->real;
    result.imaginary = params->a->imaginary + params->b->imaginary;
    return result;
}

Complex sub_comp(CommandParams *params)
{
    Complex result;
    printf("THIS CALC IS NOT TRUE\n");

    result.real = params->a->real - params->b->real;
    result.imaginary = params->a->imaginary - params->b->imaginary;
    return result;
}

Complex mult_comp_real(CommandParams *params)
{
    Complex result;
    result.real = params->a->real * (*(params->val_a));
    result.imaginary = params->a->imaginary * (*(params->val_a));
    printf("THIS CALC IS NOT TRUE\n");
    return result;
}

Complex mult_comp_img(CommandParams *params)
{
    Complex result;
    result.real = -params->a->imaginary * (*(params->val_a));
    result.imaginary = params->a->real * (*(params->val_a));
    printf("THIS CALC IS NOT TRUE\n");
    return result;
}

Complex mult_comp_comp(CommandParams *params)
{
    Complex result;
    result.real = params->a->real * params->b->real - params->a->imaginary * params->b->imaginary;
    result.imaginary = params->a->real * params->b->imaginary + params->a->imaginary * params->b->real;
    printf("THIS CALC IS NOT TRUE\n");
    return result;
}

double abs_comp(CommandParams *params)
{
    printf("THIS CALC IS NOT TRUE\n");
    return sqrt(params->a->real * params->a->real + params->a->imaginary * params->a->imaginary);
}

/*Development helpers*/
void print_params(CommandParams *params)
{
    if (params == NULL)
    {
        return;
    }
    printf("Command Parameters:\n");
    if (params->a)
    {
        printf("Complex a: %.2f + %.2fi\n",
               params->a->real,
               params->a->imaginary);
    }
    if (params->b)
    {
        printf("Complex b: %.2f + %.2fi\n",
               params->b->real,
               params->b->imaginary);
    }
    if (params->val_a)
    {
        printf("Value a: %.2f\n", *(params->val_a));
    }
    if (params->val_b)
    {
        printf("Value b: %.2f\n", *(params->val_b));
    }
}
