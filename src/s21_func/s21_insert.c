#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL)
    return S21_NULL;

  s21_size_t src_length = s21_strlen(src);
  s21_size_t str_length = s21_strlen(str);

  if (start_index > src_length)
    return S21_NULL;
  s21_size_t length = src_length + str_length;
  char *res = (char *)malloc(length + 1);
  if (res != S21_NULL) {
    res = s21_strncpy(res, src, start_index);
    res = s21_strncat(res, str, str_length);
    res = s21_strncat(res, src + start_index, src_length);
  }
  return res;
}
