#include <check.h>
#include <string.h>
#include <stdio.h>
#include "../s21_func/s21_string.h"

void run_test_cases(Suite *testcase);

Suite *suite_memchr(void);
Suite *suite_memcmp(void);
Suite *suite_memcpy(void);
Suite *suite_memset(void);
Suite *suite_strerror(void);
Suite *suite_strlen(void);
Suite *suite_strncat(void);
Suite *suite_strchr(void);
Suite *suite_strrchr(void);
Suite *suite_strpbrk(void);
Suite *suite_strncpy(void);
Suite *suite_strncmp(void);
Suite *suite_strtok(void);
Suite *suite_strcspn(void);
Suite *suite_strstr(void);
Suite *suite_to_lower(void);
Suite *suite_to_upper(void);
Suite *suite_trim(void);
Suite *suite_insert(void);

Suite *suite_sscanf_c(void);
Suite *suite_sscanf_d(void);
Suite *suite_sscanf_f(void);
Suite *suite_sscanf_i(void);
Suite *suite_sscanf_n(void);
Suite *suite_sscanf_o(void);
Suite *suite_sscanf_p(void);
Suite *suite_sscanf_perc(void);
Suite *suite_sscanf_s(void);
Suite *suite_sscanf_u(void);
Suite *suite_sscanf_x(void);

Suite *suite_sprintf_flags_c(void);
Suite *suite_sprintf_flags_d(void);
Suite *suite_sprintf_flags_e(void);
Suite *suite_sprintf_flags_f(void);
Suite *suite_sprintf_flags_i(void);
Suite *suite_sprintf_flags_s(void);
Suite *suite_sprintf_flags_u(void);
Suite *suite_sprintf_flags_o(void);
Suite *suite_sprintf_flags_x(void);
Suite *suite_sprintf_flags_g(void);
Suite *suite_sprintf_flags_p(void);
Suite *suite_sprintf_flags_n(void);
