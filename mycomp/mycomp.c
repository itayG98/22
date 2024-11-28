#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mycomp.h"
#include "complex.h"

static Command command_table[NUM_OF_CMNDS] = {
    {"read_comp", {0}, vld_read_comp},
    {"print_comp", {0}, vld_print_comp},
    {"add_comp", {0}, vld_add_comp},
    {"sub_comp", {0}, vld_sub_comp},
    {"mult_comp_real", {0}, vld_mult_comp_real},
    {"mult_comp_img", {0}, vld_mult_comp_img},
    {"mult_comp_comp", {0}, vld_mult_comp_comp},
    {"abs_comp", {0}, vld_abs_comp},
    {"stop", {0}, vld_stop}};

static ErrorInfo errors[NUM_OF_ERRORS] = {
    {ERR_UNDEFINED_COMPLEX_VAR, "Undefined complex variable"},
    {ERR_UNDEFINED_COMMAND_NAME, "Undefined command name"},
    {ERR_INVALID_PARAMETER, "Invalid parameter - not a number"},
    {ERR_MISSING_PARAMETER, "Missing parameter"},
    {ERR_EXTRANEOUS_TEXT, "Extraneous text after end of command"},
    {ERR_MULTIPLE_CONSECUTIVE_COMMAS, "Multiple consecutive commas"},
    {ERR_MISSING_COMMA, "Missing comma"},
    {ERR_ILLEGAL_COMMA, "Illegal comma"}};

static int MAX_CMD_LENGTH = 0;

int main()
{
    commandData command_data = {NULL, NULL, NULL, DEFAULT};
    initCommandTableAction();
    calculate_max_command_length();
    display_rules();
    while (command_data.flag == DEFAULT || command_data.flag == ERROR)
    {
        free_commnad_data(&command_data);
        printf("\nprompt: ");
        get_line(&command_data);
        if (command_data.line == NULL)
        {
            stop(&command_data);
        }
        if (strlen(command_data.line) == 0 || command_data.flag == ERROR)
        {
            continue;
        }
        extract_data_from_line(&command_data);
        if (command_data.command == NULL)
        {
            printf("%s\n", errors[1].message);
            continue;
        }
        execute_command(&command_data);
    }
    stop(&command_data);
    return 0;
}

/*Init*/

void initCommandTableAction(void)
{
    command_table[0].action.cmd_action = read_comp;
    command_table[1].action.cmd_action = print_comp;
    command_table[2].action.cmd_action = add_comp;
    command_table[3].action.cmd_action = sub_comp;
    command_table[4].action.cmd_action = mult_comp_real;
    command_table[5].action.cmd_action = mult_comp_img;
    command_table[6].action.cmd_action = mult_comp_comp;
    command_table[7].action.cmd_action = abs_comp;
    command_table[8].action.exit_action = stop;
}

/*Input */

void get_line(commandData *command_data)
{
    command_data->line = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (!command_data->line)
    {
        command_data->flag = MALLOC_ERROR;
        return;
    }
    if (fgets(command_data->line, MAX_LINE_LENGTH, stdin) == NULL)
    {
        command_data->flag = EOF_REACHED;
        free(command_data->line);
        command_data->line = NULL;
        return;
    }
    command_data->line[strcspn(command_data->line, "\n")] = 0;
}

void extract_data_from_line(commandData *command_data)
{
    int i, j;
    char *cmnd = NULL;
    char *suffix = NULL;
    char *line = NULL;
    i = j = 0;
    cmnd = malloc((MAX_CMD_LENGTH + 1) * sizeof(char));
    suffix = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (cmnd == NULL || suffix == NULL)
    {
        command_data->flag = MALLOC_ERROR;
        return;
    }
    line = command_data->line;
    while (line[i] && i < MAX_CMD_LENGTH && (islower(line[i]) || line[i] == '_'))
    {
        cmnd[i] = line[i];
        i++;
    }
    cmnd[i] = '\0';
    while (line[i] && !isTabOrSpace(line[i]))
    {
        i++;
    }
    while (line[i])
    {
        suffix[j++] = line[i++];
    }
    suffix[j] = '\0';
    command_data->command = cmnd;
    command_data->params = suffix;
}

