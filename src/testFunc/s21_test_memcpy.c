#include "s21_string_test.h"

void testing_memcpy(char *str, s21_size_t n){
    char str_test[n];
    char s21_test[n];

    memcpy(str_test, str, n);
    s21_memcpy(s21_test, str, n);

    ck_assert_mem_eq(str_test, s21_test, n);
}


START_TEST(zero_line){
    char *str = "";
    s21_size_t n = strlen(str);

    testing_memcpy(str, n);
}
END_TEST

START_TEST(long_string){
    char *str = "1234567890-=qwertyuiop      []asdfghjkl;'zxcvbnm,./!@#$^&*()_";
    s21_size_t n = strlen(str);

    testing_memcpy(str, n);
}
END_TEST

START_TEST(strange_string){
    char *str = "\a\t\n\n\v\r\f\"\\ \'";
    s21_size_t n = strlen(str);

    testing_memcpy(str, n);
}
END_TEST

START_TEST(register_upper_line){
    char *str = "QWERTYUIOPASDFGHJKLZXCVBNM";
    s21_size_t n = strlen(str);
    
    testing_memcpy(str, n);
}
END_TEST




Suite *suite_memcpy(void){
    Suite *s = suite_create("MEMCPY");
    TCase *tc = tcase_create("memcpy_tc");
    
    tcase_add_test(tc, zero_line);
    tcase_add_test(tc, long_string);
    tcase_add_test(tc, strange_string);
    tcase_add_test(tc, register_upper_line);

    suite_add_tcase(s, tc);
    return s;
}