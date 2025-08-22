#ifndef PARSER_H
#define PARSER_H

#include "../token/token.h"
#include "../ast/ast.h"
#include "../lexer/lexer.h"

typedef struct {
    Lexer* l;
    Token cur_token;
    Token peek_token;
} Parser;

Parser* parser_new(Lexer* l);
void parser_next_token(Parser* p);
Program* parser_parse_program(Parser* p);

#endif