#include "s21_string.h"

bool is_sign(const char c) { return c == '-' || c == '+'; }
bool is_octal(const char c) { return c >= '0' && c <= '7'; }

int get_sign(char **ptr) {
  int sign = 1;
  if (**ptr == '-') {
    (*ptr)++;
    sign = -1;
  } else if (**ptr == '+') {
    (*ptr)++;
  }
  return sign;
}

int handle_hexadecimal(char **ptr) {
  int num = 0;
  while (isxdigit(**ptr)) {
    if (isdigit(**ptr)) {
      num = num * 16 + (**ptr - '0');
    } else if (islower(**ptr)) {
      num = num * 16 + (**ptr - 'a') + 10;
    } else if (isupper(**ptr)) {
      num = num * 16 + (**ptr - 'A') + 10;
    }
    (*ptr)++;
  }
  return num;
}

int handle_octal(char **ptr) {
  int num = 0;
  while (is_octal(**ptr)) {
    num = num * 8 + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

int handle_decimal(char **ptr) {
  int num = 0;
  while (isdigit(**ptr)) {
    num = num * 10 + (**ptr - '0');
    (*ptr)++;
  }
  return num;
}

int s21_atoi(char **ptr) {
  int sign = get_sign(ptr);
  int num = 0;
  if (**ptr == '0' && ((*ptr)[1] == 'x' || (*ptr)[1] == 'X')) {
    (*ptr) += 2;
    num = handle_hexadecimal(ptr);
  } else if (**ptr == '0') {
    num = handle_octal(ptr);
  } else {
    num = handle_decimal(ptr);
  }
  return sign * num;
}

int s21_atoi_decimal(char **ptr) {
  int sign = get_sign(ptr);
  int num = handle_decimal(ptr);
  return sign * num;
}

float handle_float(char **ptr) {
  int sign = get_sign(ptr);
  float num = 0.0;
  num = s21_atoi_decimal(ptr);
  if (**ptr == '.') {
    (*ptr)++;
    char *ptr_start = *ptr;
    int decimal_digits = s21_atoi_decimal(ptr);
    int decimal_exp = *ptr - ptr_start;
    num += decimal_digits * powf(10.0f, -decimal_exp);
  }
  return sign * num;
}

float s21_atoi_float(char **ptr) {
  int sign = get_sign(ptr);
  float mantissa = 0.0;
  mantissa = handle_float(ptr);
  int exponent = 0;
  if (**ptr == 'e' || **ptr == 'E') {
    (*ptr)++;
    exponent = s21_atoi_decimal(ptr);
  }
  float result = mantissa * powf(10.0f, exponent);
  return sign * result;
}
