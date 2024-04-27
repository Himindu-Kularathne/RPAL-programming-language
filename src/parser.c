#include "./include/parser.h"
#include "./include/lexer.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

parser_T* init_parser(lexer_T* lexer){
    parser_T* parser = calloc(1, sizeof(struct parser_STRUCT));
    parser->lexer = lexer;
    parser->current_token = get_next_token(lexer);
    return parser;
}

token_T* get_next_token(lexer_T* lexer){
   return lexer_get_next_token(lexer);
}


bool match(token_T* expected_type, parser_T* parser){
    if (parser->current_token->type == expected_type->type){
        parser->current_token = get_next_token(parser->lexer);
        return true;
    } else {
        printf("Syntax error in match()\n");
        return false;
    }
}


/*
E -> ’let’ D ’in’ E => ’let’
-> ’fn’ Vb+ ’.’ E => ’lambda’
-> Ew;
*/
void E(parser_T* parser){
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        D(parser);
        match(IDENTIFIER, parser);
        E(parser);
    } else if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        Vb(parser);
        match(OPERATOR, parser);
        E(parser);
    } else {
        Ew(parser);
    }
}

/*
Ew -> T ’where’ Dr => ’where’
-> T;
*/
void Ew(parser_T* parser){
    T(parser);
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        Dr(parser);
    } else {
        T(parser);
    }

}

/*
T -> Ta ( ’,’ Ta )+ => ’tau’
-> Ta ;
*/
void T(parser_T* parser){
    Ta(parser);
    if (parser->current_token->type == PUNCTUATION){
        match(PUNCTUATION, parser);
        Ta(parser);
    } else {
        Ta(parser);
    }

}

/*
Ta -> Ta ’aug’ Tc => ’aug’
-> Tc ;
*/
void Ta(parser_T* parser){
    Tc(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Tc(parser);
    } else {
        Tc(parser);
    }

}

/*
Tc -> B ’->’ Tc ’|’ Tc => ’->’
-> B ;
*/
void Tc(parser_T* parser){
    B(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Tc(parser);
        match(OPERATOR, parser);
        Tc(parser);
    } else {
        B(parser);
    }

}


/*
B ->B’or’ Bt => ’or’
-> Bt ;
*/
void B(parser_T* parser){
    Bt(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Bt(parser);
    } else {
        Bt(parser);
    }
}


/*
Bt -> Bt ’&’ Bs => ’&’
-> Bs ;
*/
void Bt(parser_T* parser){
    Bs(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Bs(parser);
    } else {
        Bs(parser);
    }
}

/*
Bs -> ’not’ Bp => ’not’
-> Bp ;
*/
void Bs(parser_T* parser){
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Bp(parser);
    } else {
        Bp(parser);
    }
}

/*
Bp -> A ’gr’ A => ’gr’
-> A ’ge’ A => ’ge’
-> A ’ls' A => ’ls’
-> A ’le’ A => ’le’
-> A ’eq’ A => ’eq’
-> A ’ne’ A => ’ne’
-> A ;
*/
void Bp(parser_T* parser){
    A(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        A(parser);
    } else {
        A(parser);
    }

}

/*
A ->A’+’ At => ’+’
-> A ’-’ At => ’-’
-> ’+’ At
-> ’-’ At => ’neg’
-> At ;
*/
void A(parser_T* parser){
    At(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        At(parser);
    } else {
        At(parser);
    }
}

/*
At -> At ’*’ Af => ’*’
-> At ’/’ Af => ’/’
-> Af ;
*/
void At(parser_T* parser){
    Af(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Af(parser);
    } else {
        Af(parser);
    }

}

/*
Af -> Ap ’**’ Af => ’**’
-> Ap ;
*/
void Af(parser_T* parser){
    Ap(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Af(parser);
    } else {
        Ap(parser);
    }

}

/*
Ap -> Ap ’@’ ’<IDENTIFIER>’ R => ’@’
-> R ;
*/
void Ap(parser_T* parser){
    R(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        match(IDENTIFIER, parser);
        R(parser);
    } else {
        R(parser);
    }

}

/*
Rn -> ’<IDENTIFIER>’
-> ’<INTEGER>’
-> ’<STRING>’
-> ’true’ => ’true’
-> ’false’ => ’false’
-> ’nil’ => ’nil’
-> ’(’ E ’)’
-> ’dummy’ => ’dummy’ ;
*/
void Rn(parser_T* parser){
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
    } else if (parser->current_token->type == INTEGER){
        match(INTEGER, parser);
    } else if (parser->current_token->type == STRING){
        match(STRING, parser);
    } else if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
    } else if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
    } else if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
    } else if (parser->current_token->type == PUNCTUATION){
        match(PUNCTUATION, parser);
        E(parser);
        match(PUNCTUATION, parser);
    } else {
        match(IDENTIFIER, parser);
    }

}

/*
D -> Da ’within’ D => ’within’
-> Da ;
*/
void D(parser_T* parser){
    Da(parser);
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        D(parser);
    } else {
        Da(parser);
    }
}

/*
Da -> Dr ( ’and’ Dr )+ => ’and’
-> Dr ;
*/
void Da(parser_T* parser){

    Dr(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        Dr(parser);
    } else {
        Dr(parser);
    }
}

/*
Dr -> ’rec’ Db => ’rec’
-> Db ;
*/
void Dr(parser_T* parser){
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        Db(parser);
    } else {
        Db(parser);
    }
}


/*
Db -> Vl ’=’ E => ’=’
-> ’<IDENTIFIER>’ Vb+ ’=’ E => ’fcn_form’
-> ’(’ D ’)’ ;
*/
void Db(parser_T* parser){
    Vl(parser);
    if (parser->current_token->type == OPERATOR){
        match(OPERATOR, parser);
        E(parser);
    } else if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        Vb(parser);
        match(OPERATOR, parser);
        E(parser);
    } else {
        match(PUNCTUATION, parser);
        D(parser);
        match(PUNCTUATION, parser);
    }

}


void Vb_plus(parser_T* parser){
    Vb(parser);
    if (parser->current_token->type == IDENTIFIER){
        Vb(parser);
    } else {
        Vb(parser);
    }
}

/*
Vb -> ’<IDENTIFIER>’
-> ’(’ Vl ’)’
-> ’(’ ’)’ => ’()’;
*/
void Vb(parser_T* parser){
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
    } else if (parser->current_token->type == PUNCTUATION){
        match(PUNCTUATION, parser);
        Vl(parser);
        match(PUNCTUATION, parser);
    } else {
        match(PUNCTUATION, parser);
    }

}

/*
Vl -> ’<IDENTIFIER>’ list ’,’ => ’,’?;
*/
void Vl(parser_T* parser){
    if (parser->current_token->type == IDENTIFIER){
        match(IDENTIFIER, parser);
        match(OPERATOR, parser);
    } else {
        match(OPERATOR, parser);
    }

}