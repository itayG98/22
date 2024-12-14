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
    ValidationResult (*action_vld)(char *params, Requiermets req);
    ValidationResult (*stop_vld)(char *params);
} ValidateFunc;

/*
Union representing pointer the method to invoke according to the cmd code
*/
typedef union
{
    void (*cmd_action)(Parameters *params);
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

/*
Initialize  the action fields in each line of the table since
C90 forbids subobject initialization
*/
void initCommandTableAction(void);

/*Input */

/*
This method skips white charecters and than allocate and assign a new
 line using fgets to the commandData object
*/
void get_line(commandData *command_data);

/*
This method will extract the first lower or underscore charecters and assign to the command parameter
 and the rest will be assigned as the params
white charecters at the start of the line or after the line will skipped
*/
void extract_data_from_line(commandData *command_data);

/*Logic*/

/*
This method determines the longest command length and assigns it to MAX_CMD_LENGTH during runtime
*/
void calculate_max_command_length(void);
/*
This method takes the data that extracted priviously validate it and execute
 it or print an error message
*/
void execute_command(commandData *command_data);
/*
This method calls the correct validation method and return
the appropriate parameters
*/
ValidationResult validate(int index, char *params);
/*
This method stop the porgram and prints message according to reason
*/
void stop(commandData *command_data);

/*
This method prints a menu for the user explains how to use
the calculator program
*/
void display_rules(void);
/*
This method prints an error messeege according to it's code
*/
void print_error_message(int code);

/* Allocation*/

/*
This method free allocated data for the commandData fields
*/
void free_commnad_data(commandData *command_data);
/*
This method free allocated data for the ValidationResult number's pointers fields
*/

void free_validation_result(ValidationResult *vldRes);

/*Development helpers*/

/*This method prints the commandData struct */
void print_commandData(commandData *cmdData);
#endif
