#ifndef AST_H
#define AST_H

typedef struct Node Node;
typedef struct Statement Statement;
typedef struct Expression Expression;
typedef struct Program Program;

char* token_literal(Program* p);

#endif