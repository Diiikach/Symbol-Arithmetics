CXX = g++

CXXFLAGS = -std=c++20 -Iinclude -O2

SRC_DIR = src

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) main.cpp

main:
	$(CXX) $(CXXFLAGS) $(SRC_FILES) -o main
	./main

clean:
	rm main
.PHONY: pi test clean