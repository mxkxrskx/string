#include "s21_string_test.h"

void testing_strerror(int errnum) {
  char *s21_message = s21_strerror(errnum);
  char *err_message = strerror(errnum);

  ck_assert_str_eq(s21_message, err_message);
}

START_TEST(all_errors) {
  for (int i = -150; i < 150; i++) {
    testing_strerror(i);
  }
}
END_TEST

Suite *suite_strerror(void) {
  Suite *s = suite_create("STRERROR");
  TCase *tc = tcase_create("strerror_tc");

  tcase_add_test(tc, all_errors);

  suite_add_tcase(s, tc);
  return s;
}
