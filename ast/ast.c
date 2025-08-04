#include "ast.h"

// Node interface
struct Node {
    // function pointer for TokenLiteral method
    const char* (*TokenLiteral)(void* self);  // like a virtual method
};

// Statement interface extends Node
struct Statement {
    Node node;  // "inherits" from Node
    void (*statementNode)(void* self);  // marker
};

// Expression interface extends Node
struct Expression {
    Node node;
    void (*expressionNode)(void* self);  // marker
};

struct Program {
    Statement** statements;  // array of pointers to Statement
    int statement_count;
};

char* token_literal(Program* p) {
    if (strlen(p->statements) > 0) {
        return p->statements[0]->node.TokenLiteral(p->statements[0]);
    } else {
        return "";
    }
}