#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mycomp.h"
#include "complex.h"
#include "validation.h"

static CommandTable commandTable[NUM_OF_CMNDS] = {
    {"read_comp", read_comp, vld_read_comp},
    {"print_comp", print_comp, vld_print_comp},
    {"add_comp", add_comp, vld_add_comp},
    {"sub_comp", sub_comp, vld_sub_comp},
    {"mult_comp_real", mult_comp_real, vld_mult_comp_real},
    {"mult_comp_img", mult_comp_img, vld_mult_comp_img},
    {"mult_comp_comp", mult_comp_comp, vld_mult_comp_comp},
    {"abs_comp", abs_comp, vld_abs_comp},
    {"stop", stop, NULL}};

static VariableTable variables[NUM_OF_VARIABLES] = {
    {'A', {0, 0}},
    {'B', {0, 0}},
    {'C', {0, 0}},
    {'D', {0, 0}},
    {'E', {0, 0}},
    {'F', {0, 0}}};

static int MAX_CMD_LENGTH;

int main()
{
    commandData command_data = {NULL, NULL, NULL, DEFAULT};
    calculate_max_command_length();
    display_rules();
    while (command_data.flag == DEFAULT)
    {
        printf("\n\n~prompt: ");
        get_line(&command_data);
        if (command_data.line == NULL)
        {
            stop(&command_data);
        }
        if (strlen(command_data.line) != 0)
        {
            extract_data_from_line(&command_data);
            execute_command(&command_data);
        }
    }
    stop(&command_data);
    return 0;
}

void stop(commandData *command_data)
{
    free_commnad_data(command_data);
    switch (command_data->flag)
    {
    case SUCCES:
        printf("Operation successful. Exiting...\n");
        exit(EXIT_SUCCESS);
    case DEFAULT:
        printf("No inpt detected...\n");
        break;
    case EOF_REACHED:
        printf("End of file reached. Exiting...\n");
        exit(EXIT_SUCCESS);
    case ERROR:
        printf("Error occurred. Exiting...\n");
        exit(EXIT_FAILURE);
    default:
        printf("Unknown error code. Exiting...\n");
        exit(EXIT_FAILURE);
    }
}

void free_commnad_data(commandData *command_data)
{
    free(command_data->line);
    free(command_data->command);
    free(command_data->params);
}

void extract_data_from_line(commandData *command_data)
{
    int i, j;
    i = j = 0;
    char *cmnd, *suffix, *line;
    cmnd = malloc((MAX_CMD_LENGTH + 1) * sizeof(char));
    suffix = malloc(sizeof(char) * MAX_LINE_LENGTH);
    line = command_data->line;
    while (line[i] && i < MAX_CMD_LENGTH && (islower(line[i]) || line[i] == '_'))
    {
        cmnd[i] = line[i];
        i++;
    }
    cmnd[i] = '\0';
    while (line[i])
    {
        if (line[i] != '\t' && line[i] != ' ')
        {
            suffix[j] = line[i];
            j++;
        }
        i++;
    }
    suffix[j] = '\0';
    command_data->command = cmnd;
    command_data->params = suffix;
}

void execute_command(commandData *command_data)
{
    int i;
    for (i = 0; i < NUM_OF_CMNDS; i++)
    {
        if (strcmp(command_data->command, commandTable[i].command) == 0)
        {
            if (commandTable[i].action.action_params != NULL)
            {
                printf("Executing : %s\n", commandTable[i].command);
                /* commandTable[i].validate(command_data->params);*/
                printf("using : %s\n", command_data->params);
                /*commandTable[i].action(); */
                return;
            }
        }
    }
    printf("is not a valid command");
}

CommandParams extract_command_params(const commandData *cmdData)
{
    CommandParams cmdParams = {0};
    char *param_str = cmdData->params;
    char *token;
    int token_count = 0;

    token = strtok(param_str, ",");
    while (token && token_count < 4)
    {

        if (token_count == 0 && isupper(*token))
        {
            if (!is_valid_variable(*token))
                return (CommandParams){0};
            cmdParams.a = get_variable_value(*token);
        }
        else if (token_count == 1 && atof(token))
        {
            cmdParams.val_a = atof(token);
        }
        else if (token_count == 2 && atof(token))
        {
            cmdParams.val_b = atof(token);
        }
        else if (token_count == 3 && isupper(*token))
        {
            if (!is_valid_variable(*token))
                return (CommandParams){0};
            cmdParams.b = get_variable_value(*token);
        }
        else
        {
            return (CommandParams){0};
        }

        token_count++;
        token = strtok(NULL, ",");
    }

    if (token_count > 0 && cmdData->params[strlen(cmdData->params) - 1] == ',')
    {
        return (CommandParams){0};
    }

    return cmdParams;
}

void get_line(commandData *command_data)
{
    command_data->line = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (!command_data->line)
    {
        perror("Unable to allocate memory for line");
        command_data->flag = ERROR;
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

int is_valid_variable(char c)
{
    for (int i = 0; i < NUM_OF_VARIABLES; i++)
    {
        if (variables[i].key == c)
        {
            return 1;
        }
    }
    return 0;
}

void calculate_max_command_length(void)
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

void remove_spaces_and_tabs(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
        {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
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