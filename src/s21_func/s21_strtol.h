#ifndef S21_STRTOL_H
#define S21_STRTOL_H

#include "s21_char_utils.h"
#include "s21_string.h"
#include <math.h>

int parse_octal(char **ptr);
int parse_decimal(char **ptr);
int parse_hexadecimal(char **ptr);
int s21_strtol(const char *ptr, char **endptr, int base);

#endif // S21_STRTOL_H
