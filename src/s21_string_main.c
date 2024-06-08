#include "testFunc/s21_string_test.h"

int main() {
  Suite *suite_array[] = {suite_sprintf_flags_d(), suite_sprintf_flags_c(),
                          suite_sprintf_flags_u(), suite_sprintf_flags_s(),
                          suite_sprintf_flags_f(), suite_sprintf_flags_i(),
                          suite_sprintf_flags_e(), suite_sprintf_flags_o(),
                          suite_sprintf_flags_x(), suite_sprintf_flags_p(),
                          suite_sprintf_flags_g(), suite_sprintf_flags_n()};
  for (unsigned long i = 0; i < sizeof(suite_array) / sizeof(suite_array[0]);
       i++) {
    run_test_cases(suite_array[i]);
    printf("\n");
  }
  return 0;
}

void run_test_cases(Suite *testcase) {
  SRunner *sr = srunner_create(testcase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}
