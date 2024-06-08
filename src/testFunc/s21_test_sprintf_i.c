#include "s21_string_test.h"

void testing_sprinf_i(const char *format, int x) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";
  ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
  ck_assert_str_eq(original, s21);
}

START_TEST(i_normal) { testing_sprinf_i("%i", 0); }
END_TEST

START_TEST(i_flag_1) { testing_sprinf_i("%+i", 0); }
END_TEST

START_TEST(i_flag_2) { testing_sprinf_i("%010i", 52); }
END_TEST

START_TEST(i_flag_3) { testing_sprinf_i("% +10i", 52); }
END_TEST

START_TEST(i_flag_4) { testing_sprinf_i("% -52i", 52); }
END_TEST

START_TEST(i_flag_7) { testing_sprinf_i("% -04i", -52); }
END_TEST

START_TEST(i_flag_5) { testing_sprinf_i("%+010i", 52); }
END_TEST

START_TEST(i_flag_6) { testing_sprinf_i("% +010i", 52); }
END_TEST

START_TEST(i_flag_8) { testing_sprinf_i("% -+010i", 52); }
END_TEST

START_TEST(i_flag_9) { testing_sprinf_i("% 10i", -52); }
END_TEST

START_TEST(i_flag_precision_1) { testing_sprinf_i("%10.5i", -52); }
END_TEST

START_TEST(i_flag_precision_2) { testing_sprinf_i("%-10.5i", -52); }
END_TEST

START_TEST(i_flag_precision_3) { testing_sprinf_i("%-010.5i", -52); }
END_TEST

START_TEST(i_flag_precision_4) { testing_sprinf_i("% -+10.5i", 52); }
END_TEST

START_TEST(test_sprintf_i_INT_MIN) { testing_sprinf_i("%i", INT_MIN); }
END_TEST

START_TEST(test_sprintf_i_octal) {
  int x = 012;
  const char *format = "The value of x is %i";
  testing_sprinf_i(format, x);
}
END_TEST

START_TEST(test_sprintf_i_hex) {
  int x = 0xA;
  const char *format = "The value of x is %i";
  testing_sprinf_i(format, x);
}
END_TEST

//START_TEST(test_sprintf_i_binary) {
//  int x = 0b1010;
//  const char *format = "The value of x is %i";
//  testing_sprinf_i(format, x);
//}
//END_TEST

START_TEST(test_sprintf_i_octal_with_plus) {
  int x = 012;
  const char *format = "The value of x is %+i";
  testing_sprinf_i(format, x);
}
END_TEST

START_TEST(test_sprintf_i_hex_with_zero) {
  int x = 0xA;
  const char *format = "The value of x is %0i";
  testing_sprinf_i(format, x);
}
END_TEST

Suite *suite_sprintf_flags_i(void) {
  Suite *s = suite_create("SPRINTF_i");
  TCase *tc = tcase_create("sprintf_tc_i");

  tcase_add_test(tc, i_normal);
  tcase_add_test(tc, i_flag_1);
  tcase_add_test(tc, i_flag_2);
  tcase_add_test(tc, i_flag_3);
  tcase_add_test(tc, i_flag_4);
  tcase_add_test(tc, i_flag_5);
  tcase_add_test(tc, i_flag_6);
  tcase_add_test(tc, i_flag_7);
  tcase_add_test(tc, i_flag_8);
  tcase_add_test(tc, i_flag_9);
  tcase_add_test(tc, i_flag_precision_1);
  tcase_add_test(tc, i_flag_precision_2);
  tcase_add_test(tc, i_flag_precision_3);
  tcase_add_test(tc, i_flag_precision_4);
  tcase_add_test(tc, test_sprintf_i_INT_MIN);
  tcase_add_test(tc, test_sprintf_i_octal);
  tcase_add_test(tc, test_sprintf_i_hex);
//  tcase_add_test(tc, test_sprintf_i_binary);
  tcase_add_test(tc, test_sprintf_i_octal_with_plus);
  tcase_add_test(tc, test_sprintf_i_hex_with_zero);

  suite_add_tcase(s, tc);
  return s;
}
