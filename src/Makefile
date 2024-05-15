CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -lcheck
SOURCE=*.c testFunc/*.c

all: test

test:
	$(CC) $(CFLAGS) $(SOURCE) -o s21_test
clean:
	rm -f s21_test

rebuild: clean all