#include "s21_string_test.h"

START_TEST(c_normal){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "%c", x);
    s21_sprintf(s21, "%c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "%+c", x);
    s21_sprintf(s21, "%+c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "%010c", x);
    s21_sprintf(s21, "%010c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% +10c", x);
    s21_sprintf(s21, "% +10c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% -52c", x);
    s21_sprintf(s21, "% -52c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_7){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "% -04c", x);
    s21_sprintf(s21, "% -04c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_5){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "%+010c", x);
    s21_sprintf(s21, "%+010c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_6){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% +010c", x);
    s21_sprintf(s21, "% +010c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST


START_TEST(c_flag_8){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% -+010c", x);
    s21_sprintf(s21, "% -+010c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_9){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "% 10c", x);
    s21_sprintf(s21, "% 10c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_precision_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%10.5c", x);
    s21_sprintf(s21, "%10.5c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_precision_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%-10.5c", x);
    s21_sprintf(s21, "%-10.5c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_precision_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%-010.5c", x);
    s21_sprintf(s21, "%-010.5c", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(c_flag_precision_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% -+10.5c", x);
    s21_sprintf(s21, "% -+10.5c", x);
    ck_assert_str_eq(original, s21);
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