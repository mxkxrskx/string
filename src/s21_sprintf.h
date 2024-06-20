#include <stdint.h>

#include "s21_char_utils.h"
#include "s21_parse_number.h"
#include "s21_string.h"

#define DEFAULT_PRECISION 6

typedef struct Specifiers {
  bool space;
  bool zero;
  bool minus;
  bool plus;
  bool hash;
  bool fraction;

  bool set_precision;
  char length;
  int width;
  int precision;
  int postfix;
  char specifier;
  char sign_prefix;

} Specifiers;

void set_flags(const char *format, Specifiers *spec);
void set_width(const char *format, va_list args, Specifiers *spec);
void set_precision(const char *format, va_list args, Specifiers *spec);
void set_length(const char *format, Specifiers *spec);

void process_line_with_condition(char str1[BUFF], char str2[BUFF],
                                 Specifiers *spec);
void minus_process(char str1[BUFF], char str2[BUFF], Specifiers *spec,
                   s21_size_t width);
void getSTRING(char str1[BUFF], char str2[BUFF], char c, s21_size_t width);
void process_normal_f(char number[BUFF], char str[BUFF], Specifiers *spec);
void getEnumber(char str[BUFF], char number[BUFF], char postfix[BUFF]);

void process_c(va_list args, Specifiers *spec, char str[BUFF]);
void process_s(va_list args, Specifiers *spec, char str[BUFF]);
void get_line_s(char str1[BUFF], char str2[BUFF], Specifiers *spec);
void process_d(va_list args, Specifiers *spec, char str[BUFF]);
void process_u(va_list args, Specifiers *spec, char str[BUFF]);
void process_f(va_list args, Specifiers *spec, char str[BUFF]);
void process_e(va_list args, Specifiers *spec, char str[BUFF]);
void process_g(va_list args, Specifiers *spec, char str[BUFF]);
void process_o(va_list args, Specifiers *spec, char str[BUFF]);
void process_x(va_list args, Specifiers *spec, char str[BUFF]);
void process_p(va_list args, Specifiers *spec, char str[BUFF]);

void handle_specifier(const char *format, Specifiers *spec, va_list args,
                      char str[BUFF]);

void getSTRINGfromNUM(int64_t num, int base, char tmp1[], Specifiers *spec);
void getSTRINGfromE(long double e, Specifiers *spec, char sign, char str[BUFF]);
void getSTRINGfromEPLUS(long double e, Specifiers *spec, char str[BUFF]);
void getSTRINGfromEMINUS(long double e, Specifiers *spec, char str[BUFF]);

void getSTRINGfromF(long double f, Specifiers *spec, char str[BUFF]);
void create_left_part(char intpart[BUFF], long double left, long double *right,
                      Specifiers *spec);
void create_right_part(char fracpart[BUFF], long double right, Specifiers *spec,
                       int zeros);

void skip_spec_line(const char **format, char **str, Specifiers *spec);
