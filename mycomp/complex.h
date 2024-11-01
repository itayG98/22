#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct
{
    double real;
    double imaginary;
} Complex;

void read_comp(Complex *a, double real, double imaginary);
void print_comp(Complex *a);
Complex add_comp(Complex *a, Complex *b);
Complex sub_comp(Complex *a, Complex *b);
Complex mult_comp_real(Complex *a, double b);
Complex mult_comp_img(Complex *a, double b);
Complex mult_comp_comp(Complex *a, Complex *b);
double abs_comp(Complex *a);

#endif
