#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"

#define MAX_LINE_LENGTH 512
#define NUM_OF_CMNDS 9
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

typedef CommandParams (*ValidateFunc)(char *params);

typedef union
{
    void (*cmd_action)(CommandParams *params);
    void (*exit_action)(char *params);
} Action;

void *genericPtr;

typedef struct
{
    char *command;
    Action action;
    ValidateFunc validate;
} Command;

/*Input */
void get_line(commandData *command_data);
void extract_data_from_line(commandData *command_data);

/*Logic*/
void calculate_max_command_length(void);
void execute_command(commandData *command_data);
void stop(commandData *command_data);
void display_rules(void);
void print_error_message(int *code);

/* Allocation*/
void free_commnad_data(commandData *command_data);
void free_command_params(CommandParams *cmdParams);
void free_allocation(commandData *command_data);
#endif
