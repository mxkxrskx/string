#include "s21_sprintf.h"

static int count = 0;
// Функция sprintf может вернуть отрицательное значение в случае ошибки. В частности, она может вернуть:
// -1: Это указывает на то, что произошла ошибка во время форматирования строки, например, недостаточно места в буфере для записи результата. В этом случае результат в буфер не записывается.
// -2: Это возвращается, если какой-либо из аргументов функции sprintf является нулевым указателем.

int main() {
  // Suite *suite_array[] = {suite_sprintf_flags_d(), suite_sprintf_flags_c(), suite_sprintf_flags_u(), suite_sprintf_flags_s(), suite_sprintf_flags_f(), suite_sprintf_flags_i()};
  // for (unsigned long i = 0; i < sizeof(suite_array) / sizeof(suite_array[0]);
  //      i++) {
  //   run_testcase(suite_array[i]);
  //   printf("\n");
  // }

  char str[BUFF] = "\0";
  char str1[BUFF] = "\0";
  double x = 0.0000123123;
  char *format = "%+25.1e\n";
  // s21_sprintf(str1, format, x);
  // printf("s21 = %s", str1);
  sprintf(str, format, x);
  printf("orig = %s", str);

}

void set_flags(const char *format, Specifiers *spec) {
    char *tmp = (char *)format;
    tmp++;
    while(1){
      char *tmp2 = tmp;
      if (*tmp == ' ') spec->space = true;
      else if(*tmp == '0' && !is_digit(*(--tmp2))) spec->zero = true;
      else if(*tmp == '-') spec->minus = true;
      else if(*tmp == '+') spec->plus = true;
      else{
        spec->space = true;
      }
      tmp++;
      if(s21_strchr("cdieEfgGosuxXpn", *tmp) || (is_digit(*tmp) && *tmp != '0') || *tmp == '.') break;
    }
    if((spec->minus && spec->zero)){
      spec->zero = 0;
    }
    if(spec->plus && spec->space){
      spec->space = 0;
    }
}

void set_width(const char *format, va_list args, Specifiers *spec) {
  char *tmp = (char *)format;
  tmp++;
  while(*tmp){
    if((is_digit(*tmp) && *tmp != '0' )|| *tmp == '*'){
      break;
    }
    tmp++;
  }
  if (*tmp == '*') {
    spec->width = va_arg(args, int);
  } else if(is_digit(*tmp)){
    spec->width = parse_number(&tmp, 10, INT_MAX);
  }
}

void set_precision(const char *format, va_list args, Specifiers *spec) {
  char *tmp = (char *)format + 1;
  while (!s21_strchr("cdieEfgGosuxXpn", *tmp)) {
    if (*tmp == '.') {
      tmp++;
      if (*tmp == '*') {
        spec->precision = va_arg(args, int);
      } else {
        spec->precision = parse_number(&tmp, 10, INT_MAX);
      }
      break;
    }
    tmp++;
  }
}

void set_length(const char *format, Specifiers *spec) {
  char *tmp = (char *)format;
  while (!s21_strchr("cdieEfgGosuxXpn", *tmp)) {
    tmp++;
  }
  tmp--;
  if (*tmp == 'h' || *tmp == 'l') {
    spec->length = *tmp;
  }
}

void process_line_with_condition(char str1[BUFF], char str2[BUFF], Specifiers *spec){
  int width = spec->width - s21_strlen(str2);
  if(spec->zero && width > 0){
    getSTRING(str1, str2, '0', width);
  }
  else if(spec->minus && width > 0){
    minus_process(str1, str2, spec, width);
  }
  else if(width > 0 && spec->width != 0){
    getSTRING(str1, str2, ' ', width);
  }
  else{
    s21_strncat(str1, str2, s21_strlen(str2));
  }
}

void get_line_c(wchar_t c, Specifiers *spec, char str[BUFF]){
  char c_line[BUFF] = "\0";
  c_line[0] = c;
  if(spec->space){
    spec->space = 0;
  }
  process_line_with_condition(str, c_line, spec);
}

void process_c(va_list args, Specifiers *spec, char str[BUFF]){
    if(spec->length == 'l'){
        wchar_t c = va_arg(args, wchar_t);
        get_line_c(c, spec, str);
    }
    else{
        char c = va_arg(args, int);
        get_line_c(c, spec, str);
    }
}

