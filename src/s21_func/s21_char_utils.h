#ifndef CHAR_UTILS_H
#define CHAR_UTILS_H

#include <stdbool.h>

#define BASE_UNKNOWN 0
#define BASE_OCTAL 8
#define BASE_DECIMAL 10
#define BASE_HEX 16

#define SIGNED 0
#define UNSIGNED 1

bool is_sign(char c);
bool is_digit(char c);
bool is_octal(char c);
bool is_hex(char c);

void skip_whitespace(char **ptr);

int get_sign(char **ptr);
int get_base(char **ptr);

#endif // CHAR_UTILS_H
