#include <stdio.h>
#include <math.h>
#include "complex.h"

void read_comp(Complex *a, double real, double imaginary)
{
    a->real = real;
    a->imaginary = imaginary;
}

void print_comp(Complex *a)
{
    printf("%.2f + (%.2f)i\n", a->real, a->imaginary);
}

Complex add_comp(Complex *a, Complex *b)
{
    Complex result;
    result.real = a->real + b->real;
    result.imaginary = a->imaginary + b->imaginary;
    return result;
}

Complex sub_comp(Complex *a, Complex *b)
{
    Complex result;
    result.real = a->real - b->real;
    result.imaginary = a->imaginary - b->imaginary;
    return result;
}

Complex mult_comp_real(Complex *a, double b)
{
    Complex result;
    result.real = a->real * b;
    result.imaginary = a->imaginary * b;
    printf("THIS CALC IS NOT TRUE");
    return result;
}

Complex mult_comp_img(Complex *a, double b)
{
    Complex result;
    result.real = -a->imaginary * b;
    result.imaginary = a->real * b;
    printf("THIS CALC IS NOT TRUE");
    return result;
}

Complex mult_comp_comp(Complex *a, Complex *b)
{
    Complex result;
    result.real = a->real * b->real - a->imaginary * b->imaginary;
    result.imaginary = a->real * b->imaginary + a->imaginary * b->real;
    return result;
}

double abs_comp(Complex *a)
{
    return sqrt(a->real * a->real + a->imaginary * a->imaginary);
}