void getSTRINGfromNUM(int64_t num, int base, char tmp1[BUFF], Specifiers *spec){
    if(spec->specifier == 'u'){
      num = (uint64_t)num;
    }
    char tmp[BUFF] = "\0";
    int index = BUFF - 2;
    int temp = num;
    num = num > 0 ? num : -num;
    if(num == 0){
        tmp[index] = '0';
    }
    while(num > 0){
        tmp[--index] = "0123456789abcdef"[num%base];
        num/= base;
    }
    int precision = spec->precision - s21_strlen(tmp+index);
    if(precision > 0 && spec->precision != 0 && spec->specifier == 'd'){
      while(precision > 0){
        tmp[--index] = '0';
        precision--;
      }
    }
    if(temp < 0 && spec->specifier != 'u'){
        tmp[--index] = '-';
    }
    if(spec->plus && spec->zero == 0 && temp >= 0 && spec->specifier != 'u'){
      tmp[--index] = '+';
    }
    s21_strncat(tmp1, tmp+index, s21_strlen(tmp+index));
}

void getSTRING(char str1[BUFF], char str2[BUFF], char c, s21_size_t width) {
    s21_memset(str1, c, width);
    s21_strncpy(str1+width,str2, s21_strlen(str2));
}

void minus_process(char str1[BUFF], char str2[BUFF], Specifiers *spec, s21_size_t width){
  s21_memset(str2+s21_strlen(str2), ' ', width);
  s21_strncpy(str1, str2, s21_strlen(str2)-spec->space);
}

void process_u(va_list args, Specifiers *spec, char str[BUFF]){
  uint64_t u = va_arg(args, uint64_t);
  switch (spec->length)
  {
  case 0:
    u = (uint32_t)u;
    break;
  case 'h':
    u = (uint16_t)u;
  }
  char number[BUFF] = "\0";
  getSTRINGfromNUM(u, 10, number, spec);
  if(spec->plus || spec->space){
    spec->plus = false;
    spec->space = false;
  }
  process_line_with_condition(str, number, spec);
}

void process_d(va_list args, Specifiers *spec, char str[BUFF]){
    int64_t d = va_arg(args, int64_t);
    switch(spec->length){
        case 0:
            d = (int32_t)d;
            break;
        case 'h':
            d = (int16_t)d;
            break;
    }
    char number[BUFF] = "\0";
    getSTRINGfromNUM(d, 10, number, spec);
    if(number[0] != '-' && spec->space == 1 && spec->minus == 1){
      str[0] = ' ';
      str++;
    }
    if(spec->space == 1 && number[0] == '-'){
      spec->space = 0;
    }
    process_line_with_condition(str, number, spec);
    if(spec->zero && spec->space && number[0] != '-'){
      str[0] = ' ';
    }
    if(spec->zero && spec->plus && number[0] != '-' && spec->precision == 0){
      str[0] = '+';
    }
}

void switchOffSpec(Specifiers *spec){
  if (spec->plus || spec->zero || spec->space) {
      spec->plus = false;
      spec->zero = false;
      spec->space = false;
  }
  if(spec->precision == spec->width){
    spec->width = -1;
  }
}

void get_line_s(char str1[BUFF], char str2[BUFF], Specifiers *spec){
  if(spec->precision != 0){
    char temp[BUFF] = "\0";
    s21_memcpy(temp, str2, spec->precision);
    temp[spec->precision] = '\0';
    process_line_with_condition(str1, temp, spec);
  }
  else{
    process_line_with_condition(str1, str2, spec);
  }
}

void process_s(va_list args, Specifiers *spec, char str[BUFF]){
  switchOffSpec(spec);
  if(spec->length == 'l'){
    wchar_t *s = va_arg(args, wchar_t *);
    char temp[BUFF] = "\0";
    wcstombs(temp, s, BUFF);
    get_line_s(str, temp, spec);
  }
  else{
    char *s = va_arg(args, char *);
    char temp[BUFF] = "\0";
    s21_memcpy(temp, s, s21_strlen(s));
    get_line_s(str, temp, spec);
  }
}

void getSTRINGfromF(long double f, Specifiers *spec, char str[BUFF]){
    long double left = 0.0;
    long double right = modfl(f, &left);
    for(int i = 0; i < spec->precision; i++){
      right *= 10.0;
    }
    char intpart[BUFF] = "\0";
    if((int)(roundl(right)-right) == 1 && (int)right != 0){
      getSTRINGfromNUM(((int64_t)left)+1, 10, intpart, spec);
      s21_strncat(intpart, ".", 1);
      right = 0;
    }
    else{
      getSTRINGfromNUM((int64_t)left, 10, intpart, spec);
      s21_strncat(intpart, ".", 1);
    }
    right = roundl(right);
    char fracpart[BUFF] = "\0";
    int64_t farction = (double)fabsl(right);
    getSTRINGfromNUM(farction, 10, fracpart, spec);
    if(fracpart[0] == '0' || fracpart[0] == '+'){
      s21_memset(fracpart, '0', spec->precision);
    }
    s21_strncat(intpart, fracpart, s21_strlen(fracpart));
    s21_strncat(str, intpart, s21_strlen(intpart));
}

