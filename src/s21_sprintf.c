#include "s21_sprintf.h"

void set_flags(const char *format, Specifiers *spec) {
  char *tmp = (char *)format;
  tmp++;
  while (1) {
    if (s21_strchr("cdieEfgGosuxXpn", *tmp) ||
        (s21_isdigit(*tmp) && *tmp != '0') || *tmp == '.')
      break;
    char *tmp2 = tmp;
    if (*tmp == ' ')
      spec->space = true;
    else if (*tmp == '0' && !s21_isdigit(*(--tmp2)))
      spec->zero = true;
    else if (*tmp == '-')
      spec->minus = true;
    else if (*tmp == '+')
      spec->plus = true;
    else if (*tmp == '#')
      spec->hash = true;
    tmp++;
  }
  if ((spec->minus && spec->zero)) {
    spec->zero = 0;
  }
  if (spec->plus && spec->space) {
    spec->space = 0;
  }
}

void set_width(const char *format, va_list args, Specifiers *spec) {
  char *tmp = (char *)format;
  tmp++;
  while (*tmp) {
    if (*tmp == '*' || (s21_isdigit(*tmp) && *tmp != '0') ||
        s21_strchr("cdieEfgGosuxXpn", *tmp) || *tmp == '.') {
      break;
    }
    tmp++;
  }
  if (*tmp == '*') {
    spec->width = va_arg(args, int);
  } else if (s21_isdigit(*tmp)) {
    spec->width = parse_number1(&tmp, BASE_DECIMAL, INT_MAX);
  }
}

void set_precision(const char *format, va_list args, Specifiers *spec) {
  char *tmp = (char *)format + 1;
  while (!s21_strchr("cdieEfgGosuxXpn", *tmp)) {
    tmp++;
  }
  int flag = 0;
  while (*tmp != '.') {
    tmp--;
    if (*tmp == '%') {
      flag = 1;
      break;
    }
  }
  if (!flag) {
    tmp++;
    if (*tmp == '*') {
      spec->precision = va_arg(args, int);
      spec->set_precision = 1;
    } else {
      spec->precision = parse_number1(&tmp, BASE_DECIMAL, INT_MAX);
      spec->set_precision = 1;
    }
  }
}

void set_length(const char *format, Specifiers *spec) {
  char *tmp = (char *)format;
  while (!s21_strchr("cdieEfgGosuxXpn", *tmp)) {
    tmp++;
  }
  tmp--;
  if (*tmp == 'h' || *tmp == 'l' || *tmp == 'L') {
    spec->length = *tmp;
  }
}

void process_line_with_condition(char str1[BUFF], char str2[BUFF],
                                 Specifiers *spec) {
  int width = spec->width - s21_strlen(str2);
  if (spec->zero && width > 0) {
    getSTRING(str1, str2, '0', width);
  } else if (spec->minus && width > 0) {
    minus_process(str1, str2, spec, width);
  } else if (width > 0 && spec->width != 0) {
    getSTRING(str1, str2, ' ', width);
  } else {
    s21_strncat(str1, str2, s21_strlen(str2));
  }
}

void get_line_c(wchar_t c, Specifiers *spec, char str[BUFF]) {
  char c_line[BUFF] = "\0";
  c_line[0] = c;
  if (spec->space) {
    spec->space = 0;
  }
  process_line_with_condition(str, c_line, spec);
}

void process_c(va_list args, Specifiers *spec, char str[BUFF]) {
#if defined(__linux__)
  spec->zero = 0;
#endif
  if (spec->length == 'l') {
    wchar_t c = va_arg(args, wchar_t);
    get_line_c(c, spec, str);
  } else {
    char c = va_arg(args, int);
    get_line_c(c, spec, str);
  }
}

