#ifndef TOKENANDLEXER_H
#define TOKENANDLEXER_H

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

typedef struct {
    TokenType expectedType;
    char* expectedLiteral;
} Test;

typedef struct {
    char* input;
    int inputLen;
    int position;   // points to the ch currently being inspected
    int readPosition;  // "peeks" at the next ch
    int ch;
} Lexer;

#endif