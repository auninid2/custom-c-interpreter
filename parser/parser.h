#ifndef PARSER_H
#define PARSER_H

#include "../token/token.h"
#include "../ast/ast.h"
#include "../lexer/lexer.h"

typedef struct {
    Lexer* l;
    Token cur_token;
    Token peek_token;
    
    char** errors;
    int error_count;
} Parser;

Parser* parser_new(Lexer* l);
Program* parser_parse_program(Parser* p);
static Node* parser_parse_statement(Parser* p);
static Node* parser_parse_let_statement(Parser* p);
void parser_next_token(Parser* p);
static int parser_cur_token_is(Parser* p, TokenType t);
static int parser_peek_token_is(Parser* p, TokenType t);
static int parser_expect_peek(Parser* p, TokenType t);
static void parser_peek_error(Parser* p, TokenType t);

#endif