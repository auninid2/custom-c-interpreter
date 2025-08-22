#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "../token/token.h"

void check_parser_errors(Parser* p);

// ----------------------
// helper: check let stmt
// ----------------------
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

// -------------------------
// helper: check return stmt
// -------------------------
static int test_return_statement(Node* stmt) {
    if (stmt->type != NODE_RETURN_STATEMENT) {
        printf("FAIL: statement not NODE_RETURN_STATEMENT. got=%d\n", stmt->type);
        return 0;
    }

    if (strcmp(stmt->token.literal, "return") != 0) {
        printf("FAIL: stmt->token.literal not 'return'. got=%s\n", stmt->token.literal);
        return 0;
    }

    if (stmt->as.return_statement.return_value != NULL) {
        printf("FAIL: return value not NULL (expressions not parsed yet)\n");
        return 0;
    }

    return 1;
}

// ----------------------
// tests
// ----------------------
static void test_let_statements() {
    const char* input =
        "let x = 5;\n"
        "let y = 10;\n"
        "let foobar = 838383;\n";

    Lexer* l = new_lexer(input);
    Parser* p = parser_new(l);
    Program* program = parser_parse_program(p);
    check_parser_errors(p);

    if (program == NULL) {
        printf("FAIL: ParseProgram() returned NULL\n");
        exit(1);
    }

    if (program->count != 3) {
        printf("FAIL: program.Statements does not contain 3 statements. got=%d\n",
               program->count);
        exit(1);
    }

    const char* expected_identifiers[] = {"x", "y", "foobar"};

    for (int i = 0; i < 3; i++) {
        if (!test_let_statement(program->statements[i], expected_identifiers[i])) {
            exit(1);
        }
    }

    printf("test_let_statements passed!\n");
}

static void test_return_statements() {
    const char* input =
        "return 5;\n"
        "return 10;\n"
        "return 993322;\n";

    Lexer* l = new_lexer(input);
    Parser* p = parser_new(l);
    Program* program = parser_parse_program(p);
    check_parser_errors(p);

    if (program == NULL) {
        printf("FAIL: ParseProgram() returned NULL\n");
        exit(1);
    }

    if (program->count != 3) {
        printf("FAIL: program.Statements does not contain 3 statements. got=%d\n",
               program->count);
        exit(1);
    }

    for (int i = 0; i < 3; i++) {
        if (!test_return_statement(program->statements[i])) {
            exit(1);
        }
    }

    printf("test_return_statements passed!\n");
}

// ----------------------
// main
// ----------------------
int main() {
    test_let_statements();
    test_return_statements();
    printf("ALL TESTS PASSED\n");
    return 0;
}