#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "../token/token.h"

// helper: check a let statement
static int test_let_statement(Node* stmt, const char* expected_name) {
    if (stmt->type != NODE_LET_STATEMENT) {
        printf("FAIL: statement not NODE_LET_STATEMENT. got=%d\n", stmt->type);
        return 0;
    }

    if (strcmp(stmt->token.literal, "let") != 0) {
        printf("FAIL: stmt->token.literal not 'let'. got=%s\n", stmt->token.literal);
        return 0;
    }

    Node* ident = stmt->as.let_statement.name;
    if (ident->type != NODE_IDENTIFIER) {
        printf("FAIL: name is not NODE_IDENTIFIER. got=%d\n", ident->type);
        return 0;
    }

    if (strcmp(ident->as.identifier.value, expected_name) != 0) {
        printf("FAIL: identifier name wrong. expected=%s, got=%s\n",
               expected_name, ident->as.identifier.value);
        return 0;
    }

    return 1;
}

int main() {
    const char* input =
        "let x = 5;\n"
        "let y = 10;\n"
        "let foobar = 838383;\n";

    Lexer* l = new_lexer(input);
    Parser* p = parser_new(l);

    Program* program = parser_parse_program(p);
    if (program == NULL) {
        printf("FAIL: ParseProgram() returned NULL\n");
        return 1;
    }

    if (program->count != 3) {
        printf("FAIL: program.Statements does not contain 3 statements. got=%d\n",
               program->count);
        return 1;
    }

    const char* expected_identifiers[] = {"x", "y", "foobar"};

    for (int i = 0; i < 3; i++) {
        if (!test_let_statement(program->statements[i], expected_identifiers[i])) {
            return 1; // stop on failure
        } 
    }

    printf("ALL TESTS PASSED\n");
    return 0;
}
