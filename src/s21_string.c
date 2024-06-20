#include "s21_string.h"

#include "s21_strerror.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *c_adress = S21_NULL;
  char *str1 = (char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] == (char)c) {
      c_adress = str1 + i;
      break;
    }
  }
  return c_adress;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  int flag = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      flag = s1[i] - s2[i];
      break;
    }
  }
  return flag;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *source = (char *)src;
  char *s21_dest = (char *)dest;
  for (s21_size_t i = 0; i < n; i++) {
    s21_dest[i] = source[i];
  }
  return s21_dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  char *char_str = (char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    char_str[i] = c;
  }
  return char_str;
}

char *s21_strchr(const char *str, int c) {
  while (*str != (char)c && *str) {
    str++;
  }
  if (*str == '\0' && c != '\0') str = S21_NULL;
  return (char *)str;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  const char *s1 = S21_NULL;
  const char *s2 = S21_NULL;
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

s21_size_t s21_strlen(const char *str) {
  const char *str1 = (char *)str;
  while (*str1++)
    ;
  return str1 - str - 1;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t count = 0;

  for (int i = 0; count < n && src[count]; count++, i++) {
    dest[dest_len + count] = src[count];
  }
  dest[dest_len + count] = '\0';
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;
  if (str1 && str2 && n > 0) {
    for (s21_size_t i = 0; i < n; i++) {
      if (str1[i] == '\0' || str1[i] != str2[i]) {
        res = str1[i] - str2[i];
        break;
      }
    }
  }
  return res;
}

#if OS_NAME
char *s21_strerror(int errnum) {
  static char error_massage[BUFF] = "\0";
  if (errnum >= MIN_ERROR && errnum < MAX_ERROR) {
    s21_memcpy(error_massage, error_list_mac[errnum], BUFF);
  } else {
    s21_sprintf(error_massage, "Unknown error: %d", errnum);
  }
  return error_massage;
}
#else
char *s21_strerror(int errnum) {
  static char error_massage[BUFF] = "\0";
  if (errnum >= MIN_ERROR && errnum < MAX_ERROR) {
    s21_memcpy(error_massage, error_list_linux[errnum], BUFF);
  } else {
    s21_sprintf(error_massage, "Unknown error %d", errnum);
  }
  return error_massage;
}

#endif

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) dest[i] = src[i];

  return dest;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *c = S21_NULL;
  for (const char *c1 = str1; *c1; c1++) {
    for (const char *c2 = str2; *c2; c2++) {
      if (*c1 == *c2) {
        c = (char *)c1;
        break;
      }
    }
    if (c) {
      break;
    }
  }
  return c;
}

char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL) return S21_NULL;
  const char *res = S21_NULL;
  while (*str) {
    if (*str == c) res = str;
    str++;
  }
  if (c == '\0') res = (char *)str;
  return (char *)res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t len = s21_strlen(needle);
  int is_empty = 1;
  if (len) {
    is_empty = 0;
    s21_size_t h_len = s21_strlen(haystack);
    while (h_len-- >= len) {
      if (!s21_memcmp(haystack, needle, len)) {
        is_empty = 1;
        break;
      }
      haystack++;
    }
  }
  return is_empty ? (char *)haystack : S21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  static char *token;
  char *return_value = "\0";

  if (str) {
    if (str[0] == '\0') return_value = S21_NULL;
    token = str;
  } else {
    if (token[0] == '\0') return_value = S21_NULL;
    str = token;
  }

  if (return_value) {
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if (s21_strchr(delim, str[i])) {
        str[i] = '\0';
        while (s21_strchr(delim, str[i + 1]) != S21_NULL) {
          i++;
          token++;
        }
        token++;
        break;
      }
      token = str + i + 1;
    }
  }

  return return_value ? str : return_value;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t len = s21_strlen(str);
  char *res = calloc(len + 1, sizeof(char));
  s21_size_t i = 0;
  while (i < len) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      res[i] = str[i] + 32;
    } else {
      res[i] = str[i];
    }
    i++;
  }
  return res;
}

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  s21_size_t len = s21_strlen(str);
  char *res = calloc(len + 1, sizeof(char));
  s21_size_t i = 0;
  while (i < len) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      res[i] = str[i] - 32;
    } else {
      res[i] = str[i];
    }
    i++;
  }
  return res;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL || trim_chars == S21_NULL) return S21_NULL;
  s21_size_t begin = 0;
  s21_size_t end = s21_strlen(src);

  while (begin < end && s21_strchr(trim_chars, src[begin]) != S21_NULL) begin++;
  while (end > begin && s21_strchr(trim_chars, src[end - 1]) != S21_NULL) end--;

  s21_size_t length = end - begin;
  char *res = (char *)malloc(length + 1);
  if (res != S21_NULL) {
    res = s21_strncpy(res, src + begin, length);
    res[length] = '\0';
  }
  return res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == S21_NULL || str == S21_NULL) return S21_NULL;

  s21_size_t src_length = s21_strlen(src);
  s21_size_t str_length = s21_strlen(str);

  if (start_index > src_length) return S21_NULL;
  s21_size_t length = src_length + str_length;
  char *res = (char *)calloc(length + 1, sizeof(char));
  if (res != S21_NULL) {
    res = s21_strncpy(res, src, start_index);
    res = s21_strncat(res, str, str_length);
    res = s21_strncat(res, src + start_index, src_length);
  }
  return res;
}
