#ifndef TOKENANDLEXER_H
#define TOKENANDLEXER_H

#include <stdbool.h> 
#include <string.h>   

// ------------------- Token Types -------------------

typedef enum {
    // Special
    TOKEN_ILLEGAL = 0,
    TOKEN_EOF,

    // Identifiers + literals
    TOKEN_IDENT,
    TOKEN_INT,

    // Operators
    TOKEN_ASSIGN = '=',
    TOKEN_PLUS   = '+',
    TOKEN_MINUS = '-',
    TOKEN_BANG = '!',
    TOKEN_ASTERISK = '*',
    TOKEN_SLASH = '/',
    TOKEN_EQ,
    TOKEN_NOT_EQ = '!=',
    
    TOKEN_LT = '<',
    TOKEN_GT = '>', 

    // Delimiters
    TOKEN_COMMA     = ',',
    TOKEN_SEMICOLON = ';',
    TOKEN_LPAREN    = '(',
    TOKEN_RPAREN    = ')',
    TOKEN_LBRACE    = '{',
    TOKEN_RBRACE    = '}',

    // Keywords
    TOKEN_FUNCTION,
    TOKEN_LET,
    TOKEN_ELSE,
    TOKEN_IF,
    TOKEN_RETURN,
    TOKEN_TRUE,
    TOKEN_FALSE

} TokenType;

// ------------------ Token Struct -------------------

typedef struct {
    TokenType type;
    char* literal;
} Token;

// ----------------- Test Case Struct -----------------

typedef struct {
    TokenType expected_type;
    char* expected_literal;
} Test;

// ------------------- Keyword Map --------------------

typedef struct {
    const char* literal;
    TokenType type;
} Keyword;


Keyword keywords[] = {
    {"fn", TOKEN_FUNCTION},
    {"let", TOKEN_LET},
    {"else", TOKEN_ELSE},
    {"if", TOKEN_IF},
    {"return", TOKEN_RETURN},
    {"true", TOKEN_TRUE},
    {"false", TOKEN_FALSE},
    {NULL, 0}  
};

// ------------------- Lexer Struct -------------------

typedef struct {
    char* input;
    int inputLen;
    int position;   // points to the ch currently being inspected
    int readPosition;  // "peeks" at the next ch
    int ch;
} Lexer;

// --------------- Function Prototypes ----------------

// Token lookup
TokenType lookup_ident(const char* ident);

// Lexer core functions
bool is_digit(char ch);
bool is_letter(char ch);
void read_char(Lexer* lexer);
char* read_number(Lexer* lexer);
void skip_whitespace(Lexer* lexer);
char* slice(const char* str, int start, int end);

#endif