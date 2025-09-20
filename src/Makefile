CC = gcc
FLAGS = -Wall -Wextra -std=c11
CURSES_FLAG =  -lncurses
SQLFLAG = -lsqlite3
TEST_DIR = tests
TEST_RUNNER = tests/build/test_runner

SRC_GUI = gui/cli/user_screen.c
SRC_brick_game = brick_game/tetris/tetris.c \
				brick_game/lib_spec.c
SRC_DB = brick_game/tetris/dbscore.c
SRC_TXT = brick_game/tetris/txtscore.c

DIST_DIR = dist
DIST_NAME = brick_game_v1.0.tar.gz
DIST_FILES = $(SRC_brick_game) $(SRC_GUI) $(SRC_DB) $(SRC_TXT) headers Makefile Doxyfile

BUILD_DIR = build
OUTPUT_DIR = tests/report
TBD = tests/build

LINK_TEST_LIBS = -lcheck -lm -lsubunit
VALGRIND = valgrind --tool=memcheck --leak-check=full ./$(TEST_RUNNER)

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	LINK_TEST_LIBS = -lcheck -lm
	VALGRIND = echo "valgrind is not supported on MacOS"
	CLANG_FORMAT = clang_format
endif

# TODO: dvi

all: play

play: install
	$(BUILD_DIR)/tetris

play_DB: install_DB
	$(BUILD_DIR)/tetris

install: uninstall brick_game.a
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(SRC_GUI) $(CURSES_FLAG) brick_game.a -o $(BUILD_DIR)/tetris

install_DB: uninstall brick_game.a_DB
	mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(SRC_GUI) $(CURSES_FLAG) brick_game.a $(SQLFLAG) -o $(BUILD_DIR)/tetris

uninstall: clean
	rm -rf $(BUILD_DIR)
	rm -rf score.txt score.db

dvi:
	rm -rf doxygen
	doxygen && open doxygen/html/index.html

dist: clean
	mkdir -p $(DIST_DIR)
	tar -czf $(DIST_DIR)/$(DIST_NAME) $(DIST_FILES)
	echo "Archive created!"


brick_game.a: $(SRC_brick_game) $(SRC_TXT)
	$(CC) $(FLAGS) -c $(SRC_brick_game) $(SRC_TXT)
	ar rcs $@ *.o

brick_game.a_DB: $(SRC_brick_game) $(SRC_DB)
	$(CC) $(FLAGS) -c $(SRC_brick_game) $(SQLFLAG) $(SRC_DB)
	ar rcs brick_game.a *.o

gcov_report_common:
	mkdir -p tests/build
	$(CC) --coverage -fPIC -O0 brick_game/tetris/tetris.c $(SRC_TXT) $(TEST_DIR)/*.c -o $(TBD)/test_cov_runner $(LINK_TEST_LIBS)
	./$(TBD)/test_cov_runner

gcov_report_common_DB:
	mkdir -p tests/build
	$(CC) --coverage -fPIC -O0 brick_game/tetris/tetris.c $(SRC_DB) $(TEST_DIR)/*.c -o $(TBD)/test_cov_runner $(LINK_TEST_LIBS) $(SQLFLAG)
	./$(TBD)/test_cov_runner

gcov_report: gcov_report_common
	@mkdir -p $(OUTPUT_DIR)
	gcovr -e 'tests/*' --html $(OUTPUT_DIR)/gcov_report.html

gcov_report_DB: gcov_report_common_DB
	@mkdir -p $(OUTPUT_DIR)
	gcovr -e 'tests/*' --html $(OUTPUT_DIR)/gcov_report.html

lcov_report: gcov_report_common
	rm -rf  $(TBD)/test_cov_runner-test.gcda
	rm -rf  $(TBD)/test_cov_runner-tetris_test.gcda
	@mkdir -p $(OUTPUT_DIR)
	@lcov --capture --directory . --output-file $(OUTPUT_DIR)/coverage.info
	@genhtml $(OUTPUT_DIR)/coverage.info --output-directory $(OUTPUT_DIR)

lcov_report_DB: gcov_report_common_DB
	rm -rf  $(TBD)/test_cov_runner-test.gcda
	rm -rf  $(TBD)/test_cov_runner-tetris_test.gcda
	@mkdir -p $(OUTPUT_DIR)
	@lcov --capture --directory . --output-file $(OUTPUT_DIR)/coverage.info
	@genhtml $(OUTPUT_DIR)/coverage.info --output-directory $(OUTPUT_DIR)

gcov_report_console: gcov_report_common
	gcov -H $(TBD)/test_cov_runner-tetris.gcno

gcov_report_console_DB: gcov_report_common_DB
	gcov -H $(TBD)/test_cov_runner-tetris.gcno

clean:
	rm -rf doxygen
	rm -rf *.o *.a
	rm -rf $(TBD) tests/report $(DIST_DIR)

.PHONY: test
test: $(TEST_RUNNER)
	CK_FORK=yes ./$(TEST_RUNNER)

tests/build/test_runner: brick_game.a $(TEST_DIR)/*.c
	mkdir -p tests/build
	$(CC) $(TEST_DIR)/*.c brick_game.a $(LINK_TEST_LIBS) $(FLAGS) -o $@

test_DB: $(TEST_RUNNER)_DB
	CK_FORK=yes ./$(TEST_RUNNER)

tests/build/test_runner_DB: brick_game.a_DB $(TEST_DIR)/*.c
	mkdir -p tests/build
	$(CC) $(TEST_DIR)/*.c brick_game.a $(LINK_TEST_LIBS) $(FLAGS) $(SQLFLAG) -o $(TEST_RUNNER)

.PHONY: check_valgrind
check_valgrind: $(TEST_RUNNER)
	CK_FORK=no $(VALGRIND)