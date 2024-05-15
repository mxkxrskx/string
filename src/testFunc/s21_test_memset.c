#include "s21_string_test.h"

void testing_memset(const void *str, const char c, s21_size_t n) {
  void *orig_res = memchr(str, c, n);
  void *s21_res = s21_memchr(str, c, n);

  ck_assert_ptr_eq(orig_res, s21_res);
}

START_TEST(normal_line_normal_n) {
  const void *str = "bebra";
  const char c = 'A';
  s21_size_t n = 2;

  testing_memset(str, c, n);
}
END_TEST

START_TEST(normal_line_single_n) {
  const void *str = "bebra";
  const char c = 'B';
  s21_size_t n = 1;

  testing_memset(str, c, n);
}
END_TEST

START_TEST(normal_line_zero_n) {
  const void *str = "bebra";
  const char c = 'C';
  s21_size_t n = 0;

  testing_memset(str, c, n);
}
END_TEST

START_TEST(single_line_single_n) {
  const void *str = "Z";
  const char c = 'D';
  s21_size_t n = 1;

  testing_memset(str, c, n);
}
END_TEST

START_TEST(single_line_zero_n) {
  const void *str = "x";
  const char c = 'F';
  s21_size_t n = 0;

  testing_memset(str, c, n);
}
END_TEST

START_TEST(zero_line_zero_n) {
  const void *str = "";
  const char c = 'G';
  s21_size_t n = 0;

  testing_memset(str, c, n);
}
END_TEST

Suite *suite_memset(void) {
  Suite *s = suite_create("MEMSET");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, normal_line_normal_n);
  tcase_add_test(tc, normal_line_single_n);
  tcase_add_test(tc, normal_line_zero_n);
  tcase_add_test(tc, single_line_single_n);
  tcase_add_test(tc, single_line_zero_n);
  tcase_add_test(tc, zero_line_zero_n);
  
  suite_add_tcase(s, tc);
  return s;
}