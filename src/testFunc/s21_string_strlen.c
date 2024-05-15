#include "s21_string_test.h"

void testing_strlen(const char *str){
    s21_size_t n = strlen(str);
    s21_size_t n21 = s21_strlen(str);
    ck_assert_int_eq(n, n21);
}


START_TEST(one_sym){
    const char *str = "1";
    testing_strlen(str);

}
END_TEST

START_TEST(zero_sym){
    const char *str = "\0";
    testing_strlen(str);
}
END_TEST

START_TEST(long_line){
    const char *str = "123456789-=qwertyuiop[]asdfghjkl;'zxcvbnm,./";
    testing_strlen(str);
}
END_TEST

START_TEST(weird_line){
    const char *str = "\a\t\n\v\r\f\"\'\\      ";
    testing_strlen(str);
}
END_TEST


Suite *suite_strlen(void){
    Suite *s = suite_create("STRLEN");
    TCase *tc = tcase_create("strlen_tc");

    tcase_add_test(tc, one_sym);
    tcase_add_test(tc, zero_sym);
    tcase_add_test(tc, long_line);
    tcase_add_test(tc, weird_line);

    suite_add_tcase(s, tc);
    return s;
}