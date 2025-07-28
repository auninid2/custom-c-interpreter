#ifndef TOKEN_H
#define TOKEN_H

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

    // Delimiters
    TOKEN_COMMA     = ',',
    TOKEN_SEMICOLON = ';',
    TOKEN_LPAREN    = '(',
    TOKEN_RPAREN    = ')',
    TOKEN_LBRACE    = '{',
    TOKEN_RBRACE    = '}',

    // Keywords
    TOKEN_FUNCTION,
    TOKEN_LET

} TokenType;

typedef struct {
    TokenType type;
    char* literal;
} Token;

#endif