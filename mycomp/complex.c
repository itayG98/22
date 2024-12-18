#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "complex.h"
#include "string_utils.h"
#include "common_types.h"

/* Variables table-like structure containing variable name,and initalized value */
static Variable variables[NUM_OF_VARIABLES] = {
    {'A', {0.0, 0.0}},
    {'B', {0.0, 0.0}},
    {'C', {0.0, 0.0}},
    {'D', {0.0, 0.0}},
    {'E', {0.0, 0.0}},
    {'F', {0.0, 0.0}}};

int getVariableIndex(char c)
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

Complex *getVariableRefByIndex(int index)
{
    if (index >= 0 && index < NUM_OF_VARIABLES)
    {
        return &(variables[index].value);
    }
    return NULL;
}

void displayCompNum(const Complex num)
{
    printf("\n%.2f + (%.2f)i", num.real, num.imaginary);
}

/*  Actions */

void readComp(Parameters *params)
{
    params->a->real = *(params->val_a);
    params->a->imaginary = *(params->val_b);
}

void printComp(Parameters *params)
{
    displayCompNum(*params->a);
}

/* Calculation*/

void addComp(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real + params->b->real;
    result.imaginary = params->a->imaginary + params->b->imaginary;
    displayCompNum(result);
}

void subComp(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real - params->b->real;
    result.imaginary = params->a->imaginary - params->b->imaginary;
    displayCompNum(result);
}

void multCompReal(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real * (*(params->val_a));
    result.imaginary = params->a->imaginary * (*(params->val_a));
    displayCompNum(result);
}

void multCompImg(Parameters *params)
{
    Complex result = {0};
    result.real = -params->a->imaginary * (*(params->val_a));
    result.imaginary = params->a->real * (*(params->val_a));
    displayCompNum(result);
}

void multCompComp(Parameters *params)
{
    Complex result = {0};
    result.real = params->a->real * params->b->real - params->a->imaginary * params->b->imaginary;
    result.imaginary = params->a->real * params->b->imaginary + params->a->imaginary * params->b->real;
    displayCompNum(result);
}

void absComp(Parameters *params)
{
    double result = 0;
    result = sqrt(params->a->real * params->a->real + params->a->imaginary * params->a->imaginary);
    printf("\n%.2f", result);
}

/* Validation*/

ValidationResult vldAction(char *params, Requirements req)
{
    return extractCommandParams(params, req);
}
ValidationResult vldWhiteCharactersOnly(char *params)
{
    ValidationResult cmd_params = {{0}, NULL};
    if (!isSpacesString(params))
    {
        setErrorCode(&cmd_params, ERR_EXTRANEOUS_TEXT);
    }
    return cmd_params;
}

ValidationResult extractCommandParams(char *params_str, Requirements req)
{
    ValidationResult vldRes = {{0}, NULL};
    char *token = NULL;
    int token_count = 0;
    while ((token = my_strsep(&params_str, ",")) != NULL)
    {
        if (token_count == req.param_count)
        {
            setErrorCode(&vldRes, ERR_EXTRANEOUS_TEXT);
            return vldRes;
        }
        SKIP_SPACES(token);
        if (isSpacesString(token))
        {
            if (token_count > 0)
            {
                BOOLEAN isConsecCommas = checkConsecutiveCommas(params_str);
                setErrorCode(&vldRes, isConsecCommas ? ERR_MULTIPLE_CONSECUTIVE_COMMAS : ERR_MISSING_PARAMETER);
                return vldRes;
            }
            else
            {
                setErrorCode(&vldRes, ERR_MISSING_PARAMETER);
                return vldRes;
            }
        }
        switch (token_count)
        {
        case 0:
            setVarByToken(token, &vldRes, TRUE);
            if (vldRes.errorCode)
            {
                return vldRes;
            }
            break;
        case 1:
            if (req.var_2)
            {
                setVarByToken(token, &vldRes, FALSE);
            }
            else if (req.val_1)
            {
                setNumberByToken(token, &vldRes, TRUE);
            }
            if (vldRes.errorCode)
            {
                return vldRes;
            }
            break;
        case 2:
            if (req.val_1 && !vldRes.params.val_a)
            {
                setNumberByToken(token, &vldRes, TRUE);
            }
            else if (req.val_2)
            {
                setNumberByToken(token, &vldRes, FALSE);
            }
            if (vldRes.errorCode)
            {
                return vldRes;
            }
            break;
        case 3:
            if (req.val_2)
            {
                setNumberByToken(token, &vldRes, FALSE);
            }
            if (vldRes.errorCode)
            {
                return vldRes;
            }
            break;
        }
        token_count++;
    }
    if (!validate_requirements(vldRes.params, &req))
    {
        setErrorCode(&vldRes, ERR_MISSING_PARAMETER);
    }
    return vldRes;
}

void setVarByToken(char *token, ValidationResult *vldRes, BOOLEAN isFirst)
{
    char varName = getOnlyChar(token);
    if (varName != '\0')
    {
        int index = getVariableIndex(varName);
        if (index >= 0)
        {
            if (isFirst)
            {
                vldRes->params.a = getVariableRefByIndex(index);
            }
            else
            {
                vldRes->params.b = getVariableRefByIndex(index);
            }
            return;
        }
    }
    setErrorCode(vldRes, ERR_UNDEFINED_COMPLEX_VAR);
}

void setNumberByToken(char *token, ValidationResult *vldRes, BOOLEAN isFirst)
{
    if (isValidNumString(token) != '\0')
    {
        double value = atof(token);
        if (value != 0 || strcmp(token, "0") == 0)
        {
            double *ptr = allocateDoublevalue(value);
            if (ptr == NULL)
            {
                setErrorCode(vldRes, ERR_MALLOC_FAILED);
            }
            else if (isFirst)
            {
                vldRes->params.val_a = ptr;
            }
            else
            {
                vldRes->params.val_b = ptr;
            }
        }
        else
        {
            setErrorCode(vldRes, ERR_INVALID_PARAMETER);
        }
    }
    else
    {
        setErrorCode(vldRes, ERR_INVALID_PARAMETER);
    }
}

BOOLEAN validate_requirements(const Parameters params, const Requirements *req)
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

void setErrorCode(ValidationResult *vldRes, ErrorCode error)
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

double *allocateDoublevalue(double value)
{
    double *val = malloc(sizeof(double));
    if (val != NULL)
    {
        *val = value;
    }
    return val;
}
