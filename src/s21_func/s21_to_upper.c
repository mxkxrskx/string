#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *res = (char *)str;

  if (str) {
    s21_size_t len = s21_strlen(str);
    for (s21_size_t i = 0; i < len; i++) {
      if (res[i] >= 'a' && res[i] <= 'z')
        res[i] -= 'a' - 'A';
    }
  }
  return res;
}
