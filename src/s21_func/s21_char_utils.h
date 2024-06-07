#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include "s21_string.h"

#define BASE_UNKNOWN 0
#define BASE_OCTAL 8
#define BASE_DECIMAL 10
#define BASE_HEX 16

bool s21_isdigit(char c);
bool s21_isupper(char c);
char s21_tolower(char c);
bool s21_isspace(char c);
void skip_spaces(char **s);

#endif // CHAR_UTILS_H
