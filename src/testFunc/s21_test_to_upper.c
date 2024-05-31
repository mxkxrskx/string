#include "s21_string_test.h"

START_TEST(normal_line) {
  void *ptr = s21_to_upper("HellO WOoRld");
  ck_assert_msg(s21_memcmp(ptr, "HELLO WOORLD", s21_strlen("HELLO WOORLD")) ==
                    0,
                "FAIL! Test normal line, \"HellO WooRld\" != \"HELLO WOORLD\"");
}
END_TEST

START_TEST(empty_line) {
  void *ptr = s21_to_upper("");
  ck_assert_msg(s21_memcmp(ptr, "", 0) == 0,
                "FAIL! Test empty line, \"\" != \"\"");
}
END_TEST

START_TEST(all_top) {
  void *ptr = s21_to_upper("HELLO WORLD");
  ck_assert_msg(s21_memcmp(ptr, "HELLO WORLD", s21_strlen("HELLO WORLD")) == 0,
                "FAIL! Test all top, \"HELLO WORLD\" != \"HELLO WORLD\"");
}
END_TEST

START_TEST(all_lower) {
  void *ptr = s21_to_upper("hello world");
  ck_assert_msg(s21_memcmp(ptr, "HELLO WORLD", s21_strlen("HELLO WORLD")) == 0,
                "FAIL! Test all lower, \"HELLO WORLD\" != \"HELLO WORLD\"");
}
END_TEST

START_TEST(non_alphabet) {
  void *ptr = s21_to_upper("1234@#$");
  ck_assert_msg(s21_memcmp(ptr, "", 0) == 0,
                "FAIL! Test non alphabet, \"1234@#$\" != \"1234@#$\"");
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