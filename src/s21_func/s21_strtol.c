#include "s21_strtol.h"

long parse_octal(char **ptr) {
  long num = 0;
  while (is_octal(**ptr)) {
    num = num * BASE_OCTAL + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

long parse_decimal(char **ptr) {
  long num = 0;
  while (is_digit(**ptr)) {
    num = num * BASE_DECIMAL + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

long parse_hexadecimal(char **ptr) {
  long num = 0;
  while (is_hex(**ptr)) {
    if (is_digit(**ptr)) {
      num = num * BASE_HEX + (**ptr - '0');
    } else if (is_lower(**ptr)) {
      num = num * BASE_HEX + (**ptr - 'a') + 10;
    } else if (is_upper(**ptr)) {
      num = num * BASE_HEX + (**ptr - 'A') + 10;
    }
    (*ptr)++;
  }
  return num;
}

long s21_strtol(const char *str, char **endptr, int base, bool sign) {
  char *ptr = (char *)str;
  if (sign == SIGNED) {
    sign = get_sign(&ptr);
  }
  long num = 0;
  if (base == BASE_UNKNOWN || sign == UNSIGNED) {
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
