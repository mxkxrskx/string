#include "s21_sscanf.h"

#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  int num_parsed = process_format_string(str, format, &args);
  va_end(args);
  return num_parsed;
}

int process_format_string(const char *str, const char *format, va_list *args) {
  char *s = (char *)str;
  char *f = (char *)format;
  int num_parsed = -1;
  bool success = true;

  while (*f && success) {
    if (s21_isspace(*f)) {
      skip_spaces(&s);
      skip_spaces(&f);
    } else if (*f == '%') {
      f++;
      ScanContext ctx = init_scan_context(args, str);
      parse_format_specifier(&s, &ctx, &f);
      if (num_parsed == -1 && ctx.error != NULL_PTR) {
        num_parsed += 1;
      }
      num_parsed += (ctx.suppress || ctx.error != NO_ERROR) ? 0 : 1;
      success = (ctx.error == NO_ERROR || ctx.error == NO_COUNT);
    } else {
      success = match_literal(&s, &f);
    }
  }
  return num_parsed;
}

ScanContext init_scan_context(va_list *args, const char *str) {
  ScanContext ctx;
  ctx.args = args;
  ctx.width = 0;
  ctx.suppress = 0;
  ctx.length = DEFAULT;
  ctx.base = BASE_DECIMAL;
  ctx.error = NO_ERROR;
  ctx.type = SIGNED;
  ctx.str_start = str;
  return ctx;
}

void parse_format_specifier(char **str, ScanContext *ctx, char **f) {
  parse_suppress(ctx, f);
  parse_width(ctx, f);
  parse_length_description(ctx, f);
  parse_specifier(str, ctx, f);
}

bool match_literal(char **s, char **f) {
  bool success = (**s == **f);
  if (success) {
    (*s)++;
    (*f)++;
  }
  return success;
}

void parse_suppress(ScanContext *ctx, char **f) {
  if (**f == '*') {
    ctx->suppress = 1;
    (*f)++;
  }
}

void parse_width(ScanContext *ctx, char **f) {
  ctx->width = 0;
  parse_number(f, 10, &ctx->width, MAXLEN);
  if (ctx->width == 0) {
    ctx->width = MAXLEN;
  }
}

void parse_length_description(ScanContext *ctx, char **f) {
  switch (**f) {
    case 'h':
      ctx->length = SHORT_INT;
      (*f)++;
      break;
    case 'l':
      ctx->length = LONG_INT;
      (*f)++;
      break;
    case 'L':
      ctx->length = LONG_DOUBLE;
      (*f)++;
      break;
  }
}

void parse_specifier(char **str, ScanContext *ctx, char **f) {
  switch (**f) {
    case 'c':
      handle_char_case(str, ctx);
      break;
    case 'd':
      handle_decimal_case(str, ctx);
      break;
    case 'i':
      handle_integer_case(str, ctx);
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      handle_float_case(str, ctx);
      break;
    case 'o':
      handle_octal_case(str, ctx);
      break;
    case 's':
      handle_string_case(str, ctx);
      break;
    case 'u':
      handle_unsigned_case(str, ctx);
      break;
    case 'x':
    case 'X':
      handle_hex_case(str, ctx);
      break;
    case 'p':
      handle_pointer_case(str, ctx);
      break;
    case 'n':
      handle_count_case(str, ctx);
      break;
    case '%':
      handle_percent_case(str, ctx);
      break;
  }
  (*f)++;
}

void handle_char_case(char **str, ScanContext *ctx) {
  parse_char_specifier(str, ctx);
}

void handle_decimal_case(char **str, ScanContext *ctx) {
  parse_decimal_specifier(str, ctx);
}

void handle_integer_case(char **str, ScanContext *ctx) {
  ctx->base = BASE_UNKNOWN;
  parse_decimal_specifier(str, ctx);
}

void handle_float_case(char **str, ScanContext *ctx) {
  parse_float_specifier(str, ctx);
}

void handle_octal_case(char **str, ScanContext *ctx) {
  ctx->base = BASE_OCTAL;
  ctx->type = UNSIGNED;
  parse_decimal_specifier(str, ctx);
}

void handle_string_case(char **str, ScanContext *ctx) {
  parse_string_specifier(str, ctx);
}

void handle_unsigned_case(char **str, ScanContext *ctx) {
  ctx->type = UNSIGNED;
  parse_decimal_specifier(str, ctx);
}

