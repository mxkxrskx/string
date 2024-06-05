CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -c

SOURCE=s21_func/*.c testFunc/*.c s21_string_main.c
SOURCE_FUNC= s21_func/*.c
OBJS_FUNC= $(SOURCE_FUNC:.c=.o)
CLANG=clang-format -i

all: test s21_string.a gcov_report

s21_string.a:
	$(CLANG) $(SOURCE_FUNC)
	$(CC) $(CFLAGS) $(SOURCE_FUNC)

	ar rcs s21_string.a *.o
	ranlib s21_string.a

gcov_report:


clean:
	rm -f *.o
	rm -f s21_string.a
	rm -f s21_test

rebuild: clean all 