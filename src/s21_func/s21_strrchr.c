#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL)
    return S21_NULL;
  const char *res = S21_NULL;
  while (*str) {
    if (*str == c)
      res = str;
    str++;
  }
  if (c == '\0')
    res = (char *)str;
  return (char *)res;
}
