#include "s21_string_test.h"

void testing_strtok(char *str, const char *delim) {
  // make str_copy
  s21_size_t len = s21_strlen(str);

  void *str_copy = malloc(len + 1);
  s21_memcpy(str_copy, str, len);

  // comparison
  char *s21_res = s21_strtok(str, delim);
  char *orig_res = strtok(str_copy, delim);

  if (orig_res)
    ck_assert_str_eq(orig_res, s21_res);
  else
    ck_assert_ptr_eq(orig_res, s21_res);

  while (orig_res != NULL) {
    s21_res = s21_strtok(NULL, delim);
    orig_res = strtok(NULL, delim);

    if (orig_res)
      ck_assert_str_eq(orig_res, s21_res);
    else
      ck_assert_ptr_eq(orig_res, s21_res);
  }
  if (str_copy)
    free(str_copy);
}

// самый обычный тест
START_TEST(normal_line) {
  char src[] = "hello world bro";
  char delim[] = " ";

  testing_strtok(src, delim);
}
END_TEST

// много разделителей
START_TEST(many_delim) {
  char src[] = "hel.lo wo.rld b.roooooooodiiiiiiidiiiiooos";
  char delim[] = " .d";

  testing_strtok(src, delim);
}
END_TEST

// нету разделителей
START_TEST(not_delim) {
  char src[] = "hel.lo wo.rld b.roooooooodiiiiiiidiiiiooos";
  char delim[] = "";

  testing_strtok(src, delim);
}
END_TEST

// нет нужного разделителя
START_TEST(not_need_delim) {
  char src[] = "hel.lo wo.rld b.roooooooodiiiiiiidiiiiooos";
  char delim[] = "q";

  testing_strtok(src, delim);
}
END_TEST

// пустая строка
START_TEST(empty_str) {
  char src[] = "";
  char delim[] = " .d";

  testing_strtok(src, delim);
}
END_TEST

// много разделителей подряд
START_TEST(long_delim) {
  char src[] = "hellloooooooooooooooooooo o o o o wo.rld b.os";
  char delim[] = " o.d";

  testing_strtok(src, delim);
}
END_TEST

Suite *suite_strtok(void) {
  Suite *s = suite_create("STRTOK");
  TCase *tc = tcase_create("strtok_tc");

  tcase_add_test(tc, normal_line);
  tcase_add_test(tc, many_delim);
  tcase_add_test(tc, not_delim);
  tcase_add_test(tc, not_need_delim);
  tcase_add_test(tc, empty_str);
  tcase_add_test(tc, long_delim);

  suite_add_tcase(s, tc);
  return s;
}