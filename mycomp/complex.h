#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct
{
    double real;
    double imaginary;
} Complex;

typedef struct
{
    Complex a;
    Complex b;
    double val_a;
    double val_b;
} CommandParams;

void read_comp(CommandParams params);
void print_comp(CommandParams params);
Complex add_comp(CommandParams params);
Complex sub_comp(CommandParams params);
Complex mult_comp_real(CommandParams params);
Complex mult_comp_img(CommandParams params);
Complex mult_comp_comp(CommandParams params);
double abs_comp(CommandParams params);

void print_params(CommandParams params);

#endif
