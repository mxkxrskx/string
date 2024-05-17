#ifndef S21_STRTOL_H
#define S21_STRTOL_H

#include "s21_char_utils.h"
#include "s21_string.h"

long parse_octal(char **ptr);
long parse_decimal(char **ptr);
long parse_hexadecimal(char **ptr);
long s21_strtol(const char *ptr, char **endptr, int base, bool sign);

long parse_number(char **ptr, int base);

#endif // S21_STRTOL_H
