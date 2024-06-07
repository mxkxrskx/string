#include "s21_string_test.h"
START_TEST(all_empty) {
  char src[] = "";
  char res[] = "";
  char expected[] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(zero_byte) {
  char src[] = "example";
  char res[10] = "";
  char expected[10] = "";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(empty_src) {
  char src[] = "";
  char res[10] = "cd";
  char expected[10] = "cd";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(example) {
  char src[] = "example";
  char res[10] = "tc";
  char expected[10] = "tc";
  s21_size_t n_byte = 5;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(string) {
  char src[] = "example";
  char res[25] = "primer";
  char expected[25] = "primer";
  s21_size_t n_byte = 6;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(testcase) {
  char src[] = "testcase";
  char res[25] = "testcase";
  char expected[25] = "testcase";
  s21_size_t n_byte = 5;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(testcase2) {
  char src[] = "testcase";
  char res[25] = "testcase";
  char expected[25] = "testcase";
  s21_size_t n_byte = 0;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(testcase3) {
  char src[] = "testcase";
  char res[25] = "testcase";
  char expected[25] = "testcase";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(testcase4) {
  char src[] = "testcase";
  char res[25] = "testcase";
  char expected[25] = "testcase";
  s21_size_t n_byte = 10;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

START_TEST(zero_char) {
  char src[] = "\0";
  char res[25] = "testcase";
  char expected[25] = "testcase";
  s21_size_t n_byte = 1;

  s21_strncat(res, src, n_byte);
  strncat(expected, src, n_byte);

  ck_assert_mem_ge(res, expected, n_byte);
}
END_TEST

Suite *suite_strncat(void) {
  Suite *s = suite_create("STRNCAT");
  TCase *tc = tcase_create("strncat_tc");

  tcase_add_test(tc, all_empty);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, empty_src);
  tcase_add_test(tc, example);
  tcase_add_test(tc, string);
  tcase_add_test(tc, testcase);
  tcase_add_test(tc, testcase2);
  tcase_add_test(tc, testcase3);
  tcase_add_test(tc, testcase4);
  tcase_add_test(tc, zero_char);

  suite_add_tcase(s, tc);
  return s;
}
