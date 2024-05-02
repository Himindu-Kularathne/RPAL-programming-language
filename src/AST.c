#include "./include/AST.h"


AST_T* init_ast(int type){
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->type = type;
    ast->label = NULL;
    ast->value = NULL;
    ast->children = NULL;
    ast->number_of_children = 0;
    return ast;

}


AST_T* createNode(const char* label, const char* value, int num_children){
    AST_T* ast = calloc(1, sizeof(struct AST_STRUCT));
    ast->label = label;
    ast->value = value;
    ast->children = calloc(num_children, sizeof(struct AST_STRUCT*));
    ast->number_of_children = num_children;
    return ast;

}



void print_ast(AST_T* ast, int level){
    

}