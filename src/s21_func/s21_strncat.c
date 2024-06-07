#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_memcpy(dest + dest_len, src, n);
  dest[dest_len + n] = '\0';
  return dest;
}
