#include "./include/parser.h"
#include <stdbool.h>

token_T* get_next_token(lexer_T* lexer){
    return lexer_get_next_token(lexer);

}

bool match(token_T* expected_type, parser_T* parser){
    token_T* current_token = parser->current_token;
    if(current_token->type == expected_type->type){
        free(current_token->value);
        free(current_token);
        parser->current_token = get_next_token(parser->lexer);
        return true;
    }
    printf("Syntax error: Expected %s but got %s\n", expected_type->value, current_token->value);
    return false;
}

/*
E -> ’let’ D ’in’ E => ’let’
-> ’fn’ Vb+ ’.’ E => ’lambda’
-> Ew;
*/
void E(parser_T* parser){
    

    

}
void Ew(parser_T* parser){
    token_T* current_token = parser->current_token;
    if (current_token->type == OPERATOR) {
        match(current_token, parser->lexer);
        Ew(parser);
    } else if (current_token->type == PUNCTUATION) {
        match(current_token, parser->lexer);
        E(parser);
        match(current_token, parser->lexer);
    } else {
        printf("Syntax error in Ew()\n");
    }


}
void T(){

}
void Ta(){


}
void Tc(){

}
void B(){

}
void Bt(){

}
void Bs(){

}
void Bp(){

}
void A(){

}
void At(){

}
void Ap(){

}
void R(){

}
void Rn(){

}
void D(){

}
void Da(){

}
void Dr(){

}
void Db(){

}
void Vb_plus(){

}
void Vb(){

}
void Vl(){

}