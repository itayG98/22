#ifndef COMPLEX_H
#define COMPLEX_H

#include "common_types.h"

#define NUM_OF_ERRORS 8
#define NUM_OF_VARIABLES 6

/*A code to represent and error from the validation procces*/
typedef enum
{
    ERR_UNDEFINED_COMPLEX_VAR,
    ERR_UNDEFINED_COMMAND_NAME,
    ERR_INVALID_PARAMETER,
    ERR_MISSING_PARAMETER,
    ERR_EXTRANEOUS_TEXT,
    ERR_MULTIPLE_CONSECUTIVE_COMMAS,
    ERR_MISSING_COMMA,
    ERR_ILLEGAL_COMMA,
    ERR_MALLOC_FAILED
} ErrorCode;

/*
struct representing a line in the error table with code ,
and messege
 */
typedef struct
{
    ErrorCode code;
    char *message;
} ErrorInfo;

/*
Struct repreents a complex variable
*/
typedef struct
{
    double real;
    double imaginary;
} Complex;

/*
struct representing a line in the variables table with variable name
and messege
 */
typedef struct
{
    char key;
    Complex value;
} Variable;

/*
Struct represent the validation result with all od the parameters
that extracted , if error accured it has a pointer to dynmicly
alocated integer mathic an error code
*/
typedef struct
{
    Complex *a;
    Complex *b;
    double *val_a;
    double *val_b;
    ErrorCode *errorCode;
} CommandParams;

/*
Struct representing requirments for each command
*/
typedef struct
{
    BOOLEAN var_1;
    BOOLEAN var_2;
    BOOLEAN val_1;
    BOOLEAN val_2;
    unsigned param_count;
} Requiermets;

/*Variables getters*/

/*
This method iterates through all the variables to find the index of
 the item if it exists otherwise it returns -1
 */
int get_variable_index(char c);

/*
This method return a reference to the variable by it's index
 if exists otherwise NULL
*/
Complex *get_variable_ref_by_index(int index);

/*This method print a complex variable*/
void display_comp_num(const Complex num);

/*  Actions */

/*This method insert a validated input and update the variable */
void read_comp(CommandParams *params);
/*This method invoke the printig method with validated variable name*/

void print_comp(CommandParams *params);
/*This method print a addition of two complex variables*/
void add_comp(CommandParams *params);
/*This method print a subtruction of two complex variables*/
void sub_comp(CommandParams *params);
/*This method prints a multiplication of complex variable and a real number*/
void mult_comp_real(CommandParams *params);
/*This method prints the result of multiplying a complex variable by an imaginary number*/
void mult_comp_img(CommandParams *params);
/*This method prints the result of multiplying tow complex variables*/
void mult_comp_comp(CommandParams *params);
/*This method prints the absolute value of a complex variable*/
void abs_comp(CommandParams *params);

/*Validation*/

/*
Validates the string parameters according to the requirements
for an action and returns the corresponding result
*/
CommandParams vld_action(char *params, Requiermets req);
/*Validate a string parameters to be only white charecters*/
CommandParams vld_white_charecters_only(char *params);

/*Data extraction*/

/*This method iterates and check each parameter if valid and set the corresponding result*/
CommandParams extract_command_params(char *params_str, Requiermets req);
/*Handle the first parameters*/
void handle_first_param(Requiermets req, char *token, CommandParams *cmdParams);
/*Handle the second parameters*/
void handle_second_param(Requiermets req, char *token, CommandParams *cmdParams);
/*Handle the third parameters*/
void handle_third_param(Requiermets req, char *token, CommandParams *cmdParams);
/*Handle the fourth parameters*/
void handle_fourth_param(Requiermets req, char *token, CommandParams *cmdParams);
/*This method allocte a double memory and return the pointer to it*/
double *allocate_double_value(double value);
/*This method validate the all of the requirments fullfiled*/
BOOLEAN validate_requirements(const CommandParams *cmdParams, const Requiermets *req);
/*Set the CommandParams error */
void set_error_code(CommandParams *cmdParams, ErrorCode error);

/*Development helpers*/

/*This method prints Requiermets struct */
void print_Req(Requiermets *req);
/*This method prints CommandParams struct */
void print_params(CommandParams *params);
#endif
