#include "s21_string_test.h"


START_TEST(normal_line){
    const char *str1 = "1234567890";
    const char *str2 = "0987654321";

    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(zero_line_1){
    const char *str1 = "\0";
    const char *str2 = "1234567890";
    
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(zero_line_2){
    const char *str1 = "1234567890";
    const char *str2 = "\0";
    
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(weird_line){
    const char *str1 = "\a\t\n\v\r\f\\\'\"     ";
    const char *str2 = "        \a";
    
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *suite_strpbrk(void){
    Suite *s = suite_create("STRPBRK");
    TCase *tc = tcase_create("strpbrk_tc");
    
    tcase_add_test(tc, normal_line);
    tcase_add_test(tc, zero_line_1);
    tcase_add_test(tc, zero_line_2);
    tcase_add_test(tc, weird_line);

    suite_add_tcase(s, tc);
    return s;
}