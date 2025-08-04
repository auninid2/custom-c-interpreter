.PHONY: all run clean

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
SRC = main.c lexer/lexer.c repl/repl.c token/token.c
OUT = compiler

all:
	$(CC) $(CFLAGS) -o $(OUT) $(SRC)

run:
	./$(OUT)

clean:
	rm -f $(OUT)