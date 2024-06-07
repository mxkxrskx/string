#include "s21_string_test.h"

void testing_sprinf_n(const char* format, double x) {
    int chars_written_original = 0;
    int chars_written_s21 = 0;
    
    char orig[BUFF] = "\0";
    char s21[BUFF] = "\0";

    sprintf(orig, format,  x, &chars_written_original);
    s21_sprintf(s21, format, x, &chars_written_s21);
    
    //ck_assert_int_eq(chars_written_original, chars_written_s21);
    ck_assert_str_eq(orig, s21);
}

START_TEST(n_normal) {
    testing_sprinf_n("T%%he nu%%mber of char%%acters %f writt%%en so far is: %n", 123.45);
}
END_TEST

START_TEST(n_flag_1) {
    testing_sprinf_n("Testing %n specif%fier", 0.0);
}
END_TEST

START_TEST(n_flag_2) {
    testing_sprinf_n("T%%his %fis a test%n", 52.0);
}
END_TEST

START_TEST(n_flag_3) {
    testing_sprinf_n("Anoth%fer test%n", 52.0);
}
END_TEST

START_TEST(n_flag_4) {
    testing_sprinf_n("% -52f%n", 234.0);
}
END_TEST

START_TEST(n_flag_5) {
    testing_sprinf_n("%+010f%n", 234.3232);
}
END_TEST

Suite *suite_sprintf_flags_n(void) {
    Suite *s = suite_create("SPRINTF_N");
    TCase *tc = tcase_create("sprintf_tc_N");

    tcase_add_test(tc, n_normal);
    tcase_add_test(tc, n_flag_1);
    tcase_add_test(tc, n_flag_2);
    tcase_add_test(tc, n_flag_3);
    tcase_add_test(tc, n_flag_4);
    tcase_add_test(tc, n_flag_5);

    suite_add_tcase(s, tc);
    return s;
}