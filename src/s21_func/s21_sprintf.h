#include "s21_char_utils.h"
#include "s21_parse_number.h"
#include "s21_string.h"
#include "../testFunc/s21_string_test.h"

typedef struct Specifiers {
  bool space;
  bool zero;
  bool minus;
  bool plus;
  
  char length;
  int width;
  int precision;


} Specifiers;
//удалить runcase
void run_testcase(Suite *testcase);
void set_flags(const char *format, Specifiers *spec);
void set_width(const char *format, va_list args, Specifiers *spec);
void set_precision(const char *format, va_list args, Specifiers *spec);
void set_length(const char *format, Specifiers *spec);
void process_line_with_condition(char str1[BUFF], char str2[BUFF], Specifiers *spec);
void process_c(va_list args, Specifiers *spec, char str[BUFF]);
void getSTRINGfromNUM(int64_t num, int base, char tmp1[], Specifiers *spec);
void getSTRING(char str1[BUFF], char str2[BUFF], char c, s21_size_t width);
void minus_process(char str1[BUFF], char str2[BUFF], Specifiers *spec, s21_size_t width);
void process_d(va_list args, Specifiers *spec, char str[BUFF]);
void set_spec(const char *format, Specifiers *spec, va_list args,  char str[BUFF]);
void skip_spec_line(const char **format);