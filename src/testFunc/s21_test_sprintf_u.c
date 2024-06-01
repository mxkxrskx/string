#include "s21_string_test.h"

START_TEST(u_normal){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 50;
    sprintf(original, "%u", (unsigned int)x);
    s21_sprintf(s21, "%u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 51;
    sprintf(original, "%+u", (unsigned int)x);
    s21_sprintf(s21, "%+u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -52;
    sprintf(original, "%010u", (unsigned int)x);
    s21_sprintf(s21, "%010u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -53;
    sprintf(original, "% +10u", (unsigned int)x);
    s21_sprintf(s21, "% +10u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -54;
    sprintf(original, "% -52u", (unsigned int)x);
    s21_sprintf(s21, "% -52u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_7){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -55;
    sprintf(original, "% -04u", (unsigned int)x);
    s21_sprintf(s21, "% -04u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_5){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -56;
    sprintf(original, "%+010u", (unsigned int)x);
    s21_sprintf(s21, "%+010u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_6){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -57;
    sprintf(original, "% +010u", (unsigned int)x);
    s21_sprintf(s21, "% +010u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST


START_TEST(u_flag_8){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -58;
    sprintf(original, "% -+010u", (unsigned int)x);
    s21_sprintf(s21, "% -+010u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_9){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = 59;
    sprintf(original, "% 10u", (unsigned int)x);
    s21_sprintf(s21, "% 10u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_precision_1){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -60;
    sprintf(original, "%10.5u", (unsigned int)x);
    s21_sprintf(s21, "%10.5u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_precision_2){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -61;
    sprintf(original, "%-10.5u", (unsigned int)x);
    s21_sprintf(s21, "%-10.5u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_precision_3){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -62;
    sprintf(original, "%-010.5u", (unsigned int)x);
    s21_sprintf(s21, "%-010.5u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_precision_4){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    int x = -63;
    sprintf(original, "% -+10.5u", (unsigned int)x);
    s21_sprintf(s21, "% -+10.5u", (unsigned int)x);
    ck_assert_str_eq(original, s21);
}
END_TEST

Suite *suite_sprintf_flags_u(void){
    Suite *s = suite_create("SPRINTF_U");
    TCase *tc = tcase_create("sprintf_tc_U");

    tcase_add_test(tc, u_normal);
    tcase_add_test(tc, u_flag_1);
    tcase_add_test(tc, u_flag_2);
    tcase_add_test(tc, u_flag_3);
    tcase_add_test(tc, u_flag_4);
    tcase_add_test(tc, u_flag_5);
    tcase_add_test(tc, u_flag_6);
    tcase_add_test(tc, u_flag_7);
    tcase_add_test(tc, u_flag_8);
    tcase_add_test(tc, u_flag_9);
    tcase_add_test(tc, u_flag_precision_1);
    tcase_add_test(tc, u_flag_precision_2);
    tcase_add_test(tc, u_flag_precision_3);
    tcase_add_test(tc, u_flag_precision_4);


    suite_add_tcase(s, tc);
    return s;
}


