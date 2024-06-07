#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *str1 = (char *)str;
  while (*str1++);
  return str1 - str - 1;
}