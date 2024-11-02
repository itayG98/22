#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"
#include "validation.h"

#define MAX_LINE_LENGTH 256
#define NUM_OF_CMNDS 9
#define NUM_OF_VARIABLES 6

typedef enum
{
    ERROR = -1,
    DEFAULT = 0,
    EOF_REACHED = 1,
    SUCCES = 2
} STATE;

typedef struct
{
    char *line;
    char *command;
    char *params;
    STATE flag;
} commandData;

typedef union
{
    void (*action_params)(CommandParams params);
    void (*action_exit_reason)(STATE reason, int count, ...);
} Action;

typedef struct
{
    char *command;
    Action action;
    ValidateCommand validate;
} CommandTable;

typedef struct
{
    char key;
    Complex value;
} VariableTable;

void get_line(commandData *command_data);
void stop(commandData *command_data);
void free_commnad_data(commandData *command_data);
void extract_data_from_line(commandData *command_data);
void execute_command(commandData *command_data);
CommandParams extract_command_params(const commandData *cmdData);
int is_valid_variable(char c);
void calculate_max_command_length(void);
void remove_spaces_and_tabs(char *str);
void display_rules(void);

#endif
