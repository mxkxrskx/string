#include "s21_string_test.h"

void testing_strchr(const char *str, int c) {
  char *s21_c = s21_strchr(str, c);
  char *string_c = strchr(str, c);

  ck_assert_ptr_eq(s21_c, string_c);
}

START_TEST(normal_line) {
  const char *str = "qwertyuiop";
  int c = 'p';

  testing_strchr(str, c);
}
END_TEST

START_TEST(no_sym) {
  const char *str = "qwertyuio";
  int c = 'p';

  testing_strchr(str, c);
}

START_TEST(zero_line) {
  const char *str = "\0";
  int c = '\0';

  testing_strchr(str, c);
}
END_TEST

START_TEST(long_line) {
  const char *str = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./";
  int c = '/';

  testing_strchr(str, c);
}
END_TEST

START_TEST(weird_line) {
  const char *str = "\a\t\n\v\r\f\'\\\"   ";
  int c = '\n';

  testing_strchr(str, c);
}
END_TEST

START_TEST(looking_zero) {
  const char *str = "1234567890";
  int c = '\0';

  testing_strchr(str, c);
}
END_TEST

Suite *suite_strchr(void) {
  Suite *s = suite_create("STRCHR");
  TCase *tc = tcase_create("strchr_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, no_sym);
  tcase_add_test(tc, zero_line);
  tcase_add_test(tc, long_line);
  tcase_add_test(tc, weird_line);
  tcase_add_test(tc, looking_zero);

  suite_add_tcase(s, tc);
  return s;
}