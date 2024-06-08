#include "s21_string_test.h"

void testing_sprintf_u(const char *format, unsigned int x) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";

  ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
  ck_assert_str_eq(original, s21);
}

START_TEST(u_normal) { testing_sprintf_u("%u", 50); }
END_TEST

START_TEST(u_flag_1) { testing_sprintf_u("%.2u", 51); }
END_TEST

START_TEST(u_flag_2) { testing_sprintf_u("%10.3u", -52); }
END_TEST

START_TEST(u_flag_3) { testing_sprintf_u("%10.2u", -53); }
END_TEST

START_TEST(u_flag_4) { testing_sprintf_u("%-52u", -54); }
END_TEST

START_TEST(u_flag_6) { testing_sprintf_u("%-11.24u", -57); }
END_TEST

START_TEST(u_flag_7) { testing_sprintf_u("%-4u", -55); }
END_TEST

START_TEST(u_flag_8) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";

  ck_assert_int_eq(sprintf(original, "%10.1hu", (short unsigned int)-58),
                   s21_sprintf(s21, "%10.1hu", (short unsigned int)-58));
  ck_assert_str_eq(original, s21);
}
END_TEST

START_TEST(u_flag_9) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";

  ck_assert_int_eq(sprintf(original, "%10.1u", -58),
                   s21_sprintf(s21, "%10.1u", -58));
  ck_assert_str_eq(original, s21);
  testing_sprintf_u("%10.1lu", 59);
}
END_TEST

START_TEST(u_flag_precision_1) { testing_sprintf_u("%10.5u", -60); }
END_TEST

START_TEST(u_flag_precision_2) { testing_sprintf_u("%-10.5u", -61); }
END_TEST

START_TEST(u_flag_precision_4) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";

  ck_assert_int_eq(sprintf(original, "%10.5hu", (short unsigned int)-63),
                   s21_sprintf(s21, "%10.5hu", (short unsigned int)-63));
  ck_assert_str_eq(original, s21);
}
END_TEST

Suite *suite_sprintf_flags_u(void) {
  Suite *s = suite_create("SPRINTF_U");
  TCase *tc = tcase_create("sprintf_tc_U");

  tcase_add_test(tc, u_normal);
  tcase_add_test(tc, u_flag_1);
  tcase_add_test(tc, u_flag_2);
  tcase_add_test(tc, u_flag_3);
  tcase_add_test(tc, u_flag_4);
  tcase_add_test(tc, u_flag_6);
  tcase_add_test(tc, u_flag_7);
  tcase_add_test(tc, u_flag_8);
  tcase_add_test(tc, u_flag_9);
  tcase_add_test(tc, u_flag_precision_1);
  tcase_add_test(tc, u_flag_precision_2);
  tcase_add_test(tc, u_flag_precision_4);

  suite_add_tcase(s, tc);
  return s;
}
