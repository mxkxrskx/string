#ifndef PROJECT_S21_STRING_H
#define PROJECT_S21_STRING_H


#define S21_NULL ((void *)0)
#define BUFF 4096

#include <stdio.h>
#include <check.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

typedef long unsigned int s21_size_t;

//TestFunc
void run_test_cases(Suite *testcase);


//stringFunc
char *s21_strncat(char *dest, const char *src, s21_size_t n);
void *s21_memset(void *str, int c, s21_size_t n);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
//НАДО ПОМЕНТЬ SPRINTF на S21_SPRINTF на свой!!!!!!!!
char *s21_strerror(int errnum);
s21_size_t s21_strlen(const char *str);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
int s21_sprintf(char *str, const char *format, ...);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
s21_size_t s21_strcspn(const char *str1, const char *str2);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);


#endif //PROJECT_S21_STRING_H
