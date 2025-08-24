#ifndef PARSER_H
#define PARSER_H

#include "../token/token.h"
#include "../ast/ast.h"
#include "../lexer/lexer.h"

typedef struct Parser Parser;
typedef Node* (*PrefixParseFn)(Parser*);

struct Parser {
    Lexer* l;
    Token cur_token;
    Token peek_token;

    char** errors;
    int error_count;

    PrefixParseFn prefix_parse_fns[TOKEN_LAST];
};

// Precedence enum
typedef enum {
    PRECEDENCE_LOWEST = 1,
    PRECEDENCE_EQUALS,
    PRECEDENCE_LESSGREATER,
    PRECEDENCE_SUM,
    PRECEDENCE_PRODUCT,
    PRECEDENCE_PREFIX,
    PRECEDENCE_CALL
} Precedence;

Parser* parser_new(Lexer* l);
Program* parser_parse_program(Parser* p);
Node* parser_parse_statement(Parser* p);
Node* parser_parse_let_statement(Parser* p);
Node* parser_parse_return_statement(Parser* p);
Node* parse_expression(Parser* p, int precedence);
Node* parse_identifier(Parser* p);
void parser_next_token(Parser* p);
int parser_cur_token_is(Parser* p, TokenType t);
int parser_peek_token_is(Parser* p, TokenType t);
int parser_expect_peek(Parser* p, TokenType t);
void parser_peek_error(Parser* p, TokenType t);
void register_prefix(Parser* p, TokenType t, PrefixParseFn fn);
void check_parser_errors(Parser* p);

#endif
