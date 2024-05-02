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
void E(parser_T* parser);
void Ew(parser_T* parser);
void T(parser_T* parser);
void Ta(parser_T* parser);
void Tc(parser_T* parser);
void B(parser_T* parser);
void Bt(parser_T* parser);
void Bs(parser_T* parser);
void Bp(parser_T* parser);
void A(parser_T* parser);
void At(parser_T* parser);
void Af(parser_T* parser);
void Ap(parser_T* parser);
void R(parser_T* parser);
void Rn(parser_T* parser);
void D(parser_T* parser);
void Da(parser_T* parser);
void Dr(parser_T* parser);
void Db(parser_T* parser);
void Vb_plus(parser_T* parser);
void Vb(parser_T* parser);
void Vl(parser_T* parser);

#endif