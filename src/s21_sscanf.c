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

float process_E(char **ptr) {
  int sign = get_sign(ptr);

  // Parse the mantissa
  float mantissa = 0.0;
  mantissa = s21_atoi_decimal(ptr);

  // Check for decimal point
  float decimal_part = 0.0;
  if (**ptr == '.') {
    (*ptr)++;
    char *ptr_start = *ptr;
    // Parse the decimal part
    int decimal_digits = s21_atoi_decimal(ptr);
    int decimal_exp = *ptr - ptr_start;
    decimal_part = decimal_digits * powf(10.0f, -decimal_exp);
  }

  // Check for 'e' or 'E' character
  int exponent = 0;
  if (**ptr == 'e' || **ptr == 'E') {
    (*ptr)++;
    // Parse the exponent
    exponent = s21_atoi_decimal(ptr);
  }

  // Calculate the result
  float result = (mantissa + decimal_part) * powf(10.0f, exponent);

  return sign * result;
}

float process_e(char **ptr) {
  float result = 0.0;
  result = process_E(ptr);

  // Round the result to the nearest e-6
  result = roundf(result * 1e6f) / 1e6f;
  return result;
}

void handle_c(char **ptr, va_list args) {
  char *c = va_arg(args, char *);
  *c = **ptr;
  (*ptr)++;
}

void handle_d(char **ptr, va_list args) {
  if (isdigit(**ptr) || is_sign(**ptr)) {
    int *d = va_arg(args, int *);
    *d = s21_atoi(ptr);
  }
}

void handle_i(char **ptr, va_list args) {
  if (isdigit(**ptr) || is_sign(**ptr)) {
    int *d = va_arg(args, int *);
    *d = s21_atoi_decimal(ptr);
  }
}

void handle_e(char **ptr, va_list args) {
  if (isdigit(**ptr) || is_sign(**ptr)) {
    float *d = va_arg(args, float *);
    *d = process_e(ptr);
  }
}

void handle_E(char **ptr, va_list args) {
  if (isdigit(**ptr) || is_sign(**ptr)) {
    float *d = va_arg(args, float *);
    *d = process_E(ptr);
  }
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *ptr = (char *)str;
  va_list args;
  va_start(args, format);

  bool error = 0;
  int count = 0;
  while (*format && *ptr && !error) {
    count++;
    if (*format++ == '%') {
      switch (*format++) {
      case 'c':
        handle_c(&ptr, args);
        break;
      case 'd':
        handle_d(&ptr, args);
        break;
      case 'i':
        handle_i(&ptr, args);
        break;
      case 'e':
        handle_e(&ptr, args);
        break;
      case 'E':
        handle_E(&ptr, args);
        break;
      default:
        error = 1;
        count--;
        break;
      }
    }
  }

  va_end(args);
  return count;
}
