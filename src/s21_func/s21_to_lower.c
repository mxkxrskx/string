#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *res = calloc(s21_strlen(str) + 1, 1);

  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      res[i] = str[i] + 32;
    } else {
      res[i] = str[i];
    }
  }
  return res;
}