void getSTRINGfromNUM(int64_t num, int base, char tmp1[], Specifiers *spec) {
  if (spec->specifier == 'u') {
    num = (uint64_t)num;
  }
  char tmp[BUFF] = {'\0'};
  int index = BUFF - 2;
  int64_t temp = num;

  num = num > 0 ? num : -num;
  if (num == 0) {
    tmp[index] = '0';
  }
  while (num > 0) {
    index--;
    tmp[index] = "0123456789abcdef"[num % base];
    num /= base;
  }
  int precision = spec->precision - s21_strlen(tmp + index) -
                  (spec->specifier == 'o' && spec->hash ? 1 : 0);
  if (precision > 0 && spec->precision != 0 &&
      s21_strchr("diouXx", spec->specifier)) {
    while (precision > 0) {
      tmp[--index] = '0';
      precision--;
    }
  }
  if (temp < 0 && spec->specifier != 'u' && spec->specifier != 'p') {
    tmp[--index] = '-';
  }
  if (spec->plus && spec->zero == 0 && temp >= 0 && !spec->fraction &&
      !s21_strchr("ouxX", spec->specifier)) {
    tmp[--index] = '+';
  }
  s21_memcpy(tmp1, tmp + index, s21_strlen(tmp + index));
}

void getSTRING(char str1[BUFF], char str2[BUFF], char c, s21_size_t width) {
  s21_memset(str1, c, width);
  s21_memcpy(str1 + width, str2, s21_strlen(str2));
}

void minus_process(char str1[BUFF], char str2[BUFF], Specifiers *spec,
                   s21_size_t width) {
  s21_memset(str2 + s21_strlen(str2), ' ', width);
  s21_strncpy(str1, str2, s21_strlen(str2) - spec->space);
}

void switchOffSpecU(Specifiers *spec) {
  if (spec->plus || spec->space) {
    spec->plus = false;
    spec->space = false;
  }
}

void process_u(va_list args, Specifiers *spec, char str[BUFF]) {
  uint64_t u = va_arg(args, uint64_t);
  switch (spec->length) {
    case 0:
      u = (uint32_t)u;
      break;
    case 'h':
      u = (uint16_t)u;
  }
  char number[BUFF] = "\0";
  getSTRINGfromNUM(u, BASE_DECIMAL, number, spec);
  switchOffSpecU(spec);
  process_line_with_condition(str, number, spec);
}

void process_d(va_list args, Specifiers *spec, char str[BUFF]) {
  int64_t d = va_arg(args, int64_t);

  switch (spec->length) {
    case 0:
      d = (int32_t)d;
      break;
    case 'h':
      d = (int16_t)d;
      break;
  }
  char number[BUFF] = "\0";
  getSTRINGfromNUM(d, BASE_DECIMAL, number, spec);
  if (number[0] != '-' && spec->space == 1 && spec->minus == 1) {
    str[0] = ' ';
    str++;
  }
  if (spec->space && number[0] != '-' && spec->zero == 0) {
    str[0] = ' ';
  }
  if (spec->space == 1 && number[0] == '-') {
    spec->space = 0;
  }
  process_line_with_condition(str, number, spec);
  if (spec->zero && spec->space && number[0] != '-') {
    str[0] = ' ';
  }
  if (spec->zero && spec->plus && number[0] != '-' && spec->precision == 0) {
    str[0] = '+';
  }
  if (spec->set_precision == 1 && spec->precision == 0 && d == 0) {
    str[0] = '\0';
  }
}

void switchOffSpec(Specifiers *spec) {
  if (spec->plus || spec->zero || spec->space) {
    spec->plus = false;
    spec->zero = false;
    spec->space = false;
  }
  if (spec->precision == spec->width) {
    spec->width = -1;
  }
}

void get_line_s(char str1[BUFF], char str2[BUFF], Specifiers *spec) {
  if (spec->precision != 0) {
    char temp[BUFF] = "\0";
    s21_memcpy(temp, str2, spec->precision);
    temp[spec->precision] = '\0';
    process_line_with_condition(str1, temp, spec);
  } else {
    process_line_with_condition(str1, str2, spec);
  }
}

