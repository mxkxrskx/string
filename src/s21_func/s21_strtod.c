#include "s21_strtod.h"

float parse_float(char *ptr, char **endptr) {
  int sign = get_sign(&ptr);
  float num = s21_strtol(ptr, &ptr, BASE_DECIMAL, SIGNED);
  if (*ptr == '.') {
    ptr++;
    char *ptr_start = ptr;
    int decimal_digits = s21_strtol(ptr, &ptr, BASE_DECIMAL, SIGNED);
    int decimal_exp = ptr - ptr_start;
    num += decimal_digits * powf(10.0f, -decimal_exp);
  }
  if (endptr) {
    *endptr = ptr;
  }
  return sign * num;
}

float s21_strtod(const char *str, char **endptr) {
  char *ptr = (char *)str;
  int sign = get_sign(&ptr);
  float mantissa = parse_float(ptr, &ptr);
  int exponent = 0;
  if (*ptr == 'e' || *ptr == 'E') {
    ptr++;
    exponent = s21_strtol(ptr, &ptr, BASE_DECIMAL, SIGNED);
  }
  float result = mantissa * powf(10.0f, exponent);
  if (endptr) {
    *endptr = ptr;
  }
  return sign * result;
}