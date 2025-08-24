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
    TOKEN_FALSE,

    TOKEN_LAST
} TokenType;

typedef struct {
    TokenType type;
    char* literal;
} Token;

typedef struct {
    const char* literal;
    TokenType type;
} Keyword;

extern Keyword keywords[]; 

TokenType lookup_ident(const char* ident);
const char* token_type_to_string(TokenType type);

#endif