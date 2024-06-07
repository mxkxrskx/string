#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t count = 0;

  for (int i = 0; count < n && src[count]; count++, i++) {
    dest[dest_len + count] = src[count];
  }
  dest[dest_len + count] = '\0';
  return dest;
}
