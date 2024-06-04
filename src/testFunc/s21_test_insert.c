#include "s21_string_test.h"

START_TEST(normal_line) {
  char str[] = "Hello world";
  char dest[] = "bro)) ";
  int n = 5;
  ck_assert_str_eq((char *)s21_insert(str, dest, n), "Hello bro)) world");
}
END_TEST

START_TEST(empty_dest) {
  char str[] = "Hello world";
  char dest[] = "";
  int n = 5;
  ck_assert_str_eq((char *)s21_insert(str, dest, n), "Hello world");
}
END_TEST

START_TEST(empty_str) {
  char str[] = "";
  char dest[] = "bro)) ";
  int n = 0;
  ck_assert_str_eq((char *)s21_insert(str, dest, n), "bro)) ");
}
END_TEST

START_TEST(big_n) {
  char str[] = "Hello world";
  char dest[] = "bro)) ";
  int n = 20;
  ck_assert_ptr_eq((char *)s21_insert(str, dest, n), NULL);
}
END_TEST

START_TEST(negative_n) {
  char str[] = "Hello world";
  char dest[] = "bro)) ";
  int n = -5;
  ck_assert_ptr_eq((char *)s21_insert(str, dest, n), NULL);
}
END_TEST

START_TEST(empty_value) {
  char str[] = "";
  char dest[] = "";
  int n = 0;
  ck_assert_str_eq((char *)s21_insert(str, dest, n), "");
}
END_TEST

Suite *suite_insert(void) {
  Suite *s = suite_create("INSERT");
  TCase *tc = tcase_create("to_insert_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, empty_dest);
  tcase_add_test(tc, empty_str);
  tcase_add_test(tc, big_n);
  tcase_add_test(tc, negative_n);
  tcase_add_test(tc, empty_value);

  suite_add_tcase(s, tc);
  return s;
}