#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include "s21_parse_number.h"
#include "s21_string.h"

typedef enum { DEFAULT, SHORT_INT, LONG_INT, LONG_DOUBLE } s21_type;

typedef struct s21_flags s21_flags;

int get_len(char **format);
s21_type get_type(char **format);
bool get_asterisk(char **format);

void fill_flags(char **ptr, s21_flags *flags);

void skip_remain_len(char **ptr, char *ptr_start, size_t len);

void assign_value_char(va_list args, char val, s21_flags flags);
bool handle_char(char **ptr, va_list args, s21_flags flags);

bool assign_value_signed_integer(va_list args, long double val, s21_flags flags,
                                 int shift);
bool handle_signed_integer(char **ptr, va_list args, int base, s21_flags flags);

bool assign_value_float(va_list args, long double val, s21_flags flags,
                        int shift);
bool handle_float(char **ptr, va_list args, s21_flags flags);

bool assign_value_unsigned_integer(va_list args, long double val,
                                   s21_flags flags, int shift);
bool handle_unsigned_integer(char **ptr, va_list args, int base,
                             s21_flags flags);

void assign_value_string(char **ptr, char *s, s21_flags flags);
bool handle_string(char **ptr, va_list args, s21_flags flags);

bool handle_pointer(char **ptr, va_list args, s21_flags flags);

bool handle_percent(char **str, char **format);

bool match_literal(char **ptr_format, char **ptr_str);

bool handle_format_specifier(char **ptr_format, char **ptr_str, va_list args,
                             s21_flags flags, int* count);

int process_format_string(const char *str, const char *format, va_list args);

int s21_sscanf(const char *str, const char *format, ...);

#endif // S21_SSCANF_H
