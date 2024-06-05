#include "s21_string_test.h"

void testing_sprintf_g(const char* format, double x) {
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, format, x);
    s21_sprintf(s21, format, x);
    ck_assert_msg(strcmp(original, s21) == 0, "Failed: original: %s s21: %s\n", original, s21);
}

START_TEST(g_normal) {
    testing_sprintf_g("%g", 1236.489);
}
END_TEST

START_TEST(g_flag_1) {
    testing_sprintf_g("%g", 0.000002332000089);
}
END_TEST

START_TEST(g_flag_2) {
    testing_sprintf_g("%010g", 52.0);
}
END_TEST

START_TEST(g_flag_3) {
    testing_sprintf_g("% +10g", 52.0);
}
END_TEST

START_TEST(g_flag_4) {
    testing_sprintf_g("%-52g", 234.0);
}
END_TEST

START_TEST(g_flag_5) {
    testing_sprintf_g("%+010g", 234.3232);
}
END_TEST

START_TEST(g_flag_6) {
    testing_sprintf_g("% +010g", 52.435435435);
}
END_TEST

START_TEST(g_flag_7) {
    testing_sprintf_g("% -04g", -52.99999);
}
END_TEST

START_TEST(g_flag_8) {
    testing_sprintf_g("% -+010g", 52.0);
}
END_TEST

START_TEST(g_flag_9) {
    testing_sprintf_g("% 10g", -52.5315);
}
END_TEST

START_TEST(g_flag_precision_1) {
    testing_sprintf_g("%.5g", -52.666666666);
}
END_TEST

START_TEST(g_flag_precision_2) {
    testing_sprintf_g("%-10.5g", -52.0);
}
END_TEST

START_TEST(g_flag_precision_3) {
    testing_sprintf_g("%-010.5g", -52.0);
}
END_TEST

START_TEST(g_flag_precision_4_round) {
    testing_sprintf_g("% -+10.5g", 52.9999999);
}
END_TEST

START_TEST(g_negative) {
    testing_sprintf_g("%g", -10.599999999);
}
END_TEST

START_TEST(g_large_number) {
    testing_sprintf_g("%g", 1234567890.123);
}
END_TEST

START_TEST(g_large_number_1_round) {
    testing_sprintf_g("%g", 1234569.599999999);
}
END_TEST

START_TEST(g_scientific_notation) {
    testing_sprintf_g("%g", 1.23e5);
}
END_TEST

START_TEST(g_nan_test) {
    testing_sprintf_g("%g", 0.0 / -0.0);
}
END_TEST

START_TEST(g_inf_test) {
    testing_sprintf_g("%g", 1.0 / 0.0);
}
END_TEST

START_TEST(g_inf_test_minus) {
    testing_sprintf_g("%g", -1.0 / 0.0);
}
END_TEST

START_TEST(g_pi_test) {
    testing_sprintf_g("%.9g", 3.1415926535);
}
END_TEST



START_TEST(g_long_number) {
    testing_sprintf_g("%g", 12312312312.2567899);
}
END_TEST
START_TEST(g_large_negative_num) {
    testing_sprintf_g("%g", -9876543210.123456789);
}
END_TEST

START_TEST(g_decimal_less_than_one) {
    testing_sprintf_g("%g", 0.000123456789);
}
END_TEST

START_TEST(g_large_positive_num) {
    testing_sprintf_g("%g", 9876543210.0987654321);
}
END_TEST

START_TEST(g_small_num) {
    testing_sprintf_g("%g", 0.00000000123456789);
}
END_TEST

START_TEST(g_neg_small_num) {
    testing_sprintf_g("%g", -0.00000000123456789);
}
END_TEST

START_TEST(g_large_exponential_pos) {
    testing_sprintf_g("%g", 5.67e12);
}
END_TEST

START_TEST(g_large_exponential_neg) {
    testing_sprintf_g("%g", -3.21e-15);
}
END_TEST


START_TEST(g_very_large_pos) {
    testing_sprintf_g("%g", 1.23e30);
}
END_TEST

START_TEST(g_very_large_neg) {
    testing_sprintf_g("%g", -9.87e-25);
}
END_TEST


Suite *suite_sprintf_flags_g(void) {
    Suite *s = suite_create("SPRINTF_G");
    TCase *tc = tcase_create("sprintf_tc_G");

    tcase_add_test(tc, g_normal);
    tcase_add_test(tc, g_flag_1);
    tcase_add_test(tc, g_flag_2);
    tcase_add_test(tc, g_flag_3);
    tcase_add_test(tc, g_flag_4);
    tcase_add_test(tc, g_flag_5);
    tcase_add_test(tc, g_flag_6);
    tcase_add_test(tc, g_flag_7);
    tcase_add_test(tc, g_flag_8);
    tcase_add_test(tc, g_flag_9);
    tcase_add_test(tc, g_flag_precision_1);
    tcase_add_test(tc, g_flag_precision_2);
    tcase_add_test(tc, g_flag_precision_3);
    tcase_add_test(tc, g_flag_precision_4_round);
    tcase_add_test(tc, g_negative);
    tcase_add_test(tc, g_large_number);
    tcase_add_test(tc, g_scientific_notation);
    tcase_add_test(tc, g_large_number_1_round);
    tcase_add_test(tc, g_inf_test);
    tcase_add_test(tc, g_inf_test_minus);
    tcase_add_test(tc, g_nan_test);
    tcase_add_test(tc, g_pi_test);
    tcase_add_test(tc, g_long_number);


    tcase_add_test(tc, g_large_negative_num);
    tcase_add_test(tc, g_decimal_less_than_one);
    tcase_add_test(tc, g_large_positive_num);
    tcase_add_test(tc, g_small_num);
    tcase_add_test(tc, g_neg_small_num);
    tcase_add_test(tc, g_large_exponential_pos);
    tcase_add_test(tc, g_large_exponential_neg);
    tcase_add_test(tc, g_very_large_pos);
    tcase_add_test(tc, g_very_large_neg);
    suite_add_tcase(s, tc);
    return s;
}