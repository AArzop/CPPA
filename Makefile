CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -Wextra -Werror -I./lib/

SRC = ./src/step1_example.cc 

.PHONY: all parse compile

all: $(SRC) 
	$(CXX) $(CXXFLAGS) $(SRC)

