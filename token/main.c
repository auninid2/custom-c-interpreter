#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenAndLexer.h"

// reads the next char and advances the position in the input string
void readChar(Lexer* l) {
    if (l->readPosition >= l->inputLen) {
        l->ch = 0;
    }

    else {
        l->ch = l->input[l->readPosition];
    }

    l->position = l->readPosition;
    l->readPosition++;
}


Lexer* newLexer(const char* input) {
    Lexer* l = (Lexer*)malloc(sizeof(Lexer));
    if (l == NULL) return NULL;

    l->input = strdup(input);
    if (l-> input == NULL) {
        free(l);
        return NULL;
    }

    l->inputLen = strlen(input);
    l->position = 0;
    l->readPosition = 0;
    l->ch = 0;

    readChar(l);

    return l;
}

Token newToken(TokenType type, const char* literal) {
    Token token;
    token.type = type;

   token.literal = strdup(literal);
    if (token.literal == NULL) {
        token.literal = ""; 
    }

    return token;
}

Token nextToken(Lexer* l) {
    Token token;

    switch (l->ch) {
        case '=':
            token = newToken(TOKEN_ASSIGN, "=");
            break;
        case ';':
            token = newToken(TOKEN_SEMICOLON, ";");
            break;
        case '(':
            token = newToken(TOKEN_LPAREN, "(");
            break;
        case ')':
            token = newToken(TOKEN_RPAREN, ")");
            break;
        case ',':
            token = newToken(TOKEN_COMMA, ",");
            break;
        case '+':
            token = newToken(TOKEN_PLUS, "+");
            break;
        case '{':
            token = newToken(TOKEN_LBRACE, "{");
            break;
        case '}':
            token = newToken(TOKEN_RBRACE, "}");
            break;
        case 0:
            token = newToken(TOKEN_EOF, "");
            break;
        default:
            token = newToken(TOKEN_ILLEGAL, "");
            break;
    }

    readChar(l);
    return token;
}

void testNextToken() {
    const char* input = "=+(){},;";

    Test tests[] = {
        {TOKEN_ASSIGN, "="},
        {TOKEN_PLUS, "+"},
        {TOKEN_LPAREN, "("},
        {TOKEN_RPAREN, ")"},
        {TOKEN_LBRACE, "{"},
        {TOKEN_RBRACE, "}"},
        {TOKEN_COMMA, ","},
        {TOKEN_SEMICOLON, ";"},
        {TOKEN_EOF, ""},
    };

    Lexer* lexer = newLexer(input);
    if (lexer == NULL) {
        printf("Failed to create lexer\n");
        return;
    }

    int numTests = sizeof(tests) / sizeof(tests[0]);

    int all_passed = 1;

    for (int i = 0; i < numTests; i++) {
        Token tok = nextToken(lexer);
        int failed = 0;

        if (tok.type != tests[i].expectedType) {
            printf("Test %d failed: expected token type %d, got %d\n",
                i, tests[i].expectedType, tok.type);
            failed = 1;
        }

        if (strcmp(tok.literal, tests[i].expectedLiteral) != 0) {
            printf("Test %d failed: expected literal '%s', got '%s'\n",
                i, tests[i].expectedLiteral, tok.literal);
            failed = 1;
        }

        if (failed) {
            printf("\n");
            all_passed = 0;
        }

        free(tok.literal);
    }

    if (all_passed) printf("All tests passed!\n");

    free(lexer->input);
    free(lexer);
}

int main(void) {
    testNextToken();
    return 0;
}