char *copyStr(const char *source)
{
    if (source != NULL)
    {
        char *copy = malloc(sizeof(char) * MAX_LINE_LENGTH);
        if (copy == NULL)
        {
            return NULL;
        }
        strncpy(copy, source, MAX_LINE_LENGTH - 1);
        copy[MAX_LINE_LENGTH - 1] = '\0';
        return copy;
    }
    return NULL;
}

/*Logic*/
void calculate_max_command_length(void)
{
    int i;
    for (i = 0; i < NUM_OF_CMNDS; i++)
    {
        int len = strlen(command_table[i].command);
        if (len > MAX_CMD_LENGTH)
        {
            MAX_CMD_LENGTH = len;
        }
    }
}

void execute_command(commandData *command_data)
{
    int i;
    CommandParams params = {NULL, NULL, NULL, NULL, NULL};
    char *params_copy = copyStr(command_data->params);
    if (params_copy == NULL)
    {
        command_data->flag = MALLOC_ERROR;
        stop(command_data);
    }
    printf("%s %s", command_data->command, command_data->params);
    for (i = 0; i < NUM_OF_CMNDS; i++)
    {
        if (i < NUM_OF_CMNDS - 1 && strcmp(command_data->command, command_table[i].command) == 0)
        {
            params = command_table[i].validate(params_copy);
            if (params.errorCode && *params.errorCode == ERR_MALLOC_FAILED)
            {
                free(params_copy);
                command_data->flag = MALLOC_ERROR;
                stop(command_data);
            }
            else if (params.errorCode && params.errorCode)
            {
                print_error_message(*params.errorCode);
            }
            else if (command_table[i].action.cmd_action)
            {
                command_table[i].action.cmd_action(&params);
            }
            free_command_params(&params);
            free(params_copy);
            return;
        }
        else if (i == NUM_OF_CMNDS - 1 && command_table[i].action.exit_action)
        {
            free(params_copy);
            command_data->flag = SUCCES;
            command_table[i].action.exit_action(command_data);
        }
    }
    printf("\n%s is not a valid command.", command_data->line);
}

void stop(commandData *command_data)
{
    free_commnad_data(command_data);
    switch (command_data->flag)
    {
    case SUCCES:
        printf("\nOperation successful. Exiting...\n");
        exit(EXIT_SUCCESS);
    case DEFAULT:
        printf("\nNo input detected...\n");
        break;
    case EOF_REACHED:
        printf("\nEnd of file reached. Exiting...\n");
        exit(EXIT_SUCCESS);
    case ERROR:
        printf("\nError occurred. Exiting...\n");
        exit(EXIT_FAILURE);
    case MALLOC_ERROR:
        printf("\nMemory allocation failed . Exiting...\n");
    default:
        printf("\nUnknown error code. Exiting...\n");
        exit(EXIT_FAILURE);
    }
}

void display_rules(void)
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

void print_error_message(int code)
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

BOOLEAN isTabOrSpace(char c)
{
    return c == ' ' || c == '\t' ? TRUE : FALSE;
}

/* Allocation*/

void free_commnad_data(commandData *command_data)
{
    if (command_data)
    {
        if (command_data->line)
        {
            free(command_data->line);
        }
        if (command_data->command)
        {
            free(command_data->command);
        }
        if (command_data->params)
        {
            free(command_data->params);
        }
        command_data->line = NULL;
        command_data->command = NULL;
        command_data->params = NULL;
    }
}

void free_command_params(CommandParams *cmdParams)
{
    if (cmdParams)
    {
        if (cmdParams->val_a)
        {
            free(cmdParams->val_a);
        }
        if (cmdParams->val_b)
        {
            free(cmdParams->val_b);
        }
        if (cmdParams->errorCode)
        {
            free(cmdParams->errorCode);
        }
        cmdParams->a = NULL;
        cmdParams->b = NULL;
        cmdParams->val_a = NULL;
        cmdParams->val_b = NULL;
        cmdParams->errorCode = NULL;
    }
}

/*Development helpers*/
void print_commandData(commandData *cmdData)
{
    if (cmdData == NULL)
    {
        printf("commandData is NULL.\n");
        return;
    }

    printf("commandData:\n");
    printf("  Line    : %s\n", cmdData->line ? cmdData->line : "NULL");
    printf("  Command : %s\n", cmdData->command ? cmdData->command : "NULL");
    printf("  Params  : %s\n", cmdData->params ? cmdData->params : "NULL");
    printf("  Flag    : %d\n", cmdData->flag);
}
