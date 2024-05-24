#include "s21_parse_number.h"

long double parse_number(char **ptr, int base, int len) {
  const char *valid_digits[17] = {
      [8] = "01234567",               // octal
      [10] = "0123456789",            // decimal
      [16] = "0123456789abcdefABCDEF" // hexadecimal
  };
  const char *valid = valid_digits[base];

  char *ptr_start = *ptr;
  double num = 0;
  while (**ptr && *ptr - ptr_start < len && strchr(valid, **ptr) != NULL) {
    int c = to_lower(**ptr);
    int digit = is_digit(c) ? c - '0' : c - 'a' + 10;
    num = num * base + digit;
    (*ptr)++;
  }
  return num;
}
