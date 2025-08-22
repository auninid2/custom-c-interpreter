#include "../lexer/lexer.h"
#include "../ast/ast.h"
#include "parser.h"
#include <stdlib.h>

static int parser_cur_token_is(Parser* p, TokenType t);
static int parser_peek_token_is(Parser* p, TokenType t);
static int parser_expect_peek(Parser* p, TokenType t);
static Node* parser_parse_statement(Parser* p);
static Node* parser_parse_let_statement(Parser* p);

// nextToken(): advance tokens
void parser_next_token(Parser* p) {
    p->cur_token = p->peek_token;
    p->peek_token = next_token(p->l);
}

// constructor: allocate + init parser
Parser* parser_new(Lexer* l) {
    Parser* p = malloc(sizeof(Parser));
    if (!p) return NULL;

    p->l = l;

    // Initialize tokens by advancing twice
    p->cur_token = next_token(l);
    p->peek_token = next_token(l);

    return p;
}

static Node* parser_parse_let_statement(Parser* p) {
    // Allocate LetStatement node
    Node* stmt = malloc(sizeof(Node));
    if (!stmt) return NULL;

    stmt->type = NODE_LET_STATEMENT;
    stmt->token = p->cur_token;  // store "let" token

    // expect identifier
    if (!parser_expect_peek(p, TOKEN_IDENT)) {
        free(stmt);
        return NULL;
    }

    // build identifier node for Name
    Node* ident = malloc(sizeof(Node));
    if (!ident) {
        free(stmt);
        return NULL;
    }
    ident->type = NODE_IDENTIFIER;
    ident->token = p->cur_token;
    ident->as.identifier.value = strdup(p->cur_token.literal);

    stmt->as.let_statement.name = ident;

    // expect '='
    if (!parser_expect_peek(p, TOKEN_ASSIGN)) {
        // cleanup
        free(ident->as.identifier.value);
        free(ident);
        free(stmt);
        return NULL;
    }

    // TODO: skip expression until we see a semicolon
    while (!parser_cur_token_is(p, TOKEN_SEMICOLON)) {
        parser_next_token(p);
    }

    stmt->as.let_statement.value = NULL; // for now, not parsing expressions

    return stmt;
}

// -------------------
// helpers
// -------------------
static int parser_cur_token_is(Parser* p, TokenType t) {
    return p->cur_token.type == t;
}

static int parser_peek_token_is(Parser* p, TokenType t) {
    return p->peek_token.type == t;
}

static int parser_expect_peek(Parser* p, TokenType t) {
    if (parser_peek_token_is(p, t)) {
        parser_next_token(p);
        return 1;
    }
    return 0;
}

static Node* parser_parse_statement(Parser* p) {
    switch (p->cur_token.type) {
        case TOKEN_LET:
            return parser_parse_let_statement(p);
        default:
            return NULL;
    }
}

Program* parser_parse_program(Parser* p) {
    Program* program = malloc(sizeof(Program));
    if (!program) return NULL;

    program->statements = NULL;
    program->count = 0;

    while (p->cur_token.type != TOKEN_EOF) {
        Node* stmt = parser_parse_statement(p);
        if (stmt != NULL) {
            program->statements = realloc(
                program->statements,
                sizeof(Node*) * (program->count + 1)
            );
            program->statements[program->count] = stmt;
            program->count++;
        }

        parser_next_token(p);
    }

    return program;
}