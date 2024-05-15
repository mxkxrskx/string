#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n){
    char *source = (char *)src;
    char *s21_dest = (char *)dest;
    for(s21_size_t i = 0; i < n; i++){
        s21_dest[i] = source[i];
    }
    return s21_dest;
}