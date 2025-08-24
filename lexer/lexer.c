#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"

// -------------------------------
// ---- Lexer Initialization -----
// -------------------------------
Lexer* new_lexer(const char *input) {
    Lexer *lexer = malloc(sizeof(Lexer));
    if (!lexer) return NULL;

    lexer->input = strdup(input);
    if (!lexer->input) {
        free(lexer);
        return NULL;
    }

    lexer->inputLen = strlen(input);
    lexer->position = 0;
    lexer->readPosition = 0;
    lexer->ch = 0;

    read_char(lexer);
    return lexer;
}

// -------------------------------
// ---- Token Helpers ------------
// -------------------------------
Token new_token(TokenType type, const char *literal) {
    Token token;
    token.type = type;
    token.literal = strdup(literal);
    if (!token.literal) token.literal = "";
    return token;
}

// -------------------------------
// ---- Main Tokenizer -----------
// -------------------------------
Token next_token(Lexer *lexer) {
    Token token;
    skip_whitespace(lexer);

    switch (lexer->ch) {
        case '=':
            token = (peek_char(lexer) == '=') 
                ? (read_char(lexer), new_token(TOKEN_EQ, "==")) 
                : new_token(TOKEN_ASSIGN, "=");
            break;
        case '!':
            token = (peek_char(lexer) == '=') 
                ? (read_char(lexer), new_token(TOKEN_NOT_EQ, "!=")) 
                : new_token(TOKEN_BANG, "!");
            break;
        case '+': token = new_token(TOKEN_PLUS, "+"); break;
        case '-': token = new_token(TOKEN_MINUS, "-"); break;
        case '*': token = new_token(TOKEN_ASTERISK, "*"); break;
        case '/': token = new_token(TOKEN_SLASH, "/"); break;
        case '<': token = new_token(TOKEN_LT, "<"); break;
        case '>': token = new_token(TOKEN_GT, ">"); break;
        case ';': token = new_token(TOKEN_SEMICOLON, ";"); break;
        case '(': token = new_token(TOKEN_LPAREN, "("); break;
        case ')': token = new_token(TOKEN_RPAREN, ")"); break;
        case ',': token = new_token(TOKEN_COMMA, ","); break;
        case '{': token = new_token(TOKEN_LBRACE, "{"); break;
        case '}': token = new_token(TOKEN_RBRACE, "}"); break;
        case 0: token = new_token(TOKEN_EOF, ""); break;
        default:
            if (is_letter(lexer->ch)) {
                char* ident = real_identifier(lexer);
                token.type = lookup_ident(ident);
                token.literal = ident;
                return token;
            } else if (is_digit(lexer->ch)) {
                token.type = TOKEN_INT;
                token.literal = read_number(lexer);
                return token;
            } else {
                char illegal[2] = {lexer->ch, '\0'};
                token = new_token(TOKEN_ILLEGAL, illegal);
            }
    }

    read_char(lexer);
    return token;
}

// -------------------------------
// ----- Character Helpers -------
// -------------------------------
void read_char(Lexer* lexer) {
    if (lexer->readPosition >= lexer->inputLen) {
        lexer->ch = 0;
    } else {
        lexer->ch = lexer->input[lexer->readPosition];
    }
    lexer->position = lexer->readPosition;
    lexer->readPosition++;
}

char peek_char(Lexer* lexer) {
    return (lexer->readPosition >= lexer->inputLen) ? 0 : lexer->input[lexer->readPosition];
}

bool is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}

bool is_digit(char ch) {
    return ch >= '0' && ch <= '9';
}

void skip_whitespace(Lexer* lexer) {
    while (lexer->ch == ' ' || lexer->ch == '\t' || lexer->ch == '\n' || lexer->ch == '\r') {
        read_char(lexer);
    }
}

// -------------------------------
// ---- Identifier / Number ------
// -------------------------------
char* real_identifier(Lexer *lexer) {
    int start = lexer->position;
    if (!is_letter(lexer->ch)) return NULL;

    read_char(lexer);
    while (lexer->position < lexer->inputLen && (is_letter(lexer->ch) || is_digit(lexer->ch))) {
        read_char(lexer);
    }

    int len = lexer->position - start;
    char* ident = malloc(len + 1);
    if (!ident) return NULL;

    memcpy(ident, lexer->input + start, len);
    ident[len] = '\0';
    return ident;
}

char* read_number(Lexer* lexer) {
    int start = lexer->position;
    while (is_digit(lexer->ch)) read_char(lexer);
    return slice(lexer->input, start, lexer->position);
}

// -------------------------------
// ---- Slice Helper -------------
// -------------------------------
char* slice(const char* str, int start, int end) {
    if (end <= start) return NULL;

    int len = end - start;
    char* substr = malloc(len + 1);
    if (!substr) return NULL;

    memcpy(substr, str + start, len);
    substr[len] = '\0';
    return substr;
}