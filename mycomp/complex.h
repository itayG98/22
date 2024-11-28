#ifndef COMPLEX_H
#define COMPLEX_H

#include "complex.h"

#define NUM_OF_ERRORS 8
#define NUM_OF_VARIABLES 6

typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

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

typedef struct
{
    ErrorCode code;
    char *message;
} ErrorInfo;

typedef struct
{
    double real;
    double imaginary;
} Complex;

typedef struct
{
    char key;
    Complex value;
} Variable;

typedef struct
{
    Complex *a;
    Complex *b;
    double *val_a;
    double *val_b;
    ErrorCode *errorCode;
} CommandParams;

typedef struct
{
    BOOLEAN var_1;
    BOOLEAN var_2;
    BOOLEAN val_1;
    BOOLEAN val_2;
} Requiermets;

/*Variables getters*/
int get_variable_index(char c);
Complex *get_variable_ref_by_index(int index);

/*Calculations*/
void read_comp(CommandParams *params);
void print_comp(CommandParams *params);
void add_comp(CommandParams *params);
void sub_comp(CommandParams *params);
void mult_comp_real(CommandParams *params);
void mult_comp_img(CommandParams *params);
void mult_comp_comp(CommandParams *params);
void abs_comp(CommandParams *params);

/*Validation*/
CommandParams vld_read_comp(char *params);
CommandParams vld_print_comp(char *params);
CommandParams vld_add_comp(char *params);
CommandParams vld_sub_comp(char *params);
CommandParams vld_mult_comp_real(char *params);
CommandParams vld_mult_comp_img(char *params);
CommandParams vld_mult_comp_comp(char *params);
CommandParams vld_abs_comp(char *params);
CommandParams vld_stop(char *params);

void display_comp_num(Complex num);

/*Data extraction*/
CommandParams extract_command_params(char *params_str, Requiermets req);
void handle_first_param(Requiermets req, char *token, CommandParams *cmdParams);
void handle_second_param(Requiermets req, char *token, CommandParams *cmdParams);
void handle_third_param(Requiermets req, char *token, CommandParams *cmdParams);
void handle_fourth_param(Requiermets req, char *token, CommandParams *cmdParams);
char getOnlyChar(const char *str);
BOOLEAN validateToken(const char *str);
double *allocate_double_value(double value);
BOOLEAN validate_requirements(const CommandParams *cmdParams, const Requiermets *req);
void set_error_code(CommandParams *cmdParams, ErrorCode error);

/*Development helpers*/
void print_Req(Requiermets *req);
void print_params(CommandParams *params);
#endif
