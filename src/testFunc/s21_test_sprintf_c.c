#include "s21_string_test.h"

void testing_sprinf_c(const char *format, int x) {
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
    ck_assert_str_eq(original, s21);
}

START_TEST(c_normal) {
    testing_sprinf_c("%c", 52);
}
END_TEST

START_TEST(c_flag_1) {
    testing_sprinf_c("%+c", 52);
}
END_TEST

START_TEST(c_flag_2) {
    testing_sprinf_c("%010c", 52);
}
END_TEST

START_TEST(c_flag_3) {
    testing_sprinf_c("% +10c", 52);
}
END_TEST

START_TEST(c_flag_4) {
    testing_sprinf_c("% -52c", 52);
}
END_TEST

START_TEST(c_flag_5) {
    testing_sprinf_c("%+010c", 52);
}
END_TEST

START_TEST(c_flag_6) {
    testing_sprinf_c("% +010c", 52);
}
END_TEST

START_TEST(c_flag_7) {
    testing_sprinf_c("% -04c", -52);
}
END_TEST

START_TEST(c_flag_8) {
    testing_sprinf_c("% -+010c", 52);
}
END_TEST

START_TEST(c_flag_9) {
    testing_sprinf_c("% 10c", -52);
}
END_TEST

START_TEST(c_flag_precision_1) {
    testing_sprinf_c("%10.5c", -52);
}
END_TEST

START_TEST(c_flag_precision_2) {
    testing_sprinf_c("%-10.5c", -52);
}
END_TEST

START_TEST(c_flag_precision_3) {
    testing_sprinf_c("%-010.5c", -52);
}
END_TEST

START_TEST(c_flag_precision_4) {
    testing_sprinf_c("% -+10.5c", 52);
}
END_TEST

Suite *suite_sprintf_flags_c(void){
    Suite *s = suite_create("SPRINTF_C");
    TCase *tc = tcase_create("sprintf_tc_C");

    tcase_add_test(tc, c_normal);
    tcase_add_test(tc, c_flag_1);
    tcase_add_test(tc, c_flag_2);
    tcase_add_test(tc, c_flag_3);
    tcase_add_test(tc, c_flag_4);
    tcase_add_test(tc, c_flag_5);
    tcase_add_test(tc, c_flag_6);
    tcase_add_test(tc, c_flag_7);
    tcase_add_test(tc, c_flag_8);
    tcase_add_test(tc, c_flag_9);
    tcase_add_test(tc, c_flag_precision_1);
    tcase_add_test(tc, c_flag_precision_2);
    tcase_add_test(tc, c_flag_precision_3);
    tcase_add_test(tc, c_flag_precision_4);


    suite_add_tcase(s, tc);
    return s;
}