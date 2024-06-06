#include "s21_string_test.h"

void testing_memchr(const void *str, int c, s21_size_t n) {
  void *string_memchr = memchr(str, c, n);
  void *s21_string_memchr = s21_memchr(str, c, n);

  ck_assert_ptr_eq(string_memchr, s21_string_memchr);
}

START_TEST(no_symbol) {
  const void *str = "1234567890";
  int c = '\n';
  s21_size_t n = 10;

  testing_memchr(str, c, n);
}
END_TEST

START_TEST(symbol_in_array) {
  const void *str = "123457890";
  int c = '0';
  s21_size_t n = 10;

  testing_memchr(str, c, n);
}

START_TEST(empty_line) {
  const void *str = "\0";
  int c = '\0';
  s21_size_t n = 1;

  testing_memchr(str, c, n);
}

START_TEST(repeat_symbol) {
  const void *str = "mmmmmmmmmmmmmmm";
  int c = 'm';
  s21_size_t n = 16;

  testing_memchr(str, c, n);
}
END_TEST

START_TEST(special_symbol) {
  const void *str = "\n\t\n\t\n\v\"";
  int c = '\v';
  s21_size_t n = 8;

  testing_memchr(str, c, n);
}
END_TEST

Suite *suite_memchr(void) {
  Suite *s = suite_create("MEMCHR");
  TCase *tc = tcase_create("memchr_tc");

  tcase_add_test(tc, no_symbol);
  tcase_add_test(tc, symbol_in_array);
  tcase_add_test(tc, empty_line);
  tcase_add_test(tc, repeat_symbol);
  tcase_add_test(tc, special_symbol);

  suite_add_tcase(s, tc);
  return s;
}