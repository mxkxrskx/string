#ifndef S21_STRTOD_H
#define S21_STRTOD_H

#include "s21_char_utils.h"
#include "s21_strtol.h"

float parse_float(char *ptr, char **endptr);
float s21_strtod(const char *ptr, char **endptr);

#endif // S21_STRTOD_H
