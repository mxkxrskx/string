#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *token;
  char *return_value = "\0";

  if (str) {
    if (str[0] == '\0')
      return_value = NULL;
    token = str;
  } else {
    if (token[0] == '\0')
      return_value = NULL;
    str = token;
  }

  if (return_value) {
    for (s21_size_t i = 0; i < s21_strlen(str); i++) {
      if (s21_strchr(delim, str[i])) {
        str[i] = '\0';
        while (s21_strchr(delim, str[i + 1]) != NULL) {
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
