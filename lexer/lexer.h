#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include "../token/token.h"

typedef struct {
    char* input;
    int inputLen;
    int position;   // points to the ch currently being inspected
    int readPosition;  // "peeks" at the next ch
    int ch;
} Lexer;

void read_char(Lexer* lexer);
void skip_whitespace(Lexer* lexer);
char peek_char(Lexer* lexer);
Token new_token(TokenType type, const char *literal);
Token next_token(Lexer *lexer);
char* real_identifier(Lexer *lexer);
bool is_digit(char ch);
bool is_letter(char ch);
char* read_number(Lexer *lexer);
char* slice(const char* str, int start, int end);
Lexer* new_lexer(const char* input);   // Add this declaration
extern TokenType lookup_ident(const char* ident);

#endif