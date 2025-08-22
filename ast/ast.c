#include "ast.h"

const char* program_token_literal(Program* p) {
    if (p->count > 0) {
        return p->statements[0]->token.literal;
    }
    return "";
}

const char* let_statement_token_literal(const Statement* s) {
    return s->token.literal;
}

const char* identifier_token_literal(const Expression* e) {
    return e->token.literal;
}

const char* return_statement_token_literal(Node* rs) {
    return rs->token.literal;
}