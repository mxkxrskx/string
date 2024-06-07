#include "s21_string_test.h"

void testing_insert(const char *src, const char *str, s21_size_t start_index,
                    const char *expect) {
  char *actual = (char *)s21_insert(src, str, start_index);
  ck_assert_str_eq(actual, expect);
  if (actual)
    free(actual);
}

void testing_insert_null(const char *src, const char *str,
                         s21_size_t start_index) {
  char *actual = (char *)s21_insert(src, str, start_index);
  ck_assert_ptr_null(actual);
}

START_TEST(insert_begin) {
  char src[] = "hello world!";
  char str[] = "Amazing ";
  s21_size_t index = 0;
  testing_insert(src, str, index, "Amazing hello world!");
}
END_TEST

START_TEST(insert_middle) {
  char src[] = "Hello world!";
  char str[] = "amazing ";
  s21_size_t index = 6;
  testing_insert(src, str, index, "Hello amazing world!");
}
END_TEST

START_TEST(insert_end) {
  char src[] = "Hello world";
  char str[] = " amazing!";
  s21_size_t index = 11;
  testing_insert(src, str, index, "Hello world amazing!");
}
END_TEST

START_TEST(empty_source_string) {
  char src[] = "";
  char str[] = "Hello world!";
  s21_size_t index = 0;
  testing_insert(src, str, index, "Hello world!");
}
END_TEST

START_TEST(empty_insert_string) {
  char src[] = "Hello world!";
  char str[] = "";
  s21_size_t index = 7;
  testing_insert(src, str, index, "Hello world!");
}
END_TEST

START_TEST(improper_index) {
  char src[] = "Hello world!";
  char str[] = "amazing";
  s21_size_t index = 20;
  testing_insert_null(src, str, index);
}
END_TEST

START_TEST(null_source_string) {
  char *src = S21_NULL;
  char str[] = "Hello world!";
  s21_size_t index = 7;
  testing_insert_null(src, str, index);
}
END_TEST

START_TEST(null_insert_string) {
  char src[] = "Hello world!";
  char *str = S21_NULL;
  s21_size_t index = 7;
  testing_insert_null(src, str, index);
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("INSERT");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, insert_begin);
  tcase_add_test(tc, insert_middle);
  tcase_add_test(tc, insert_end);
  tcase_add_test(tc, empty_source_string);
  tcase_add_test(tc, empty_insert_string);
  tcase_add_test(tc, improper_index);
  tcase_add_test(tc, null_source_string);
  tcase_add_test(tc, null_insert_string);

  suite_add_tcase(s, tc);
  return s;
}
