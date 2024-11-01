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
    calculate_max_command_length();
    char *line, *cmnd, *params;
    int params_start_idx = -1;
    diplayRules();
    while (TRUE)
    {
        line = get_line();
        if (line == NULL)
        {
            printf("End of input detected. Exiting...\n");
            free(line);
            stop();
        }
        if (strlen(line) != 0)
        {
            cmnd = extract_cmnd(line, &params_start_idx);
            execute_command(cmnd, line, params_start_idx);
        }
    }
    free(line);
    free(cmnd);
    free(params);
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

char *extract_cmnd(const char *line, int *params_start_idx)
{
    char *cmnd = malloc((MAX_CMD_LENGTH + 1) * sizeof(char));
    int i = 0;
    while (line[i] && i < 15 && (islower(line[i]) || line[i] == '_'))
    {
        cmnd[i] = line[i];
        i++;
    }
    cmnd[i] = '\0';
    *params_start_idx = i;
    return cmnd;
}

void execute_command(char *cmnd, char *line, int params_start_idx)
{
    int i = 0;
    for (i = 0; i < NUM_OF_CMNDS; i++)
    {
        if (strcmp(cmnd, commandTable[i].command) == 0)
        {
            if (commandTable[i].action)
            {
                printf("Executing : %s\n", commandTable[i].command);
                printf("using : %s\n", line + params_start_idx);
                /*commandTable[i].action(); */
            }
            return;
        }
    }
    printf("Unknown command: %s\n", cmnd);
}

char *get_line()
{
    char *line = malloc(sizeof(char) * MAX_LINE_LENGTH);
    if (!line)
    {
        perror("Unable to allocate memory for line");
        return NULL;
    }
    if (fgets(line, sizeof(char) * MAX_LINE_LENGTH, stdin) == NULL)
    {
        return NULL;
    }
    line[strcspn(line, "\n")] = 0;
    remove_spaces_and_tabs(line);
    return line;
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

void stop(void)
{
    exit(0);
}

void diplayRules(void)
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