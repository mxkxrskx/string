#include "s21_string_test.h"

void testing_sprinf_f(const char*format, double x){
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, format, x);
    s21_sprintf(s21, format, x);
    //ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
    ck_assert_str_eq(original, s21);
}

START_TEST(f_normal){
    testing_sprinf_f("%f", 0.0);
}
END_TEST

START_TEST(f_flag_1){
    testing_sprinf_f("%+f", 0.0);
}
END_TEST

START_TEST(f_flag_2){
    testing_sprinf_f("%010f", 52.0);
}
END_TEST

START_TEST(f_flag_3){
    testing_sprinf_f("% +10f", 52.0);
}
END_TEST

START_TEST(f_flag_4){
    testing_sprinf_f("% -52f", 234.0);
}
END_TEST

START_TEST(f_flag_5){
    testing_sprinf_f("%+010f", 234.3232);
}
END_TEST

START_TEST(f_flag_6){
    testing_sprinf_f("% +010f", 52.435435435);
}
END_TEST

START_TEST(f_flag_7){
    testing_sprinf_f("% -04f", -52.99999);
}
END_TEST

START_TEST(f_flag_8){
    testing_sprinf_f("% -+010f", 52.0);
}
END_TEST

START_TEST(f_flag_9){
    testing_sprinf_f("% 10f", -52.5315);
}
END_TEST

START_TEST(f_flag_precision_1){
    testing_sprinf_f("%10.5f", -52.666666666);
}
END_TEST

START_TEST(f_flag_precision_2){
    testing_sprinf_f("%-10.5f", -52.0);
}
END_TEST

START_TEST(f_flag_precision_3){
    testing_sprinf_f("%-010.5f", -52.0);
}
END_TEST

START_TEST(f_flag_precision_4_round){
    testing_sprinf_f("% -+10.5f", 52.9999999);
}
END_TEST

START_TEST(f_negative){
    testing_sprinf_f("%f", -10.599999999);
}
END_TEST

START_TEST(f_large_number){
    testing_sprinf_f("%f", 1234567890.123);
}
END_TEST

START_TEST(f_large_number_1_round){
    testing_sprinf_f("%f", 1234567890.599999999);
}
END_TEST

START_TEST(f_scientific_notation){
    testing_sprinf_f("%f", 1.23e5);
}
END_TEST

START_TEST(f_nan_test){
    testing_sprinf_f("%f", -0.0/0.0);
}
END_TEST

START_TEST(f_inf_test){
    testing_sprinf_f("%f", -1.0/0.0);
}
END_TEST

START_TEST(f_pi_test){
    testing_sprinf_f("%.9f", 3.1415926535);
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
    tcase_add_test(tc, f_flag_precision_4_round);
    tcase_add_test(tc, f_negative);
    tcase_add_test(tc, f_large_number);
    tcase_add_test(tc, f_scientific_notation);
    tcase_add_test(tc, f_large_number_1_round);
    tcase_add_test(tc, f_inf_test);
    tcase_add_test(tc, f_nan_test);
    tcase_add_test(tc, f_pi_test);

    suite_add_tcase(s, tc);
    return s;
}