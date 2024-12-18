#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mycomp.h"
#include "complex.h"
#include "string_utils.h"

/*
Command table-like structure containing name, action placeholder, validation function
and Requirements
*/
static Command commandTable[NUM_OF_CMNDS] = {
    {"read_comp", {0}, {0}, {TRUE, FALSE, TRUE, TRUE, 3}},
    {"print_comp", {0}, {0}, {TRUE, FALSE, FALSE, FALSE, 1}},
    {"add_comp", {0}, {0}, {TRUE, TRUE, FALSE, FALSE, 2}},
    {"sub_comp", {0}, {0}, {TRUE, TRUE, FALSE, FALSE, 2}},
    {"mult_comp_real", {0}, {0}, {TRUE, FALSE, TRUE, FALSE, 2}},
    {"mult_comp_img", {0}, {0}, {TRUE, FALSE, TRUE, FALSE, 2}},
    {"mult_comp_comp", {0}, {0}, {TRUE, TRUE, FALSE, FALSE, 2}},
    {"abs_comp", {0}, {0}, {TRUE, FALSE, FALSE, FALSE, 1}},
    {"stop", {0}, {0}, {0}},
};

/* Error information table defining error codes and their corresponding messages. */
static ErrorInfo errors[NUM_OF_ERRORS] = {
    {ERR_UNDEFINED_COMPLEX_VAR, "Undefined complex variable"},
    {ERR_UNDEFINED_COMMAND_NAME, "Undefined command name"},
    {ERR_INVALID_PARAMETER, "Invalid parameter - not a number"},
    {ERR_MISSING_PARAMETER, "Missing parameter"},
    {ERR_EXTRANEOUS_TEXT, "Extraneous text after end of command"},
    {ERR_MULTIPLE_CONSECUTIVE_COMMAS, "Multiple consecutive commas"},
    {ERR_MISSING_COMMA, "Missing comma"},
    {ERR_ILLEGAL_COMMA, "Illegal comma"}};

/*Dynamicly assigned value for the longest command length*/
static int MAX_CMD_LENGTH = 0;

/*
The entry point of the complex calculator program
this program iterate through inputs from the stdin and
execute each valid command , each command has up to 2 variable names
and two double values.
This method will exit whenever it fails to allocate memory , EOF
or valid stop command is encountered.
Example usage :
 read_comp  A , 1 , -1
 will insert 1+(-1)i to A
*/
int main()
{
    CommandData commanData = {NULL, NULL, NULL, DEFAULT};
    initCommandTableAction();
    calculateMaxCommandLength();
    displayRules();
    while (commanData.flag == DEFAULT)
    {
        freeCommandData(&commanData);
        printf("\nprompt: ");
        getLine(&commanData);
        if (commanData.line == NULL || commanData.flag < DEFAULT)
        {
            stop(&commanData);
        }
        if (isSpacesString(commanData.line))
        {
            continue;
        }
        extractDataFromLine(&commanData);
        if (commanData.command == NULL)
        {
            printf("%s\n", errors[1].message);
            continue;
        }
        if (isSpacesString(commanData.command) && isSpacesString(commanData.params))
        {
            continue;
        }
        executeCommand(&commanData);
    }
    stop(&commanData);
    return 0;
}

/*Init*/

void initCommandTableAction(void)
{
    int i;
    for (i = 0; i < NUM_OF_CMNDS - 1; i++)
    {
        commandTable[i].validate.actionVld = vldAction;
    }
    commandTable[NUM_OF_CMNDS - 1].validate.stopVld = vldWhiteCharactersOnly;
    commandTable[0].action.cmdAction = readComp;
    commandTable[1].action.cmdAction = printComp;
    commandTable[2].action.cmdAction = addComp;
    commandTable[3].action.cmdAction = subComp;
    commandTable[4].action.cmdAction = multCompReal;
    commandTable[5].action.cmdAction = multCompImg;
    commandTable[6].action.cmdAction = multCompComp;
    commandTable[7].action.cmdAction = absComp;
    commandTable[8].action.exitAction = stop;
}

/*Input */

void getLine(CommandData *commanData)
{
    int ch;
    /*skip empty lines or white characters*/
    while ((ch = getc(stdin)) != EOF)
    {
        if (ch != ' ' && ch != '\t' && ch != '\n')
        {
            ungetc(ch, stdin);
            break;
        }
    }
    if (ch == EOF)
    {
        commanData->flag = EOF_REACHED;
        commanData->line = NULL;
        return;
    }
    commanData->line = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (!commanData->line)
    {
        commanData->flag = MALLOC_ERROR;
        return;
    }
    if (fgets(commanData->line, MAX_LINE_LENGTH, stdin) == NULL)
    {
        commanData->flag = EOF_REACHED;
        free(commanData->line);
        commanData->line = NULL;
        return;
    }
    commanData->line[strcspn(commanData->line, "\n")] = '\0';
}

void extractDataFromLine(CommandData *commanData)
{
    int i, j;
    char *cmnd = NULL;
    char *suffix = NULL;
    char *line = commanData->line;
    i = j = 0;
    cmnd = malloc((MAX_CMD_LENGTH + 1) * sizeof(char));
    suffix = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (cmnd == NULL || suffix == NULL)
    {
        commanData->flag = MALLOC_ERROR;
        return;
    }
    SKIP_SPACES(line);
    while (line[i] && i < MAX_CMD_LENGTH && (islower(line[i]) || line[i] == '_'))
    {
        cmnd[i] = line[i];
        i++;
    }
    cmnd[i] = '\0';
    SKIP_SPACES_WITH_i(line);
    while (line[i])
    {
        suffix[j++] = line[i++];
    }
    suffix[j] = '\0';
    commanData->command = cmnd;
    commanData->params = suffix;
}

