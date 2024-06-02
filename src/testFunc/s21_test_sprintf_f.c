#include "s21_string_test.h"

START_TEST(f_normal){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 0;
    sprintf(original, "%f", x);
    s21_sprintf(s21, "%f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 0;
    sprintf(original, "%+f", x);
    s21_sprintf(s21, "%+f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "%010f", x);
    s21_sprintf(s21, "%010f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "% +10f", x);
    s21_sprintf(s21, "% +10f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "% -52f", x);
    s21_sprintf(s21, "% -52f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_7){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = -52;
    sprintf(original, "% -04f", x);
    s21_sprintf(s21, "% -04f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_5){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "%+010f", x);
    s21_sprintf(s21, "%+010f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_6){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "% +010f", x);
    s21_sprintf(s21, "% +010f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST


START_TEST(f_flag_8){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "% -+010f", x);
    s21_sprintf(s21, "% -+010f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_9){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = -52;
    sprintf(original, "% 10f", x);
    s21_sprintf(s21, "% 10f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_precision_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = -52;
    sprintf(original, "%10.5f", x);
    s21_sprintf(s21, "%10.5f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_precision_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = -52;
    sprintf(original, "%-10.5f", x);
    s21_sprintf(s21, "%-10.5f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_precision_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = -52;
    sprintf(original, "%-010.5f", x);
    s21_sprintf(s21, "%-010.5f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(f_flag_precision_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    double x = 52;
    sprintf(original, "% -+10.5f", x);
    s21_sprintf(s21, "% -+10.5f", x);
    ck_assert_str_eq(original, s21);
}
END_TEST

Suite *suite_sprintf_flags_f(void){
    Suite *s = suite_create("SPRINTF_F");
    TCase *tc = tcase_create("sprintf_tc_F");

    tcase_add_test(tc, f_normal);
    tcase_add_test(tc, f_flag_1);
    tcase_add_test(tc, f_flag_2);
    tcase_add_test(tc, f_flag_3);
    tcase_add_test(tc, f_flag_4);
    tcase_add_test(tc, f_flag_5);
    tcase_add_test(tc, f_flag_6);
    tcase_add_test(tc, f_flag_7);
    tcase_add_test(tc, f_flag_8);
    tcase_add_test(tc, f_flag_9);
    tcase_add_test(tc, f_flag_precision_1);
    tcase_add_test(tc, f_flag_precision_2);
    tcase_add_test(tc, f_flag_precision_3);
    tcase_add_test(tc, f_flag_precision_4);


    suite_add_tcase(s, tc);
    return s;
}


