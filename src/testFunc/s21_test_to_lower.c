#include "s21_string_test.h"

START_TEST(normal_line) {
  void *ptr = s21_to_lower("HellO WOoRld");
  ck_assert_msg(s21_memcmp(ptr, "hello woorld", s21_strlen("HELLO WOORLD")) ==
                    0,
                "FAIL! Test normal line, \"HellO WooRld\" != \"HELLO WOORLD\"");
}
END_TEST

START_TEST(empty_line) {
  void *ptr = s21_to_lower("");
  ck_assert_msg(s21_memcmp(ptr, "", 0) == 0,
                "FAIL! Test empty line, \"\" != \"\"");
}
END_TEST

START_TEST(all_top) {
  void *ptr = s21_to_lower("HELLO WORLD");
  ck_assert_msg(s21_memcmp(ptr, "hello world", s21_strlen("hello world")) == 0,
                "FAIL! Test all top, \"hello world\" != \"hello world\"");
}
END_TEST

START_TEST(all_lower) {
  void *ptr = s21_to_lower("hello world");
  ck_assert_msg(s21_memcmp(ptr, "hello world", s21_strlen("hello world")) == 0,
                "FAIL! Test all_lower, \"hello world\" != \"hello world\"");
}
END_TEST

START_TEST(non_alphabet) {
  void *ptr = s21_to_lower("1234@#$");
  ck_assert_msg(s21_memcmp(ptr, "1234@#$", s21_strlen("1234@#$")) == 0,
                "FAIL! Test non alphabet, \"1234@#$\" != \"1234@#$\"");
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