/*Logic*/

void calculateMaxCommandLength(void)
{
    int i;
    for (i = 0; i < NUM_OF_CMNDS; i++)
    {
        int len = strlen(commandTable[i].command);
        if (len > MAX_CMD_LENGTH)
        {
            MAX_CMD_LENGTH = len;
        }
    }
}

void executeCommand(CommandData *commanData)
{
    int i;
    int stop_index = NUM_OF_CMNDS - 1;
    char *paramsCopy = copyStr(commanData->params, MAX_LINE_LENGTH);
    ValidationResult vldResult = {{0}, NULL};
    if (paramsCopy == NULL)
    {
        commanData->flag = MALLOC_ERROR;
        stop(commanData);
    }
    printf("%s %s", commanData->command, commanData->params);
    for (i = 0; i < NUM_OF_CMNDS; i++)
    {
        if (i < NUM_OF_CMNDS && strcmp(commanData->command, commandTable[i].command) == 0)
        {
            vldResult = validate(i, paramsCopy);
            if (vldResult.errorCode && *vldResult.errorCode == ERR_MALLOC_FAILED)
            {
                free(paramsCopy);
                commanData->flag = MALLOC_ERROR;
                stop(commanData);
            }
            else if (vldResult.errorCode && vldResult.errorCode)
            {
                printErrorMessage(*vldResult.errorCode);
            }
            else if (i < stop_index && commandTable[i].action.cmdAction)
            {
                commandTable[i].action.cmdAction(&vldResult.params);
            }
            else if (i == stop_index && commandTable[i].action.exitAction)
            {
                free(paramsCopy);
                commanData->flag = SUCCESS;
                commandTable[stop_index].action.exitAction(commanData);
            }
            freeValidationResult(&vldResult);
            free(paramsCopy);
            return;
        }
    }
    printErrorMessage(ERR_UNDEFINED_COMMAND_NAME);
}

ValidationResult validate(int index, char *params)
{
    if (index < NUM_OF_CMNDS - 1)
    {
        return commandTable[index].validate.actionVld(params, commandTable[index].req);
    }
    else
    {
        return commandTable[index].validate.stopVld(params);
    }
}

void stop(CommandData *commanData)
{
    freeCommandData(commanData);
    switch (commanData->flag)
    {
    case SUCCESS:
        printf("\nOperation successful.\nExiting...");
        exit(EXIT_SUCCESS);
    case DEFAULT:
        printf("\nNo input detected.\nExiting...");
        exit(EXIT_SUCCESS);
        break;
    case EOF_REACHED:
        printf("\nEnd of file reached.\nExiting...");
        exit(EXIT_SUCCESS);
    case MALLOC_ERROR:
        printf("\nMemory allocation failed.\nExiting...");
        exit(EXIT_FAILURE);
    default:
        printf("\nUnknown error code.\nExiting...");
        exit(EXIT_FAILURE);
    }
}

void displayRules(void)
{
    /* Introduction and instructions for user */
    printf("Welcome to the complex numbers calculator.\n");
    printf("First consider this rules and examples :\n");
    printf("1. Valid complex variable names: A, B, C, D, E, F.\n");
    printf("2. Valid operations are as follows:\n");
    printf("   - read_comp: To input a complex number.\n");
    printf("   - print_comp: To display a complex number.\n");
    printf("   - add_comp: To add two complex numbers.\n");
    printf("   - sub_comp: To subtract one complex number from another.\n");
    printf("   - mult_comp_real: To multiply a complex number by a real number.\n");
    printf("   - mult_comp_img: To multiply a complex number by an imaginary number.\n");
    printf("   - mult_comp_comp: To multiply two complex numbers.\n");
    printf("   - abs_comp: To find the absolute value of a complex number.\n");
    printf("3. Command formats:\n");
    printf("   - For read_comp: read_comp <variable>, <real part>, <imaginary part> <ENTER>\n");
    printf("     Example: read_comp A, 3.5, -2.1\n");
    printf("   - For print_comp: print_comp <variable><ENTER>\n");
    printf("     Example: print_comp A\n");
    printf("   - For operations with two variables (add/sub/mult_comp_comp):\n");
    printf("     <operation> <variable1>, <variable2><ENTER>\n");
    printf("     Example: add_comp A, B\n");
    printf("   - For operations with a variable and a real number (mult_comp_real):\n");
    printf("     mult_comp_real <variable>, <real value><ENTER>\n");
    printf("     Example: mult_comp_real B, 4.5\n");
    printf("   - For operations with a variable and an imaginary value (mult_comp_img):\n");
    printf("     mult_comp_img <variable>, <imaginary value><ENTER>\n");
    printf("     Example: mult_comp_img C, 2.3\n");
    printf("4. To quit: stop<ENTER>\n");
}

void printErrorMessage(int code)
{
    if (code >= 0 && code < NUM_OF_ERRORS)
    {
        printf("\n%s.", errors[code].message);
    }
    else
    {
        printf("Invalid error code.");
    }
}

/* Allocation*/

void freeCommandData(CommandData *commanData)
{
    if (commanData->line)
    {
        free(commanData->line);
    }
    if (commanData->command)
    {
        free(commanData->command);
    }
    if (commanData->params)
    {
        free(commanData->params);
    }
    commanData->line = NULL;
    commanData->command = NULL;
    commanData->params = NULL;
}

void freeValidationResult(ValidationResult *vldRes)
{
    Parameters params = vldRes->params;
    if (params.val_a)
    {
        free(params.val_a);
    }
    if (params.val_b)
    {
        free(params.val_b);
    }
    if (vldRes->errorCode)
    {
        free(vldRes->errorCode);
    }
}