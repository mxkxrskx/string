#include "s21_string.h"
#include "s21_strtod.h"
#include "s21_strtol.h"

void handle_char(char **ptr, va_list args) {
  char *c = va_arg(args, char *);
  if (**ptr) {
    *c = **ptr;
    (*ptr)++;
  }
}

void handle_signed_integer(char **ptr, va_list args, int base) {
  if (is_digit(**ptr) || is_sign(**ptr)) {
    int *d = va_arg(args, int *);
    *d = s21_strtol(*ptr, ptr, base);
  }
}

void handle_float(char **ptr, va_list args) {
  if (is_digit(**ptr) || is_sign(**ptr)) {
    float *d = va_arg(args, float *);
    *d = s21_strtod(*ptr, ptr);
  }
}

void handle_string(char **ptr, va_list args) {
  char *s = va_arg(args, char *);
  while (**ptr && **ptr != ' ') {
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

  int count = 0;
  bool error = false;
  while (*format && *ptr && !error) {
    if (*format == '%') {
      format++;
      skip_whitespace(&ptr);
      switch (*format) {
      case 'c':
        handle_char(&ptr, args);
        count++;
        break;
      case 'd':
        handle_signed_integer(&ptr, args, BASE_DECIMAL);
        count++;
        break;
      case 'i':
        handle_signed_integer(&ptr, args, BASE_UNKNOWN);
        count++;
        break;
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        handle_float(&ptr, args);
        count++;
        break;
      case 's':
        handle_string(&ptr, args);
        count++;
        break;
      default:
        error = true;
        break;
      }
    } else {
      format++;
    }
  }

  va_end(args);
  return count;
}
