CC=gcc
COMLFAGS=-Wall -Werror -Wextra -std=c11 -pedantic 
TFLAGS=-o testing -lcheck --coverage 
USERNAME=$(shell whoami)
ifeq ($(shell uname), Linux)
 TFLAGS += -lm -lsubunit
endif

.PHONY: all clean s21_matrix.a format test gcov_report

all: s21_matrix.a test gcov_report 

ifeq ($(shell uname), Darwin)
	TFLAGS += -fprofile-arcs
endif

s21_matrix.a:
	$(CC) $(COMLFAGS) -c *.c
	ar -rc s21_matrix.a *.o
 
test: s21_matrix.a
	@checkmk clean_mode=1  test.check > testing.c
	@$(CC) *.c s21_matrix.a $(TFLAGS)
	./testing


gcov_report:
	@gcov -b . ../ *.c 
	@lcov -d . -c -o coverage.info
	@genhtml -o html_report coverage.info
	@open html_report/index.html

clean:
	@rm -rf *.o testing.c testing *.a *.gcno *.gcda *.gcov *.info
	@rm -rf html_report

format:
	find . -type f -name "*.c" -exec clang-format -style=Google -i {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -i {} \;

format_check:
	find . -type f -name "*.c" -exec clang-format -style=Google -n {} \;
	find . -type f -name "*.h" -exec clang-format -style=Google -n {} \;

brsw:
	eval "$(/opt/goinfre/$(USERNAME)/homebrew/bin/brew shellenv)"
	brew update --force --quiet
	chmod -R go-w "$(brew --prefix)/share/zsh"
