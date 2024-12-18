#ifndef MYCOMP_H
#define MYCOMP_H

#include "complex.h"

/*Max line length ... longer lines will miss interperted by the program*/
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
    DEFAULT = 0,
    SUCCESS = 1
} STATE;

/*Struct to represent the state of the program*/
typedef struct
{
    char *line;
    char *command;
    char *params;
    STATE flag;
} CommandData;

/*
Union representing pointer to a validation method
*/
typedef union
{
    ValidationResult (*actionVld)(char *params, Requirements req);
    ValidationResult (*stopVld)(char *params);
} ValidateFunc;

/*
Union representing pointer the method to invoke according to the cmd code
*/
typedef union
{
    void (*cmdAction)(Parameters *params);
    void (*exitAction)(CommandData *commandData);
} Action;

/*
Struct representing a line in the commands table with code ,
validation method action method nad it's requirements
 */
typedef struct
{
    char *command;
    Action action;
    ValidateFunc validate;
    Requirements req;
} Command;

/*Init*/

/*
Initialize  the action fields in each line of the table since
C90 forbids subobject initialization
*/
void initCommandTableAction(void);

/*Input */

/*
This method skips white characters and than allocate and assign a new
 line using fgets to the commandData object
*/
void getLine(CommandData *command_data);

/*
This method will extract the first lower or underscore characters and assign to the command parameter
 and the rest will be assigned as the params
white characters at the start of the line or after the line will skipped
*/
void extractDataFromLine(CommandData *command_data);

/*Logic*/

/*
This method determines the longest command length and assigns it to MAX_CMD_LENGTH during runtime
*/
void calculateMaxCommandLength(void);
/*
This method takes the data that extracted previously validate it and execute
 it or print an error message
*/
void executeCommand(CommandData *command_data);
/*
This method calls the correct validation method and return
the appropriate parameters
*/
ValidationResult validate(int index, char *params);
/*
This method stop the program and prints message according to reason
*/
void stop(CommandData *command_data);

/*
This method prints a menu for the user explains how to use
the calculator program
*/
void displayRules(void);
/*
This method prints an error messene according to it's code
*/
void printErrorMessage(int code);

/* Allocation*/

/*
This method free allocated data for the commandData fields
*/
void freeCommandData(CommandData *command_data);
/*
This method free allocated data for the ValidationResult number's pointers fields
*/

void freeValidationResult(ValidationResult *vldRes);
#endif