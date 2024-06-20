#include "s21_string_test.h"

void testing_to_upper(const char *src, const char *expect) {
  char *actual = (char *)s21_to_upper(src);
  ck_assert_str_eq(actual, expect);
  if (actual) free(actual);
}

void testing_to_upper_null(const char *src) {
  char *actual = (char *)s21_to_upper(src);
  ck_assert_ptr_null(actual);
}

START_TEST(normal_line) {
  char str[] = "HellO WOoRld";
  char expect[] = "HELLO WOORLD";
  testing_to_upper(str, expect);
}
END_TEST

START_TEST(empty_line) {
  char str[] = "";
  char expect[] = "";
  testing_to_upper(str, expect);
}
END_TEST

START_TEST(all_top) {
  char str[] = "HELLO WORLD";
  char expect[] = "HELLO WORLD";
  testing_to_upper(str, expect);
}
END_TEST

START_TEST(all_lower) {
  char str[] = "hello world";
  char expect[] = "HELLO WORLD";
  testing_to_upper(str, expect);
}
END_TEST

START_TEST(non_alphabet) {
  char str[] = "1234!@#";
  char expect[] = "1234!@#";
  testing_to_upper(str, expect);
}
END_TEST

START_TEST(null_string) {
  char *src = S21_NULL;
  testing_to_upper_null(src);
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
  tcase_add_test(tc, null_string);

  suite_add_tcase(s, tc);
  return s;
}
