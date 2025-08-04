#include "token.h"

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

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_ILLEGAL: return "TOKEN_ILLEGAL";
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_IDENT: return "TOKEN_IDENT";
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_ASSIGN: return "TOKEN_ASSIGN";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_BANG: return "TOKEN_BANG";
        case TOKEN_ASTERISK: return "TOKEN_ASTERISK";
        case TOKEN_SLASH: return "TOKEN_SLASH";
        case TOKEN_LT: return "TOKEN_LT";
        case TOKEN_GT: return "TOKEN_GT";
        case TOKEN_EQ: return "TOKEN_EQ";
        case TOKEN_NOT_EQ: return "TOKEN_NOT_EQ";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_LBRACE: return "TOKEN_LBRACE";
        case TOKEN_RBRACE: return "TOKEN_RBRACE";
        case TOKEN_FUNCTION: return "TOKEN_FUNCTION";
        case TOKEN_LET: return "TOKEN_LET";
        case TOKEN_TRUE: return "TOKEN_TRUE";
        case TOKEN_FALSE: return "TOKEN_FALSE";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ELSE: return "TOKEN_ELSE";
        case TOKEN_RETURN: return "TOKEN_RETURN";
        default: return "UNKNOWN_TOKEN";
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