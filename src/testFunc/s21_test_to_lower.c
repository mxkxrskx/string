#include "s21_string_test.h"

START_TEST(normal_line) {
  char *ptr = s21_to_lower("HellO WOoRld");
  ck_assert_str_eq(ptr, "hello woorld");
}
END_TEST

START_TEST(empty_line) {
  char *ptr = s21_to_lower("");
  ck_assert_str_eq(ptr, "");
}
END_TEST

START_TEST(all_top) {
  char *ptr = s21_to_lower("HELLO WORLD");
  ck_assert_str_eq(ptr, "hello world");
}
END_TEST

START_TEST(all_lower) {
  char *ptr = s21_to_lower("hello world");
  ck_assert_str_eq(ptr, "hello world");
}
END_TEST

START_TEST(non_alphabet) {
  char *ptr = s21_to_lower("1234@#$");
  ck_assert_str_eq(ptr, "1234@#$");
}
END_TEST

Suite *suite_to_lower(void) {
  Suite *s = suite_create("TO_LOWER");
  TCase *tc = tcase_create("to_lower_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, empty_line);
  tcase_add_test(tc, all_top);
  tcase_add_test(tc, all_lower);
  tcase_add_test(tc, non_alphabet);

  suite_add_tcase(s, tc);
  return s;
}