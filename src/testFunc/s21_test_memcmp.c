#include "s21_string_test.h"

void testing_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int orig_res = memcmp(str1, str2, n);
  int s21_res = s21_memcmp(str1, str2, n);

  ck_assert_int_eq(orig_res, s21_res);
}

START_TEST(normal_line) {
  const void *str1 = "123456789";
  const void *str2 = "123456789";
  s21_size_t n = 10;

  testing_memcmp(str1, str2, n);
}
END_TEST

START_TEST(normal_line1) {
  const void *str1 = "123456789";
  const void *str2 = "0987654321";
  s21_size_t n = 10;

  testing_memcmp(str1, str2, n);
}
END_TEST

START_TEST(empty_line) {
  const void *str1 = "\0";
  const void *str2 = "\0";
  s21_size_t n = 2;

  testing_memcmp(str1, str2, n);
}
END_TEST

START_TEST(zero_n) {
  const void *str1 = "12345";
  const void *str2 = "123467";
  s21_size_t n = 0;

  testing_memcmp(str1, str2, n);
}
END_TEST

START_TEST(long_line_not_eq_1) {
  const void *str1 = "1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./";
  const void *str2 = "1234567890qwertyuiop[]asdfghjkl;'zxcvbnM,./";
  s21_size_t n = 44;

  testing_memcmp(str1, str2, n);
}
END_TEST

START_TEST(long_line_not_eq_2) {
  const void *str1 = "1234567890qwertyuiop[]asdfghjkl;'zxcvbnM,./";
  const void *str2 = "1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./";
  s21_size_t n = 44;

  testing_memcmp(str1, str2, n);
}
END_TEST

START_TEST(long_line_eq) {
  const void *str1 = "1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,./";
  const void *str2 = "1234567890qwertyuiop[]asdfghjkl;'zxcvbnm,.&";
  s21_size_t n = 44;

  testing_memcmp(str1, str2, n);
}
END_TEST

Suite *suite_memcmp(void) {
  Suite *s = suite_create("MEMCMP");
  TCase *tc = tcase_create("memcmp_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, normal_line1);
  tcase_add_test(tc, empty_line);
  tcase_add_test(tc, zero_n);
  tcase_add_test(tc, long_line_not_eq_1);
  tcase_add_test(tc, long_line_not_eq_2);
  tcase_add_test(tc, long_line_eq);

  suite_add_tcase(s, tc);
  return s;
}