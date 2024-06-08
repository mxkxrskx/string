#include "s21_string_test.h"

void testing_sprintf_s(const char *format, const char *str) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";

  ck_assert_int_eq(sprintf(original, format, str),
                   s21_sprintf(s21, format, str));
  ck_assert_str_eq(original, s21);
}

START_TEST(s_normal) { testing_sprintf_s("%s", "school21remeberlegends"); }
END_TEST

START_TEST(s_flag_1) { testing_sprintf_s("%s", "school21remeberlegends"); }
END_TEST

START_TEST(s_flag_2) { testing_sprintf_s("%10s", "school21remeberlegends"); }
END_TEST

START_TEST(s_flag_4) { testing_sprintf_s("%52s", "school21remeberlegends"); }
END_TEST

START_TEST(s_flag_7) { testing_sprintf_s("%-4s", "school21remeberlegends"); }
END_TEST

START_TEST(s_flag_5) { testing_sprintf_s("%10.5s", "school21remeberlegends"); }
END_TEST

START_TEST(s_flag_precision_2) {
  testing_sprintf_s("%-10.5s", "school21remeberlegends");
}
END_TEST

Suite *suite_sprintf_flags_s(void) {
  Suite *s = suite_create("SPRINTF_S");
  TCase *tc = tcase_create("sprintf_tc_S");

  tcase_add_test(tc, s_normal);
  tcase_add_test(tc, s_flag_1);
  tcase_add_test(tc, s_flag_2);
  tcase_add_test(tc, s_flag_4);
  tcase_add_test(tc, s_flag_5);
  tcase_add_test(tc, s_flag_7);
  tcase_add_test(tc, s_flag_precision_2);

  suite_add_tcase(s, tc);
  return s;
}
