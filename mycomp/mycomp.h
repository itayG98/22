#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"
#include "validation.h"

#define MAX_LINE_LENGTH 256
#define NUM_OF_CMNDS 9
#define NUM_OF_VARIABLES 6

char *get_line(void);
void calculate_max_command_length(void);
char *extract_cmnd(const char *line, int *params_start_idx);
void remove_spaces_and_tabs(char *str);
void execute_command(char *cmnd, char *params, int params_start_idx);
void display_rules(void);
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
