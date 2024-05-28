#include "s21_sscanf.h"

typedef struct s21_flags {
  int len;
  s21_type type;
  bool asterisk;
} s21_flags;

int get_len(char **format) {
  char *ptr_start = *format;
  int n = parse_number(format, BASE_DECIMAL, INT_MAX);
  if (*format - ptr_start == 0 || n == 0)
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

bool get_asterisk(char **format) {
  bool flag = true;
  if (format && **format == '*')
    (*format)++;
  else
    flag = false;
  return flag;
}

void fill_flags(char **ptr, s21_flags *flags) {
  flags->len = get_len(ptr);
  flags->type = get_type(ptr);
  flags->asterisk = get_asterisk(ptr);
}

void skip_remain_len(char **ptr, char *ptr_start, size_t len) {
  if (ptr && *ptr) {
    char *p = *ptr;
    char *end = ptr_start + len;
    while (p < end && *p != '\0' && len < INT_MAX) {
      p++;
    }
    *ptr = p;
  }
}

void assign_value_char(va_list args, char val, s21_flags flags) {
  if (!flags.asterisk)
    *va_arg(args, char *) = val;
}

bool handle_char(char **ptr, va_list args, s21_flags flags) {
  bool flag = true;
  if (**ptr) {
    assign_value_char(args, **ptr, flags);
    char *ptr_start = *ptr;
    (*ptr)++;
    skip_remain_len(ptr, ptr_start, flags.len);
  } else
    flag = false;
  return flag;
}

bool assign_value_signed_integer(va_list args, long double val, s21_flags flags,
                                 int shift) {
  bool flag = true;
  if (shift == 0)
    flag = false;
  else if (!flags.asterisk) {
    switch (flags.type) {
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
  }
  return flag;
}

bool handle_signed_integer(char **ptr, va_list args, int base,
                           s21_flags flags) {
  skip_whitespace(ptr);
  char *ptr_start = *ptr;
  int sign = get_sign(ptr);

  if (base == BASE_UNKNOWN)
    base = get_base(ptr);

  flags.len -= (*ptr - ptr_start);
  ptr_start = *ptr;

  long double val = sign * parse_number(ptr, base, flags.len);

  bool flag = assign_value_signed_integer(args, val, flags, *ptr - ptr_start);

  return flag;
}

bool assign_value_float(va_list args, long double val, s21_flags flags,
                        int shift) {
  bool flag = true;
  if (shift == 0)
    flag = false;
  else if (!flags.asterisk) {
    switch (flags.type) {
    case LONG_DOUBLE:
      *va_arg(args, long double *) = (long double)val;
      break;
    default:
      *va_arg(args, float *) = (float)val;
      break;
    }
  }
  return flag;
}

bool handle_float(char **ptr, va_list args, s21_flags flags) {
  skip_whitespace(ptr);
  char *ptr_num_start = *ptr;
  int sign = get_sign(ptr);
  int len = flags.len;

  len -= (*ptr - ptr_num_start);
  ptr_num_start = *ptr;

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


  if (*ptr - ptr_num_start == 0 || (*(*ptr - 1) == '.' && *ptr - ptr_num_start == 1))
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

  bool flag = assign_value_float(args, val, flags, *ptr - ptr_num_start);

  return flag;
}

bool assign_value_unsigned_integer(va_list args, long double val,
                                   s21_flags flags, int shift) {
  bool flag = true;
  if (shift == 0)
    flag = false;
  else if (!flags.asterisk) {
    switch (flags.type) {
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
  }
  return flag;
}

bool handle_unsigned_integer(char **ptr, va_list args, int base,
                             s21_flags flags) {
  skip_whitespace(ptr);
  get_sign(ptr);
  char *ptr_start = *ptr;
  get_base(ptr);
  long double val = parse_number(ptr, base, flags.len);
  bool flag = assign_value_unsigned_integer(args, val, flags, *ptr - ptr_start);
  return flag;
}

void assign_value_string(char **ptr, char *s, s21_flags flags) {
  char *ptr_start = *ptr;
  bool space = false;
  while (**ptr && *ptr - ptr_start < flags.len && !space) {
    if (is_space(**ptr)) {
      space = true;
    } else if (!flags.asterisk) {
      *s = **ptr;
      s++;
    }
    (*ptr)++;
  }
  if (!flags.asterisk) {
    *s = '\0';
  }
}

bool handle_string(char **ptr, va_list args, s21_flags flags) {
  bool flag = true;
  if (**ptr) {
    char *s = va_arg(args, char *);
    assign_value_string(ptr, s, flags);
  } else
    flag = false;
  return flag;
}

bool handle_pointer(char **ptr, va_list args, s21_flags flags) {
  skip_whitespace(ptr);
  bool flag = true;
  char *ptr_start = *ptr;
  get_base(ptr);
  unsigned long num = 0;
  bool is_overflow = false;
  while (**ptr && *ptr - ptr_start < flags.len && is_hex(**ptr)) {
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
  if (*ptr - ptr_start == 0)
    flag = false;
  else if (!flags.asterisk)
    *va_arg(args, unsigned long *) = num;
  return flag;
}

bool handle_percent(char **str, char **format) {
  bool flag = true;
  if (**str != '%')
    flag = false;
  else
    (*str)++;
  return flag;
}

bool handle_format_specifier(char **ptr_format, char **ptr_str, va_list args,
                             s21_flags flags, int* count) {
  bool success = false;
  switch (**ptr_format) {
  case 'c':
    success = handle_char(ptr_str, args, flags);
    break;
  case 'd':
    success = handle_signed_integer(ptr_str, args, BASE_DECIMAL, flags);
    break;
  case 'i':
    success = handle_signed_integer(ptr_str, args, BASE_UNKNOWN, flags);
    break;
  case 'e':
  case 'E':
  case 'f':
  case 'g':
  case 'G':
    success = handle_float(ptr_str, args, flags);
    break;
  case 'o':
    success = handle_signed_integer(ptr_str, args, BASE_OCTAL, flags);
    break;
  case 'u':
    success = handle_signed_integer(ptr_str, args, BASE_DECIMAL, flags);
    break;
  case 'x':
  case 'X':
    success = handle_signed_integer(ptr_str, args, BASE_HEX, flags);
    break;
  case 's':
    success = handle_string(ptr_str, args, flags);
    break;
  case 'p':
    success = handle_pointer(ptr_str, args, flags);
    break;
  case '%':
    success = handle_percent(ptr_str, ptr_format);
    break;
  default:
    success = false;
    break;
  }
  if (success) {
    if (!flags.asterisk && **ptr_format != '%')
      (*count)++;
    (*ptr_format)++;
  }
  return success;
}

bool match_literal(char **ptr_format, char **ptr_str) {
  bool flag = true;
  if (**ptr_format != **ptr_str)
    flag = false;
  else {
    (*ptr_format)++;
    (*ptr_str)++;
  }
  return flag;
}

int process_format_string(const char *str, const char *format, va_list args) {
  char *ptr_str = (char *)str;
  char *ptr_format = (char *)format;

  int count = 0;
  bool success = true;

  while (*ptr_format && *ptr_str && success) {
    if (*ptr_format == '%') {
      ptr_format++;

      s21_flags flags = {};
      fill_flags(&ptr_format, &flags);

      if (flags.type != DEFAULT && flags.asterisk)
        success = false;
      else
        success = handle_format_specifier(&ptr_format, &ptr_str, args, flags, &count);

    } else if (is_space(*ptr_format)) {
      skip_whitespace(&ptr_str);
      skip_whitespace(&ptr_format);
    } else {
      success = match_literal(&ptr_format, &ptr_str);
    }
  }
  return count;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int count = process_format_string(str, format, args);

  va_end(args);
  return count;
}
