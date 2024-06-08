#ifndef S21_PARSE_NUMBER_H
#define S21_PARSE_NUMBER_H

#include "s21_char_utils.h"
#include "s21_string.h"

int parse_number(char **ptr, int base, long long *num, int len);
long parse_number1(char **ptr, int base, int len);

#endif  // S21_PARSE_NUMBER_H