void process_s(va_list args, Specifiers *spec, char str[BUFF]) {
  switchOffSpec(spec);
  if (spec->length == 'l') {
    wchar_t *s = va_arg(args, wchar_t *);
    if (s) {
      char temp[BUFF] = "\0";
      s21_memset(temp, 0, BUFF - 1);
      wcstombs(temp, s, BUFF);
      get_line_s(str, temp, spec);
    }
  } else {
    char *s = va_arg(args, char *);
    if (s) {
      char temp[BUFF] = "\0";
      s21_memset(temp, 0, BUFF - 1);
      s21_memcpy(temp, s, s21_strlen(s));
      get_line_s(str, temp, spec);
    }
  }
}

void create_left_part(char intpart[BUFF], long double left, long double *right,
                      Specifiers *spec) {
  long double abs_right = fabsl(*right);
  if (fabsl(abs_right - 1000000) <= 0.2) {
    int sign = left < 0 ? -1 : 1;
    left = sign * (fabsl(left) + 1);
    getSTRINGfromNUM((int64_t)left, BASE_DECIMAL, intpart, spec);
    s21_strncat(intpart, ".", 1);
    *right = 0;
  } else {
    getSTRINGfromNUM((int64_t)left, BASE_DECIMAL, intpart, spec);
    s21_strncat(intpart, ".", 1);
  }
  *right = roundl(*right);
}

void delete_zeros(char fracpart[BUFF]) {
  for (s21_size_t i = 0; i < s21_strlen(fracpart); i++) {
    if (fracpart[i] == '0') {
      fracpart[i] = '\0';
      break;
    }
  }
}

void create_right_part(char fracpart[BUFF], long double right, Specifiers *spec,
                       int zeros) {
  spec->fraction = 1;
  int64_t fraction = (double)fabsl(right);
  s21_memset(fracpart, '0', DEFAULT_PRECISION);
  getSTRINGfromNUM(fraction, BASE_DECIMAL, fracpart + zeros, spec);
  if (spec->precision < DEFAULT_PRECISION) {
    fracpart[spec->precision - 1] = fracpart[spec->precision];
    fracpart[spec->precision] = '\0';
  } else {
    fracpart[spec->precision] = '\0';
  }
  if (spec->specifier == 'g' || spec->specifier == 'G') {
    delete_zeros(fracpart);
  }
  spec->fraction = 0;
}

void getSTRINGfromF(long double f, Specifiers *spec, char str[BUFF]) {
  long double left = 0.0;
  long double right = modfl(f, &left);
  int zeros = 0;
  int flag = 1;
  spec->precision > 15 ? spec->precision = 15 : 0;
  int precision =
      spec->precision > DEFAULT_PRECISION ? spec->precision : DEFAULT_PRECISION;
  for (int i = 0; i < precision; i++) {
    right *= 10.0;
    if (fabsl(right) < 0.9999 && flag) {
      zeros++;
    } else {
      flag = 0;
    }
  }
  char intpart[BUFF] = "\0";
  create_left_part(intpart, left, &right, spec);

  char fracpart[BUFF] = "\0";
  create_right_part(fracpart, right, spec, zeros);

  s21_strncat(intpart, fracpart, s21_strlen(fracpart));
  if (intpart[s21_strlen(intpart) - 1] == '.') {
    intpart[s21_strlen(intpart) - 1] = '\0';
  }
  s21_strncat(str, intpart, s21_strlen(intpart));
}

char *commonAction(long double *x, Specifiers *spec, va_list args) {
  if (spec->length == 'L') {
    *x = va_arg(args, long double);
  } else {
    *x = va_arg(args, double);
  }
  if (spec->precision == 0 && spec->set_precision == 0) {
    spec->precision = DEFAULT_PRECISION;
  }

  char *error_massage = S21_NULL;
  if (isnan(*x)) {
#if defined(__linux__)
    if (signbit(*x)) {
      error_massage = "-nan";
    } else {
      error_massage = "nan";
    }
#else
    error_massage = "nan";
#endif
  } else if (isinf(*x) && signbit(*x)) {
    error_massage = "-inf";
  } else if (isinf(*x) && !signbit(*x)) {
    error_massage = "inf";
  } else if (isnan(*x) && spec->specifier == 'f') {
    error_massage = "nan";
  }
  return error_massage;
}

