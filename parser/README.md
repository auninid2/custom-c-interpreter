## Functionality of a Parser

The parser is the part of our interpreter that gives meaning to the code we are writing. Let’s take the code `let x = 5;` as an example. Without parsing, our interpreter only recognizes that there is `let`, `x`, `=`, and `5` which doesn’t really have a meaning for the computer. However, when a parser comes across it, it recognizes that we have a *let statement*, and that it should be followed by an identifier (`x`), an assignment (`=`), and an expression (`5`). While building up the data structure, the parser also checks if the given input is valid according to our grammar.

Formally speaking, the parser takes text as input and builds a data structure out of it—an abstract syntax tree (AST for short) in our case. *Abstract* refers to the fact that certain details visible in the source code are not added to the syntax tree. Depending on the language, things like semicolons, whitespace, or newlines aren’t represented in the tree, but merely serve as guides for the parser and lexer to do their job.

For example, the statement `let x = 5;` might be represented in the AST like this:

```
Program
 └── LetStatement
      ├── Identifier: "x"
      └── Expression
           └── IntegerLiteral: 5
```

When it comes to parsing a programming language, there are two main methodologies that come in different flavors: **top-down parsing** and **bottom-up parsing**. In a *top-down parser*, the process begins at the root of the AST and works its way down toward the leaves, predicting which grammar rules to use based on the current token. A *bottom-up parser*, on the other hand, starts with the tokens (the leaves) and gradually reduces them into higher-level grammar constructs until it reaches the root of the tree.

You can think of it this way: a top-down parser tries to answer *“what should this code look like?”* and then checks if the tokens match, while a bottom-up parser takes the tokens as they come and tries to answer *“what can these tokens be combined into?”*. In our case, we are using a **recursive descent parser**, which starts with the root node of the AST and works its way downward. It’s called *recursive* because the parser uses functions that call themselves (directly or indirectly) to process the grammar rules. You can see this in the code: functions like `parse_statement()`, `parse_expression()`, and `parse_let_statement()` call each other recursively to build the AST.

## Parsing Expressions

In the Monkey programming language, we differentiate between **statements** and **expressions**. If you look at the code, you’ll see that parsing statements is pretty straightforward: we process tokens from left to right, check whether the next tokens are what we expect, and if everything matches, we return an AST node.

The real challenge comes when parsing expressions. Parsing a simple expression like the `5` in `let x = 5;` is easy, since it’s just a single value. But more complex expressions, such as `5 + 10 * 4`, introduce operator precedence — and this is where things get trickier. The parser has to know that multiplication should be evaluated before addition, and it needs to build the AST in a way that reflects this order.