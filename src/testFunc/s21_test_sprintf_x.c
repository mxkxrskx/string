#include "s21_string_test.h"

void testing_sprintf_x(const char *format, int x) {
    char original[BUFF] = "\0";
    char s21[BUFF] = "\0";
    sprintf(original, format, x);
    s21_sprintf(s21, format, x);
    //ck_assert_int_eq(sprintf(original, format, x), s21_sprintf(s21, format, x));
    ck_assert_str_eq(original, s21);
}

START_TEST(X_normal){
    testing_sprintf_x("%X", 42);
}
END_TEST

START_TEST(X_flag_1){
    testing_sprintf_x("%#X", 255);
}
END_TEST

START_TEST(X_flag_2){
    testing_sprintf_x("%010X", 123456789);
}
END_TEST

START_TEST(X_flag_3){
    testing_sprintf_x("% #10X", 987654321);
}
END_TEST

START_TEST(X_flag_4){
    testing_sprintf_x("%-52X", 52);
}
END_TEST

START_TEST(X_flag_5){
    testing_sprintf_x("%+010X", 10101337);
}
END_TEST

START_TEST(X_flag_6){
    testing_sprintf_x("% 010X", 255);
}
END_TEST

START_TEST(X_flag_7){
    testing_sprintf_x("%-010X", 257);
}
END_TEST

START_TEST(X_flag_8){
    testing_sprintf_x("%#-10X", 255);
}
END_TEST

START_TEST(X_flag_precision_1){
    testing_sprintf_x("%.5X", 1024);
}
END_TEST

START_TEST(X_flag_precision_2){
    testing_sprintf_x("%#.5X", 255);
}
END_TEST

START_TEST(X_flag_precision_3){
    testing_sprintf_x("%-.5X", 32);
}
END_TEST

START_TEST(X_flag_precision_4){
    testing_sprintf_x("%#-.5X", 258);
}
END_TEST

START_TEST(X_flag_precision_5){
    testing_sprintf_x("%#+010X", 9);
}

START_TEST(x_normal){
    testing_sprintf_x("%x", 42);
}
END_TEST

START_TEST(x_flag_1){
    testing_sprintf_x("%#x", 255);
}
END_TEST

START_TEST(x_flag_2){
    testing_sprintf_x("%010x", 1234567899);
}
END_TEST

START_TEST(x_flag_3){
    testing_sprintf_x("% #10x", 987654321);
}
END_TEST

START_TEST(x_flag_4){
    testing_sprintf_x("%-52x", 52);
}
END_TEST

START_TEST(x_flag_5){
    testing_sprintf_x("%+010x", 10101337);
}
END_TEST

START_TEST(x_flag_6){
    testing_sprintf_x("% 010x", 255);
}
END_TEST

START_TEST(x_flag_7){
    testing_sprintf_x("%-010x", 257);
}
END_TEST

START_TEST(x_flag_8){
    testing_sprintf_x("%#-10x", 255);
}
END_TEST

START_TEST(x_flag_precision_1){
    testing_sprintf_x("%.5x", 1024);
}
END_TEST

START_TEST(x_flag_precision_2){
    testing_sprintf_x("%#.5x", 255);
}
END_TEST

START_TEST(x_flag_precision_3){
    testing_sprintf_x("%-.5x", 32);
}
END_TEST

START_TEST(x_flag_precision_4){
    testing_sprintf_x("%#-.5x", 258);
}
END_TEST

START_TEST(x_flag_precision_5){
    testing_sprintf_x("%#+010X", 19);
}



Suite *suite_sprintf_flags_x(void){
    Suite *s = suite_create("SPRINTF_X");
    TCase *tc = tcase_create("sprintf_tc_X");

    tcase_add_test(tc, X_normal);
    tcase_add_test(tc, X_flag_1);
    tcase_add_test(tc, X_flag_2);
    tcase_add_test(tc, X_flag_3);
    tcase_add_test(tc, X_flag_4);
    tcase_add_test(tc, X_flag_5);
    tcase_add_test(tc, X_flag_6);
    tcase_add_test(tc, X_flag_7);
    tcase_add_test(tc, X_flag_8);
    tcase_add_test(tc, X_flag_precision_1);
    tcase_add_test(tc, X_flag_precision_2);
    tcase_add_test(tc, X_flag_precision_3);
    tcase_add_test(tc, X_flag_precision_4);
    tcase_add_test(tc, X_flag_precision_5);

    tcase_add_test(tc, x_normal);
    tcase_add_test(tc, x_flag_1);
    tcase_add_test(tc, x_flag_2);
    tcase_add_test(tc, x_flag_3);
    tcase_add_test(tc, x_flag_4);
    tcase_add_test(tc, x_flag_5);
    tcase_add_test(tc, x_flag_6);
    tcase_add_test(tc, x_flag_7);
    tcase_add_test(tc, x_flag_8);
    tcase_add_test(tc, x_flag_precision_1);
    tcase_add_test(tc, x_flag_precision_2);
    tcase_add_test(tc, x_flag_precision_3);
    tcase_add_test(tc, x_flag_precision_4);
    tcase_add_test(tc, x_flag_precision_5);

    suite_add_tcase(s, tc);
    return s;
}