void process_normal_f(char number[BUFF], char str[BUFF], Specifiers *spec) {
  if (number[0] != '-' && spec->space == 1 && spec->minus == 1) {
    str[0] = ' ';
    str++;
  }
  if (spec->space == 1 && number[0] == '-') {
    spec->space = 0;
  }
  if (spec->zero && spec->plus && number[0] != '-') {
    str[0] = '+';
  }
  process_line_with_condition(str, number, spec);
  if (spec->zero && spec->plus && number[0] != '-') {
    str[0] = '+';
  }
}

void process_f(va_list args, Specifiers *spec, char str[BUFF]) {
  long double f = 0.0;
  char *error = commonAction(&f, spec, args);
  if (error) {
    s21_strncat(str, error, s21_strlen(error));
  } else {
    char number[BUFF] = "\0";
    getSTRINGfromF(f, spec, number);
    if (spec->space && number[0] != '-' && spec->zero == 0) {
      str[0] = ' ';
    }
    process_normal_f(number, str, spec);
  }
}

void postfix_process(int postfix, Specifiers *spec, char postfix_number[BUFF],
                     char c) {
  spec->sign_prefix = c;
  if (postfix >= 0 && postfix < 10) {
    postfix_number[0] = c;
    postfix_number[1] = '0';
    postfix_number[2] = '0' + postfix;
    postfix_number[3] = '\0';
  } else {
    postfix_number[0] = c;
    getSTRINGfromNUM(postfix, BASE_DECIMAL, postfix_number + 1, spec);
  }
}

void getEnumber(char str[BUFF], char number[BUFF], char postfix[BUFF]) {
  s21_strncat(str, number, s21_strlen(number));
  s21_strncat(str, "e", 2);
  s21_strncat(str, postfix, s21_strlen(postfix));
}

void getSTRINGfromE(long double e, Specifiers *spec, char sign,
                    char str[BUFF]) {
  char number[BUFF] = "\0";
  getSTRINGfromF(e, spec, number);

  char postfix_d[BUFF] = "\0";
  postfix_process(spec->postfix, spec, postfix_d, sign);

  //собираем число
  getEnumber(str, number, postfix_d);
}

int postfix_minus(long double *e) {
  int postfix = 0;
  while ((int)*e != 0) {
    *e /= 10.0;
    postfix++;
  }
  *e *= 10;
  if (postfix != 0) postfix--;
  return postfix;
}

void getSTRINGfromEPLUS(long double e, Specifiers *spec, char str[BUFF]) {
  spec->postfix = postfix_minus(&e);
  getSTRINGfromE(e, spec, '+', str);
}

int postfix_plus(double long *e) {
  int postfix = 0;
  while ((int)*e == 0) {
    *e *= 10.0;
    postfix++;
  }
  return postfix;
}

void getSTRINGfromEMINUS(long double e, Specifiers *spec, char str[BUFF]) {
  spec->postfix = postfix_plus(&e);
  getSTRINGfromE(e, spec, '-', str);
}

void process_e(va_list args, Specifiers *spec, char str[BUFF]) {
  long double e = 0.0;
  char *error = commonAction(&e, spec, args);
  if (error) {
    s21_strncat(str, error, s21_strlen(error));
  } else {
    char number[BUFF] = "\0";
    if ((int)e == 0) {
      getSTRINGfromEMINUS(e, spec, number);
    } else {
      getSTRINGfromEPLUS(e, spec, number);
    }
    process_normal_f(number, str, spec);
  }
}

int starting_frac(char const number[BUFF]) {
  int start_frac = 0;
  while (number[start_frac] != '.' && number[start_frac] != '\0') {
    start_frac++;
  }
  return start_frac;
}

