#CC=gcc
#CFLAGS=-Wall -Wextra -Werror -std=c11 -c
#
#SOURCE=s21_func/*.c testFunc/*.c s21_string_main.c
#SOURCE_FUNC= s21_func/*.c
#OBJS_FUNC= $(SOURCE_FUNC:.c=.o)
#CLANG=clang-format -i
#
#all: s21_string.a gcov_report
#
#s21_string.a:
#	$(CLANG) $(SOURCE_FUNC)
#	$(CC) $(CFLAGS) $(SOURCE_FUNC)
#
#	ar rcs s21_string.a *.o
#	ranlib s21_string.a
#
#gcov_report:
#
#
#clean:
#	rm -f *.o
#	rm -f s21_string.a
#	rm -f s21_test
#
#rebuild: clean all
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
CHECK = -lcheck
SOURCES = $(wildcard s21_func/*.c)
TESTS = testFunc/*.c s21_string_main.c
OBJECTS = $(SOURCES:.c=.o)
CLANG = clang-format -i

all: s21_string.a gcov_report

s21_string.a: clang $(OBJECTS)
	ar rcs s21_string.a $(OBJECTS)
	ranlib s21_string.a
	rm -rf $(OBJECTS)
	
clang:
	$(CLANG) $(SOURCES)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: s21_string.a
	$(CC) $(CFLAGS) $(TESTS) s21_string.a -o s21_test $(CHECK)
	
gcov_report: 
	$(CC) $(GCOV_FLAGS) $(TESTS) $(SOURCES) -o report.out -lm -lcheck
	./report.out
#	gcov -f $(SOURCES)
	lcov -t "gcov_report" -o coverage.info -c -d .
	genhtml -o ./report coverage.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index-sort-f.html

clean:
	rm -f *.o *.a *.gcno *.gcda s21_test

rebuild: clean all
