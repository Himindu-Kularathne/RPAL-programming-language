#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
    enum
    {
        IDENTIFIER,
        INTEGER,
        OPERATOR,
        STRING,
        DELETE,
        PUNCTUATION
    
    } type;
    char *value;
} token_T;

token_T* init_token(int type, char *value);

#endif