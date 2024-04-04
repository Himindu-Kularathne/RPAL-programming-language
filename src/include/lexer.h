#ifndef LEXER_H
#define LEXER_H
#include "token.h"
typedef struct LEXER_STRUCT
{
    char *contents;
    char c;
    unsigned int i;
} lexer_T;


lexer_T* init_lexer(char *contents);
int is_operator_symbol(char c);
int is_punctuation_symbol(char c);

void lexer_advance(lexer_T *lexer);

token_T* lexer_skip_whitespace(lexer_T *lexer);
token_T* lexer_advance_with_token(lexer_T *lexer, token_T *token);
token_T* lexer_get_next_token(lexer_T *lexer);



token_T* lexer_collect_identifier(lexer_T *lexer);
token_T* lexer_collect_integer(lexer_T *lexer);
token_T* lexer_collect_operator(lexer_T *lexer);
token_T* lexer_collect_string(lexer_T *lexer);
token_T* lexer_collect_delete(lexer_T *lexer);
token_T* lexer_collect_punctuation(lexer_T *lexer);



char* lexer_get_current_char_as_string(lexer_T *lexer);
void print_tokens(lexer_T *lexer);
#endif