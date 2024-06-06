#include "s21_string_test.h"

void testing_strncat(char *dest, const void *str, s21_size_t n) {
  void *orig_res = strncat(dest, str, n);
  void *s21_res = s21_strncat(dest, str, n);

  ck_assert_ptr_eq(orig_res, s21_res);
}

START_TEST(zero_dest_zero_n) {
  char dest[] = "\0";
  const char *str = "adding";
  s21_size_t n = 0;

  testing_strncat(dest, str, n);
}
END_TEST

// START_TEST(zero_dest_single_n) {
//   char dest[] = "\0";
//   const char *str = "adding";
//   s21_size_t n = 1;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(zero_dest_normal_n) {
//   char dest[] = "1";
//   const char *str = "adding";
//   s21_size_t n = 4;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(zero_dest_max_n) {
//   char dest[] = "\0";
//   const char *str = "adding";
//   s21_size_t n = 6;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(single_dest_zero_n) {
//   char dest[] = "1";
//   const char *str = "adding";
//   s21_size_t n = 0;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(single_dest_single_n) {
//   char dest[] = "1";
//   const char *str = "adding";
//   s21_size_t n = 1;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(single_dest_normal_n) {
//   char dest[] = "1";
//   const char *str = "adding";
//   s21_size_t n = 4;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(single_dest_max_n) {
//   char dest[] = "1";
//   const char *str = "adding";
//   s21_size_t n = 6;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(normal_dest_zero_n) {
//   char dest[] = "123";
//   const char *str = "adding";
//   s21_size_t n = 0;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(normal_dest_single_n) {
//   char dest[] = "123";
//   const char *str = "adding";
//   s21_size_t n = 1;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(normal_dest_normal_n) {
//   char dest[] = "123";
//   const char *str = "adding";
//   s21_size_t n = 4;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST
//
// START_TEST(normal_dest_max_n) {
//   char dest[] = "123";
//   const char *str = "adding";
//   s21_size_t n = 6;
//
//   testing_strncat(dest, str, n);
// }
// END_TEST

Suite *suite_strncat(void) {
  Suite *s = suite_create("STRNCAT");
  TCase *tc = tcase_create("memset_tc");

  tcase_add_test(tc, zero_dest_zero_n);
  //  tcase_add_test(tc, zero_dest_single_n);
  //  tcase_add_test(tc, zero_dest_normal_n);
  //  tcase_add_test(tc, zero_dest_max_n);
  //
  //  tcase_add_test(tc, single_dest_zero_n);
  //  tcase_add_test(tc, single_dest_single_n);
  //  tcase_add_test(tc, single_dest_normal_n);
  //  tcase_add_test(tc, single_dest_max_n);
  //
  //  tcase_add_test(tc, normal_dest_zero_n);
  //  tcase_add_test(tc, normal_dest_single_n);
  //  tcase_add_test(tc, normal_dest_normal_n);
  //  tcase_add_test(tc, normal_dest_max_n);

  suite_add_tcase(s, tc);
  return s;
}
