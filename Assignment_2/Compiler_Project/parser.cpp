#include "parser.h"
using namespace std;

Parser::Parser() {
    token = lex.lexer();
    RAT18S();
}

void Parser::RAT18S() {
//    printf("<RAT18S> -> <Opt Function Definitions>   %%  <Opt Declaration List>  <Statement List>  \n");
    token = lex.lexer();
    OptFunctionDefinitions();
    token = lex.lexer();
    if (token == PERCENT) {
        OptDeclarationList();
        StatementList();
    }
}
void Parser::OptDeclarationList() {
//    printf("<Opt Declaration List> -> \n");
}

void Parser::OptParameterList() {
//    printf("<Opt Parameter List> ->\n");
    ParameterList();
}

/*------------------------------QUESTION-------------------------------------*/
void Parser::Identifier() {
    printf("<Identifier> ->\n");
}
void Parser::OptFunctionDefinitions() {
//    printf("<Opt Function Definitions> -> <Function Definitions> \n");
    FunctionDefinitions();
}

void Parser::FunctionDefinitions() {
//    printf("<Function Definitions> -> <Function> \n");
    Function();
}

void Parser::Function() {
//    printf("<Function> ->\n");
    lex.lexer();
    string lexeme = lex.getLexeme();
//    printf("%s\n",lexeme.c_str());
    if ( lexeme == "function" ) {
        token = lex.lexer();
        if (token == IDENT) {
            token = lex.lexer();
            if (token == LEFT_BLOCK) {
                OptParameterList();
                token = lex.lexer();
                if (token == RIGHT_BLOCK) {
                    OptDeclarationList();
                    Body();
                }
            }
        }
    }
}// END Function

void Parser::ParameterList() {
//    printf("<Parameter List> ->\n");
    Parameter();
    token = lex.lexer();
    if (token == COMMA) {
        Parameter();
        ParameterList();
    }
}


void Parser::Parameter() {
//    printf("<Parameter> ->\n");
    token = lex.lexer();
    if (token == IDENT) {
      token = lex.lexer();
      if (token == COLON) {
        Qualifier();
      } else {
        printf("ERROR*---* No Colon found\n");
      }
    } else {
      printf("ERROR*---* No Identifier found\n");
    }
}

void Parser::IDs() {
    printf("<IDs> ->\n");
}
/*---------------------fix--------------------*/
void Parser::Qualifier() {
    char* lexeme = lex.getLexeme();
    if (strncmp(lexeme, "int", strlen("int")) || strncmp(lexeme, "real", strlen("real")) || strncmp(lexeme, "boolean", strlen("boolean"))) {

    } else {
      printf("ERROR*---* No Qualifier found\n");
    }
}

void Parser::Body() {
    token = lex.lexer();
    if (token == LEFT_CURLY_BRACE) {
        token = lex.lexer();
        StatementList();
        if (token != RIGHT_CURLY_BRACE) {
            printf("ERROR*---* No Right Curly Brace found\n");
        }
    } else {
      printf("ERROR*---* No Left Curly Brace found\n");
    }
}


/*------------------------------QUESTION-------------------------------------*/
void Parser::StatementList() {
    Statement();
}

void Parser::Statement() {
    string lexeme = lex.getLexeme();
//    printf("%s\n",lexeme.c_str());
    
    if (lexeme == "return") {
        Return();
    } else if (lexeme == "if") {
        If();
    } else if (lexeme == "get") {
        Scan();
    } else if (lexeme == "put") {
        Print();
    } else if (lexeme == "while") {
        While();
    } else {
        Compound();
    }
}

void Parser::Compound() {
    token = lex.lexer();
    if (token == LEFT_CURLY_BRACE) {
        token = lex.lexer();
        StatementList();
        if (token != RIGHT_CURLY_BRACE) {
            printf("ERROR*---* No Right Curly Brace found\n");
        }
    } else {
        printf("ERROR*---* No Left Curly Brace found\n");
    }
}


/*------------------------------QUESTION-------------------------------------*/
void Parser::Assign() {
    Identifier();
}

void Parser::If() {
    token = lex.lexer();
    char* lexeme = lex.getLexeme();
    if ( strncmp(lexeme, "if", strlen("if")) ) {
        token = lex.lexer();
        if (token == LEFT_PAREN) {
            token = lex.lexer();
            Condition();
            if (token == RIGHT_BLOCK) {
                token = lex.lexer();
                Statement();
                char* lexeme = lex.getLexeme();
                if ( strncmp(lexeme, "endif", strlen("endif")) ) {
                    lex.lexer();
                }
            }// right block
        }
    } else {
        printf("ERROR*---* No if found\n");
    }
}


