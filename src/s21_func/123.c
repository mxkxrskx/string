#include "s21_sscanf.h"
#include <check.h>
#include <stdio.h>
#include <string.h>

// Function to compare the results of s21_sscanf and sscanf
void testing_sscanf(const char *input, const char *format, void *s21_output,
                    void *std_output, char type) {
  switch (type) {
  case 'i':
    s21_sscanf(input, format, (int *)s21_output);
    sscanf(input, format, (int *)std_output);
    ck_assert_int_eq(*(int *)s21_output, *(int *)std_output);
    break;
  case 'f':
    s21_sscanf(input, format, (float *)s21_output);
    sscanf(input, format, (float *)std_output);
    ck_assert_float_eq_tol(*(float *)s21_output, *(float *)std_output, 0.00001);
    break;
  case 'd':
    s21_sscanf(input, format, (long double *)s21_output);
    sscanf(input, format, (long double *)std_output);
    ck_assert_ldouble_eq_tol(*(long double *)s21_output,
                             *(long double *)std_output, 0.00001);
    break;
  case 's':
    s21_sscanf(input, format, (char *)s21_output);
    sscanf(input, format, (char *)std_output);
    ck_assert_str_eq((char *)s21_output, (char *)std_output);
    break;
  case 'c':
    s21_sscanf(input, format, (char *)s21_output);
    sscanf(input, format, (char *)std_output);
    ck_assert_int_eq(*(char *)s21_output, *(char *)std_output);
    break;
  case 'h':
    s21_sscanf(input, format, (short *)s21_output);
    sscanf(input, format, (short *)std_output);
    ck_assert_int_eq(*(short *)s21_output, *(short *)std_output);
    break;
  case 'u':
    s21_sscanf(input, format, (short unsigned int *)s21_output);
    sscanf(input, format, (short unsigned int *)std_output);
    ck_assert_int_eq(*(short unsigned int *)s21_output, *(short unsigned int *)std_output);
    break;
  }
}

START_TEST(test_sscanf_integer) {
  int s21_int, std_int;
  testing_sscanf("123", "%d", &s21_int, &std_int, 'i');
  testing_sscanf("-456", "%d", &s21_int, &std_int, 'i');
  testing_sscanf("0", "%d", &s21_int, &std_int, 'i');
  testing_sscanf("+789", "%d", &s21_int, &std_int, 'i');
}
END_TEST

START_TEST(test_sscanf_float) {
  float s21_float, std_float;
  testing_sscanf("123.45", "%f", &s21_float, &std_float, 'f');
  testing_sscanf("-123.45", "%f", &s21_float, &std_float, 'f');
  testing_sscanf("0.0", "%f", &s21_float, &std_float, 'f');
  testing_sscanf("+456.78", "%f", &s21_float, &std_float, 'f');
}
END_TEST

START_TEST(test_sscanf_double) {
  long double s21_double, std_double;
  testing_sscanf("123.45", "%Lf", &s21_double, &std_double, 'd');
  testing_sscanf("-123.45", "%Lf", &s21_double, &std_double, 'd');
  testing_sscanf("0.0", "%Lf", &s21_double, &std_double, 'd');
  testing_sscanf("+456.78", "%Lf", &s21_double, &std_double, 'd');
}
END_TEST

START_TEST(test_sscanf_string) {
  char s21_str[100], std_str[100];
  testing_sscanf("hello", "%s", s21_str, std_str, 's');
  testing_sscanf("world", "%s", s21_str, std_str, 's');
  testing_sscanf("hello world", "%s", s21_str, std_str, 's');
  testing_sscanf("   leading spaces", "%s", s21_str, std_str, 's');
  testing_sscanf("trailing spaces   ", "%s", s21_str, std_str, 's');
}
END_TEST

START_TEST(test_sscanf_mixed) {
  int s21_int;
  float s21_float;
  char s21_str[100];

  int std_int;
  float std_float;
  char std_str[100];

  const char *input = "123 456.78 hello";
  s21_sscanf(input, "%d %f %s", &s21_int, &s21_float, s21_str);
  sscanf(input, "%d %f %s", &std_int, &std_float, std_str);

  ck_assert_int_eq(s21_int, std_int);
  ck_assert_float_eq_tol(s21_float, std_float, 0.00001);
  ck_assert_str_eq(s21_str, std_str);
}
END_TEST

START_TEST(test_sscanf_complex) {
  int s21_int1, s21_int2, std_int1, std_int2;
  float s21_float1, s21_float2, std_float1, std_float2;
  char s21_str1[100], s21_str2[100], std_str1[100], std_str2[100];

  const char *input = "42 3.14 test_string 12345 678.90 another_test";
  s21_sscanf(input, "%d %f %s %d %f %s", &s21_int1, &s21_float1, s21_str1,
             &s21_int2, &s21_float2, s21_str2);
  sscanf(input, "%d %f %s %d %f %s", &std_int1, &std_float1, std_str1,
         &std_int2, &std_float2, std_str2);

  ck_assert_int_eq(s21_int1, std_int1);
  ck_assert_float_eq_tol(s21_float1, std_float1, 0.00001);
  ck_assert_str_eq(s21_str1, std_str1);
  ck_assert_int_eq(s21_int2, std_int2);
  ck_assert_float_eq_tol(s21_float2, std_float2, 0.00001);
  ck_assert_str_eq(s21_str2, std_str2);
}
END_TEST

