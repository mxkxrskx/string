#include "s21_sprintf.h"

int main() {
  Suite *suite_array[] = {suite_sprintf_flags_d(), suite_sprintf_flags_c()};
  for (unsigned long i = 0; i < sizeof(suite_array) / sizeof(suite_array[0]);
       i++) {
    run_testcase(suite_array[i]);
    printf("\n");
  }
  // char str[BUFF] = "\0";
  // s21_sprintf(str, "%-10c", 'B');
  // printf("%s", str);



  return 0;
}

void run_testcase(Suite *testcase){
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);  
}

// void getFLOATfromString(double f, Specifiers *spec){
//     long double left = 0.0;
//     long double right = modfl(f, &left);
//     getNUMfromString((int)left, 10, spec);
//     spec->i_len--;
//     int count = 0;
//     while(count != 6){
//         right*=10;
//         count++;
//     }
//     strcat(spec->argv[spec->i_len], ".");
//     getNUMfromString((int)right, 10, spec);
// }


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
    if((spec->minus == 1 && spec->zero == 1)){
      spec->zero = 0;
    }
    if(spec->plus == 1 && spec->space == 1){
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
  s21_size_t width = spec->width - s21_strlen(str2);
  if(spec->zero && width > 0 && spec->precision == 0){
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

void getSTRINGfromNUM(int64_t num, int base, char tmp1[], Specifiers *spec){
    char tmp[BUFF] = "\0";
    int index = BUFF - 2;
    int temp = num;
    num = num > 0 ? num : -num;
    if(num == 0){
        tmp[index] = '0';
    }
    while(num > 0){
        index--;
        tmp[index] = "0123456789abcdef"[num%base];
        num/= base;
    }
    s21_size_t precision = spec->precision - s21_strlen(tmp+index);
    if(precision > 0 && spec->precision != 0){
      while(precision > 0){
        tmp[--index] = '0';
        precision--;
      }
    }
    if(temp < 0){
        tmp[--index] = '-';
    }
    if(spec->plus && spec->zero == 0 && temp > 0){
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

void set_spec(const char *format, Specifiers *spec, va_list args,  char str[BUFF]) {
  char *tmp = (char *)format;
  while (!s21_strchr("cdieEfgGosuxXpn", *tmp)) {
    tmp++;
  }
  switch (*tmp) {
    case 'c':
        process_c(args, spec, str);
        break; 
    case 'd':
        process_d(args, spec, str);
        break;
    case 'f':
        break;
    case 's':
        break;
    case 'u':
        process_d(args, spec, str);
        break;
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

  while (*format) {
    char temp[BUFF] = "\0";
    Specifiers spec = {0};

    if (*format == '%') {
      set_flags(format, &spec);
      set_width(format, args, &spec);
      set_precision(format, args, &spec);
      set_length(format, &spec);
      set_spec(format, &spec, args, temp);
      s21_strncat(str, temp, s21_strlen(temp));
      skip_spec_line(&format);
    }
    if(*format == '\0'){
      break;
    }
    *str++ = *format++;
  }

  va_end(args);

  return 0;
}