void round_last_digit(char *buff, Specifiers *spec) {
  int precision = spec->precision;
  int sig_digs = 0;
  s21_size_t len = s21_strlen(buff);
  int not_zero_found = 0;
  for (s21_size_t i = 0; i < s21_strlen(buff); i++) {
    if ((buff[i] == '0' && !not_zero_found) || buff[i] == '.')
      continue;
    else
      not_zero_found = 1;
    if (isdigit(buff[i]) && not_zero_found) {
      sig_digs++;
    }
    if (sig_digs == precision && i + 1 < len) {
      int next = buff[i + 1] == '.' ? 2 : 1;
      buff[i] = buff[i + next] - '0' > 5 && buff[i] != '9' ? (char)(buff[i] + 1)
                                                           : buff[i];
      buff[i + 1] = '\0';
      break;
    }
  }
}

bool count_nines(char *fracpart) {
  int count = 1;
  bool flag = 1;
  for (; *fracpart++;) {
    if (*fracpart == '9') {
      count++;
    }
  }
  if (count >= 5) {
    flag = 0;
  }
  return flag;
}

bool is_e_in_str(char *string) {
  bool flag = 0;
  while (*string++) {
    if ('e' == *string) {
      flag = 1;
      break;
    }
  }
  return flag;
}

void handle_float_G(char float_number[BUFF], Specifiers *spec) {
  s21_size_t frac_len = s21_strlen(float_number + starting_frac(float_number));
  bool firstCondition = frac_len < DEFAULT_PRECISION;
  bool secondCondition = float_number[s21_strlen(float_number)] == '9';

  if (!(firstCondition && secondCondition))
    round_last_digit(float_number, spec);
}

void handle_science_number(char science_number[BUFF], Specifiers *spec) {
  round_last_digit(science_number, spec);
  if (!is_e_in_str(science_number)) {
    char postfix[BUFF] = "\0";
    postfix_process(spec->postfix, spec, postfix, spec->sign_prefix);
    s21_strncat(science_number, "e", 2);
    s21_strncat(science_number, postfix, s21_strlen(postfix));
  }
}

void create_science_number(char science_number[BUFF], Specifiers *spec,
                           long double g) {
  if ((int)g == 0) {
    getSTRINGfromEMINUS(g, spec, science_number);
  } else {
    getSTRINGfromEPLUS(g, spec, science_number);
  }
}

void process_g(va_list args, Specifiers *spec, char str[BUFF]) {
  long double g = 0.0;
  char *error = commonAction(&g, spec, args);
  if (error) {
    s21_strncat(str, error, s21_strlen(error));
  } else {
    char science_number[BUFF] = "\0";
    create_science_number(science_number, spec, g);

    if (spec->postfix < 4) {
      char float_number[BUFF] = "\0";
      getSTRINGfromF(g, spec, float_number);

      handle_float_G(float_number, spec);
      process_normal_f(float_number, str, spec);
    } else {
      handle_science_number(science_number, spec);
      process_normal_f(science_number, str, spec);
    }
  }
}

void process_o(va_list args, Specifiers *spec, char str[BUFF]) {
  int64_t o = va_arg(args, int64_t);
  char octal[BUFF] = "0";
  getSTRINGfromNUM(o, BASE_OCTAL, octal + spec->hash, spec);
  process_line_with_condition(str, octal, spec);
}

void process_hex_hash(char str[BUFF], Specifiers *spec) {
  if (spec->hash && spec->zero) {
    char *temp = str;
    while (*temp++) {
      if (*temp == 'x') {
        *temp = '0';
        break;
      }
    }
    str[0] = '0';
    str[1] = 'x';
  }
}

