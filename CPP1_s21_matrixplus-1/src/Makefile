CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic --std=c++17 -O2 -fprofile-arcs -ftest-coverage -Iheaders
LDFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage
CLANGFORMAT = clang-format
CLANGFORMATFLAGS = -n
VALGRIND = valgrind
VALGRINDFLAGS = --leak-check=full --error-exitcode=1
SRC_DIR = main
TEST_DIR = tests
BUILD_DIR = build
COV_DIR = coverage
HEADER = headers
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
TEST_OBJ_FILES = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_FILES))

all: $(BUILD_DIR)/test coverage format-check memory-check open_coverage

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test: $(OBJ_FILES) $(TEST_OBJ_FILES)
	ar rcs $(BUILD_DIR)/s21_matrix_oop.a $(OBJ_FILES)
	ranlib $(BUILD_DIR)/s21_matrix_oop.a
	$(CXX) $(OBJ_FILES) $(TEST_OBJ_FILES) $(LDFLAGS) -o $(BUILD_DIR)/test
	$(BUILD_DIR)/test

clean:
	rm -rf $(BUILD_DIR) $(COV_DIR) *.gcda *.gcno *.gcov Coverage_Report.info test s21_matrix_oop.a

coverage: $(BUILD_DIR)/test
	mkdir -p $(COV_DIR)
	# Collect coverage data only for the main directory
	lcov --capture --directory . --output-file Coverage_Report.info --rc branch_coverage=1 --no-external --exclude '*/tests/*'
	genhtml Coverage_Report.info --output-directory $(COV_DIR)

open_coverage:
	@xdg-open $(COV_DIR)/index.html || open $(COV_DIR)/index.html || echo "Unable to open coverage report."

format-check:
	$(CLANGFORMAT) $(CLANGFORMATFLAGS) headers/*.h main/*.cpp tests/*.cpp

memory-check: $(BUILD_DIR)/test
	$(VALGRIND) $(VALGRINDFLAGS) $(BUILD_DIR)/test

.PHONY: all clean coverage open_coverage format-check memory-check
