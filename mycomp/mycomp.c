#include <stdio.h>
#include <stdlib.h>
#include "mycomp.h"
#include "complex.h"
#include "validation.h"

static CommandTable commandTable[NUM_OF_CMNDS] = {
    {"read_comp", read_comp, vld_read_comp},
    {"print_comp", print_comp, vld_print_comp},
    {"add_comp", add_comp, vld_add_comp},
    {"sub_comp", sub_comp, vld_sub_comp},
    {"mult_comp_real", mult_comp_real, vld_mult_comp_real},
    {"mult_comp_img", mult_comp_img, vld_mult_comp_img},
    {"mult_comp_comp", mult_comp_comp, vld_mult_comp_comp},
    {"abs_comp", abs_comp, vld_abs_comp},
    {"stop", stop, NULL}};

static VariableTable variables[NUM_OF_VARIABLES] = {
    {'A', {0, 0}},
    {'B', {0, 0}},
    {'C', {0, 0}},
    {'D', {0, 0}},
    {'E', {0, 0}},
    {'F', {0, 0}}};

int main()
{
    int flag = 1, c = 0, i = 0;
    diplayRules();
    while (1)
    {
        scanf("%d", &i);
    }

    return 0;
}

void stop(void)
{
    exit(0);
}

void diplayRules(void)
{
    /* Introduction and instructions for user */
    printf("Welcome to COMPLEX OPERATIONS.\n");
    printf("Let's explore complex number operations together.\n");
    printf("First consider this rules and examples :\n");
    printf("1. Valid complex variable names: A, B, C, D, E, F.\n");
    printf("2. Valid operations are as follows:\n");
    printf("   - read_comp: To input a complex number.\n");
    printf("   - print_comp: To display a complex number.\n");
    printf("   - add_comp: To add two complex numbers.\n");
    printf("   - sub_comp: To subtract one complex number from another.\n");
    printf("   - mult_comp_real: To multiply a complex number by a real number.\n");
    printf("   - mult_comp_img: To multiply a complex number by an imaginary number.\n");
    printf("   - mult_comp_comp: To multiply two complex numbers.\n");
    printf("   - abs_comp: To find the absolute value of a complex number.\n");
    printf("3. Command formats:\n");
    printf("   - For read_comp: read_comp <variable>, <real part>, <imaginary part> <ENTER>\n");
    printf("     Example: read_comp A, 3.5, -2.1\n");
    printf("   - For print_comp: print_comp <variable><ENTER>\n");
    printf("     Example: print_comp A\n");
    printf("   - For operations with two variables (add/sub/mult_comp_comp):\n");
    printf("     <operation> <variable1>, <variable2><ENTER>\n");
    printf("     Example: add_comp A, B\n");
    printf("   - For operations with a variable and a real number (mult_comp_real):\n");
    printf("     mult_comp_real <variable>, <real value><ENTER>\n");
    printf("     Example: mult_comp_real B, 4.5\n");
    printf("   - For operations with a variable and an imaginary value (mult_comp_img):\n");
    printf("     mult_comp_img <variable>, <imaginary value><ENTER>\n");
    printf("     Example: mult_comp_img C, 2.3\n");
    printf("4. To quit: stop<ENTER>\n");
}