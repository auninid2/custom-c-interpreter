#ifndef AST_H
#define AST_H

#include "../token/token.h"

typedef enum {
    NODE_PROGRAM,
    NODE_LET_STATEMENT,
    NODE_RETURN_STATEMENT,
    NODE_EXPRESSION_STATEMENT,
    NODE_IDENTIFIER,
    NODE_INTEGER_LITERAL,
} NodeType;

// Node (base for all AST nodes)
typedef struct Node {
    Token token;   
    NodeType type; 
    union {
        struct {              
            struct Node* name;  
            struct Node* value;
        } let_statement;

        struct {
            struct Node* return_value;
        } return_statement;

        struct {               
            char* value;       
        } identifier;
    } as;
} Node;

typedef Node Statement;
typedef Node Expression;

// Program holds a list of statements
typedef struct {
    Statement** statements;
    int count;
} Program;


const char* program_token_literal(Program* p);
const char* let_statement_token_literal(const Statement* s);
const char* identifier_token_literal(const Expression* e);
const char* return_statement_token_literal(Node* rs);

#endif 