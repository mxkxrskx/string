#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include "s21_parse_number.h"
#include "s21_string.h"

#define MAXLEN 100

typedef enum { DEFAULT, SHORT_INT, LONG_INT, LONG_DOUBLE } LengthDescription;
typedef enum { NO_ERROR, NULL_PTR, ASSIGN_ERROR, NO_COUNT } Error;
typedef enum { SIGNED, UNSIGNED } Type;

typedef struct {
  va_list *args;
  long long width;
  int suppress;
  LengthDescription length;
  int base;
  Type type;
  Error error;
  const char *str_start;
} ScanContext;

int s21_sscanf(const char *str, const char *format, ...);
int process_format_string(const char *str, const char *format, va_list *args);

ScanContext init_scan_context(va_list *args, const char *str_start);
void parse_format_specifier(char **str, ScanContext *ctx, char **format);
bool match_literal(char **str, char **format);

void parse_suppress(ScanContext *ctx, char **format);
void parse_width(ScanContext *ctx, char **format);
void parse_length_description(ScanContext *ctx, char **format);
void parse_specifier(char **str, ScanContext *ctx, char **format);

void handle_char_case(char **str, ScanContext *ctx);
void handle_decimal_case(char **str, ScanContext *ctx);
void handle_integer_case(char **str, ScanContext *ctx);
void handle_float_case(char **str, ScanContext *ctx);
void handle_octal_case(char **str, ScanContext *ctx);
void handle_string_case(char **str, ScanContext *ctx);
void handle_unsigned_case(char **str, ScanContext *ctx);
void handle_hex_case(char **str, ScanContext *ctx);
void handle_pointer_case(char **str, ScanContext *ctx);
void handle_count_case(char **str, ScanContext *ctx);
void handle_percent_case(char **str, ScanContext *ctx, char **format);

void parse_char_specifier(char **str, ScanContext *ctx);
void parse_decimal_specifier(char **str, ScanContext *ctx);
void parse_float_specifier(char **str, ScanContext *ctx);
void parse_string_specifier(char **str, ScanContext *ctx);
void skip_percent(char **str, ScanContext *ctx, char **format);
void set_count_specifier(char **str, ScanContext *ctx);

char parse_char(char **str, ScanContext *ctx);
long long parse_decimal_integer(char **str, ScanContext *ctx);
long double parse_floating_point(char **str, ScanContext *ctx);

void set_signed_value(long long decimal_integer, ScanContext *ctx);
void set_unsigned_value(long long decimal_integer, ScanContext *ctx);

int parse_fractional_part(char **str, ScanContext *ctx, long double *fraction);
int parse_exponent_part(char **str, ScanContext *ctx, long double *exp_value);

void s21_isnull(char **str, ScanContext *ctx);
int parse_sign(char **str, ScanContext *ctx);
int parse_base(char **str);
int skip_base(char **str, int base);

#endif /* S21_SSCANF_H */
