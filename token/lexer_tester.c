#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token_and_lexer.h"
#include "helper_functions.h"
#include "test_inputs.h"

// Extracts an identifier starting at current lexer position
// Returns a newly allocated string or NULL on failure
char *real_identifier(Lexer *lexer) {
    int start = lexer->position;

    if (!is_letter(lexer->ch)) {
        return NULL;
    }

    read_char(lexer);

    while (lexer->position < lexer->inputLen && 
           (is_letter(lexer->ch) || is_digit(lexer->ch))) {
        read_char(lexer);
    }

    int length = lexer->position - start;
    if (length <= 0) {
        return NULL;
    }

    char *ident = malloc(length + 1);
    if (ident == NULL) {
        return NULL;
    }

    memcpy(ident, lexer->input + start, length);
    ident[length] = '\0';

    return ident;
}

// Initializes a new Lexer and copies input string
Lexer *new_lexer(const char *input) {
    Lexer *lexer = malloc(sizeof(Lexer));
    if (lexer == NULL) {
        return NULL;
    }

    lexer->input = strdup(input);
    if (lexer->input == NULL) {
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

// Creates a new token with given type and literal string
Token new_token(TokenType type, const char *literal) {
    Token token;
    token.type = type;

    token.literal = strdup(literal);
    if (token.literal == NULL) {
        token.literal = "";
    }

    return token;
}

// Returns the next token from the lexer input
Token next_token(Lexer *lexer) {
    Token token;

    skip_whitespace(lexer);

    switch (lexer->ch) {
        case '=':
            if (peek_char(lexer) == '=') {
                read_char(lexer);  
                token = new_token(TOKEN_EQ, "==");
            } else {
                token = new_token(TOKEN_ASSIGN, "=");
            }
            break;
        case ';':
            token = new_token(TOKEN_SEMICOLON, ";");
            break;
        case '(':
            token = new_token(TOKEN_LPAREN, "(");
            break;
        case ')':
            token = new_token(TOKEN_RPAREN, ")");
            break;
        case ',':
            token = new_token(TOKEN_COMMA, ",");
            break;
        case '+':
            token = new_token(TOKEN_PLUS, "+");
            break;
        case '-':
            token = new_token(TOKEN_MINUS, "-");    
            break;
        case '!':
            if (peek_char(lexer) == '=') {
                read_char(lexer);  
                token = new_token(TOKEN_NOT_EQ, "!=");
            } else {
                token = new_token(TOKEN_BANG, "!");
            }
            break;
        case '*':
            token = new_token(TOKEN_ASTERISK, "*");
            break;
        case '/':
            token = new_token(TOKEN_SLASH, "/");    
            break;
        case '<':
            token = new_token(TOKEN_LT, "<");
            break;
        case '>':
            token = new_token(TOKEN_GT, ">");
            break;
        case '{':
            token = new_token(TOKEN_LBRACE, "{");
            break;
        case '}':
            token = new_token(TOKEN_RBRACE, "}");
            break;
        case 0:
            token = new_token(TOKEN_EOF, "");
            break;
        default:
            if (is_letter(lexer->ch)) {
                token.literal = real_identifier(lexer);
                token.type = lookup_ident(token.literal);
                return token;
            } else if (is_digit(lexer->ch)) {
                token.type = TOKEN_INT;
                token.literal = read_number(lexer);
                return token;
            } else {
                char illegal_literal[2] = {lexer->ch, '\0'};
                token = new_token(TOKEN_ILLEGAL, illegal_literal);
            }
            break;
    }

    read_char(lexer);
    return token;
}

int main(void) {
    Lexer *lexer = new_lexer(input);
    if (lexer == NULL) {
        printf("Failed to create lexer\n");
        return 1;
    }

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    bool all_passed = true;

    for (int i = 0; i < num_tests; i++) {
        Token tok = next_token(lexer);
        bool failed = false;

        if (tok.type != tests[i].expected_type) {
            printf("Test %d failed: expected token type %d, got %d\n",
                   i, tests[i].expected_type, tok.type);
            failed = true;
        }

        if (strcmp(tok.literal, tests[i].expected_literal) != 0) {
            printf("Test %d failed: expected literal '%s', got '%s'\n",
                   i, tests[i].expected_literal, tok.literal);
            failed = true;
        }

        if (failed) {
            printf("\n");
            all_passed = false;
        }

        free(tok.literal);
    }

    if (all_passed) {
        printf("All tests passed!\n");
    }

    free(lexer->input);
    free(lexer);

    return 0;
}