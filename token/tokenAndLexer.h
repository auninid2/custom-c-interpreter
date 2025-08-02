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
    const char* literal;
    TokenType type;
} Keyword;

Keyword keywords[] = {
    {"fn", TOKEN_FUNCTION},
    {"let", TOKEN_LET},
    {NULL, 0}  
};

TokenType lookupIdent(const char* ident) {
    for (int i = 0; keywords[i].literal != NULL; i++) {
        if (strcmp(keywords[i].literal, ident) == 0) {
            return keywords[i].type;
        }
    }
    return TOKEN_IDENT;  
}

typedef struct {
    char* input;
    int inputLen;
    int position;   // points to the ch currently being inspected
    int readPosition;  // "peeks" at the next ch
    int ch;
} Lexer;

#endif