#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int flag = 0;
  char *c = S21_NULL;
  for (; *str1;) {
    for (; *str2;) {
      if (*str1 == *str2) {
        c = (char *)str1;
        flag = 1;
        break;
      }
      str2++;
    }
    str1++;
    if (flag) break;
  }
  return c;
}