char *commonAction(long double *x, Specifiers *spec, va_list args){
  if(spec->length == 'L'){
    *x = va_arg(args, long double);
  }
  else{
    *x = va_arg(args, double);
  }
  if(spec->precision == 0){
    spec->precision = 6;
  }
  char *error_massage = S21_NULL;
  if (isnan(*x) && signbit(*x)) {
    error_massage = "-nan";
  } else if (isnan(*x) && !signbit(*x)) {
      error_massage = "nan";
  } else if (isinf(*x) && signbit(*x)) {
      error_massage = "-inf";
  } else if (isinf(*x) && !signbit(*x)) {
      error_massage = "inf";
  }
  return error_massage;
}

void process_normal_f(char number[BUFF], char str[BUFF], Specifiers *spec, long double f){
  getSTRINGfromF(f, spec, number);
  if(number[0] != '-' && spec->space == 1 && spec->minus == 1){
    str[0] = ' ';
    str++;
  }
  if(spec->space == 1 && number[0] == '-'){
    spec->space = 0;
  }
  if(spec->zero && spec->plus && number[0] != '-'){
    str[0] = '+';
  }
  process_line_with_condition(str, number, spec);
  if(spec->zero && spec->plus && number[0] != '-'){
    str[0] = '+';
  }
  if(spec->zero && spec->space && number[0] != '-'){
    str[0] = ' ';
  }
}

void process_f(va_list args, Specifiers *spec, char str[BUFF]){
  long double f = 0.0;
  char *error = commonAction(&f, spec, args);
  if(error){
    s21_strncat(str, error, s21_strlen(error));
  }
  else{
    char number[BUFF] = "\0";
    process_normal_f(number, str, spec, f);
  }
}

void getSTRINGfromEPLUS(long double e, Specifiers *spec, char str[BUFF]){
  int postfix = 0;
  while((int)e != 0){
    e/=10.0;
    postfix++;
  }
  e*=10;
  if(postfix != 0) postfix--;
  char temp[BUFF] = "\0";
  getSTRINGfromF(e, spec, temp);
  char postfix_d[BUFF] = "\0";
  if(postfix > 0 || postfix < 10){
    postfix_d[1] = '0';
    postfix_d[2] = '\0';
  }
  postfix_d[0] = '+';
  getSTRINGfromNUM(postfix, 10, postfix_d, spec);
  s21_strncat(str, temp, s21_strlen(temp));
  s21_strncat(str, &spec->specifier,  2);
  s21_strncat(str, postfix_d, s21_strlen(postfix_d));
}

void process_e(va_list args, Specifiers *spec, char str[BUFF]){
  long double e = 0.0;
  char *error = commonAction(&e, spec, args);
  if(error){
    s21_strncat(str, error, s21_strlen(error));
  }
  else{
    char number[BUFF] = "\0";
    if((int)e == 0){

    }
    else{
      getSTRINGfromEPLUS(e, spec, str);

    }
  }
}



void process_g(va_list args, Specifiers *spec, char str[BUFF]){
  long double g = 0.0;
  char *error = commonAction(&g, spec, args);
  if(error){
    s21_strncat(str, error, s21_strlen(error));
  }
  else{
    char number[BUFF] = "\0";
    //getSTRINGfromG(g, spec, str);
  }
}


void set_spec(const char *format, Specifiers *spec, va_list args,  char str[BUFF]) {
  char *tmp = (char *)format;
  while (1) {
    tmp++;
    if(s21_strchr("cdieEfgGosuxXpn", *tmp)){
      spec->specifier = *tmp;
      break;
    }
  }
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
  } else if(*tmp == 'e' || *tmp == 'E'){
    process_e(args, spec, str);
  } else if(*tmp == 'g' || *tmp == 'G'){
    process_g(args, spec, str);
  }
}

void skip_spec_line(const char **format){
  while(1){
    *format+=1;
    if(s21_strchr("cdieEfgGosuxXpn", **format)){
      *format+=1;
      break;
    }
  }
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list args;
  va_start(args, format);
  //int count = 0;
  char *str_beg = str;
  while (*format) {
    char temp[BUFF] = "\0";
    Specifiers spec = {0};

    if (*format == '%') {
      set_flags(format, &spec);
      set_width(format, args, &spec);
      set_precision(format, args, &spec);
      set_length(format, &spec);
      set_spec(format, &spec, args, temp);
      s21_memcpy(str, temp, s21_strlen(temp));
      str += s21_strlen(temp);
      skip_spec_line(&format);
      //count += (int)s21_strlen(temp);
    }
    if(*format == '\0'){
      break;
    }
    *str++ = *format++;
    //count++;
  }

  va_end(args);
  return str-str_beg;
}