void handle_hex_case(char **str, ScanContext *ctx) {
  ctx->base = BASE_HEX;
  ctx->type = UNSIGNED;
  parse_decimal_specifier(str, ctx);
}

void handle_pointer_case(char **str, ScanContext *ctx) {
  ctx->base = BASE_HEX;
  ctx->type = UNSIGNED;
  ctx->length = LONG_INT;
  parse_decimal_specifier(str, ctx);
}

void handle_count_case(char **str, ScanContext *ctx) {
  set_count_specifier(str, ctx);
}

void handle_percent_case(char **str, ScanContext *ctx) {
  skip_percent(str, ctx);
}

void parse_char_specifier(char **str, ScanContext *ctx) {
  char c = parse_char(str, ctx);
  if (!ctx->suppress && ctx->error == NO_ERROR) {
    *va_arg(*ctx->args, char *) = c;
  }
}

void parse_decimal_specifier(char **str, ScanContext *ctx) {
  long long decimal_integer = parse_decimal_integer(str, ctx);

  if (!ctx->suppress && ctx->error == NO_ERROR) {
    if (ctx->type == SIGNED) {
      set_signed_value(decimal_integer, ctx);
    } else if (ctx->type == UNSIGNED) {
      set_unsigned_value(decimal_integer, ctx);
    }
  }
}

void parse_float_specifier(char **str, ScanContext *ctx) {
  long double floating_point = parse_floating_point(str, ctx);
  if (!ctx->suppress && ctx->error == NO_ERROR) {
    switch (ctx->length) {
      case LONG_DOUBLE:
        *va_arg(*ctx->args, long double *) = (long double)floating_point;
        break;
      default:
        *va_arg(*ctx->args, float *) = (float)floating_point;
        break;
    }
  }
}

void parse_string_specifier(char **str, ScanContext *ctx) {
  skip_spaces(str);
  s21_isnull(str, ctx);

  if (ctx->error == NO_ERROR) {
    char *start_ptr = *str;
    char *destination;
    if (!ctx->suppress) {
      destination = va_arg(*ctx->args, char *);
    }
    bool space_encountered = false;

    while (**str && *str - start_ptr < ctx->width && !space_encountered) {
      if (s21_isspace(**str)) {
        space_encountered = true;
      } else if (!ctx->suppress) {
        *destination = **str;
        destination++;
      }
      (*str)++;
    }

    if (!ctx->suppress) {
      *destination = '\0';
    }

    if (start_ptr == *str) {
      ctx->error = ASSIGN_ERROR;
    }
  }
}

void skip_percent(char **str, ScanContext *ctx) {
  skip_spaces(str);
  s21_isnull(str, ctx);
  if (ctx->error == NO_ERROR) {
    if (**str != '%') {
      ctx->error = NULL_PTR;
    } else {
      ctx->error = NO_COUNT;
      (*str)++;
    }
  }
}

void set_count_specifier(char **str, ScanContext *ctx) {
  *va_arg(*ctx->args, int *) = *str - ctx->str_start;
  ctx->error = NO_COUNT;
}

char parse_char(char **str, ScanContext *ctx) {
  s21_isnull(str, ctx);
  char c = '\0';
  if (ctx->error == NO_ERROR) {
    c = **str;
    (*str)++;
  }
  return c;
}

long long parse_decimal_integer(char **str, ScanContext *ctx) {
  skip_spaces(str);
  s21_isnull(str, ctx);
  long long num = 0;

  if (ctx->error == NO_ERROR) {
    int sign = parse_sign(str, ctx);

    if (ctx->width > 1) {
      int base = parse_base(str);
      if (ctx->base == BASE_UNKNOWN) {
        ctx->base = base;
      }
    } else if (ctx->base == BASE_UNKNOWN) {
      ctx->base = BASE_DECIMAL;
    }

    int shift = skip_base(str, ctx->base);

    ctx->width -= shift;

    int parsed = parse_number(str, ctx->base, &num, ctx->width);

    if (parsed == -1) {
      if (ctx->type == SIGNED)
        num = sign == 1 ? LONG_MAX : LONG_MIN;
      else
        num = ULONG_MAX;
    } else if (parsed + shift == 0) {
      ctx->error = ASSIGN_ERROR;
    }

    if (num != -1) {
      num = sign * num;
    }
  }

  return num;
}

