CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -pedantic -lm
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
TEST_FLAGS = -lcheck
SOURCES = $(wildcard s21_func/*.c)
TESTS = testFunc/*.c s21_string_main.c
OBJECTS = $(SOURCES:.c=.o)
CLANG = clang-format -i

ifeq ($(OS), Windows_NT)
    SYSTEM := Windows
else
    SYSTEM := $(shell uname -s)
    ifeq ($(SYSTEM), Linux)
		TEST_FLAGS += -lsubunit -lrt -lm
	endif
	ifeq ($(SYSTEM), Darwin)
	endif
endif

all: gcov_report

s21_string.a: $(OBJECTS)
	ar rcs s21_string.a $(OBJECTS)
	ranlib s21_string.a
	rm -rf $(OBJECTS)
	
clang:
	$(CLANG) $(SOURCES) $(TESTS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: clean s21_string.a
	$(CC) $(CFLAGS) $(TESTS) s21_string.a -o s21_test $(TEST_FLAGS)
	
gcov_report: clean
	$(CC) $(GCOV_FLAGS) $(TESTS) $(SOURCES) -o report.out $(TEST_FLAGS)
	./report.out
	lcov -t "gcov_report" -o coverage.info -c -d .
	genhtml -o ./report coverage.info
	rm -f *.gcno *.gcda *.info *.gcov
	open ./report/index-sort-f.html

clean:
	rm -f *.o *.a *.out *.gcno *.gcda s21_test
	rm -rf report

rebuild: clean all
