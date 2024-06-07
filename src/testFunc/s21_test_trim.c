#include "s21_string_test.h"

void testing_trim(const char *src, const char *trim_chars, const char *expect) {
  char *actual = (char *)s21_trim(src, trim_chars);
  ck_assert_str_eq(actual, expect);
  if (actual) free(actual);
}

void testing_trim_null(const char *src, const char *trim_chars) {
  char *actual = (char *)s21_trim(src, trim_chars);
  ck_assert_ptr_null(actual);
}

START_TEST(one_trim_symbol_begin) {
  char src[] = "!Hello World";
  char trim_chars[] = "!";
  testing_trim(src, trim_chars, "Hello World");
}
END_TEST

START_TEST(one_trim_symbol_end) {
  char src[] = "Hello World!";
  char trim_chars[] = "!";
  testing_trim(src, trim_chars, "Hello World");
}
END_TEST

START_TEST(two_trim_symbols_start) {
  char src[] = "! Hello World";
  char trim_chars[] = "! ";
  testing_trim(src, trim_chars, "Hello World");
}
END_TEST

START_TEST(two_trim_symbols_end) {
  char src[] = "Hello World! ";
  char trim_chars[] = "! ";
  testing_trim(src, trim_chars, "Hello World");
}
END_TEST

START_TEST(empty_source_string) {
  char src[] = "";
  char trim_chars[] = "!";
  testing_trim(src, trim_chars, "");
}
END_TEST

START_TEST(empty_trim_string) {
  char src[] = "Hello world!";
  char trim_chars[] = "";
  testing_trim(src, trim_chars, "Hello world!");
}
END_TEST

START_TEST(empty_both_strings) {
  char src[] = "";
  char trim_chars[] = "";
  testing_trim(src, trim_chars, "");
}
END_TEST

START_TEST(full_trim_string) {
  char src[] = "hhhhhh";
  char trim_chars[] = "h";
  testing_trim(src, trim_chars, "");
}
END_TEST

START_TEST(mixed_trim_symbols) {
  char src[] = "  ! Hello world ! hh ";
  char trim_chars[] = "h !";
  testing_trim(src, trim_chars, "Hello world");
}
END_TEST

START_TEST(absent_trim_symbols) {
  char src[] = "Hello world!";
  char trim_chars[] = "abc";
  testing_trim(src, trim_chars, "Hello world!");
}
END_TEST

START_TEST(one_source_symbol_with) {
  char src[] = "h";
  char trim_chars[] = "h";
  testing_trim(src, trim_chars, "");
}
END_TEST

START_TEST(one_soruce_symbol_without) {
  char src[] = "h";
  char trim_chars[] = "e";
  testing_trim(src, trim_chars, "h");
}
END_TEST

START_TEST(null_source_string) {
  char *src = S21_NULL;
  char trim_chars[] = "e";
  testing_trim_null(src, trim_chars);
}
END_TEST

START_TEST(null_trim_string) {
  char src[] = "h";
  char *trim_chars = S21_NULL;
  testing_trim_null(src, trim_chars);
}
END_TEST

Suite *suite_trim(void) {
  Suite *s = suite_create("TRIM");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, one_trim_symbol_begin);
  tcase_add_test(tc, one_trim_symbol_end);
  tcase_add_test(tc, two_trim_symbols_start);
  tcase_add_test(tc, two_trim_symbols_end);
  tcase_add_test(tc, empty_source_string);
  tcase_add_test(tc, empty_trim_string);
  tcase_add_test(tc, empty_both_strings);
  tcase_add_test(tc, full_trim_string);
  tcase_add_test(tc, mixed_trim_symbols);
  tcase_add_test(tc, absent_trim_symbols);
  tcase_add_test(tc, one_source_symbol_with);
  tcase_add_test(tc, one_soruce_symbol_without);
  tcase_add_test(tc, null_source_string);
  tcase_add_test(tc, null_trim_string);

  suite_add_tcase(s, tc);
  return s;
}
