#include "s21_string_test.h"

void testing_sprintf_o(const char *format, int x) {
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, format, x);
    s21_sprintf(s21, format, x);
    //ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
    ck_assert_str_eq(original, s21);
}

START_TEST(o_normal){
    testing_sprintf_o("%o", 0);
}
END_TEST

START_TEST(o_flag_1){
    testing_sprintf_o("%#o", 52);
}
END_TEST

START_TEST(o_flag_2){
    testing_sprintf_o("%010o", 52);
}
END_TEST

START_TEST(o_flag_3){
    testing_sprintf_o("% #10o", 52);
}
END_TEST

START_TEST(o_flag_4){
    testing_sprintf_o("%-52o", 52);
}
END_TEST

START_TEST(o_flag_5){
    testing_sprintf_o("%+010o", 52);
}
END_TEST

START_TEST(o_flag_6){
    testing_sprintf_o("% 010o", 52);
}
END_TEST

START_TEST(o_flag_7){
    testing_sprintf_o("%-010o", 52);
}
END_TEST

START_TEST(o_flag_8){
    testing_sprintf_o("%#-10o", 52);
}
END_TEST

START_TEST(o_flag_precision_1){
    testing_sprintf_o("%.5o", 52);
}
END_TEST

START_TEST(o_flag_precision_2){
    testing_sprintf_o("%#.5o", 52);
}
END_TEST

START_TEST(o_flag_precision_3){
    testing_sprintf_o("%-.5o", 52);
}
END_TEST

START_TEST(o_flag_precision_4){
    testing_sprintf_o("%#-.5o", 52);
}
END_TEST

Suite *suite_sprintf_flags_o(void){
    Suite *s = suite_create("SPRINTF_O");
    TCase *tc = tcase_create("sprintf_tc_O");

    tcase_add_test(tc, o_normal);
    tcase_add_test(tc, o_flag_1);
    tcase_add_test(tc, o_flag_2);
    tcase_add_test(tc, o_flag_3);
    tcase_add_test(tc, o_flag_4);
    tcase_add_test(tc, o_flag_5);
    tcase_add_test(tc, o_flag_6);
    tcase_add_test(tc, o_flag_7);
    tcase_add_test(tc, o_flag_8);
    tcase_add_test(tc, o_flag_precision_1);
    tcase_add_test(tc, o_flag_precision_2);
    tcase_add_test(tc, o_flag_precision_3);
    tcase_add_test(tc, o_flag_precision_4);

    suite_add_tcase(s, tc);
    return s;
}