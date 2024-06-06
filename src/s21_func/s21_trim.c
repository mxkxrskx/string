#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL)
    return S21_NULL;
  s21_size_t begin = 0;
  s21_size_t end = s21_strlen(src);

  while (begin < end && s21_strchr(trim_chars, src[begin]) != S21_NULL)
    begin++;
  while (end > begin && s21_strchr(trim_chars, src[end - 1]) != S21_NULL)
    end--;

  s21_size_t length = end - begin;
  char *res = (char *)malloc(length + 1);
  if (res != S21_NULL) {
    res = s21_strncpy(res, src + begin, length);
    res[length] = '\0';
  }
  return res;
}
