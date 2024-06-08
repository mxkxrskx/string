#include "s21_string_test.h"

void testing_sprinf_d(const char *format, int x) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";
  ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
  ck_assert_str_eq(original, s21);
}

START_TEST(d_normal) { testing_sprinf_d("%d", 0); }
END_TEST

START_TEST(d_flag_1) { testing_sprinf_d("%+d", 0); }
END_TEST

START_TEST(d_flag_2) { testing_sprinf_d("%010d", 52); }
END_TEST

START_TEST(d_flag_3) { testing_sprinf_d("% +10d", 52); }
END_TEST

START_TEST(d_flag_4) { testing_sprinf_d("% -52d", 52); }
END_TEST

START_TEST(d_flag_5) { testing_sprinf_d("%+010d", 52); }
END_TEST

START_TEST(d_flag_6) { testing_sprinf_d("% +010d", 52); }
END_TEST

START_TEST(d_flag_7) { testing_sprinf_d("% -04d", -52); }
END_TEST

START_TEST(d_flag_8) { testing_sprinf_d("% -+010d", 52); }
END_TEST

START_TEST(d_flag_9) { testing_sprinf_d("% 10d", -52); }
END_TEST

START_TEST(d_flag_precision_1) { testing_sprinf_d("%10.5d", -52); }
END_TEST

START_TEST(d_flag_precision_2) { testing_sprinf_d("%-10.5d", -52); }
END_TEST

START_TEST(d_flag_precision_3) { testing_sprinf_d("%-010.5d", -52); }
END_TEST

START_TEST(d_flag_precision_4) { testing_sprinf_d("% -+10.5d", 52); }
END_TEST

START_TEST(two_number) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";
  ck_assert_int_eq(sprintf(original, "%d%10d% 10d", 10, 21, 23),
                   s21_sprintf(s21, "%d%10d% 10d", 10, 21, 23));
  ck_assert_str_eq(original, s21);
}
Suite *suite_sprintf_flags_d(void) {
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
  tcase_add_test(tc, two_number);

  suite_add_tcase(s, tc);
  return s;
}
