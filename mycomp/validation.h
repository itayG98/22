#ifndef VALIDATION_H
#define VALIDATION_H
#include "complex.h"

typedef CommandParams (*ValidateCommand)(char *);

CommandParams vld_read_comp(char *line);
CommandParams vld_print_comp(char *line);
CommandParams vld_add_comp(char *line);
CommandParams vld_sub_comp(char *line);
CommandParams vld_mult_comp_real(char *line);
CommandParams vld_mult_comp_img(char *line);
CommandParams vld_mult_comp_comp(char *line);
CommandParams vld_abs_comp(char *line);

CommandParams *create_empty_command_params();
#endif
