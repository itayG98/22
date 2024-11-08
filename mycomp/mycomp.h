#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"
#include "validation.h"

#define MAX_LINE_LENGTH 512
#define NUM_OF_CMNDS 9
#define NUM_OF_VARIABLES 6
#define NUM_OF_ERRORS 8

typedef enum
{
    MALLOC_ERROR = -3,
    EOF_REACHED = -2,
    ERROR = -1,
    DEFAULT = 0,
    SUCCES = 1
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
} Command;

typedef struct
{
    char key;
    Complex value;
} Variable;

/*Input */
void get_line(commandData *command_data);
void extract_data_from_line(commandData *command_data);
CommandParams extract_command_params(commandData *cmdData);
void remove_spaces_and_tabs(char *str);

/*Logic*/
int get_variable_index(char c);
Complex *get_variable_ref_by_index(int index);
void calculate_max_command_length(void);
void execute_command(commandData *command_data, CommandParams params);
void stop(commandData *command_data, CommandParams *cmdParams);
void display_rules(void);

/* Allocation*/
void free_command_data(commandData *command_data);
void free_command_params(CommandParams *cmdParams);
void free_allocation(commandData *command_data, CommandParams *params);
#endif
