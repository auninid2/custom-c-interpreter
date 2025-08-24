#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include "parser.h"

// -------------------------------
// ------ Parser Initialization --
// -------------------------------
Parser* parser_new(Lexer* l) {
    Parser* p = malloc(sizeof(Parser));
    if (!p) return NULL;

    p->l = l;
    p->cur_token = next_token(l);
    p->peek_token = next_token(l);

    p->errors = NULL;
    p->error_count = 0;

    for (int i = 0; i < TOKEN_LAST; i++)
        p->prefix_parse_fns[i] = NULL;

    register_prefix(p, TOKEN_IDENT, parse_identifier);

    return p;
}

// -------------------------------
// ------ Parsing Statements ------
// -------------------------------
Node* parser_parse_let_statement(Parser* p) {
    Node* stmt = malloc(sizeof(Node));
    if (!stmt) return NULL;

    stmt->type = NODE_LET_STATEMENT;
    stmt->token = p->cur_token;

    if (!parser_expect_peek(p, TOKEN_IDENT)) {
        free(stmt);
        return NULL;
    }

    Node* ident = malloc(sizeof(Node));
    if (!ident) { free(stmt); return NULL; }

    ident->type = NODE_IDENTIFIER;
    ident->token = p->cur_token;
    ident->as.identifier.value = strdup(p->cur_token.literal);

    stmt->as.let_statement.name = ident;

    if (!parser_expect_peek(p, TOKEN_ASSIGN)) {
        free(ident->as.identifier.value);
        free(ident);
        free(stmt);
        return NULL;
    }

    while (!parser_cur_token_is(p, TOKEN_SEMICOLON))
        parser_next_token(p);

    stmt->as.let_statement.value = NULL;

    return stmt;
}

Node* parser_parse_return_statement(Parser* p) {
    Node* stmt = malloc(sizeof(Node));
    if (!stmt) return NULL;

    stmt->type = NODE_RETURN_STATEMENT;
    stmt->token = p->cur_token;

    parser_next_token(p);
    while (!parser_cur_token_is(p, TOKEN_SEMICOLON))
        parser_next_token(p);

    stmt->as.return_statement.return_value = NULL;
    return stmt;
}

Node* parse_expression_statement(Parser* p) {
    Node* stmt = malloc(sizeof(Node));
    if (!stmt) return NULL;

    stmt->type = NODE_EXPRESSION_STATEMENT;
    stmt->token = p->cur_token;

    stmt->as.expression_statement.expression = parse_expression(p, PRECEDENCE_LOWEST);

    if (parser_peek_token_is(p, TOKEN_SEMICOLON))
        parser_next_token(p);

    return stmt;
}

// -------------------------------
// ------ Parsing Expressions -----
// -------------------------------
Node* parse_expression(Parser* p, int precedence) {
    PrefixParseFn prefix = p->prefix_parse_fns[p->cur_token.type];
    if (!prefix) {
        parser_peek_error(p, p->cur_token.type);
        return NULL;
    }
    return prefix(p);
}

Node* parse_identifier(Parser* p) {
    Node* ident = malloc(sizeof(Node));
    if (!ident) return NULL;

    ident->type = NODE_IDENTIFIER;
    ident->token = p->cur_token;
    ident->as.identifier.value = strdup(p->cur_token.literal);

    return ident;
}

// -------------------------------
// ------ Register Prefix ---------
// -------------------------------
void register_prefix(Parser* p, TokenType t, PrefixParseFn fn) {
    p->prefix_parse_fns[t] = fn;
}

// -------------------------------
// ------ Error Handling ----------
// -------------------------------
void check_parser_errors(Parser* p) {
    if (p->error_count == 0) return;

    printf("parser has %d error(s):\n", p->error_count);
    for (int i = 0; i < p->error_count; i++)
        printf("  parser error: %s\n", p->errors[i]);

    exit(1);
}

void parser_peek_error(Parser* p, TokenType t) {
    const char* expected = token_type_to_string(t);
    const char* got = token_type_to_string(p->peek_token.type);

    char buffer[256];
    snprintf(buffer, sizeof(buffer),
             "expected next token to be %s, got %s instead",
             expected, got);

    p->errors = realloc(p->errors, sizeof(char*) * (p->error_count + 1));
    p->errors[p->error_count] = strdup(buffer);
    p->error_count++;
}

char** parser_errors(Parser* p, int* out_count) {
    *out_count = p->error_count;
    return p->errors;
}

void parser_free_errors(Parser* p) {
    for (int i = 0; i < p->error_count; i++)
        free(p->errors[i]);
    free(p->errors);
    p->errors = NULL;
    p->error_count = 0;
}

// -------------------------------
// ------ Token Helpers -----------
// -------------------------------
int parser_cur_token_is(Parser* p, TokenType t) { return p->cur_token.type == t; }
int parser_peek_token_is(Parser* p, TokenType t) { return p->peek_token.type == t; }

void parser_next_token(Parser* p) {
    p->cur_token = p->peek_token;
    p->peek_token = next_token(p->l);
}

int parser_expect_peek(Parser* p, TokenType t) {
    if (parser_peek_token_is(p, t)) {
        parser_next_token(p);
        return 1;
    }
    parser_peek_error(p, t);
    return 0;
}

// -------------------------------
// ------ Program Parsing --------
// -------------------------------
Node* parser_parse_statement(Parser* p) {
    switch (p->cur_token.type) {
        case TOKEN_LET: return parser_parse_let_statement(p);
        case TOKEN_RETURN: return parser_parse_return_statement(p);
        default: return parse_expression_statement(p);
    }
}

Program* parser_parse_program(Parser* p) {
    Program* program = malloc(sizeof(Program));
    if (!program) return NULL;

    program->statements = NULL;
    program->count = 0;

    while (!parser_cur_token_is(p, TOKEN_EOF)) {
        Node* stmt = parser_parse_statement(p);
        if (stmt) {
            program->statements = realloc(
                program->statements,
                sizeof(Node*) * (program->count + 1)
            );
            program->statements[program->count++] = stmt;
        }
        parser_next_token(p);
    }

    return program;
}