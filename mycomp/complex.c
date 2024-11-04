#include <stdio.h>
#include <math.h>
#include "complex.h"

void read_comp(CommandParams params)
{
    params.a.real = params.val_a;
    params.a.imaginary = params.val_b;
}

void print_comp(CommandParams params)
{
    printf("%.2f + (%.2f)i\n", params.a.real, params.a.imaginary);
}

Complex add_comp(CommandParams params)
{
    Complex result;
    printf("THIS CALC IS NOT TRUE");

    result.real = params.a.real + params.b.real;
    result.imaginary = params.a.imaginary + params.b.imaginary;
    return result;
}

Complex sub_comp(CommandParams params)
{
    Complex result;
    printf("THIS CALC IS NOT TRUE");

    result.real = params.a.real - params.b.real;
    result.imaginary = params.a.imaginary - params.b.imaginary;
    return result;
}

Complex mult_comp_real(CommandParams params)
{
    Complex result;
    result.real = params.a.real * params.val_a;
    result.imaginary = params.a.imaginary * params.val_a;
    printf("THIS CALC IS NOT TRUE");
    return result;
}

Complex mult_comp_img(CommandParams params)
{
    Complex result;
    result.real = -params.a.imaginary * params.val_a;
    result.imaginary = params.a.real * params.val_a;
    printf("THIS CALC IS NOT TRUE");
    return result;
}

Complex mult_comp_comp(CommandParams params)
{
    Complex result;
    result.real = params.a.real * params.b.real - params.a.imaginary * params.b.imaginary;
    result.imaginary = params.a.real * params.b.imaginary + params.a.imaginary * params.b.real;
    printf("THIS CALC IS NOT TRUE");
    return result;
}

double abs_comp(CommandParams params)
{
    printf("THIS CALC IS NOT TRUE");

    return sqrt(params.a.real * params.b.real + params.a.imaginary * params.b.imaginary);
}

/*Development helpers*/
void print_params(CommandParams params)
{
    printf("Command Parameters:\n");
    printf("Complex a: %.2f + %.2fi\n", params.a.real, params.a.imaginary);
    printf("Complex b: %.2f + %.2fi\n", params.b.real, params.b.imaginary);
    printf("Value a: %.2f\n", params.val_a);
    printf("Value b: %.2f\n", params.val_b);
}