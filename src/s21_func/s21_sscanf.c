#include "s21_sscanf.h"

int get_len(char **ptr) {
  char *ptr_start = *ptr;
  int n = parse_number(ptr, BASE_DECIMAL, INT_MAX);
  if (*ptr - ptr_start == 0 || n == 0)
    n = INT_MAX;
  return n;
}

bool handle_char(char **ptr, va_list args, int len) {
  bool flag = 1;
  char *c = va_arg(args, char *);
  if (**ptr) {
    *c = **ptr;
    char *ptr_start = *ptr;
    (*ptr)++;
    while (**ptr && *ptr - ptr_start < len && len != INT_MAX) {
      (*ptr)++;
    }
  } else
    flag = 0;
  return flag;
}

bool handle_signed_integer(char **ptr, va_list args, int base, int len) {
  bool flag = 1;
  int *d = va_arg(args, int *);
  int sign = get_sign(ptr);
  char *ptr_start = *ptr;
  if (base == BASE_UNKNOWN)
    base = get_base(ptr);
  long val = sign * parse_number(ptr, base, len);
  if (*ptr - ptr_start > 0)
    if (val >= INT_MIN && val <= INT_MAX)
      *d = (int)val;
    else
      *d = -1;
  else
    flag = 0;
  return flag;
}

bool handle_float(char **ptr, va_list args, int len) {
  bool flag = 1;
  float *d = va_arg(args, float *);

  char *ptr_num_start = *ptr;
  int sign = get_sign(ptr);
  if (*ptr - ptr_num_start > 0) {
    ptr_num_start = *ptr;
    len--;
  }

  float mantissa = parse_number(ptr, BASE_DECIMAL, len);
  len -= *ptr - ptr_num_start;
  if (**ptr == '.' && len > 0) {
    (*ptr)++;
    len--;
    char *ptr_point_start = *ptr;
    long decimal_digits = parse_number(ptr, BASE_DECIMAL, len);
    int decimal_exp = *ptr - ptr_point_start;
    len -= decimal_exp;
    mantissa += decimal_digits * powf(10.0f, -decimal_exp);
  }

  if (*ptr - ptr_num_start == 0) return false;

  int exponent = 0;
  if ((**ptr == 'e' || **ptr == 'E') && len > 0) {
    (*ptr)++;
    len--;
    char *temp_ptr = *ptr;
    int sign_e = get_sign(ptr);
    if (*ptr - temp_ptr > 0)
      len--;
    char *ptr_point_start = *ptr;
    long number_e = parse_number(ptr, BASE_DECIMAL, len);
    if (*ptr - ptr_point_start > 0)
      exponent = sign_e * number_e;
    else 
      *ptr = temp_ptr - 1;
  }

  float val = mantissa * powf(10.0f, exponent);
  if (*ptr - ptr_num_start > 0)
    *d = sign * val;
  else
    flag = 0;

  return flag;
}

bool handle_unsigned_integer(char **ptr, va_list args, int base, int len) {
  bool flag = 1;
  unsigned int *d = va_arg(args, unsigned int *);
  char *ptr_start = *ptr;
  get_base(ptr);
  long val = parse_number(ptr, base, len);
  if (*ptr - ptr_start > 0)
    if (val >= 0 && val <= UINT_MAX)
      *d = (unsigned int)val;
    else
      *d = -1;
  else
    flag = 0;
  return flag;
}

bool handle_string(char **ptr, va_list args, int len) {
  bool flag = 0;
  if (**ptr)
    flag = 1;
  char *s = va_arg(args, char *);
  char *ptr_start = *ptr;
  while (**ptr && **ptr != ' ' && *ptr - ptr_start < len) {
    *s = **ptr;
    (*ptr)++;
    s++;
  }
  *s = '\0';
  return flag;
}

bool handle_pointer(char **ptr, va_list args, int len) {
  bool flag = 1;
  unsigned long *ll = va_arg(args, unsigned long *);
  char *ptr_start = *ptr;
  get_base(ptr);
  unsigned long num = 0;
  bool is_overflow = false;
  while (**ptr && *ptr - ptr_start < len && is_hex(**ptr)) {
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

bool handle_percent(char **str, char **format) {
  bool flag = 1;
  (*format)++;
  if (**str != '%')
    flag = 0;
  else
    (*str)++;
  return flag;
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *ptr_str = (char *)str;
  char *ptr_format = (char *)format;
  va_list args;
  va_start(args, format);

  int count = 0;
  bool success = true;
  while (*ptr_format && *ptr_str && success) {
    skip_whitespace(&ptr_format);
    if (*ptr_format == '%') {
      ptr_format++;
      skip_whitespace(&ptr_str);
      int len = get_len(&ptr_format);
      switch (*ptr_format) {
      case 'c':
        success = handle_char(&ptr_str, args, len);
        break;
      case 'd':
      case 'i':
        success = handle_signed_integer(&ptr_str, args, BASE_DECIMAL, len);
        break;
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        success = handle_float(&ptr_str, args, len);
        break;
      case 'o':
        success = handle_unsigned_integer(&ptr_str, args, BASE_OCTAL, len);
        break;
      case 'u':
        success = handle_unsigned_integer(&ptr_str, args, BASE_DECIMAL, len);
        break;
      case 'x':
      case 'X':
        success = handle_unsigned_integer(&ptr_str, args, BASE_HEX, len);
        break;
      case 's':
        success = handle_string(&ptr_str, args, len);
        break;
      case 'p':
        success = handle_pointer(&ptr_str, args, len);
        break;
      case '%':
        success = handle_percent(&ptr_str, &ptr_format);
        break;
      default:
        success = false;
        break;
      }
      if (success) {
        count++;
        ptr_format++;
      }
    } else if (*ptr_format != *ptr_str) {
      success = false;
    } else {
      ptr_format++;
      ptr_str++;
    }
  }

  va_end(args);
  return count;
}
