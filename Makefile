
CC=gcc
CFLAGS=-Wall -Wextra
BIN=main
SRC=main.c node.c
OBJ=main.o node.o

.PHONY: all clean test

all: $(BIN)
	./$(BIN)

$(BIN): $(OBJ)
	$(CC) -o $@ $(OBJ) 

%.o: %.c
	$(CC) -c $< -o $@

clean: 
	rm -rf $(BIN) *.o

