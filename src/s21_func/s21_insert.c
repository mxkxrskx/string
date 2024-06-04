#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t len_src = 0, len_str = 0;
  char *res = NULL;

  len_src = (src) ? s21_strlen(src) : 0;
  len_str = (str) ? s21_strlen(str) : 0;

  if (start_index <= len_src) {
    res = (char *)calloc(len_src + len_str + 1, 1);

    for (s21_size_t i = 0; i < len_src + 1; i++) {
      if (i <= start_index)
        res[i] = src[i];
      if (i > start_index)
        res[i + len_str] = src[i];
      if (i == start_index)
        res = s21_strncat(res, str, len_str);
    }
  }
  return res;
}