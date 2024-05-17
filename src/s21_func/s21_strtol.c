#include "s21_strtol.h"

int parse_octal(char **ptr) {
  int num = 0;
  while (is_octal(**ptr)) {
    num = num * BASE_OCTAL + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

int parse_decimal(char **ptr) {
  int num = 0;
  while (is_digit(**ptr)) {
    num = num * BASE_DECIMAL + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

int parse_hexadecimal(char **ptr) {
  int num = 0;
  while (is_hex(**ptr)) {
    if (is_digit(**ptr)) {
      num = num * BASE_HEX + (**ptr - '0');
    } else if (islower(**ptr)) {
      num = num * BASE_HEX + (**ptr - 'a') + 10;
    } else if (isupper(**ptr)) {
      num = num * BASE_HEX + (**ptr - 'A') + 10;
    }
    (*ptr)++;
  }
  return num;
}

int s21_strtol(const char *str, char **endptr, int base) {
  char *ptr = (char *)str;
  int sign = get_sign(&ptr);
  int num = 0;
  if (base == BASE_UNKNOWN) {
    base = get_base(&ptr);
  }
  switch (base) {
  case BASE_OCTAL:
    num = parse_octal(&ptr);
    break;
  case BASE_DECIMAL:
    num = parse_decimal(&ptr);
    break;
  case BASE_HEX:
    num = parse_hexadecimal(&ptr);
    break;
  }
  if (endptr) {
    *endptr = ptr;
  }
  return sign * num;
}
