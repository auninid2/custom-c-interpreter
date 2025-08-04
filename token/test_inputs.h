// Source code to be interpreted
const char* input = 
    "let five = 5;\n"
    "let ten = 10;\n"
    "\n"
    "let add = fn(x, y) {\n"
    "    x + y;\n"
    "};\n"
    "\n"
    "let result = add(five, ten);\n"
    "!-/*5;\n"
    "5 < 10 > 5;\n"
    "\n"
    "if (5 < 10) {\n"
    "    return true;\n"
    "} else {\n"
    "    return false;\n"
    "}\n"
    "\n"
    "10 ==  10;\n"
    "10 != 9;\n";

// Input (source code) as tokens
Test tests[] = {
    {TOKEN_LET, "let"},
    {TOKEN_IDENT, "five"},
    {TOKEN_ASSIGN, "="},
    {TOKEN_INT, "5"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_LET, "let"},
    {TOKEN_IDENT, "ten"},
    {TOKEN_ASSIGN, "="},
    {TOKEN_INT, "10"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_LET, "let"},
    {TOKEN_IDENT, "add"},
    {TOKEN_ASSIGN, "="},
    {TOKEN_FUNCTION, "fn"},
    {TOKEN_LPAREN, "("},
    {TOKEN_IDENT, "x"},
    {TOKEN_COMMA, ","},
    {TOKEN_IDENT, "y"},
    {TOKEN_RPAREN, ")"},

    {TOKEN_LBRACE, "{"},
    {TOKEN_IDENT, "x"},
    {TOKEN_PLUS, "+"},
    {TOKEN_IDENT, "y"},
    {TOKEN_SEMICOLON, ";"},
    {TOKEN_RBRACE, "}"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_LET, "let"},
    {TOKEN_IDENT, "result"},
    {TOKEN_ASSIGN, "="},
    {TOKEN_IDENT, "add"},
    {TOKEN_LPAREN, "("},
    {TOKEN_IDENT, "five"},
    {TOKEN_COMMA, ","},
    {TOKEN_IDENT, "ten"},
    {TOKEN_RPAREN, ")"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_BANG, "!"},
    {TOKEN_MINUS, "-"},
    {TOKEN_SLASH, "/"},
    {TOKEN_ASTERISK, "*"},
    {TOKEN_INT, "5"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_INT, "5"},
    {TOKEN_LT, "<"},
    {TOKEN_INT, "10"},
    {TOKEN_GT, ">"},
    {TOKEN_INT, "5"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_IF, "if"},
    {TOKEN_LPAREN, "("},
    {TOKEN_INT, "5"},
    {TOKEN_LT, "<"},
    {TOKEN_INT, "10"},
    {TOKEN_RPAREN, ")"},
    {TOKEN_LBRACE, "{"},

    {TOKEN_RETURN, "return"},
    {TOKEN_TRUE, "true"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_RBRACE, "}"},
    {TOKEN_ELSE, "else"},
    {TOKEN_LBRACE, "{"},

    {TOKEN_RETURN, "return"},
    {TOKEN_FALSE, "false"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_RBRACE, "}"},

    {TOKEN_INT, "10"},
    {TOKEN_EQ, "=="},
    {TOKEN_INT, "10"},
    {TOKEN_SEMICOLON, ";"},

    {TOKEN_INT, "10"},
    {TOKEN_NOT_EQ, "!="},
    {TOKEN_INT, "9"},
    {TOKEN_SEMICOLON, ";"},
    
    {TOKEN_EOF, ""}
};