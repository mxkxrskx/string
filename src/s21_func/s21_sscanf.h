#ifndef S21_SSCANF_H_
#define S21_SSCANF_H_

#include "s21_parse_number.h"
#include "s21_string.h"

typedef enum { DEFAULT, SHORT_INT, LONG_INT, LONG_DOUBLE } s21_type;

typedef struct s21_flags {
  int len;
  s21_type type;
  bool asterisk;
} s21_flags;

int get_len(char **ptr);

s21_type get_type(char **format);

bool get_asterisk(char **format);

void fill_struct(char **ptr, s21_flags *flags);

void assign_value_char(va_list args, char val, bool asterisk);
bool handle_char(char **ptr, va_list args, int len, bool asterisk);

bool assign_value_signed_integer(va_list args, long double val, s21_type type,
                                 int shift, bool asterisk);
bool handle_signed_integer(char **ptr, va_list args, int base, int len,
                           s21_type type, bool asterisk);

bool assign_value_float(va_list args, long double val, s21_type type, int shift,
                        bool asterisk);
bool handle_float(char **ptr, va_list args, int len, s21_type type,
                  bool asterisk);

bool assign_value_unsigned_integer(va_list args, long double val, s21_type type,
                                   int shift, bool asterisk);
bool handle_unsigned_integer(char **ptr, va_list args, int base, int len,
                             s21_type type, bool asterisk);

void assign_value_string(char **ptr, char *s, int len, bool asterisk);
bool handle_string(char **ptr, va_list args, int len, bool asterisk);

bool handle_pointer(char **ptr, va_list args, int len, bool asterisk);

bool handle_percent(char **str, char **format);

int s21_sscanf(const char *str, const char *format, ...);

#endif // S21_SSCANF_H_
