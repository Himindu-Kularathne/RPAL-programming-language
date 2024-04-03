
#include <stdio.h>
#include "include/lexer.h"


int main(int args, char* argv[]) {
    lexer_T* lexer = init_lexer(
        "var name = \"Himindu Kularathne\";\n"
        "print(name);\n"
    );
   

    token_T* token = lexer_get_next_token(lexer);
    while(token->type != TOKEN_EOF){
        printf("TOKEN(%d, %s)\n", token->type, token->value);
        token = lexer_get_next_token(lexer);
    }
    return 0;
}