void process_x(va_list args, Specifiers *spec, char str[BUFF]) {
  uint64_t x = va_arg(args, uint64_t);
  switch (spec->length) {
    case 0:
      x = (uint32_t)x;
      break;
    case 'h':
      x = (uint16_t)x;
      break;
    case 'l':
      x = (uint64_t)x;
      break;
  }
  char hex[BUFF] = "\0";
  if (spec->hash && x != 0) {
    hex[0] = '0';
    hex[1] = 'x';
  } else {
    spec->hash = 0;
  }
  char temp[BUFF] = "\0";
  getSTRINGfromNUM(x, BASE_HEX, hex + spec->hash + spec->hash, spec);
  process_line_with_condition(temp, hex, spec);
  process_hex_hash(temp, spec);
  if (spec->specifier == 'X') {
    void *ptemp = s21_to_upper(temp);
    if (ptemp != S21_NULL) {
      s21_memcpy(temp, (char *)ptemp, s21_strlen(temp));
      free(ptemp);
    }
  }
  s21_strncpy(str, temp, s21_strlen(temp));
}

void process_p(va_list args, Specifiers *spec, char str[BUFF]) {
  uint64_t p = va_arg(args, uint64_t);
  char pointer[BUFF] = "\0";
  pointer[0] = '0';
  pointer[1] = 'x';
  if (!p) {
#if defined(__linux__)
    s21_memcpy(pointer, "(nil)", 6);
    process_line_with_condition(str, pointer, spec);
#endif
#if defined(__APPLE__) && defined(__MACH__)
    s21_memcpy(pointer, "0x0", 4);
    process_line_with_condition(str, pointer, spec);
#endif
  } else {
    getSTRINGfromNUM(p, BASE_HEX, pointer + 2, spec);
#if defined(__linux__)
    if (pointer[0] != '-' && spec->space == 1) {
      str[0] = ' ';
      str++;
    }
    if (spec->zero && spec->plus && pointer[0] != '-' && spec->precision == 0) {
      str[0] = '+';
    }
#endif
    process_line_with_condition(str, pointer, spec);
  }
}

void handle_specifier(const char *format, Specifiers *spec, va_list args,
                      char str[BUFF]) {
  char *tmp = (char *)format;
  while (!s21_strchr("cdieEfgGosuxXpn", *tmp)) {
    tmp++;
  }
  spec->specifier = *tmp;
  if (*tmp == 'c') {
    process_c(args, spec, str);
  } else if (*tmp == 'd' || *tmp == 'i') {
    process_d(args, spec, str);
  } else if (*tmp == 'f') {
    process_f(args, spec, str);
  } else if (*tmp == 's') {
    process_s(args, spec, str);
  } else if (*tmp == 'u') {
    process_u(args, spec, str);
  } else if (*tmp == 'e' || *tmp == 'E') {
    process_e(args, spec, str);
  } else if (*tmp == 'g' || *tmp == 'G') {
    process_g(args, spec, str);
  } else if (*tmp == 'o') {
    process_o(args, spec, str);
  } else if (*tmp == 'x' || *tmp == 'X') {
    process_x(args, spec, str);
  } else if (*tmp == 'p') {
    process_p(args, spec, str);
  }
}

void skip_spec_line(const char **format, char **str, Specifiers *spec) {
  while (1) {
    if (spec->specifier == '%') {
      **str = **format;
      *str += 1;
    }
    *format += 1;
    if (s21_strchr("cdieEfgGosuxXpn", **format) || **format == '%') {
      *format += 1;
      break;
    }
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  char *str_beg = str;
  while (*format) {
    char temp[BUFF] = "\0";
    Specifiers spec = {0};
    char *tmp = (char *)format;
    tmp++;
    if (*format == '%' && *tmp != '%') {
      set_flags(format, &spec);
      set_width(format, args, &spec);
      set_precision(format, args, &spec);
      set_length(format, &spec);
      handle_specifier(format, &spec, args, temp);

      if (spec.specifier == 'n') {
        *(va_arg(args, int *)) = str - str_beg;
      }

      s21_memcpy(str, temp, s21_strlen(temp));

      str += s21_strlen(temp);
      skip_spec_line(&format, &str, &spec);
    }
    if (*format == '%' && *tmp == '%') {
      *str = '%';
      format += 2;
      str++;
    }
    if (*format == '\0') {
      break;
    }
    if (*format == '%') {
      continue;
    } else {
      *str++ = *format++;
    }
  }
  *str = '\0';
  va_end(args);
  return str - str_beg;
}
