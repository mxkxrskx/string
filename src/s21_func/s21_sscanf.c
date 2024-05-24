#include "s21_sscanf.h"

int get_len(char **ptr) {
  char *ptr_start = *ptr;
  int n = parse_number(ptr, BASE_DECIMAL, INT_MAX);
  if (*ptr - ptr_start == 0 || n == 0)
    n = INT_MAX;
  return n;
}

s21_type get_type(char **format) {
  s21_type type = DEFAULT;
  switch (**format) {
  case 'h':
    type = SHORT_INT;
    (*format)++;
    break;
  case 'l':
    type = LONG_INT;
    (*format)++;
    break;
  case 'L':
    type = LONG_DOUBLE;
    (*format)++;
    break;
  }
  return type;
}

bool handle_char(char **ptr, va_list args, int len) {
  bool flag = true;
  if (**ptr) {
    *va_arg(args, char *) = **ptr;
    char *ptr_start = *ptr;
    (*ptr)++;
    while (**ptr && *ptr - ptr_start < len && len != INT_MAX) {
      (*ptr)++;
    }
  } else
    flag = false;
  return flag;
}

bool assign_value_signed_integer(va_list args, long double val, s21_type type,
                                 int shift) {
  bool flag = true;
  if (shift > 0) {
    switch (type) {
    case SHORT_INT:
      if (val >= SHRT_MIN && val <= SHRT_MAX)
        *va_arg(args, short int *) = (short int)val;
      else
        *va_arg(args, short int *) = -1;
      break;
    case LONG_INT:
      if (val >= LONG_MIN && val <= LONG_MAX)
        *va_arg(args, long int *) = (long int)val;
      else
        *va_arg(args, long int *) = -1;
      break;
    default:
      if (val >= INT_MIN && val <= INT_MAX)
        *va_arg(args, int *) = (int)val;
      else
        *va_arg(args, int *) = -1;
      break;
    }
  } else
    flag = false;
  return flag;
}

bool handle_signed_integer(char **ptr, va_list args, int base, int len,
                           s21_type type) {
  int sign = get_sign(ptr);
  char *ptr_start = *ptr;
  if (base == BASE_UNKNOWN)
    base = get_base(ptr);
  long double val = sign * parse_number(ptr, base, len);
  return assign_value_signed_integer(args, val, type, *ptr - ptr_start);
}

bool assign_value_float(va_list args, long double val, s21_type type,
                        int shift) {
  bool flag = true;
  if (shift > 0) {
    switch (type) {
    case LONG_DOUBLE:
      *va_arg(args, long double *) = (long double)val;
      break;
    default:
      *va_arg(args, float *) = (float)val;
      break;
    }
  } else
    flag = false;
  return flag;
}

bool handle_float(char **ptr, va_list args, int len, s21_type type) {
  char *ptr_num_start = *ptr;
  int sign = get_sign(ptr);
  if (*ptr - ptr_num_start > 0) {
    ptr_num_start = *ptr;
    len--;
  }

  long double mantissa = parse_number(ptr, BASE_DECIMAL, len);
  len -= *ptr - ptr_num_start;
  if (**ptr == '.' && len > 0) {
    (*ptr)++;
    len--;
    char *ptr_point_start = *ptr;
    long double decimal_digits = parse_number(ptr, BASE_DECIMAL, len);
    int decimal_exp = *ptr - ptr_point_start;
    len -= decimal_exp;
    mantissa += decimal_digits * pow(10.0, -decimal_exp);
  }

  if (*ptr - ptr_num_start == 0)
    return false;

  int exponent = 0;
  if ((**ptr == 'e' || **ptr == 'E') && len > 0) {
    char *temp_ptr = *ptr;
    (*ptr)++;

    int sign_e = get_sign(ptr);
    len -= *ptr - temp_ptr;
    char *ptr_point_start = *ptr;
    long double number_e = parse_number(ptr, BASE_DECIMAL, len);
    if (*ptr - ptr_point_start > 0)
      exponent = sign_e * number_e;
    else
      *ptr = temp_ptr;
  }

  long double val = mantissa * pow(10.0, exponent) * sign;

  return assign_value_float(args, val, type, *ptr - ptr_num_start);
}

bool assign_value_unsigned_integer(va_list args, long double val, s21_type type,
                                   int shift) {
  bool flag = true;
  if (shift > 0) {
    switch (type) {
    case SHORT_INT:
      if (val >= 0 && val <= USHRT_MAX)
        *va_arg(args, unsigned short int *) = (unsigned short int)val;
      else
        *va_arg(args, unsigned short int *) = -1;
      break;
    case LONG_INT:
      if (val >= 0 && val <= ULONG_MAX)
        *va_arg(args, unsigned long int *) = (unsigned long int)val;
      else
        *va_arg(args, unsigned long int *) = -1;
      break;
    default:
      if (val >= 0 && val <= UINT_MAX)
        *va_arg(args, unsigned int *) = (unsigned int)val;
      else
        *va_arg(args, unsigned int *) = -1;
      break;
    }
  } else
    flag = false;
  return flag;
}

bool handle_unsigned_integer(char **ptr, va_list args, int base, int len,
                             s21_type type) {
  char *ptr_start = *ptr;
  get_base(ptr);
  long double val = parse_number(ptr, base, len);
  return assign_value_unsigned_integer(args, val, type, *ptr - ptr_start);
}

bool handle_string(char **ptr, va_list args, int len) {
  bool flag = false;
  if (**ptr)
    flag = true;
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
  bool flag = true;
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
    *va_arg(args, unsigned long *) = num;
  else
    flag = false;
  return flag;
}

bool handle_percent(char **str, char **format) {
  bool flag = true;
  (*format)++;
  if (**str != '%')
    flag = false;
  else
    (*str)++;
  return flag;
}

int s21_sscanf(const char *str, const char *format, ...) {
  char *ptr_str = (char *)str;
  char *ptr_format = (char *)format;
  va_list args;
  va_start(args, format);

  int count = -1;
  bool success = true;
  skip_whitespace(&ptr_str);
  while (*ptr_format && *ptr_str && success) {
    skip_whitespace(&ptr_format);
    if (*ptr_format == '%') {
      ptr_format++;
      skip_whitespace(&ptr_str);
      int len = get_len(&ptr_format);
      s21_type type = get_type(&ptr_format);
      switch (*ptr_format) {
      case 'c':
        success = handle_char(&ptr_str, args, len);
        break;
      case 'd':
      case 'i':
        success =
            handle_signed_integer(&ptr_str, args, BASE_DECIMAL, len, type);
        break;
      case 'e':
      case 'E':
      case 'f':
      case 'g':
      case 'G':
        success = handle_float(&ptr_str, args, len, type);
        break;
      case 'o':
        success =
            handle_unsigned_integer(&ptr_str, args, BASE_OCTAL, len, type);
        break;
      case 'u':
        success =
            handle_unsigned_integer(&ptr_str, args, BASE_DECIMAL, len, type);
        break;
      case 'x':
      case 'X':
        success = handle_unsigned_integer(&ptr_str, args, BASE_HEX, len, type);
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
        if (count < 0)
          count++;
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
