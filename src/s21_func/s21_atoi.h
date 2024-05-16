#ifndef S21_ATOI_H
#define S21_ATOI_H

bool is_sign(const char c);
int get_sign(char **ptr);
int s21_atoi(char **ptr);
int s21_atoi_decimal(char **ptr);
float handle_float(char **ptr);
float s21_atoi_float(char **ptr);

#endif // S21_ATOI_H