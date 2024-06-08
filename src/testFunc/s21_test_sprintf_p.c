#include "s21_string_test.h"

void testing_sprintf_p(const char *format, void *ptr) {
  char original[BUFF] = "\0";
  char s21[BUFF] = "\0";

  ck_assert_int_eq(sprintf(original, format, ptr),
                   s21_sprintf(s21, format, ptr));
  ck_assert_str_eq(original, s21);
}

START_TEST(p_normal) {
  void *ptr = NULL;
  testing_sprintf_p("%p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_1) {
  void *ptr = (void *)0x1234;
  testing_sprintf_p("%#p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_2) {
  void *ptr = (void *)0xabcdef;
  testing_sprintf_p("%010p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_3) {
  void *ptr = (void *)0x987654;
  testing_sprintf_p("% #10p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_4) {
  void *ptr = (void *)0x52;
  testing_sprintf_p("%-52p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_5) {
  void *ptr = (void *)0x10101337;
  testing_sprintf_p("%+010p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_6) {
  void *ptr = (void *)0x100;
  testing_sprintf_p("% 010p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_7) {
  void *ptr = (void *)0x257;
  testing_sprintf_p("%-010p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_8) {
  void *ptr = (void *)0x255;
  testing_sprintf_p("%#-10p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_precision_1) {
  void *ptr = (void *)0x1024;
  testing_sprintf_p("%.5p", (void *)&ptr);
}
END_TEST

START_TEST(p_flag_precision_2) {
  void *ptr = (void *)0x255;
  testing_sprintf_p("%#.5p", (void *)&ptr);
}
END_TEST

Suite *suite_sprintf_flags_p(void) {
  Suite *s = suite_create("SPRINTF_P");
  TCase *tc = tcase_create("sprintf_tc_P");

  tcase_add_test(tc, p_normal);
  tcase_add_test(tc, p_flag_1);
  tcase_add_test(tc, p_flag_2);
  tcase_add_test(tc, p_flag_3);
  tcase_add_test(tc, p_flag_4);
  tcase_add_test(tc, p_flag_5);
  tcase_add_test(tc, p_flag_6);
  tcase_add_test(tc, p_flag_7);
  tcase_add_test(tc, p_flag_8);
  tcase_add_test(tc, p_flag_precision_1);
  tcase_add_test(tc, p_flag_precision_2);

  suite_add_tcase(s, tc);
  return s;
}