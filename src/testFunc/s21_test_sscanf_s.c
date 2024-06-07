#include "s21_string_test.h"

START_TEST(strings1) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};

  const char str[] = "Aboba Floppa Keppa Shleppa Anuroba";
  const char fstr[] = "%s %s %s %s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings_mixed3) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};

  long long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0, d1 = 0, d2 = 0;

  const char str[] = "Aboba 123 Floppa -3 Keppa 4444Shleppa 333Anuroba 3";
  const char fstr[] = "%s%ld%s%d%s%d%s";

  int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, &b1, s3, &c1, s4, &d1);
  int16_t res2 = s21_sscanf(str, fstr, s5, &a2, s6, &b2, s7, &c2, s8, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings2) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%s%s%s%s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings3) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};

  const char str[] = "aboba\tkepaboba floppa shleppa koooppa ap p p p p";
  const char fstr[] = "%*s%*s%*s%*s";

  int16_t res1 = s21_sscanf(str, fstr);
  int16_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings4) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%1s%1s%1s%1s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings5) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%3s%3s%3s%3s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings6) {
  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};

  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};

  const char str[] = "aboba\tshlepa\tasdfasdf\tasdfasdf";
  const char fstr[] = "%150s%1s%1s\t%3s";

  int16_t res1 = s21_sscanf(str, fstr, s1, s2, s3, s4);
  int16_t res2 = sscanf(str, fstr, s5, s6, s7, s8);

  ck_assert_int_eq(res1, res2);

  ck_assert_str_eq(s1, s5);
  ck_assert_str_eq(s2, s6);
  ck_assert_str_eq(s3, s7);
  ck_assert_str_eq(s4, s8);
}
END_TEST

START_TEST(strings_mixed1) {
  unsigned long a1 = 0, a2 = 0, b1 = 0, b2 = 0, c1 = 0, c2 = 0;
  long d1 = 0, d2 = 0;
  long double e1 = 0, e2 = 0;

  const char str[] = "4444444"
                     "eeeeeee\teeeeeee";
  const char fstr[] = "%5s %1s %*s %*s %lu %s %lu %lu %ld %Lf %33s";

  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};
  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};
  char s7[BUFF] = {'\0'};
  char s8[BUFF] = {'\0'};
  char s9[BUFF] = {'\0'};
  char s10[BUFF] = {'\0'};

  int16_t res1 = sscanf(str, fstr, s7, s9, &a1, s5, &b1, &c1, &d1, &e1, s1);
  int16_t res2 = sscanf(str, fstr, s8, s10, &a2, s6, &b2, &c2, &d2, &e2, s2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(strings_mixed2) {
  int d1 = 0, d2 = 0, b1 = 0, b2 = 0, a1 = 0, a2 = 0;
  long long v1, v2;

  const char str[] = "1 1 1 1 1 -1";
  const char fstr[] = "%1s %5d %1s %1s %d %lld %d";

  char s1[BUFF] = {'\0'};
  char s2[BUFF] = {'\0'};
  char s3[BUFF] = {'\0'};
  char s4[BUFF] = {'\0'};
  char s5[BUFF] = {'\0'};
  char s6[BUFF] = {'\0'};

  int16_t res1 = s21_sscanf(str, fstr, s1, &a1, s2, s3, &b1, &v1, &d1);
  int16_t res2 = sscanf(str, fstr, s4, &a2, s5, s6, &b2, &v2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(s1, s2);
  ck_assert_str_eq(s3, s4);
  ck_assert_str_eq(s5, s6);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

Suite *suite_sscanf_s(void) {
  Suite *s = suite_create("SSCANF_S");
  TCase *tc = tcase_create("sscanf_tc");

  tcase_add_test(tc, strings1);
  tcase_add_test(tc, strings2);
  tcase_add_test(tc, strings3);
  tcase_add_test(tc, strings4);
  tcase_add_test(tc, strings5);
  tcase_add_test(tc, strings6);
  tcase_add_test(tc, strings_mixed1);
  tcase_add_test(tc, strings_mixed2);
  tcase_add_test(tc, strings_mixed3);

  suite_add_tcase(s, tc);
  return s;
}
