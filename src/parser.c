#include "include/parser.h"



parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    return parser;

}
void parser_eat(parser_T* parser, int token_type){
    if(parser->current_token->type == token_type){
        parser->current_token = lexer_get_next_token(parser->lexer);
    }else{
        printf("Unexpected token: %s with type %d\n", parser->current_token->value, parser->current_token->type);
        exit(1);
    }
}
AST_T* parser_parse(parser_T* parser){
    return parser_parse_statements(parser);

}
AST_T* parser_parse_statement(parser_T* parser){

}  
AST_T* parser_parse_statements(parser_T* parser){

    AST_T* compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT));
    AST_T* ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    
}
AST_T* parser_parse_expression(parser_T* parser){

}
AST_T* parser_parse_factor(parser_T* parser){

}
AST_T* parser_parse_term(parser_T* parser){

}
AST_T* parser_parse_function_call(parser_T* parser){

}
AST_T* parser_parse_variable(parser_T* parser){

}
AST_T* parser_parse_string(parser_T* parser){

}