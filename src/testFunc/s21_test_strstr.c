#include "s21_string_test.h"

void testing_strstr(const char *h, const char *n) {
  char *actual = s21_strstr(h, n);
  char *expect = strstr(h, n);

  ck_assert_ptr_eq(actual, expect);
}

void testing_strstr_null(const char *h, const char *n) {
  char *actual = (char *)s21_strstr(h, n);
  ck_assert_ptr_null(actual);
}

START_TEST(ordinary) {
  const char *haystack = "Hello world!";
  const char *needle = "world";

  testing_strstr(haystack, needle);
}
END_TEST

START_TEST(no_match) {
  const char *haystack = "Hello world!";
  const char *needle = "abc";

  testing_strstr(haystack, needle);
}
END_TEST

START_TEST(empty_haystack) {
  const char *haystack = "";
  const char *needle = "abc";

  testing_strstr(haystack, needle);
}
END_TEST

START_TEST(empty_needle) {
  const char *haystack = "Hello world!";
  const char *needle = "";

  testing_strstr_null(haystack, needle);
}
END_TEST

START_TEST(empty_both) {
  const char *haystack = "";
  const char *needle = "";

  testing_strstr_null(haystack, needle);
}
END_TEST

START_TEST(full_match) {
  const char *haystack = "Hello world!";
  const char *needle = "Hello world!";

  testing_strstr(haystack, needle);
}
END_TEST

Suite *suite_strstr(void) {
  Suite *s = suite_create("STRSTR");
  TCase *tc = tcase_create("strstr_tc");

  tcase_add_test(tc, ordinary);
  tcase_add_test(tc, no_match);
  tcase_add_test(tc, empty_haystack);
  tcase_add_test(tc, empty_needle);
  tcase_add_test(tc, empty_both);
  tcase_add_test(tc, full_match);

  suite_add_tcase(s, tc);
  return s;
}
