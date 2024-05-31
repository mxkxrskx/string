#include "s21_char_utils.h"

bool s21_isspace(char c) {
  return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
         c == '\v';
}

bool s21_isdigit(char c) { return c >= '0' && c <= '9'; }

bool s21_isoctal(char c) { return c >= '0' && c <= '7'; }

bool s21_isupper(char c) { return c >= 'A' && c <= 'Z'; }

char s21_tolower(char c) { return s21_isupper(c) ? c - 'A' + 'a' : c; }

bool s21_ishex(char c) {
  char lower_c = s21_tolower(c);
  return (c >= '0' && c <= '9') || (lower_c >= 'a' && lower_c <= 'f');
}

void skip_spaces(char **s) {
  while (s21_isspace(**s)) {
    (*s)++;
  }
}
