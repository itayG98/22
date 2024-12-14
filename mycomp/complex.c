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

void read_comp(Parameters *params)
{
    params->a->real = *(params->val_a);
    params->a->imaginary = *(params->val_b);
}

void print_comp(Parameters *params)
{
    display_comp_num(*params->a);
}

/* Calculation*/

void add_comp(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real + params->b->real;
    result.imaginary = params->a->imaginary + params->b->imaginary;
    display_comp_num(result);
}

void sub_comp(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real - params->b->real;
    result.imaginary = params->a->imaginary - params->b->imaginary;
    display_comp_num(result);
}

void mult_comp_real(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real * (*(params->val_a));
    result.imaginary = params->a->imaginary * (*(params->val_a));
    display_comp_num(result);
}

void mult_comp_img(Parameters *params)
{
    Complex result = {0};
    result.real = -params->a->imaginary * (*(params->val_a));
    result.imaginary = params->a->real * (*(params->val_a));
    display_comp_num(result);
}

void mult_comp_comp(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real * params->b->real - params->a->imaginary * params->b->imaginary;
    result.imaginary = params->a->real * params->b->imaginary + params->a->imaginary * params->b->real;
    display_comp_num(result);
}

void abs_comp(Parameters *params)
{
    double result = 0;
    result = sqrt(params->a->real * params->a->real + params->a->imaginary * params->a->imaginary);
    printf("\n%.2f", result);
}

/* Validation*/

ValidationResult vld_action(char *params, Requiermets req)
{
    return extract_command_params(params, req);
}
ValidationResult vld_white_charecters_only(char *params)
{
    ValidationResult cmd_params = {{0}, NULL};
    if (!isSpacesString(params))
    {
        set_error_code(&cmd_params, ERR_EXTRANEOUS_TEXT);
    }
    return cmd_params;
}

ValidationResult extract_command_params(char *params_str, Requiermets req)
{
    ValidationResult vldRes = {{0}, NULL};
    char *token = NULL;
    int token_count = 0;
    while ((token = my_strsep(&params_str, ",")) != NULL)
    {
        if (token_count == req.param_count)
        {
            set_error_code(&vldRes, ERR_EXTRANEOUS_TEXT);
            return vldRes;
        }
        SKIP_SPACES(token);
        if (isSpacesString(token))
        {
            if (token_count > 0)
            {
                BOOLEAN isConsecCommas = checkConsecutiveCommas(params_str);
                set_error_code(&vldRes, isConsecCommas ? ERR_MULTIPLE_CONSECUTIVE_COMMAS : ERR_MISSING_PARAMETER);
                return vldRes;
            }
            else
            {
                set_error_code(&vldRes, ERR_MISSING_PARAMETER);
                return vldRes;
            }
        }
        switch (token_count)
        {
        case 0:
            handle_first_param(req, token, &vldRes);
            if (vldRes.errorCode != NULL)
            {
                return vldRes;
            }
            break;
        case 1:
            handle_second_param(req, token, &vldRes);
            if (vldRes.errorCode != NULL)
            {
                return vldRes;
            }
            break;
        case 2:
            handle_third_param(req, token, &vldRes);
            if (vldRes.errorCode != NULL)
            {
                return vldRes;
            }
            break;
        case 3:
            handle_fourth_param(req, token, &vldRes);
            if (vldRes.errorCode != NULL)
            {
                return vldRes;
            }
            break;
        }
        token_count++;
    }
    if (!validate_requirements(vldRes.params, &req))
    {
        set_error_code(&vldRes, ERR_MISSING_PARAMETER);
    }
    return vldRes;
}

void handle_first_param(Requiermets req, char *token, ValidationResult *vldRes)
{
    char varName = getOnlyChar(token);
    if (varName != '\0')
    {
        int index = get_variable_index(varName);
        if (index >= 0)
        {
            vldRes->params.a = get_variable_ref_by_index(index);
            return;
        }
    }
    set_error_code(vldRes, ERR_UNDEFINED_COMPLEX_VAR);
}

void handle_second_param(Requiermets req, char *token, ValidationResult *vldRes)
{
    if (req.var_2)
    {
        char varName = getOnlyChar(token);
        if (varName != '\0')
        {
            int index = get_variable_index(varName);
            if (index >= 0)
            {
                vldRes->params.b = get_variable_ref_by_index(index);
                return;
            }
            else
            {
                set_error_code(vldRes, ERR_UNDEFINED_COMPLEX_VAR);
            }
        }
        else
        {
            set_error_code(vldRes, ERR_UNDEFINED_COMPLEX_VAR);
        }
    }
    else if (req.val_1 && isValidNumString(token))
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            vldRes->params.val_a = allocate_double_value(value);
            if (vldRes->params.val_a == NULL)
            {
                set_error_code(vldRes, ERR_MALLOC_FAILED);
            }
        }
        else
        {
            set_error_code(vldRes, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        set_error_code(vldRes, ERR_INVALID_PARAMETER);
    }
}
void handle_third_param(Requiermets req, char *token, ValidationResult *vldRes)
{
    if (req.val_2 && vldRes->params.val_b == NULL && isValidNumString(token))
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            if (vldRes->params.val_a == NULL)
            {
                vldRes->params.val_a = allocate_double_value(value);
                if (vldRes->params.val_a == NULL)
                {
                    set_error_code(vldRes, ERR_MALLOC_FAILED);
                }
            }
            else
            {
                vldRes->params.val_b = allocate_double_value(value);
                if (vldRes->params.val_b == NULL)
                {
                    set_error_code(vldRes, ERR_MALLOC_FAILED);
                }
            }
        }
        else
        {
            set_error_code(vldRes, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        set_error_code(vldRes, ERR_INVALID_PARAMETER);
    }
}
void handle_fourth_param(Requiermets req, char *token, ValidationResult *vldRes)
{

    if (req.val_2 && isValidNumString(token))
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            if (vldRes->params.val_b == NULL)
            {
                vldRes->params.val_b = allocate_double_value(value);
                if (vldRes->params.val_b == NULL)
                {
                    set_error_code(vldRes, ERR_MALLOC_FAILED);
                }
            }
        }
        else
        {
            set_error_code(vldRes, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        set_error_code(vldRes, ERR_INVALID_PARAMETER);
    }
}
BOOLEAN validate_requirements(const Parameters params, const Requiermets *req)
{
    if (req->var_1 && params.a == NULL)
    {
        return FALSE;
    }
    if (req->var_2 && params.b == NULL)
    {
        return FALSE;
    }
    if (req->val_1 && params.val_a == NULL)
    {
        return FALSE;
    }
    if (req->val_2 && params.val_b == NULL)
    {
        return FALSE;
    }
    return TRUE;
}

void set_error_code(ValidationResult *vldRes, ErrorCode error)
{
    vldRes->errorCode = malloc(sizeof(ErrorCode));
    if (vldRes->errorCode == NULL)
    {
        *vldRes->errorCode = ERR_MALLOC_FAILED;
    }
    else
    {
        *vldRes->errorCode = error;
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
void print_params(Parameters params)
{
    printf("Command Parameters:\n");
    if (params.a)
    {
        printf("Complex a: %.2f + %.2fi\n",
               params.a->real,
               params.a->imaginary);
    }
    if (params.b)
    {
        printf("Complex b: %.2f + %.2fi\n",
               params.b->real,
               params.b->imaginary);
    }
    if (params.val_a)
    {
        printf("Value a: %.2f\n", *(params.val_a));
    }
    if (params.val_b)
    {
        printf("Value b: %.2f\n", *(params.val_b));
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
