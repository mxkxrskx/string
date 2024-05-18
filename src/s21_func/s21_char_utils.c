#include "s21_char_utils.h"

bool is_sign(char c) { return c == '-' || c == '+'; }
bool is_lower(char c) { return c >= 'a' && c <= 'f'; }
bool is_upper(char c) { return c >= 'A' && c <= 'F'; }
bool is_digit(char c) { return c >= '0' && c <= '9'; }
bool is_octal(char c) { return c >= '0' && c <= '7'; }
bool is_hex(char c) { return is_digit(c) || is_lower(c) || is_upper(c); }

char to_lower(char c) { return is_upper(c) ? c - 'A' + 'a' : c; }

void skip_whitespace(char **ptr) {
  while (**ptr == ' ') {
    (*ptr)++;
  }
}

int get_sign(char **ptr) {
  int sign = 1;
  if (**ptr == '-') {
    (*ptr)++;
    sign = -1;
  } else if (**ptr == '+') {
    (*ptr)++;
  }
  return sign;
}

int get_base(char **ptr) {
  int base = BASE_UNKNOWN;
  if (**ptr == '0') {
    if ((*ptr)[1] == 'x' || (*ptr)[1] == 'X') {
      base = BASE_HEX;
      *ptr += 2;
    } else {
      base = BASE_OCTAL;
      (*ptr)++;
    }
  } else if (is_digit(**ptr)) {
    base = BASE_DECIMAL;
  }
  return base;
}