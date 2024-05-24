#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include "s21_parse_number.h"
#include "s21_string.h"

typedef enum { DEFAULT, SHORT_INT, LONG_INT, LONG_DOUBLE } s21_type;

int get_len(char **ptr);

bool handle_char(char **ptr, va_list args, int len);

bool assign_value_signed_integer(va_list args, long double val, s21_type type,
                                 int shift);
bool handle_signed_integer(char **ptr, va_list args, int base, int len,
                           s21_type type);

bool assign_value_float(va_list args, long double val, s21_type type, int shift);
bool handle_float(char **ptr, va_list args, int len, s21_type type);

bool assign_value_unsigned_integer(va_list args, long double val, s21_type type,
                                 int shift);
bool handle_unsigned_integer(char **ptr, va_list args, int base, int len,
                             s21_type type);

bool handle_string(char **ptr, va_list args, int len);

bool handle_pointer(char **ptr, va_list args, int len);

bool handle_percent(char **str, char **format);

int s21_sscanf(const char *str, const char *format, ...);

#endif // S21_SSCANF_H_
