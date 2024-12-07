#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"

/*Max line length ... longer lines will miss interperted by the porgram*/
#define MAX_LINE_LENGTH 512
/*Commands options*/
#define NUM_OF_CMNDS 9
/*Errors options for bad input*/
#define NUM_OF_ERRORS 8

/*Code to represent the state of the program*/
typedef enum
{
    MALLOC_ERROR = -3,
    EOF_REACHED = -2,
    ERROR = -1,
    DEFAULT = 0,
    SUCCES = 1
} STATE;

/*Struct to represent the state of the program*/
typedef struct
{
    char *line;
    char *command;
    char *params;
    STATE flag;
} commandData;

/*
Union represeting pointer to a validation method
*/
typedef union
{
    CommandParams (*action_vld)(char *params, Requiermets req);
    CommandParams (*stop_vld)(char *params);
} ValidateFunc;

/*
Union representing pointer the method to invoke according to the cmd code
*/
typedef union
{
    void (*cmd_action)(CommandParams *params);
    void (*exit_action)(commandData *command_data);
} Action;

/*
Struct representing a line in the commands table with code ,
validation method and action method
 */
typedef struct
{
    char *command;
    Action action;
    ValidateFunc validate;
    Requiermets req;
} Command;

/*Init*/

void initCommandTableAction(void);

/*Input */

void get_line(commandData *command_data);
void extract_data_from_line(commandData *command_data);

/*Logic*/

void calculate_max_command_length(void);
void execute_command(commandData *command_data);
CommandParams validate(int index, char *params);
void stop(commandData *command_data);
void display_rules(void);
void print_error_message(int code);
BOOLEAN isTabOrSpace(char c);
/* Allocation*/

void free_commnad_data(commandData *command_data);
void free_command_params(CommandParams *cmdParams);

/*Development helpers*/

void print_commandData(commandData *cmdData);
#endif
