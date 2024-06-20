#include "s21_parse_number.h"

#include "s21_string.h"

int parse_number(char **ptr, int base, long long *num, int len) {
  const char *valid_digits[17] = {
      [8] = "01234567",                // octal
      [10] = "0123456789",             // decimal
      [16] = "0123456789abcdefABCDEF"  // hexadecimal
  };
  const char *valid = valid_digits[base];
  char *ptr_start = *ptr;
  *num = 0;
  int success = 1;

  while (**ptr && s21_strchr(valid, **ptr) != S21_NULL && len > 0 && success) {
    int c = s21_tolower(**ptr);
    int digit = s21_isdigit(c) ? c - '0' : c - 'a' + 10;

    if (*num > (LONG_MAX - digit) / base) {
      success = -1;
    }

    *num = *num * base + digit;
    (*ptr)++;
    len--;
  }

  if (success != -1) {
    success = *ptr - ptr_start;
  }

  return success;
}

long parse_number1(char **ptr, int base, int len) {
  const char *valid_digits[17] = {
      [8] = "01234567",                // octal
      [10] = "0123456789",             // decimal
      [16] = "0123456789abcdefABCDEF"  // hexadecimal
  };
  const char *valid = valid_digits[base];

  char *ptr_start = *ptr;
  long num = 0;
  while (**ptr && *ptr - ptr_start < len &&
         s21_strchr(valid, **ptr) != S21_NULL) {
    int c = s21_tolower(**ptr);
    int digit = s21_isdigit(c) ? c - '0' : c - 'a' + 10;
    num = num * base + digit;
    (*ptr)++;
  }
  return num;
}
