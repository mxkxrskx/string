#include "s21_parse_number.h"

long parse_number(char **ptr, int base) {
  const char *valid_digits[17] = {
      [8] = "01234567",               // octal
      [10] = "0123456789",            // decimal
      [16] = "0123456789abcdefABCDEF" // hexadecimal
  };
  const char *valid = valid_digits[base];

  long num = 0;
  while (**ptr && strchr(valid, **ptr) != NULL) {
    int c = to_lower(**ptr);
    int digit = is_digit(c) ? c - '0' : c - 'a' + 10;
    num = num * base + digit;
    (*ptr)++;
  }
  return num;
}
