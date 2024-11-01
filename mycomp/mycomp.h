#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"
#include "validation.h"

#define NUM_OF_CMNDS 9
#define NUM_OF_VARIABLES 6

void displayRules(void);
void stop(void);

typedef struct
{
    char *command;
    ValidateCommand validate;
    void (*action)();
} CommandTable;

typedef struct
{
    char key;
    Complex value;
} VariableTable;

#endif
