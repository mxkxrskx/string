#include "s21_string_test.h"

void testing_strncpy(char *dest, const char *src, s21_size_t n) {
    void *orig_res = strncpy(dest, src, n);
    void *s21_res = s21_strncpy(dest, src, n);

    ck_assert_ptr_eq(orig_res, s21_res);
}

// самый обычный тест
START_TEST(normal_line) {
    char dest[100] = "";
    char src[100] = "hello world bro";
    s21_size_t n = 10;

    testing_strncpy(dest, src, n);
}
END_TEST

// src на 4 элемента, a n на 10 элементов
START_TEST(small_line_in_src) {
    char dest[100] = "";
    char src[100] = "hell";
    s21_size_t n = 10;

    testing_strncpy(dest, src, n);
}
END_TEST

// максимальная длинна src 4 элемента, a n на 10 элементов
START_TEST(small_maxline_in_src) {
    char dest[100] = "";
    char src[4] = "hell";
    s21_size_t n = 10;

    testing_strncpy(dest, src, n);
}
END_TEST

// дест слишком маленький для n
START_TEST(small_line_in_dest) {
    char dest[100] = "";
    char src[120] = "Open the door to a world of fantastic possibilities and dive into an ocean of endless ideas and inspiration!";
    s21_size_t n = 110;

    testing_strncpy(dest, src, n);
}
END_TEST

// dest больше чем src
START_TEST(n_less_than_dest) {
    char dest[100] = "hellooooooooooo";
    char src[100] = "Open the door to a world of fantastic possibilities and dive in!";
    s21_size_t n = 10;

    testing_strncpy(dest, src, n);
}
END_TEST

// zero
START_TEST(zero_dest_src) {
    char dest[0];
    char src[0];
    s21_size_t n = 0;

    testing_strncpy(dest, src, n);
}
END_TEST

// one
START_TEST(one_dest_src) {
    char dest[1];
    char src[1] = "l";
    s21_size_t n = 1;

    testing_strncpy(dest, src, n);
}
END_TEST

Suite *suite_strncpy(void){
    Suite *s = suite_create("STRNCPY");
    TCase *tc = tcase_create("strncpy_tc");
    
    tcase_add_test(tc, normal_line);
    tcase_add_test(tc, small_line_in_src);
    tcase_add_test(tc, small_maxline_in_src);
    tcase_add_test(tc, small_line_in_dest);
    tcase_add_test(tc, n_less_than_dest);
    tcase_add_test(tc, zero_dest_src);
    tcase_add_test(tc, one_dest_src);
    
    suite_add_tcase(s, tc);
    return s;
}