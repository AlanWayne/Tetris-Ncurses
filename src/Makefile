.PHONY: all test clean dvi pdf
CC = gcc
TITLE = tetris
MAIN_FILES = gui/cli/main.c
FRONT_FILES = gui/cli/draw.c gui/cli/front_init.c gui/cli/print.c
BACK_FILES = $(wildcard brick_game/tetris/*.c) 
TEST_FILES = test/test.c
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lncursesw -lm
TFLAGS = -lcheck -pthread -lsubunit -L. -ltetris
GFLAGS = -fprofile-arcs -ftest-coverage
OBJECTS=$(BACK_FILES:.c=.o)

all: clean install

install:
	@mkdir build
	@$(CC) $(CFLAGS) $(MAIN_FILES) $(FRONT_FILES) $(BACK_FILES) $(LFLAGS) -o build/tetris

uninstall:
	@rm -rf build

run:
	@build/tetris

test: clean $(TEST_FILES) tetris.a
	@$(CC) $(CFLAGS) $(TEST_FILES) $(BACK_FILES) $(LFLAGS) $(TFLAGS) -o test.out
	@./test.out

tetris.a: $(OBJECTS)
	@ar rc libtetris.a $(OBJECTS)

gcov_report: clean $(OBJECTS)
# @$(CC) -c $(CFLAGS) $(LFLAGS) $(GFLAGS) $(BACK_FILES)
	@mkdir build
	@ar rcs libtetris.a $(OBJECTS)
	@$(CC) -o gcov.out $(TEST_FILES) $(BACK_FILES) $(LFLAGS) $(TFLAGS) $(GFLAGS) -lgcov
	@rm -f *.o
	@./gcov.out
	@lcov -c -d . -o coverage.info
	@genhtml coverage.info -o gcov_report
	@open gcov_report/index.html

seg: clean
	@$(CC) $(FRONT_FILES) $(BACK_FILES) $(LFLAGS) -o tetris -g
	@gdb ./tetris

clang:
	@cp ../materials/linters/.clang-format .clang-format
	@clang-format -i $(FRONT_FILES) $(BACK_FILES) $(TEST_FILES)
	@rm -rf .clang-format

clean: uninstall
	@rm -rf *.o *.a *.gcno *.out *.info *.gcda brick_game/tetris/*.o gcov_report *.bin \
	dvi/*.aux dvi/*.log dvi/*.out dvi/*.pdf *.log

valgrind: 
	@valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all ./tetris

dist:
	@tar -czvf tetris.tar.gz build
	
TEX=dvi/documentation.tex
OUTPUT_DIR=dvi
TARGET=$(OUTPUT_DIR)/documentation

dvi: $(TARGET).dvi $(TARGET).pdf

$(TARGET).dvi: $(TEX)
	@xelatex -output-directory=$(OUTPUT_DIR) -interaction=batchmode $< > /dev/null 2>&1

$(TARGET).pdf: $(TEX)
	@xelatex -output-directory=$(OUTPUT_DIR) -interaction=batchmode $< > /dev/null 2>&1
