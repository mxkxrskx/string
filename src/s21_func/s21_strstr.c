#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  const char *res = S21_NULL;
  for (const char *p = haystack; *p != '\0'; p++) {
    if (*p == *needle) {
      const char *s = p;
      const char *n = needle;
      while (*s != '\0' && *n != '\0' && *s == *n) {
        s++;
        n++;
      }
      if (*n == '\0') {
        res = p;
        break;
      }
    }
  }
  return (char *)res;
}
