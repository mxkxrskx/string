#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *c_adress = S21_NULL;
  char *str1 = (char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] == (char)c) {
      c_adress = str1 + i;
      break;
    }
  }
  return c_adress;
}