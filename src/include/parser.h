#ifndef PHARSER_H
#define PHARSER_H
#include "token.h"
#include <stdbool.h>
#include "lexer.h"


typedef struct parser_STRUCT{
    token_T* current_token;
    lexer_T* lexer;
    
}parser_T;

parser_T* init_parser(lexer_T* lexer);
token_T* get_next_token(lexer_T* lexer);
bool match(token_T* expected_type,  parser_T* parser);
void E();
void Ew();
void T();
void Ta();
void Tc();
void B();
void Bt();
void Bs();
void Bp();
void A();
void At();
void Ap();
void R();
void Rn();
void D();
void Da();
void Dr();
void Db();
void Vb_plus();
void Vb();
void Vl();

#endif