#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  const char *s1 = NULL;
  const char *s2 = NULL;
  int stop = 0;

  for (s1 = str1; *s1 != '\0'; s1++) {
    for (s2 = str2; *s2 != '\0'; s2++) {
      if (*s1 == *s2) {
        stop = 1;
        break;
      }
    }
    if (stop) break;
    res++;
  }
  return res;
}
