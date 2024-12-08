#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "complex.h"
#include "string_utils.h"
#include "common_types.h"

/* Variables table-like structure containing variable name,and initilized value */
static Variable variables[NUM_OF_VARIABLES] = {
    {'A', {0.0, 0.0}},
    {'B', {0.0, 0.0}},
    {'C', {0.0, 0.0}},
    {'D', {0.0, 0.0}},
    {'E', {0.0, 0.0}},
    {'F', {0.0, 0.0}}};

int get_variable_index(char c)
{
    int i;
    for (i = 0; i < NUM_OF_VARIABLES; i++)
    {
        if (variables[i].key == c)
        {
            return i;
        }
    }
    return -1;
}

Complex *get_variable_ref_by_index(int index)
{
    if (index >= 0 && index < NUM_OF_VARIABLES)
    {
        return &(variables[index].value);
    }
    return NULL;
}

void display_comp_num(const Complex num)
{
    printf("\n%.2f + (%.2f)i", num.real, num.imaginary);
}

/*  Actions */

void read_comp(CommandParams *params)
{
    params->a->real = *(params->val_a);
    params->a->imaginary = *(params->val_b);
}

void print_comp(CommandParams *params)
{
    display_comp_num(*params->a);
}

/* Calculation*/

void add_comp(CommandParams *params)
{
    Complex result = {0};
    result.real = params->a->real + params->b->real;
    result.imaginary = params->a->imaginary + params->b->imaginary;
    display_comp_num(result);
}

void sub_comp(CommandParams *params)
{
    Complex result = {0};
    result.real = params->a->real - params->b->real;
    result.imaginary = params->a->imaginary - params->b->imaginary;
    display_comp_num(result);
}

void mult_comp_real(CommandParams *params)
{
    Complex result = {0};
    result.real = params->a->real * (*(params->val_a));
    result.imaginary = params->a->imaginary * (*(params->val_a));
    display_comp_num(result);
}

void mult_comp_img(CommandParams *params)
{
    Complex result = {0};
    result.real = -params->a->imaginary * (*(params->val_a));
    result.imaginary = params->a->real * (*(params->val_a));
    display_comp_num(result);
}

void mult_comp_comp(CommandParams *params)
{
    Complex result = {0};
    result.real = params->a->real * params->b->real - params->a->imaginary * params->b->imaginary;
    result.imaginary = params->a->real * params->b->imaginary + params->a->imaginary * params->b->real;
    display_comp_num(result);
}

void abs_comp(CommandParams *params)
{
    double result = 0;
    result = sqrt(params->a->real * params->a->real + params->a->imaginary * params->a->imaginary);
    printf("\n%.2f", result);
}

/* Validation*/

CommandParams vld_action(char *params, Requiermets req)
{
    return extract_command_params(params, req);
}
CommandParams vld_white_charecters_only(char *params)
{
    CommandParams cmd_params = {NULL, NULL, NULL, NULL, NULL};
    if (!isSpacesString(params))
    {
        set_error_code(&cmd_params, ERR_EXTRANEOUS_TEXT);
    }
    return cmd_params;
}

CommandParams extract_command_params(char *params_str, Requiermets req)
{
    CommandParams cmdParams = {NULL, NULL, NULL, NULL, NULL};
    char *token = NULL;
    int token_count = 0;
    while ((token = my_strsep(&params_str, ",")) != NULL)
    {
        if (token_count == req.param_count)
        {
            set_error_code(&cmdParams, ERR_EXTRANEOUS_TEXT);
            return cmdParams;
        }
        SKIP_SPACES(token);
        if (isSpacesString(token))
        {
            if (token_count > 0)
            {
                BOOLEAN isConsecCommas = checkConsecutiveCommas(params_str);
                set_error_code(&cmdParams, isConsecCommas ? ERR_MULTIPLE_CONSECUTIVE_COMMAS : ERR_MISSING_PARAMETER);
                return cmdParams;
            }
            else
            {
                set_error_code(&cmdParams, ERR_MISSING_PARAMETER);
                return cmdParams;
            }
        }
        switch (token_count)
        {
        case 0:
            handle_first_param(req, token, &cmdParams);
            if (cmdParams.errorCode != NULL)
            {
                return cmdParams;
            }
            break;
        case 1:
            handle_second_param(req, token, &cmdParams);
            if (cmdParams.errorCode != NULL)
            {
                return cmdParams;
            }
            break;
        case 2:
            handle_third_param(req, token, &cmdParams);
            if (cmdParams.errorCode != NULL)
            {
                return cmdParams;
            }
            break;
        case 3:
            handle_fourth_param(req, token, &cmdParams);
            if (cmdParams.errorCode != NULL)
            {
                return cmdParams;
            }
            break;
        }
        token_count++;
    }
    if (!validate_requirements(&cmdParams, &req))
    {
        set_error_code(&cmdParams, ERR_MISSING_PARAMETER);
    }
    return cmdParams;
}

