#include "testFunc/s21_string_test.h"
#define COUNT 9


int main(){
    Suite *suite_array[] = {suite_memchr(), suite_memcmp(), suite_memcpy(), suite_strerror(), suite_strlen(), suite_strncat(), suite_memset(), suite_strchr(), suite_strpbrk()};
    for(int i = 0; i < COUNT; i++){
        run_test_cases(suite_array[i]);
        printf("\n");
    }
    return 0;
}

void run_test_cases(Suite *testcase){
    SRunner *sr = srunner_create(testcase);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    srunner_free(sr);
}