START_TEST(test_sscanf_empty_input) {
  int s21_int = 66666, std_int = 66666;
  float s21_float = 666.66, std_float = 666.66;
  char s21_str[100] = "66666666", std_str[100] = "66666666";

  // Edge case: Empty input
  testing_sscanf("", "%d", &s21_int, &std_int, 'i');
  testing_sscanf("", "%f", &s21_float, &std_float, 'f');
  testing_sscanf("", "%s", s21_str, std_str, 's');
}
END_TEST

START_TEST(test_sscanf_large_numbers) {
  int s21_int, std_int;

  // Edge case: Large numbers
  testing_sscanf("2147483647", "%d", &s21_int, &std_int, 'i');  // INT_MAX
  testing_sscanf("-2147483648", "%d", &s21_int, &std_int, 'i'); // INT_MIN
}
END_TEST

START_TEST(test_sscanf_floating_point_precision) {
  float s21_float, std_float;

  // Edge case: Floating point precision
  testing_sscanf("3.4028235E+38", "%f", &s21_float, &std_float, 'f'); // FLT_MAX
  testing_sscanf("1.17549435E-38", "%f", &s21_float, &std_float,
                 'f'); // FLT_MIN
}
END_TEST

START_TEST(test_sscanf_special_characters) {
  char s21_str[100], std_str[100];

  // Edge case: Special characters in strings
  testing_sscanf("hello, world!", "%s", s21_str, std_str, 's');
  testing_sscanf("123_456", "%s", s21_str, std_str, 's');
}
END_TEST

START_TEST(test_sscanf_hexadecimal) {
  int s21_int, std_int;
  testing_sscanf("0x1A3", "%x", &s21_int, &std_int, 'i');
  testing_sscanf("0X4B0", "%x", &s21_int, &std_int, 'i');
  testing_sscanf("7F", "%x", &s21_int, &std_int, 'i');
}
END_TEST

START_TEST(test_sscanf_octal) {
  int s21_int, std_int;
  testing_sscanf("0755", "%o", &s21_int, &std_int, 'i');
  testing_sscanf("0123", "%o", &s21_int, &std_int, 'i');
  testing_sscanf("01777", "%o", &s21_int, &std_int, 'i');
}
END_TEST

START_TEST(test_sscanf_char) {
  char s21_char = 'z', std_char = 'z';
  testing_sscanf("a", "%c", &s21_char, &std_char, 'c');
  testing_sscanf("z", "%c", &s21_char, &std_char, 'c');
  testing_sscanf("5", "%c", &s21_char, &std_char, 'c');
}
END_TEST

START_TEST(test_sscanf_width) {
  char s21_str[100], std_str[100];
  testing_sscanf("hello world", "%5s", s21_str, std_str,
                 's'); // Should only read "hello"
  testing_sscanf("1234567890", "%4s", s21_str, std_str,
                 's'); // Should only read "1234"
}
END_TEST

START_TEST(test_sscanf_ignore_spaces) {
  int s21_int, std_int;
  testing_sscanf("   42", "%d", &s21_int, &std_int, 'i');
  testing_sscanf("42   ", "%d", &s21_int, &std_int, 'i');
  testing_sscanf("   42   ", "%d", &s21_int, &std_int, 'i');
}
END_TEST

START_TEST(test_sscanf_multiple_spaces) {
  int s21_int1, s21_int2;
  int std_int1, std_int2;
  s21_sscanf("42   99", "%d %d", &s21_int1, &s21_int2);
  sscanf("42   99", "%d %d", &std_int1, &std_int2);

  ck_assert_int_eq(s21_int1, std_int1);
  ck_assert_int_eq(s21_int2, std_int2);
}
END_TEST

START_TEST(test_sscanf_short_integers) {
  short s21_short = 0, std_short = 0;
  testing_sscanf("32767", "%hd", &s21_short, &std_short, 'h');  // SHRT_MAX
  testing_sscanf("-32768", "%hd", &s21_short, &std_short, 'h'); // SHRT_MIN
  testing_sscanf("123", "%hi", &s21_short, &std_short, 'h');
  testing_sscanf("0123", "%ho", &s21_short, &std_short, 'h');
  testing_sscanf("65535", "%hu", &s21_short, &std_short, 'u');
  testing_sscanf("0x7FFF", "%hx", &s21_short, &std_short, 'h');
  testing_sscanf("0X7FFF", "%hx", &s21_short, &std_short, 'h');
}
END_TEST

// Test suite setup
Suite *sscanf_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("s21_sscanf");

  /* Core test case */
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_sscanf_integer);
  tcase_add_test(tc_core, test_sscanf_float);
  tcase_add_test(tc_core, test_sscanf_double);
  tcase_add_test(tc_core, test_sscanf_string);
  tcase_add_test(tc_core, test_sscanf_mixed);
  tcase_add_test(tc_core, test_sscanf_complex);
  tcase_add_test(tc_core, test_sscanf_empty_input);
  tcase_add_test(tc_core, test_sscanf_large_numbers);
  tcase_add_test(tc_core, test_sscanf_floating_point_precision);
  tcase_add_test(tc_core, test_sscanf_special_characters);
  tcase_add_test(tc_core, test_sscanf_hexadecimal);
  tcase_add_test(tc_core, test_sscanf_octal);
  tcase_add_test(tc_core, test_sscanf_char);
  tcase_add_test(tc_core, test_sscanf_width);
  tcase_add_test(tc_core, test_sscanf_ignore_spaces);
  tcase_add_test(tc_core, test_sscanf_multiple_spaces);
  tcase_add_test(tc_core, test_sscanf_short_integers);
  suite_add_tcase(s, tc_core);

  return s;
}

// Main function to run the tests
int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = sscanf_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
