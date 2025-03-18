CXX = g++

CXXFLAGS = -std=c++20 -Iinclude -O2

GTEST_LIB_DIR = $(GTEST_DIR)/build/lib
GTEST_LIBS = -L$(GTEST_LIB_DIR) -lgtest -lgtest_main -lpthread

SRC_DIR = src
TEST_DIR = tests
GTEST_DIR = googletest

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

main:
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o main
	./main

test:
	$(CXX) $(CXXFLAGS) $(wildcard src/*.cpp) $(wildcard tests/*.cpp) $(GTEST_LIBS) -o test.out
	./test.out

clean:
	rm main
.PHONY: clean