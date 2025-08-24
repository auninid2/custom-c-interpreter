#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

// -------------------------------
// -- token_literal() functions --
// -------------------------------
const char* program_token_literal(Program* p) {
    return (p->count > 0) ? p->statements[0]->token.literal : "";
}

const char* let_statement_token_literal(const Statement* s) {
    return s->token.literal;
}

const char* return_statement_token_literal(Node* rs) {
    return rs->token.literal;
}

const char* identifier_token_literal(const Expression* e) {
    return e->token.literal;
}

const char* expression_statement_token_literal(Node* es) {
    return es->token.literal;
}

// -------------------------------
// ------- string helpers --------
// -------------------------------
static char* strdup_safe(const char* str) {
    return str ? strdup(str) : strdup("");
}

static char* concat_strings(const char* a, const char* b) {
    size_t len = strlen(a) + strlen(b) + 1;
    char* out = malloc(len);
    if (!out) exit(1);
    snprintf(out, len, "%s%s", a, b);
    return out;
}

// -------------------------------
// ---- node-specific string -----
// -------------------------------
static char* let_statement_string(Node* n) {
    char* name_str = node_string(n->as.let_statement.name);
    char* value_str = n->as.let_statement.value ? node_string(n->as.let_statement.value) : strdup_safe("");

    size_t size = strlen(n->token.literal) + 1 + strlen(name_str) + 3 + strlen(value_str) + 2;
    char* out = malloc(size);
    snprintf(out, size, "%s %s = %s;", n->token.literal, name_str, value_str);

    free(name_str);
    free(value_str);
    return out;
}

static char* return_statement_string(Node* n) {
    char* val_str = n->as.return_statement.return_value ? node_string(n->as.return_statement.return_value) : strdup_safe("");

    size_t size = strlen(n->token.literal) + 1 + strlen(val_str) + 2;
    char* out = malloc(size);
    snprintf(out, size, "%s %s;", n->token.literal, val_str);

    free(val_str);
    return out;
}

static char* expression_statement_string(Node* n) {
    return n->as.expression_statement.expression ? node_string(n->as.expression_statement.expression) : strdup_safe("");
}

static char* identifier_string(Node* n) {
    return strdup_safe(n->as.identifier.value);
}

// -------------------------------
// ---- node_string dispatcher ---
// -------------------------------
char* node_string(Node* n) {
    switch (n->type) {
        case NODE_LET_STATEMENT:        return let_statement_string(n);
        case NODE_RETURN_STATEMENT:     return return_statement_string(n);
        case NODE_EXPRESSION_STATEMENT: return expression_statement_string(n);
        case NODE_IDENTIFIER:           return identifier_string(n);
        default:                        return strdup_safe("");
    }
}

// -------------------------------
// ------- program_string --------
// -------------------------------
char* program_string(Program* p) {
    size_t bufsize = 1;
    char* result = malloc(bufsize);
    if (!result) exit(1);
    result[0] = '\0';

    for (int i = 0; i < p->count; i++) {
        char* stmt_str = node_string(p->statements[i]);
        char* tmp = concat_strings(result, stmt_str);
        free(result);
        free(stmt_str);
        result = tmp;
    }

    return result;
}