#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "../token/token.h"

// -------------------------------
// ---- macros for assertion -----
// -------------------------------
#define ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "FAIL: %s\n", msg); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

// -------------------------------
// ---------- helpers  -----------
// -------------------------------
static Program* parse_input(const char* input) {
    Lexer* l = new_lexer(input);
    Parser* p = parser_new(l);
    Program* program = parser_parse_program(p);
    check_parser_errors(p);

    ASSERT(program != NULL, "ParseProgram() returned NULL");
    return program;
}

static void assert_stmt_type(Node* stmt, NodeType expected, const char* msg) {
    ASSERT(stmt->type == expected, msg);
}

static void assert_identifier(Node* ident, const char* expected_name) {
    assert_stmt_type(ident, NODE_IDENTIFIER, "node is not Identifier");
    ASSERT(strcmp(ident->as.identifier.value, expected_name) == 0, "identifier name mismatch");
}

static void check_program_count(Program* program, int expected) {
    ASSERT(program->count == expected, "program.Statements count mismatch");
}

// -------------------------------
// ----------- tests -------------
// -------------------------------
static void test_let_statements() {
    const char* input =
        "let x = 5;\n"
        "let y = 10;\n"
        "let foobar = 838383;\n";

    Program* program = parse_input(input);
    check_program_count(program, 3);

    const char* expected_identifiers[] = {"x", "y", "foobar"};

    for (int i = 0; i < 3; i++) {
        Node* stmt = program->statements[i];
        assert_stmt_type(stmt, NODE_LET_STATEMENT, "statement not NODE_LET_STATEMENT");
        ASSERT(strcmp(stmt->token.literal, "let") == 0, "stmt->token.literal not 'let'");
        Node* ident = stmt->as.let_statement.name;
        assert_identifier(ident, expected_identifiers[i]);
    }

    printf("PASS: test_let_statements\n");
}

static void test_return_statements() {
    const char* input =
        "return 5;\n"
        "return 10;\n"
        "return 993322;\n";

    Program* program = parse_input(input);
    check_program_count(program, 3);

    for (int i = 0; i < 3; i++) {
        Node* stmt = program->statements[i];
        assert_stmt_type(stmt, NODE_RETURN_STATEMENT, "statement not NODE_RETURN_STATEMENT");
        ASSERT(strcmp(stmt->token.literal, "return") == 0, "stmt->token.literal not 'return'");
        ASSERT(stmt->as.return_statement.return_value == NULL, "return value not NULL");
    }

    printf("PASS: test_return_statements\n");
}

static void test_identifier_expression() {
    const char* input = "foobar;";

    Program* program = parse_input(input);
    check_program_count(program, 1);

    Node* stmt = program->statements[0];
    assert_stmt_type(stmt, NODE_EXPRESSION_STATEMENT, "program.Statements[0] is not ExpressionStatement");

    Node* expr = stmt->as.expression_statement.expression;
    assert_identifier(expr, "foobar");

    ASSERT(strcmp(identifier_token_literal(expr), "foobar") == 0,
           "ident.TokenLiteral not foobar");

    printf("PASS: test_identifier_expression\n");
}

typedef void (*TestFn)(void);

int main() { 
    test_let_statements(); 
    test_return_statements(); 
    test_identifier_expression(); 
    
    printf("ALL TESTS PASSED\n"); 
    return 0; 
}