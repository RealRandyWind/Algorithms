NAME ?= ssco
CXX ?= g++
COMPILE_FLAGS = -lfl -std=c++98 -pedantic -Wall -Wextra -g -lm

.PHONY: all clean

all: main-build

main-build:
	$(CXX) -o a.out $(NAME).c $(COMPILE_FLAGS)

clean:
	rm -f ./$(NAME).a ./a.out ./*.o