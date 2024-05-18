#include "s21_parse_number.h"
#include "s21_string.h"

bool handle_char(char **ptr, va_list args) {
  bool flag = 1;
  char *c = va_arg(args, char *);
  if (**ptr) {
    *c = **ptr;
    (*ptr)++;
  } else
    flag = 0;
  return flag;
}

bool handle_signed_integer(char **ptr, va_list args, int base) {
  bool flag = 1;
  int *d = va_arg(args, int *);
  int sign = get_sign(ptr);
  char *ptr_start = *ptr;
  if (base == BASE_UNKNOWN)
    base = get_base(ptr);
  long val = sign * parse_number(ptr, base);
  if (*ptr - ptr_start > 0)
    if (val >= INT_MIN && val <= INT_MAX)
      *d = (int)val;
    else
      *d = -1;
  else
    flag = 0;
  return flag;
}

bool handle_float(char **ptr, va_list args) {
  bool flag = 1;
  float *d = va_arg(args, float *);

  int sign = get_sign(ptr);
  char *ptr_num_start = *ptr;

  float mantissa = parse_number(ptr, BASE_DECIMAL);
  if (**ptr == '.') {
    (*ptr)++;
    char *ptr_point_start = *ptr;
    long decimal_digits = parse_number(ptr, BASE_DECIMAL);
    int decimal_exp = *ptr - ptr_point_start;
    mantissa += decimal_digits * powf(10.0f, -decimal_exp);
  }

  int exponent = 0;
  if (**ptr == 'e' || **ptr == 'E') {
    (*ptr)++;
    exponent = get_sign(ptr) * parse_number(ptr, BASE_DECIMAL);
  }

  float val = mantissa * powf(10.0f, exponent);
  if (*ptr - ptr_num_start > 0)
    *d = sign * val;
  else
    flag = 0;

  return flag;
}

bool handle_unsigned_integer(char **ptr, va_list args, int base) {
  bool flag = 1;
  unsigned int *d = va_arg(args, unsigned int *);
  char *ptr_start = *ptr;
  get_base(ptr);
  long val = parse_number(ptr, base);
  if (*ptr - ptr_start > 0)
    if (val >= 0 && val <= UINT_MAX)
      *d = (unsigned int)val;
    else
      *d = -1;
  else
    flag = 0;
  return flag;
}

bool handle_string(char **ptr, va_list args) {
  bool flag = 0;
  if (**ptr)
    flag = 1;
  char *s = va_arg(args, char *);
  while (**ptr && **ptr != ' ') {
    *s = **ptr;
    (*ptr)++;
    s++;
  }
  *s = '\0';
  return flag;
}

bool handle_pointer(char **ptr, va_list args) {
  bool flag = 1;
  unsigned long *ll = va_arg(args, unsigned long *);
  char *ptr_start = *ptr;
  get_base(ptr);
  unsigned long num = 0;
  bool is_overflow = false;
  while (**ptr && is_hex(**ptr)) {
    int c = tolower((unsigned char)**ptr);
    int digit = isdigit(c) ? c - '0' : c - 'a' + 10;
    if (num * BASE_HEX + digit > ULONG_MAX / BASE_HEX)
      is_overflow = true;
    else
      num = num * BASE_HEX + digit;
    (*ptr)++;
  }
  if (is_overflow)
    num = ULONG_MAX;
  if (*ptr - ptr_start > 0)
    *ll = num;
  else
    flag = 0;
  return flag;
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
        error = !handle_char(&ptr, args);
        break;
      case 'd':
      case 'i':
        error = !handle_signed_integer(&ptr, args, BASE_DECIMAL);
        break;
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        error = !handle_float(&ptr, args);
        break;
      case 'o':
        error = !handle_unsigned_integer(&ptr, args, BASE_OCTAL);
        break;
      case 'u':
        error = !handle_unsigned_integer(&ptr, args, BASE_DECIMAL);
        break;
      case 'x':
      case 'X':
        error = !handle_unsigned_integer(&ptr, args, BASE_HEX);
        break;
      case 's':
        error = !handle_string(&ptr, args);
        break;
      case 'p':
        error = !handle_pointer(&ptr, args);
        break;
      case '%':
        format++;
        if (*ptr != '%')
          error = true;
        else
          ptr++;
        break;
      default:
        error = true;
        break;
      }
      if (!error) {
        count++;
        format++;
      }
    } else if (*format != *ptr)
      error = true;
    else {
      format++;
      ptr++;
    }
  }

  va_end(args);
  return count;
}

