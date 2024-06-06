#include "s21_string_test.h"

START_TEST(normal_line) {
  char str[] = "HellO WOoRld";
  ck_assert_str_eq((char *)s21_to_upper(str), "HELLO WOORLD");
}
END_TEST

START_TEST(empty_line) {
  char str[] = "";
  ck_assert_str_eq((char *)s21_to_upper(str), "");
}
END_TEST

START_TEST(all_top) {
  char str[] = "HELLO WORLD";
  ck_assert_str_eq((char *)s21_to_upper(str), "HELLO WORLD");
}
END_TEST

START_TEST(all_lower) {
  char str[] = "hello world";
  ck_assert_str_eq((char *)s21_to_upper(str), "HELLO WORLD");
}
END_TEST

START_TEST(non_alphabet) {
  char str[] = "1234!@#";
  ck_assert_str_eq((char *)s21_to_upper(str), "1234!@#");
}
END_TEST

Suite *suite_to_upper(void) {
  Suite *s = suite_create("TO_UPPER");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, empty_line);
  tcase_add_test(tc, all_top);
  tcase_add_test(tc, all_lower);
  tcase_add_test(tc, non_alphabet);

  suite_add_tcase(s, tc);
  return s;
}