void handle_first_param(Requiermets req, char *token, CommandParams *cmdParams)
{
    char varName = getOnlyChar(token);
    if (varName != '\0')
    {
        int index = get_variable_index(varName);
        if (index >= 0)
        {
            cmdParams->a = get_variable_ref_by_index(index);
            return;
        }
    }
    set_error_code(cmdParams, ERR_UNDEFINED_COMPLEX_VAR);
}
void handle_second_param(Requiermets req, char *token, CommandParams *cmdParams)
{
    if (req.var_2)
    {
        char varName = getOnlyChar(token);
        if (varName != '\0')
        {
            int index = get_variable_index(varName);
            if (index >= 0)
            {
                cmdParams->b = get_variable_ref_by_index(index);
            }
            else
            {
                set_error_code(cmdParams, ERR_UNDEFINED_COMPLEX_VAR);
            }
        }
        else
        {
            set_error_code(cmdParams, ERR_UNDEFINED_COMPLEX_VAR);
        }
    }
    else if (req.val_1 && isValidNumString(token))
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            cmdParams->val_a = allocate_double_value(value);
            if (cmdParams->val_a == NULL)
            {
                set_error_code(cmdParams, ERR_MALLOC_FAILED);
            }
        }
        else
        {
            set_error_code(cmdParams, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        set_error_code(cmdParams, ERR_INVALID_PARAMETER);
    }
}
void handle_third_param(Requiermets req, char *token, CommandParams *cmdParams)
{
    if (req.val_2 && cmdParams->val_b == NULL && isValidNumString(token))
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            if (cmdParams->val_a == NULL)
            {
                cmdParams->val_a = allocate_double_value(value);
                if (cmdParams->val_a == NULL)
                {
                    set_error_code(cmdParams, ERR_MALLOC_FAILED);
                }
            }
            else
            {
                cmdParams->val_b = allocate_double_value(value);
                if (cmdParams->val_b == NULL)
                {
                    set_error_code(cmdParams, ERR_MALLOC_FAILED);
                }
            }
        }
        else
        {
            set_error_code(cmdParams, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        set_error_code(cmdParams, ERR_INVALID_PARAMETER);
    }
}
void handle_fourth_param(Requiermets req, char *token, CommandParams *cmdParams)
{
    if (req.val_2 && isValidNumString(token))
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            if (cmdParams->val_b == NULL)
            {
                cmdParams->val_b = allocate_double_value(value);
                if (cmdParams->val_b == NULL)
                {
                    set_error_code(cmdParams, ERR_MALLOC_FAILED);
                }
            }
        }
        else
        {
            set_error_code(cmdParams, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        set_error_code(cmdParams, ERR_INVALID_PARAMETER);
    }
}
BOOLEAN validate_requirements(const CommandParams *cmdParams, const Requiermets *req)
{
    if (req->var_1 && cmdParams->a == NULL)
    {
        return FALSE;
    }
    if (req->var_2 && cmdParams->b == NULL)
    {
        return FALSE;
    }
    if (req->val_1 && cmdParams->val_a == NULL)
    {
        return FALSE;
    }
    if (req->val_2 && cmdParams->val_b == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

void set_error_code(CommandParams *cmdParams, ErrorCode error)
{
    cmdParams->errorCode = malloc(sizeof(ErrorCode));
    if (cmdParams->errorCode == NULL)
    {
        *cmdParams->errorCode = ERR_MALLOC_FAILED;
    }
    else
    {
        *cmdParams->errorCode = error;
    }
}

/*helper method*/

double *allocate_double_value(double value)
{
    double *val = malloc(sizeof(double));
    if (val != NULL)
    {
        *val = value;
    }
    return val;
}

/*Development helpers*/
void print_params(CommandParams *params)
{
    if (params == NULL)
    {
        return;
    }
    printf("Command Parameters:\n");
    if (params->a)
    {
        printf("Complex a: %.2f + %.2fi\n",
               params->a->real,
               params->a->imaginary);
    }
    if (params->b)
    {
        printf("Complex b: %.2f + %.2fi\n",
               params->b->real,
               params->b->imaginary);
    }
    if (params->val_a)
    {
        printf("Value a: %.2f\n", *(params->val_a));
    }
    if (params->val_b)
    {
        printf("Value b: %.2f\n", *(params->val_b));
    }
}

void print_Req(Requiermets *req)
{
    if (req == NULL)
    {
        printf("Requiermets structure is NULL.\n");
        return;
    }

    printf("Requiermets Structure:\n");
    printf("  var_1 : %s\n", req->var_1 ? "TRUE" : "FALSE");
    printf("  var_2 : %s\n", req->var_2 ? "TRUE" : "FALSE");
    printf("  val_1 : %s\n", req->val_1 ? "TRUE" : "FALSE");
    printf("  val_2 : %s\n", req->val_2 ? "TRUE" : "FALSE");
}
