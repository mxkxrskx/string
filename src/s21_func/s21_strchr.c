#include "s21_string.h"

char *s21_strchr(const char *str, int c){
    while(*str != (char)c && *str){
        str++;
    }
    if(*str == '\0' && c != '\0') str = S21_NULL;
    return (char *)str;
}