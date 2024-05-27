#include "s21_char_utils.h"
#include "s21_parse_number.h"
#include "s21_string.h"


int main() {
  char str1[BUFF] = "\0";
  s21_sprintf(str1, "%- +024d strstrstr%c", -51, '1');
  printf("%s", str1);          

  return 0;
}


// Спецификаторы PART 2: c d f s u
typedef struct Specifiers {
  bool space;
  bool zero;
  bool minus;
  bool plus;
  
  char length;
  int width;
  int precision;


} Specifiers;

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

// void input_spaces(Specifiers *spec, int spaces){
//     s21_memset(spec->argv[spec->i_len], ' ', spaces);
//     spec->argv[spec->i_len][spaces+1] = '\0';
// }

void is_negative(int num, int *spaces) {
  if (num < 0.0) {
    *spaces += 1;
  }
}

void set_flags(const char *format, Specifiers *spec) {
    char *tmp = (char *)format;
    tmp++;
    while(1){
      if (*tmp == ' ') spec->space = true;
      else if(*tmp == '0') spec->zero = true;
      else if(*tmp == '-') spec->minus = true;
      else if(*tmp == '+') spec->plus = true;
      else{
        spec->space = true;
      }
      tmp++;
      if(s21_strchr("cdieEfgGosuxXpn", *tmp) || (is_digit(*tmp) && *tmp != '0') || *tmp == '.') break;
    }
    if(spec->minus && spec->zero){
      spec->zero = 0;
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
  while (!s21_strchr("cdfsu", *tmp)) {
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

void process_c(va_list args, Specifiers *spec, char temp[BUFF]){
    if(spec->length == 'l'){
        wchar_t c = va_arg(args, wchar_t);
        //пробелы минусы нули
    }
    else{
        char c = va_arg(args, int);
        //пробелы минусы нули
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
    if(temp < 0){
        tmp[--index] = '-';
    }
    if(spec->plus && spec->zero && temp > 0){
      tmp[--index] = '+';
    }
    s21_strncat(tmp1, tmp+index, s21_strlen(tmp+index));
}

void getSTRING(char str1[BUFF], char str2[BUFF], Specifiers *spec, char c) {
    int index = 0;
    if (str2[0] == '-' && c == '0') {
        str1[index++] = '-';
    }
    s21_size_t width = spec->width - s21_strlen(str2);
    s21_strncpy(str1+index+width,str2+index, s21_strlen(str2+index));
    if(spec->zero && spec->space && str2[0] != '-'){
      str1[0] = ' ';
    }
    if(spec->zero && spec->plus && str2[0] != '-'){
      str1[0] = '+';
    }
}

void process_d(va_list args, Specifiers *spec, char str1[BUFF]){
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
    bool condition = s21_strlen(number) < (s21_size_t)spec->width;
    printf("zero = %d, space = %d, plus = %d width = %d\n", spec->zero, spec->space, spec->plus, spec->width);
    if(spec->zero && condition){
      getSTRING(str1, number, spec, '0');
    }
    else if(spec->minus && condition){
      s21_memset(number+s21_strlen(number), ' ', spec->width-s21_strlen(number));
      s21_strncpy(str1, number, s21_strlen(number));
    }
    else if(condition && spec->width != 0){
      getSTRING(str1, number, spec, ' ');
    }
    else{
      s21_strncat(str1, number, s21_strlen(number));
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
        printf("%s", str);
        break;
    case 'f':
        break;
    case 's':
        break;
    case 'u':
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

