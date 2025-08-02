#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token_and_lexer.h"

// Checks if a character is a digit (0-9)
bool is_digit(char ch) {
    return (ch >= '0' && ch <= '9'); 
}

// Checks if a character is a letter (a-z, A-Z) or underscore
bool is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z') || 
           (ch >= 'A' && ch <= 'Z') || 
           (ch == '_');
}

// Returns a newly allocated substring from str[start] to str[end-1]
// Returns NULL if end <= start or on malloc failure
char* slice(const char* str, int start, int end) {
    if (end <= start) {
        return NULL;
    }

    int length = end - start;
    char* substr = malloc(length + 1);
    if (!substr) {
        return NULL;
    }

    memcpy(substr, str + start, length);
    substr[length] = '\0';

    return substr;
}

// Reads the next character from input, advancing lexer's position
void read_char(Lexer* lexer) {
    if (lexer->readPosition >= lexer->inputLen) {
        lexer->ch = 0;  // EOF marker
    } else {
        lexer->ch = lexer->input[lexer->readPosition];
    }

    lexer->position = lexer->readPosition;
    lexer->readPosition++;
}

// Reads a sequence of digits and returns it as a newly allocated string
char* read_number(Lexer* lexer) {
    int start = lexer->position;

    while (is_digit(lexer->ch)) {
        read_char(lexer);
    }

    return slice(lexer->input, start, lexer->position);
}

// Skips whitespace characters in the input stream
void skip_whitespace(Lexer* lexer) {
    while (lexer->ch == ' ' || lexer->ch == '\t' || 
           lexer->ch == '\n' || lexer->ch == '\r') {
        read_char(lexer);
    }
}

TokenType lookup_ident(const char* ident) {
    for (int i = 0; keywords[i].literal != NULL; i++) {
        if (strcmp(keywords[i].literal, ident) == 0) {
            return keywords[i].type;
        }
    }
    return TOKEN_IDENT;  
}

#endif