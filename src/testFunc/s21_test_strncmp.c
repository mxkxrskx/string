#include "s21_string_test.h"

void testing_strncmp(const char *str1, const char *str2, s21_size_t n) {
  bool orig_res = strncmp(str1, str2, n);
  bool s21_res = s21_strncmp(str1, str2, n);
  ck_assert_int_eq(orig_res, s21_res);
}

START_TEST(normal_line) {
  const char str1[100] = "hello world";
  const char str2[100] = "hello world";
  s21_size_t n = 4;

  testing_strncmp(str1, str2, n);
}
END_TEST

// разные регистры
START_TEST(different_registers) {
  const char str1[100] = "helLO wOrld";
  const char str2[100] = "hello world";
  s21_size_t n = 4;

  testing_strncmp(str1, str2, n);
}
END_TEST

// n больше чем массив
START_TEST(n_more_than_arr) {
  const char str1[10] = "hello wor";
  const char str2[10] = "hello wor";
  s21_size_t n = 20;

  testing_strncmp(str1, str2, n);
}
END_TEST

// в массивах только одно разное значение
START_TEST(arr_one_value) {
  const char str1[1] = "s";
  const char str2[1] = "h";
  s21_size_t n = 1;

  testing_strncmp(str1, str2, n);
}
END_TEST
// в массивах только одно одинаковое значение
START_TEST(same_one_value) {
  const char str1[1] = "d";
  const char str2[1] = "d";
  s21_size_t n = 1;

  testing_strncmp(str1, str2, n);
}
END_TEST

// n = 0
START_TEST(n_zero) {
  const char str1[100] = "hello world";
  const char str2[100] = "hello world";
  s21_size_t n = 0;

  testing_strncmp(str1, str2, n);
}
END_TEST

// строчки разные
START_TEST(different_arr) {
  const char str1[10] = "world";
  const char str2[10] = "hello";
  s21_size_t n = 5;

  testing_strncmp(str1, str2, n);
}
END_TEST

Suite *suite_strncmp(void) {
  Suite *s = suite_create("STRNCMP");
  TCase *tc = tcase_create("strncmp_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, different_registers);
  tcase_add_test(tc, n_more_than_arr);
  tcase_add_test(tc, arr_one_value);
  tcase_add_test(tc, same_one_value);
  tcase_add_test(tc, n_zero);
  tcase_add_test(tc, different_arr);

  suite_add_tcase(s, tc);
  return s;
}
