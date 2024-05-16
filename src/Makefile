CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -lcheck
SOURCE=s21_func/*.c testFunc/*.c s21_string_main.c
CLANG=clang-format -i

all: test

test:
	$(CLANG) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test
clean:
	rm -f s21_test

rebuild: clean all