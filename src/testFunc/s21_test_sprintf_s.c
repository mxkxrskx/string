#include "s21_string_test.h"

START_TEST(s_normal){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%s", "school21remeberlegends");
    s21_sprintf(s21, "%s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(s_flag_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%s", "school21remeberlegends");
    s21_sprintf(s21, "%s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(s_flag_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%10s", "school21remeberlegends");
    s21_sprintf(s21, "%10s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(s_flag_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%52s", "school21remeberlegends");
    s21_sprintf(s21, "%52s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(s_flag_7){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%-4s", "school21remeberlegends");
    s21_sprintf(s21, "%-4s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(s_flag_5){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%10.5s", "school21remeberlegends");
    s21_sprintf(s21, "%10.5s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(s_flag_precision_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, "%-10.5s", "school21remeberlegends");
    s21_sprintf(s21, "%-10.5s", "school21remeberlegends");
    ck_assert_str_eq(original, s21);
}
END_TEST

Suite *suite_sprintf_flags_s(void){
    Suite *s = suite_create("SPRINTF_S");
    TCase *tc = tcase_create("sprintf_tc_S");

    tcase_add_test(tc, s_normal);
    tcase_add_test(tc, s_flag_1);
    tcase_add_test(tc, s_flag_2);
    tcase_add_test(tc, s_flag_4);
    tcase_add_test(tc, s_flag_5);
    tcase_add_test(tc, s_flag_7);
    tcase_add_test(tc, s_flag_precision_2);


    suite_add_tcase(s, tc);
    return s;
}