long double parse_floating_point(char **str, ScanContext *ctx) {
  long double result = 0.0;
  skip_spaces(str);
  s21_isnull(str, ctx);

  if (ctx->error == NO_ERROR) {
    char *initial_position = *str;
    int integer_length = 0;
    int fractional_length = 0;
    int sign = parse_sign(str, ctx);

    long long integer_part = 0;
    integer_length = parse_number(str, 10, &integer_part, ctx->width);

    if (integer_length != -1) {
      ctx->width -= integer_length;
      result = integer_part;

      if (ctx->width > 0 && **str == '.') {
        (*str)++;
        ctx->width -= 1;
        long double fractional_part = 0.0;
        fractional_length = parse_fractional_part(str, ctx, &fractional_part);
        result += fractional_part;
      }

      if (ctx->width > 0 && (**str == 'e' || **str == 'E')) {
        (*str)++;
        ctx->width -= 1;
        long double exponent_value = 0.0;
        int exponent_length = parse_exponent_part(str, ctx, &exponent_value);
        result *= exponent_value;
        if (exponent_length < 1) {
          (*str)--;
        }
      }

      result *= sign;
    } else {
      ctx->error = ASSIGN_ERROR;
    }

    if (*str - initial_position == 0 ||
        integer_length + fractional_length == 0) {
      ctx->error = ASSIGN_ERROR;
    }
  }

  return result;
}

void set_signed_value(long long decimal_integer, ScanContext *ctx) {
  switch (ctx->length) {
    case SHORT_INT:
      *va_arg(*ctx->args, short int *) = (short int)decimal_integer;
      break;
    case LONG_INT:
      *va_arg(*ctx->args, long int *) = (long int)decimal_integer;
      break;
    default:
      *va_arg(*ctx->args, int *) = (int)decimal_integer;
      break;
  }
}

void set_unsigned_value(long long decimal_integer, ScanContext *ctx) {
  switch (ctx->length) {
    case SHORT_INT:
      *va_arg(*ctx->args, unsigned short *) = (unsigned short)decimal_integer;
      break;
    case LONG_INT:
      *va_arg(*ctx->args, unsigned long *) = (unsigned long)decimal_integer;
      break;
    default:
      *va_arg(*ctx->args, unsigned int *) = (unsigned int)decimal_integer;
      break;
  }
}

int parse_fractional_part(char **str, ScanContext *ctx, long double *fraction) {
  *fraction = 0.0;
  long long fractional_part = 0;
  int parsed_length = parse_number(str, 10, &fractional_part, ctx->width);

  if (parsed_length != -1) {
    ctx->width -= parsed_length;
    *fraction = fractional_part / pow(10.0, parsed_length);
  } else {
    ctx->error = ASSIGN_ERROR;
  }
  return parsed_length;
}

int parse_exponent_part(char **str, ScanContext *ctx, long double *exponent) {
  *exponent = 1.0;
  int sign = parse_sign(str, ctx);
  long long exponent_value = 0;
  int parsed_length = parse_number(str, 10, &exponent_value, ctx->width);

  if (parsed_length != -1) {
    ctx->width -= parsed_length;
    *exponent = pow(10.0, sign * exponent_value);
  } else {
    ctx->error = ASSIGN_ERROR;
  }
  return parsed_length;
}

void s21_isnull(char **str, ScanContext *ctx) {
  if (*str == NULL || **str == '\0') {
    ctx->error = NULL_PTR;
  }
}

int parse_sign(char **str, ScanContext *ctx) {
  int sign = (**str == '-') ? -1 : 1;
  if (**str == '-' || **str == '+') {
    (*str)++;
    ctx->width--;
  }
  return sign;
}

int parse_base(char **str) {
  int base = BASE_DECIMAL;
  if (**str == '0') {
    if ((*str)[1] == 'x' || (*str)[1] == 'X') {
      base = BASE_HEX;
    } else {
      base = BASE_OCTAL;
    }
  } else if (s21_isdigit(**str)) {
    base = BASE_DECIMAL;
  }
  return base;
}

int skip_base(char **str, int base) {
  int shift = 0;
  switch (base) {
    case BASE_OCTAL:
      if (**str == '0') {
        shift = 1;
      }
      break;
    case BASE_HEX:
      if (**str == '0' && ((*str)[1] == 'x' || (*str)[1] == 'X')) {
        shift = 2;
      }
      break;
  }
  *str += shift;
  return shift;
}
