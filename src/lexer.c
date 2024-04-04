#include "./include/lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>



lexer_T* init_lexer(char *contents){

    lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->contents = contents;
    lexer->i = 0;
    lexer->c = contents[lexer->i];

    return lexer;

}

int is_operator_symbol(char c) {
    char operators[] = "+-*/<>&.@/:=˜|$!#%^_[]{}\"‘?";
    return strchr(operators, c) != NULL;
}


int is_punctuation(char c) {
    return c == '(' || c == ')' || c == ';' || c == ',';
}

//take the pointer to the next charactor
void lexer_advance(lexer_T *lexer){
    if(lexer->c != '\0' && lexer->i < strlen(lexer->contents)){
        lexer->i += 1;
        lexer->c = lexer->contents[lexer->i];
    }
    

}


//the 10 is in this case the newline character
token_T* lexer_skip_whitespace(lexer_T *lexer){
    while(lexer->c == ' ' || lexer->c == 10){
        lexer_advance(lexer);

    }

    return init_token(DELETE, "\0");
}

token_T* lexer_get_next_token(lexer_T *lexer){
    while(lexer->c != '\0' && lexer->i < strlen(lexer->contents)){
        if(lexer->c == ' ' || lexer->c == 10){
            return lexer_skip_whitespace(lexer);
            
        }

        

        if(lexer->c == '"'){
             token_T *token = lexer_collect_string(lexer);
             return token;
             
        }

        if(isalnum(lexer->c)){
            return lexer_collect_identifier(lexer);
        }

        if(isdigit(lexer->c)){
            return lexer_collect_integer(lexer);
        }

        if(is_operator_symbol(lexer->c)){
            return lexer_collect_operator(lexer);
        }

        if(is_punctuation(lexer->c)){
            return lexer_collect_punctuation(lexer);
        }


        
    }

    return init_token(DELETE, "\0");
}   


//Identifier -> Letter (Letter | Digit | '_' )*

token_T* lexer_collect_identifier(lexer_T *lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(isalnum(lexer->c) || lexer->c == '_'){
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(IDENTIFIER, value);
    
}


//Integer -> Digit+ 

token_T* lexer_collect_integer(lexer_T *lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(isdigit(lexer->c)){
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(INTEGER, value);
    
}

//Operator -> Operator_symbol+
token_T* lexer_collect_operator(lexer_T *lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';
    if(lexer->c == '/'){

        lexer_advance(lexer);
        if(lexer->c == '/'){
            lexer_advance(lexer);
            return lexer_collect_delete(lexer);
        }
    }

    while(is_operator_symbol(lexer->c)){
        
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(OPERATOR, value);

}
/*
String -> ’’’’
( ’\’ ’t’ | ’\’ ’n’ | ’\’ ’\’ | ’\’ ’’’’
| ’(’ | ’)’ | ’;’ | ’,’
|’’
| Letter | Digit | Operator_symbol
)* ’’’’ 
*/
token_T* lexer_collect_string(lexer_T *lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    lexer_advance(lexer);

    while(lexer->c != '"'){
        if(lexer->c == '\0'){
            printf("Error: Unterminated string\n");
            exit(1);
        }

        if(lexer->c == '\\'){
            lexer_advance(lexer);

            switch(lexer->c){
                case 'n':
                    strcat(value, "\n");
                    break;
                case 't':
                    strcat(value, "\t");
                    break;
                case '\\':
                    strcat(value, "\\");
                    break;
                case '"':
                    strcat(value, "\"");
                    break;
                case '(':
                    strcat(value, "(");
                    break;
                case ')':
                    strcat(value, ")");
                    break;
                case ';':
                    strcat(value, ";");
                    break;
                case ',':
                    strcat(value, ",");
                    break;
                case '\0':
                    printf("Error: Unterminated string\n");
                    exit(1);
                default:
                    printf("Error: Invalid escape character: \\%c\n", lexer->c);
                    exit(1);
            }
        }else{
            char* s = lexer_get_current_char_as_string(lexer);
            value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
            strcat(value, s);
        }

        lexer_advance(lexer);
    }

    lexer_advance(lexer);

    return init_token(STRING, value);


}
/*
Spaces -> ( ’ ’ | ht | Eol )+ => ’<DELETE>’;
Comment -> ’//’
( ’’’’ | ’(’ | ’)’ | ’;’ | ’,’ | ’\’ | ’ ’
| ht | Letter | Digit | Operator_symbol
)* Eol 
*/
token_T* lexer_collect_delete(lexer_T *lexer){
    char* value = calloc(1, sizeof(char));
    value[0] = '\0';

    while(lexer->c != '\n'){
        char* s = lexer_get_current_char_as_string(lexer);
        value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
        strcat(value, s);

        lexer_advance(lexer);
    }

    return init_token(DELETE, value);

}

/*
Punction 
-> ’(’ => ’(’
-> ’)’ => ’)’
-> ’;’ => ’;’
-> ’,’ => ’,’;
*/
token_T* lexer_collect_punctuation(lexer_T *lexer){
    char* value = lexer_get_current_char_as_string(lexer);
    lexer_advance(lexer);

    return init_token(PUNCTUATION, value);
}


token_T* lexer_advance_with_token(lexer_T *lexer, token_T *token){
    lexer_advance(lexer);

    return token;

}

char* lexer_get_current_char_as_string(lexer_T *lexer){
    char* str = calloc(1, sizeof(char));
    str[0] = lexer->c;
    str[1] = '\0';
    return str;
}

void print_tokens(lexer_T *lexer){
    token_T *token = lexer_get_next_token(lexer);
    while(lexer->i < strlen(lexer->contents)-1){
        switch (token->type)
        {

        case INTEGER:
            printf("<INTEGER> %s\n" , (token->value));
            break;
        case IDENTIFIER:
            printf("<IDENTIFIER> %s\n", token->value);
            break;
        case OPERATOR:
            printf("<OPERATOR> %s\n", token->value);
            break;
        case STRING:
            printf("<STRING> %s\n", token->value);
            break;
        case DELETE:
            printf("<DELETE> %s\n", token->value);
            break;
        case PUNCTUATION:
            printf("%s\n", token->value);
            break;
        default:
            break;


        }
        token = lexer_get_next_token(lexer);
    }
    
}
