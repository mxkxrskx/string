#include "testFunc/s21_string_test.h"

int main() {
  Suite *suite_array[] = {suite_memchr(),          suite_memcmp(),
                          suite_memcpy(),          suite_strerror(),
                          suite_strlen(),          suite_strncat(),
                          suite_memset(),          suite_strchr(),
                          suite_strrchr(),         suite_strpbrk(),
                          suite_strncpy(),         suite_strncmp(),
                          suite_strtok(),          suite_strcspn(),
                          suite_strstr(),          suite_to_lower(),
                          suite_to_upper(),        suite_trim(),
                          suite_insert(),          suite_sscanf_c(),
                          suite_sscanf_d(),        suite_sscanf_f(),
                          suite_sscanf_i(),        suite_sscanf_n(),
                          suite_sscanf_o(),        suite_sscanf_p(),
                          suite_sscanf_perc(),     suite_sscanf_s(),
                          suite_sscanf_u(),        suite_sscanf_x(),
                          suite_sprintf_flags_d(), suite_sprintf_flags_c(),
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
