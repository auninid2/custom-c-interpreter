#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"

// Initializes a new Lexer and copies input string
Lexer* new_lexer(const char *input) {
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

// Reads the next character from input, advancing lexer's position
void read_char(Lexer* lexer) {
    if (lexer->readPosition >= lexer->inputLen) {
        lexer->ch = 0;  // EOF marker
    } else {
        lexer->ch = lexer->input[lexer->readPosition];
    }

    lexer->position = lexer->readPosition;
    lexer->readPosition++;
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

// Checks if a character is a digit (0-9)
bool is_digit(char ch) {
    return (ch >= '0' && ch <= '9'); 
}

// Checks if a character is a letter (a-z, A-Z) or underscore
bool is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z') || 
           (ch >= 'A' && ch <= 'Z') || 
           (ch == '_');
}

// Skips whitespace characters in the input stream
void skip_whitespace(Lexer* lexer) {
    while (lexer->ch == ' ' || lexer->ch == '\t' || 
           lexer->ch == '\n' || lexer->ch == '\r') {
        read_char(lexer);
    }
}

// Reads a sequence of digits and returns it as a newly allocated string
char* read_number(Lexer* lexer) {
    int start = lexer->position;

    while (is_digit(lexer->ch)) {
        read_char(lexer);
    }

    return slice(lexer->input, start, lexer->position);
}

char peek_char(Lexer* lexer) {
    if (lexer->readPosition >= lexer->inputLen) {
        return 0;  // EOF marker
    } else {
        return lexer->input[lexer->readPosition];
    }
}

// Returns a newly allocated substring from str[start] to str[end-1]
// Returns NULL if end <= start or on malloc failure
char* slice(const char* str, int start, int end) {
    if (end <= start) {
        return NULL;
    }

    int length = end - start;
    char* substr = malloc(length + 1);
    if (!substr) {
        return NULL;
    }

    memcpy(substr, str + start, length);
    substr[length] = '\0';

    return substr;
}