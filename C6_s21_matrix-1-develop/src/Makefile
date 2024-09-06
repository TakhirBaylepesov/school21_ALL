CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

HEADERS = s21_matrix.h
SOURCE_ALL = $(wildcard function/*.c)

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SOURCE_ALL))

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -o $@

.PHONY: all clean rebuild test personal gcov_report check

all: s21_matrix.a test gcov_report

s21_matrix.a: $(OBJ_LIBRARY)
	ar rcs s21_matrix.a $(OBJ_LIBRARY)
	ranlib s21_matrix.a
	rm -rf ./function/*.o

test: s21_matrix.a tests/unit_test.c
	gcc $(CFLAGS) tests/unit_test.c s21_matrix.a -o test.out -lcheck -lsubunit -lm
	./test.out

personal: s21_matrix.a tests/personal.c
	gcc $(CFLAGS) tests/personal.c s21_matrix.a -o personal_test.out -lcheck -lsubunit -lm
	./personal_test.out

gcov_report: s21_matrix.a tests/unit_test.c
	gcc $(CFLAGS) $(GCOVFLAGS) tests/unit_test.c $(SOURCE_ALL) -o report.out -lcheck -lsubunit -lm
	./report.out
	gcov -f *.gcda *.gcno
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html || echo "Report generated at ./report/index.html"

check:
	clang-format -style=Google -n ./*/*.c

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