void Parser::Return() {
    string lexeme = lex.getLexeme();
    if ( lexeme == "return" ) {
        token = lex.lexer();
        if( token == SEMICOLON ) {
            token = lex.lexer();
        } else {
//            token = lex.lexer();
            string lexeme = lex.getLexeme();
            printf("%s\n",lexeme.c_str());
            Expression();
        }
    }
}


void Parser::Print() {
    token = lex.lexer();
    string lexeme = lex.getLexeme();
    if ( lexeme == "put" ) {
        token = lex.lexer();
        if( token == LEFT_PAREN ) {
            token = lex.lexer();
            Expression();
            if (token == RIGHT_PAREN) {
                token = lex.lexer();
                if (token == SEMICOLON) {
                    token = lex.lexer();
                }
            }
        }
    }
}

void Parser::Scan() {
    token = lex.lexer();
    string lexeme = lex.getLexeme();
    if ( lexeme == "get" ) {
        token = lex.lexer();
        if( token == LEFT_PAREN ) {
            token = lex.lexer();
            IDs();
            if (token == RIGHT_PAREN) {
                token = lex.lexer();
                if (token == SEMICOLON) {
                    lex.lexer();
                }
            }
        }
    }
}

void Parser::While() {
    printf("<While> ->\n");
    token = lex.lexer();
    string lexeme = lex.getLexeme();
    if ( lexeme == "while" ) {
        token = lex.lexer();
        if( token == LEFT_PAREN ) {
            token = lex.lexer();
            Condition();
            if (token == RIGHT_PAREN) {
                token = lex.lexer();
                Statement();
            }
        }
    }
}

void Parser::Condition() {
    token = lex.lexer();
    Expression();
    Relop();
    Expression();
}


void Parser::Relop() {
    printf("<Relop> ->\n");
    token = lex.lexer();
    switch (token) {
        case EQ_EQ_OP: {
            token = lex.lexer();
            break;
        }
        case EQ_OP: {
            token = lex.lexer();
            break;
        }
        case GT_OP: {
            token = lex.lexer();
            break;
        }
        case LT_OP: {
            token = lex.lexer();
            break;
        }
        case EQ_GT_OP: {
           token =  lex.lexer();
            break;
        }
        case EQ_LT_OP: {
            token = lex.lexer();
            break;
        }
        default:
            break;
    }
}

void Parser::Expression() {
    Term();
    ExpressionPrime();
}

void Parser::ExpressionPrime() {
    int eplison = 1;
    string lexeme = lex.getLexeme();
    if ( lexeme == "+" ) {
        eplison = 0;
        token = lex.lexer();
        Term();
        ExpressionPrime();
    } else if ( lexeme == "-" ) {
        eplison = 0;
        token = lex.lexer();
        Term();
        ExpressionPrime();
    }
    
    if (eplison == 1) { /*printf("<EpressionPrime> -> null\n");*/ }
}


void Parser::Term() {
    Factor();
    TermPrime();
}

void Parser::TermPrime() {
    int eplison = 1;
    string lexeme = lex.getLexeme();
    if ( lexeme == "*" ) {
        token = lex.lexer();
        printf("%s\n",lexeme.c_str());
        eplison = 0;
        Factor();
        TermPrime();
    } else if ( lexeme == "/" ) {
        eplison = 0;
        Factor();
        TermPrime();
    }
    
    if (eplison == 1) { /*printf("<TermPrime> -> null\n");*/ }
}

void Parser::Factor() {
    string lexeme = lex.getLexeme();
//    printf("%s\n",lexeme.c_str());
    if ( lexeme == "-" ) {
        Primary();
    } else {
        Primary();
    }
}

void Parser::Primary() {
    token = lex.lexer();
    switch (token) {
        case IDENT: {
            string lexeme = lex.getLexeme();
            printf("%s\n",lexeme.c_str());
            token = lex.lexer();
            Identifier();
            if( token == LEFT_PAREN ) {
                token = lex.lexer();
                string lexeme = lex.getLexeme();
                printf("%s\n",lexeme.c_str());
                IDs();
                if (token == RIGHT_PAREN) {
                    token = lex.lexer();
                }
            }
            break;
        }
        case INT_LIT: {
            token = lex.lexer();
            break;
        }
        case LEFT_PAREN: {
//            token = lex.lexer();
            Expression();
            break;
        }
        case REAL_LIT: {
            token = lex.lexer();
            break;
        }
        case TRUE_OP: {
            token =  lex.lexer();
            break;
        }
        case FALSE_OP: {
            token = lex.lexer();
            break;
        }
        default:
            break;
    }
}

void Parser::Integer(){
}
void Parser::Real(){
    
}

void Parser::Empty() {
    printf("<Empty> -> null\n");
}
