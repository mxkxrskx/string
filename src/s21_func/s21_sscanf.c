#include "s21_atoi.h"
#include "s21_string.h"

void skip_whitespace(char **ptr) {
  while (isspace(**ptr)) {
    (*ptr)++;
  }
}
void handle_c(char **ptr, va_list args) {
  char *c = va_arg(args, char *);
  if (**ptr) {
    *c = **ptr;
    (*ptr)++;
  }
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

void handle_f(char **ptr, va_list args) {
  if (isdigit(**ptr) || is_sign(**ptr)) {
    float *d = va_arg(args, float *);
    *d = s21_atoi_float(ptr);
  }
}

void handle_s(char **ptr, va_list args) {
  char *s = va_arg(args, char *);
  while (**ptr != '\0' && **ptr != ' ') {
    *s = **ptr;
    (*ptr)++;
    s++;
  }
  *s = '\0';
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
        skip_whitespace(&ptr);
        handle_d(&ptr, args);
        break;
      case 'i':
        skip_whitespace(&ptr);
        handle_i(&ptr, args);
        break;
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        skip_whitespace(&ptr);
        handle_f(&ptr, args);
        break;
      case 'o':
        // implement o here
        break;
      case 's':
        skip_whitespace(&ptr);
        handle_s(&ptr, args);
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
