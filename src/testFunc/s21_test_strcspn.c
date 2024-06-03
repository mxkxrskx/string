#include "s21_string_test.h"

void testing_strcspn(const char *str1, const char *str2) {
  s21_size_t actual = s21_strcspn(str1, str2);
  size_t expect = strcspn(str1, str2);

  ck_assert_uint_eq(actual, expect);
}

START_TEST(ordinary) {
  const char *str1 = "Hello world!";
  const char *str2 = "!";

  testing_strcspn(str1, str2);
}
END_TEST

START_TEST(no_match) {
  const char *str1 = "Hello world!";
  const char *str2 = "abc";

  testing_strcspn(str1, str2);
}
END_TEST

START_TEST(empty_str1) {
  const char *str1 = "";
  const char *str2 = "abc";

  testing_strcspn(str1, str2);
}
END_TEST

START_TEST(empty_str2) {
  const char *str1 = "Hello world!";
  const char *str2 = "";

  testing_strcspn(str1, str2);
}
END_TEST

START_TEST(empty_both) {
  const char *str1 = "";
  const char *str2 = "";

  testing_strcspn(str1, str2);
}
END_TEST

START_TEST(full_match) {
  const char *str1 = "Hello world!";
  const char *str2 = "Hello world!";

  testing_strcspn(str1, str2);
}
END_TEST

Suite *suite_strcspn(void) {
  Suite *s = suite_create("STRCSPN");
  TCase *tc = tcase_create("strcspn_tc");

  tcase_add_test(tc, ordinary);
  tcase_add_test(tc, no_match);
  tcase_add_test(tc, empty_str1);
  tcase_add_test(tc, empty_str2);
  tcase_add_test(tc, empty_both);
  tcase_add_test(tc, full_match);

  suite_add_tcase(s, tc);
  return s;
}
