CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = lexer_tester

.PHONY: all run clean

all: $(TARGET)

$(TARGET): lexer_tester.c
	$(CC) $(CFLAGS) lexer_tester.c -o $(TARGET)

run: 
	$(CC) $(CFLAGS) lexer_tester.c -o $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)