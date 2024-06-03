#include "s21_string_test.h"

void testing_strrchr(const char *str, int c) {
  char *s21_c = s21_strrchr(str, c);
  char *string_c = strrchr(str, c);

  ck_assert_ptr_eq(s21_c, string_c);
}

START_TEST(normal_line) {
  const char *str = "qwertypuiop";
  int c = 'p';

  testing_strrchr(str, c);
}
END_TEST

START_TEST(no_sym) {
  const char *str = "qwertyuio";
  int c = 'p';

  testing_strrchr(str, c);
}

START_TEST(zero_line) {
  const char *str = "\0";
  int c = '\0';

  testing_strrchr(str, c);
}
END_TEST

START_TEST(long_line) {
  const char *str = "1234567890-=qwertyuiop[]asd/fghjkl;'zxcvbnm,./";
  int c = '/';

  testing_strrchr(str, c);
}
END_TEST

START_TEST(weird_line) {
  const char *str = "\a\t\n\v\r\f\'\\\"   /n";
  int c = '\n';

  testing_strrchr(str, c);
}
END_TEST

START_TEST(looking_zero) {
  const char *str = "1234567890";
  int c = '\0';

  testing_strrchr(str, c);
}
END_TEST

Suite *suite_strrchr(void) {
  Suite *s = suite_create("STRRCHR");
  TCase *tc = tcase_create("strrchr_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, no_sym);
  tcase_add_test(tc, zero_line);
  tcase_add_test(tc, long_line);
  tcase_add_test(tc, weird_line);
  tcase_add_test(tc, looking_zero);

  suite_add_tcase(s, tc);
  return s;
}
