CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -lcheck
SOURCE=s21_sprintf.c s21_parse_number.c s21_strlen.c s21_char_utils.c s21_strchr.c s21_strncat.c

all: test

test:
	$(CLANG) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test
clean:
	rm -f s21_test

rebuild: clean all 