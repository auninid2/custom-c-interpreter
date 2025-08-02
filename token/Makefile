CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = lexer_tester.c
TARGET = interpreter

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)