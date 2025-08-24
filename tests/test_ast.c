#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../ast/ast.h"
#include "../token/token.h"  

int main(void) {
    // Create tokens
    Token let_token = { .type = TOKEN_LET, .literal = "let" };
    Token ident_token1 = { .type = TOKEN_IDENT, .literal = "myVar" };
    Token ident_token2 = { .type = TOKEN_IDENT, .literal = "anotherVar" };

    // Create identifiers
    Node* name = malloc(sizeof(Node));
    name->token = ident_token1;
    name->type = NODE_IDENTIFIER;
    name->as.identifier.value = strdup("myVar");

    Node* value = malloc(sizeof(Node));
    value->token = ident_token2;
    value->type = NODE_IDENTIFIER;
    value->as.identifier.value = strdup("anotherVar");

    // Create let statement
    Node* let_stmt = malloc(sizeof(Node));
    let_stmt->token = let_token;
    let_stmt->type = NODE_LET_STATEMENT;
    let_stmt->as.let_statement.name = name;
    let_stmt->as.let_statement.value = value;

    // Create program
    Program program;
    program.count = 1;
    program.statements = malloc(sizeof(Statement*));
    program.statements[0] = let_stmt;

    char* out = program_string(&program);
    assert(strcmp(out, "let myVar = anotherVar;") == 0);
    printf("Program.String() = %s\n", out);

    // Cleanup
    free(out);
    free(name->as.identifier.value);
    free(value->as.identifier.value);
    free(name);
    free(value);
    free(let_stmt);
    free(program.statements);

    return 0;
}