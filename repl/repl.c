#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/lexer.h"
#include "../token/token.h"

#define PROMPT ">> "
#define MAX_LINE_LEN 1024

void start_repl() {
    char line[MAX_LINE_LEN];

    while (1) {
        printf(PROMPT);
        fflush(stdout);  

        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        Lexer *lexer = new_lexer(line);
        if (!lexer) {
            fprintf(stderr, "Failed to create lexer.\n");
            continue;
        }

        Token tok;
        do {
            tok = next_token(lexer);
            printf("Type: %-15s Literal: %s\n", token_type_to_string(tok.type), tok.literal);
            free(tok.literal); 
        } while (tok.type != TOKEN_EOF);

        free(lexer->input);
        free(lexer);
    }
}
