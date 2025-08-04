#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>

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
    TOKEN_MINUS  = '-',
    TOKEN_BANG   = '!',
    TOKEN_ASTERISK = '*',
    TOKEN_SLASH  = '/',
    TOKEN_EQ,
    TOKEN_NOT_EQ,

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

typedef struct {
    TokenType type;
    char* literal;
} Token;

typedef struct {
    const char* literal;
    TokenType type;
} Keyword;

static Keyword keywords[] = {
    {"fn", TOKEN_FUNCTION},
    {"let", TOKEN_LET},
    {"else", TOKEN_ELSE},
    {"if", TOKEN_IF},
    {"return", TOKEN_RETURN},
    {"true", TOKEN_TRUE},
    {"false", TOKEN_FALSE},
    {NULL, 0}
};

static TokenType lookup_ident(const char* ident) {
    for (int i = 0; keywords[i].literal != NULL; i++) {
        if (strcmp(keywords[i].literal, ident) == 0) {
            return keywords[i].type;
        }
    }
    return TOKEN_IDENT;
}

#endif