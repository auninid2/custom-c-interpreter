#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
// -------------------------------
// -- token_literal() functions --
// -------------------------------
// These functions return the literal string of the first token associated with a node
// Mainly used for debugging and testing the AST

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

const char* expression_statement_token_literal(Node* es) {
    return es->token.literal;
}

// -------------------------------
// ------ string() functions -----
// -------------------------------
// These functions generate a human-readable string representation of AST nodes
// Useful for debugging and writing tests
// They recursively build strings for child nodes and return heap-allocated strings

// Build a single string representing the entire program by concatenating the string of each statement.
char* program_string(Program* p) {
    size_t bufsize = 1; 
    char* result = malloc(bufsize);
    result[0] = '\0';

    for (int i = 0; i < p->count; i++) {
        char* stmt_str = node_string(p->statements[i]); 
        size_t newsize = bufsize + strlen(stmt_str);
        result = realloc(result, newsize);
        strcat(result, stmt_str);
        bufsize = newsize;
        free(stmt_str);
    }

    return result;
}

// Builds a string for a LetStatement: "let <name> = <value>;"
static char* let_statement_string(Node* n) {    
    char* name_str = node_string(n->as.let_statement.name);
    char* value_str = n->as.let_statement.value ? node_string(n->as.let_statement.value) : strdup("");

    size_t size = strlen(n->token.literal) + 1 + strlen(name_str) + 3 + strlen(value_str) + 2;
    char* out = malloc(size);
    snprintf(out, size, "%s %s = %s;", n->token.literal, name_str, value_str);

    free(name_str);
    free(value_str);
    return out;
}

// Builds a string for a ReturnStatement: "return <value>;"
static char* return_statement_string(Node* n) {   
    char* val_str = n->as.return_statement.return_value ? node_string(n->as.return_statement.return_value) : strdup("");

    size_t size = strlen(n->token.literal) + 1 + strlen(val_str) + 2;
    char* out = malloc(size);
    snprintf(out, size, "%s %s;", n->token.literal, val_str);

    free(val_str);
    return out;
}

// Builds a string for an ExpressionStatement.
static char* expression_statement_string(Node* n) {
    if (n->as.expression_statement.expression) {
        return node_string(n->as.expression_statement.expression);
    }
    return strdup("");
}

// Returns a copy of the identifier's value.
static char* identifier_string(Node* n) {
    return strdup(n->as.identifier.value);
}

// -------------------------------
// ---- node_string dispatcher ---
// -------------------------------
// Goes to the correct string-building function based on node type
char* node_string(Node* n) {
    switch (n->type) {
        case NODE_LET_STATEMENT:
            return let_statement_string(n);
        case NODE_RETURN_STATEMENT:
            return return_statement_string(n);
        case NODE_EXPRESSION_STATEMENT:
            return expression_statement_string(n);
        case NODE_IDENTIFIER:
            return identifier_string(n);
        default:
            return strdup("");  
    }
}