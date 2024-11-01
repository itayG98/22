#ifndef VALIDATION_H
#define VALIDATION_H

typedef enum
{
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef BOOLEAN (*ValidateCommand)(char *);

BOOLEAN vld_read_comp(char *line);
BOOLEAN vld_print_comp(char *line);
BOOLEAN vld_add_comp(char *line);
BOOLEAN vld_sub_comp(char *line);
BOOLEAN vld_mult_comp_real(char *line);
BOOLEAN vld_mult_comp_img(char *line);
BOOLEAN vld_mult_comp_comp(char *line);
BOOLEAN vld_abs_comp(char *line);

#endif
