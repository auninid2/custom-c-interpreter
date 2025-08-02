#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tokenAndLexer.h"

// reads current char and advances the position in the input string
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

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9'; 
}

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_');
}


char* realIdentifier(Lexer* l) {
    int start = l->position;

    if (!isLetter(l->ch)) {
        return NULL;
    }

    readChar(l);

    while (l->position < l->inputLen && (isLetter(l->ch) || isDigit(l->ch))) {
        readChar(l);
    }

    int length = l->position - start;
    if (length <= 0) {
        return NULL;
    }

    char* ident = malloc(length + 1);
    if (ident == NULL) {
        return NULL;
    }

    memcpy(ident, l->input + start, length);
    ident[length] = '\0';
    return ident;
}


// initializies a new lexical analyzer and copies the input string into the lexers memory
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

char* slice(const char* str, int start, int end) {
    if (end <= start) return NULL;
    int length = end - start;
    char* substr = malloc(length + 1);
    if (!substr) return NULL;
    memcpy(substr, str + start, length);
    substr[length] = '\0';
    return substr;
}

void skipWhitespace(Lexer* l) {
    while(l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        readChar(l);
    }
}

char* readNumber(Lexer* l) {
    int start = l->position;
    while (isDigit(l->ch)) {
        readChar(l);
    }
    return slice(l->input, start, l->position);
}

Token nextToken(Lexer* l) {
    Token token;
    skipWhitespace(l);

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
            if (isLetter(l->ch)) {
                token.literal = realIdentifier(l);
                token.type = lookupIdent(token.literal); 
                return token;
            }
            else if (isDigit(l->ch)) {
                token.type = TOKEN_INT;
                token.literal = readNumber(l);
                return token;
            }
            else {
                char illegalLiteral[2] = { l->ch, '\0' };
                token = newToken(TOKEN_ILLEGAL, illegalLiteral);
            }
            break;
    }

    readChar(l);
    return token;
}

int main(void) {
        const char* input = 
        "let five = 5;\n"
        "let ten = 10;\n"
        "\n"
        "let add = fn(x, y) {\n"
        "    x + y;\n"
        "};\n"
        "\n"
        "let result = add(five, ten);\n";

    Test tests[] = {
        {TOKEN_LET, "let"},
        {TOKEN_IDENT, "five"},
        {TOKEN_ASSIGN, "="},
        {TOKEN_INT, "5"},
        {TOKEN_SEMICOLON, ";"},

        {TOKEN_LET, "let"},
        {TOKEN_IDENT, "ten"},
        {TOKEN_ASSIGN, "="},
        {TOKEN_INT, "10"},
        {TOKEN_SEMICOLON, ";"},

        {TOKEN_LET, "let"},
        {TOKEN_IDENT, "add"},
        {TOKEN_ASSIGN, "="},
        {TOKEN_FUNCTION, "fn"},
        {TOKEN_LPAREN, "("},
        {TOKEN_IDENT, "x"},
        {TOKEN_COMMA, ","},
        {TOKEN_IDENT, "y"},
        {TOKEN_RPAREN, ")"},

        {TOKEN_LBRACE, "{"},
        {TOKEN_IDENT, "x"},
        {TOKEN_PLUS, "+"},
        {TOKEN_IDENT, "y"},
        {TOKEN_SEMICOLON, ";"},
        {TOKEN_RBRACE, "}"},
        {TOKEN_SEMICOLON, ";"},

        {TOKEN_LET, "let"},
        {TOKEN_IDENT, "result"},
        {TOKEN_ASSIGN, "="},
        {TOKEN_IDENT, "add"},
        {TOKEN_LPAREN, "("},
        {TOKEN_IDENT, "five"},
        {TOKEN_COMMA, ","},
        {TOKEN_IDENT, "ten"},
        {TOKEN_RPAREN, ")"},
        {TOKEN_SEMICOLON, ";"},

        {TOKEN_EOF, ""},
    };

    Lexer* lexer = newLexer(input);
    if (lexer == NULL) {
        printf("Failed to create lexer\n");
        return 0;
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

    return 0;
}