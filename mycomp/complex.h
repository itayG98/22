#ifndef COMPLEX_H
#define COMPLEX_H

#include "common_types.h"

#define NUM_OF_ERRORS 8
#define NUM_OF_VARIABLES 6

/*A code to represent and error from the validation proccess*/
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
and message
 */
typedef struct
{
    ErrorCode code;
    char *message;
} ErrorInfo;

/*
Struct represents a complex variable
*/
typedef struct
{
    double real;
    double imaginary;
} Complex;

/*
struct representing a line in the variables table with variable name
and message
 */
typedef struct
{
    char key;
    Complex value;
} Variable;

/*
Struct represent the parameters to be given to the command
*/
typedef struct
{
    Complex *a;
    Complex *b;
    double *val_a;
    double *val_b;
} Parameters;

/*
Struct represent the validation result with all of the parameters
that extracted , if error accrued it has a pointer to dynamicly
allocated integer representing an error code
*/
typedef struct
{
    Parameters params;
    ErrorCode *errorCode;
} ValidationResult;

/*
Struct representing requirements for each command
*/
typedef struct
{
    BOOLEAN var_1;
    BOOLEAN var_2;
    BOOLEAN val_1;
    BOOLEAN val_2;
    unsigned param_count;
} Requirements;

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
void read_comp(Parameters *params);
/*This method invoke the printing method with validated variable name*/

void print_comp(Parameters *params);
/*This method print a addition of two complex variables*/
void add_comp(Parameters *params);
/*This method print a subtraction of two complex variables*/
void sub_comp(Parameters *params);
/*This method prints a multiplication of complex variable and a real number*/
void mult_comp_real(Parameters *params);
/*This method prints the result of multiplying a complex variable by an imaginary number*/
void mult_comp_img(Parameters *params);
/*This method prints the result of multiplying tow complex variables*/
void mult_comp_comp(Parameters *params);
/*This method prints the absolute value of a complex variable*/
void abs_comp(Parameters *params);

/*Validation*/

/*
Validates the string parameters according to the requirements
for an action and returns the corresponding result
*/
ValidationResult vld_action(char *params, Requirements req);
/*Validate a string parameters to be only white characters*/
ValidationResult vld_white_characters_only(char *params);
/*This method iterates and check each parameter if valid and set the corresponding result*/
ValidationResult extract_command_params(char *params_str, Requirements req);

/*Data extraction*/

/*
Extract and validate a reference to complex variable according to the token
 or set an appropriate error msg code
 */
void setVarByToken(char *token, ValidationResult *vldRes, BOOLEAN isFirst);
/*
Extract and validate a double value by the token and allocate memory for it's new variable variable
 or set an appropriate error msg code
 */
void setNumberByToken(char *token, ValidationResult *vldRes, BOOLEAN isFirst);

double *allocate_double_value(double value);
/*This method validate the all of the requirements fullfield*/
BOOLEAN validate_requirements(const Parameters params, const Requirements *req);
/*Set the ValidationResult error */
void set_error_code(ValidationResult *vldRes, ErrorCode error);

/*Development helpers*/

/*This method prints Requirements struct */
void print_Req(Requirements *req);
/*This method prints ValidationResult struct */
void print_params(Parameters params);
#endif
