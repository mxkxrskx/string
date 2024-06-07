#include "s21_string_test.h"

void testing_sprintf_e(const char* format, double x) {
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, format, x);
    s21_sprintf(s21, format, x);
    //ck_assert_str_eq(original, s21);
    ck_assert_msg(strcmp(original, s21) == 0, "Failed: original: %s, s21: %s\n", original, s21);
}

START_TEST(e_normal) {
    testing_sprintf_e("%e", 123456.789);
}
END_TEST

START_TEST(e_flag_1) {
    testing_sprintf_e("%e", 0.0000023327000089);
}
END_TEST

START_TEST(e_flag_2){
    testing_sprintf_e("%010e", 52.0);
}
END_TEST

START_TEST(e_flag_3){
    testing_sprintf_e("% +10e", 52.0);
}
END_TEST

START_TEST(e_flag_4){
    testing_sprintf_e("% -52e", 234.0);
}
END_TEST

START_TEST(e_flag_5){
    testing_sprintf_e("%+010e", 234.3232);
}
END_TEST

START_TEST(e_flag_6){
    testing_sprintf_e("% +010e", 52.435435435);
}
END_TEST

START_TEST(e_flag_7){
    testing_sprintf_e("% -04e", -52.99999);
}
END_TEST

START_TEST(e_flag_8){
    testing_sprintf_e("% -+010e", 52.0);
}
END_TEST

START_TEST(e_flag_9){
    testing_sprintf_e("% 10e", -52.5315);
}
END_TEST

START_TEST(e_flag_precision_1){
    testing_sprintf_e("%#10.5e", -52.666666666);
}
END_TEST

START_TEST(e_flag_precision_2){
    testing_sprintf_e("%-10.5e", -52.0);
}
END_TEST

START_TEST(e_flag_precision_3){
    testing_sprintf_e("%-010.5e", -52.0);
}
END_TEST

START_TEST(e_flag_precision_4_round){
    testing_sprintf_e("% -+10.5e", 52.9999999);
}
END_TEST

START_TEST(e_negative){
    testing_sprintf_e("%e", -10.599999999);
}
END_TEST

START_TEST(e_large_number){
    testing_sprintf_e("%e", 1234567890.123);
}
END_TEST

START_TEST(e_large_number_1_round){
    testing_sprintf_e("%e", 1234567890.599999999);
}
END_TEST

START_TEST(e_scientific_notation){
    testing_sprintf_e("%e", 1.23e5);
}
END_TEST

START_TEST(e_nan_test){
    testing_sprintf_e("%e", 0.0/-0.0);
}
END_TEST

START_TEST(e_inf_test){
    testing_sprintf_e("%e", 1.0/0.0);
}
END_TEST

START_TEST(e_inf_test_minus){
    testing_sprintf_e("%e", -1.0/0.0);
}
END_TEST

START_TEST(e_pi_test){
    testing_sprintf_e("%.9e", 3.1415926535);
}
END_TEST

START_TEST(e_long_number){
    testing_sprintf_e("%e", 12312312312.2567899);
}
END_TEST

Suite *suite_sprintf_flags_e(void){
    Suite *s = suite_create("SPRINTF_E");
    TCase *tc = tcase_create("sprintf_tc_E");

    tcase_add_test(tc, e_normal);
    tcase_add_test(tc, e_flag_1);
    tcase_add_test(tc, e_flag_2);
    tcase_add_test(tc, e_flag_3);
    tcase_add_test(tc, e_flag_4);
    tcase_add_test(tc, e_flag_5);
    tcase_add_test(tc, e_flag_6);
    tcase_add_test(tc, e_flag_7);
    tcase_add_test(tc, e_flag_8);
    tcase_add_test(tc, e_flag_9);
    tcase_add_test(tc, e_flag_precision_1);
    tcase_add_test(tc, e_flag_precision_2);
    tcase_add_test(tc, e_flag_precision_3);
    tcase_add_test(tc, e_flag_precision_4_round);    
    tcase_add_test(tc, e_negative);
    tcase_add_test(tc, e_large_number);
    tcase_add_test(tc, e_scientific_notation);
    tcase_add_test(tc, e_large_number_1_round);
    tcase_add_test(tc, e_inf_test);
    tcase_add_test(tc, e_inf_test_minus);
    tcase_add_test(tc, e_nan_test);
    tcase_add_test(tc, e_pi_test);
    tcase_add_test(tc, e_long_number);

    suite_add_tcase(s, tc);
    return s;
}