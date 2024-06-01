#include "s21_string_test.h"

START_TEST(d_normal){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 0;
    sprintf(original, "%d", x);
    s21_sprintf(s21, "%d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 0;
    sprintf(original, "%+d", x);
    s21_sprintf(s21, "%+d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "%010d", x);
    s21_sprintf(s21, "%010d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% +10d", x);
    s21_sprintf(s21, "% +10d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% -52d", x);
    s21_sprintf(s21, "% -52d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_7){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "% -04d", x);
    s21_sprintf(s21, "% -04d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_5){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "%+010d", x);
    s21_sprintf(s21, "%+010d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_6){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% +010d", x);
    s21_sprintf(s21, "% +010d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST


START_TEST(d_flag_8){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% -+010d", x);
    s21_sprintf(s21, "% -+010d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_9){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "% 10d", x);
    s21_sprintf(s21, "% 10d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_precision_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%10.5d", x);
    s21_sprintf(s21, "%10.5d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_precision_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%-10.5d", x);
    s21_sprintf(s21, "%-10.5d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_precision_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%-010.5d", x);
    s21_sprintf(s21, "%-010.5d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(d_flag_precision_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 52;
    sprintf(original, "% -+10.5d", x);
    s21_sprintf(s21, "% -+10.5d", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

Suite *suite_sprintf_flags_d(void){
    Suite *s = suite_create("SPRINTF_D");
    TCase *tc = tcase_create("sprintf_tc_D");

    tcase_add_test(tc, d_normal);
    tcase_add_test(tc, d_flag_1);
    tcase_add_test(tc, d_flag_2);
    tcase_add_test(tc, d_flag_3);
    tcase_add_test(tc, d_flag_4);
    tcase_add_test(tc, d_flag_5);
    tcase_add_test(tc, d_flag_6);
    tcase_add_test(tc, d_flag_7);
    tcase_add_test(tc, d_flag_8);
    tcase_add_test(tc, d_flag_9);
    tcase_add_test(tc, d_flag_precision_1);
    tcase_add_test(tc, d_flag_precision_2);
    tcase_add_test(tc, d_flag_precision_3);
    tcase_add_test(tc, d_flag_precision_4);


    suite_add_tcase(s, tc);
    return s;
}


