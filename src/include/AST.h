#ifndef AST_H
#define AST_H
#include <stdlib.h>
typedef struct AST_STRUCT{
    enum {
        LET,
        ID,
        WHERE,
        REC,
        EQ,
        INT,
        ARROW,
        PLUS,
        COMMA,
        PRINT,
        LPAREN,
        RPAREN,
        SEMICOLON
    }type;


    char* label;
    char* value;
    struct AST_STRUCT** children;   
    int number_of_children;
   

}AST_T;

AST_T* init_ast(int type);

AST_T* createNode(const char* label, const char* value, int num_children);
void print_ast(AST_T* ast, int level);
#endif