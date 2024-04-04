
#include <stdio.h>
#include "include/lexer.h"



int main(int args, char* argv[]) {
    lexer_T* lexer = init_lexer(
        "// this is a comment\n"
        "let Sum(A) = Psum (A,Order A )\n"
            "where rec Psum (T,N) = N eq 0 -> 0\n"
                "| Psum(T,N-1)+T N\n"
        "in Print ( Sum (1,2,3,4,5) )\n"
    );
   
    print_tokens(lexer);
    
}