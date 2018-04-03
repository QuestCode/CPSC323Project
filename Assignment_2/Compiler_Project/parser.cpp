#include "parser.h"
using namespace std;

Token Parser::nonComment() {
    while (token == COM) {
//        printToken(token, lex.getLexeme());
        token = lex.lexer();
    }
    return token;
}

void Parser::printToken(Token token,string lexeme) {
    std::string id[] = {"Identifier","Keyword", "Integer", "Real","Separator","Operator","Comment","Boolean"};
    
    switch (token) {
        case KEYWORD:
            printf("Token: %s\t\t\tLexeme: %s\n", id[1].c_str(),lexeme.c_str());
            break;
        case IDENT:
            printf("Token: %s\t\tLexeme: %s\n", id[0].c_str(),lexeme.c_str());
            break;
        case INT_LIT:
            printf("Token: %s\t\t\tLexeme: %s\n", id[2].c_str(),lexeme.c_str());
            break;
        case REAL_LIT:
            printf("Token: %s\t\tLexeme: %s\n", id[3].c_str(),lexeme.c_str());
            break;
        case COM:
            printf("Token: %s\t\tLexeme: %s\n", id[6].c_str(),lexeme.c_str());
            break;
        case PERCENT:
        case COMMA:
        case COLON:
        case SEMICOLON:
        case LEFT_BLOCK:
        case LEFT_PAREN:
        case RIGHT_BLOCK:
        case RIGHT_PAREN:
        case LEFT_CURLY_BRACE:
        case RIGHT_CURLY_BRACE:
            printf("Token: %s\t\tLexeme: %s\n", id[4].c_str(),lexeme.c_str());
            break;
        case ADD_OP:
        case SUB_OP:
        case MULT_OP:
        case DIV_OP:
        case EQ_OP:
        case LT_OP:
        case GT_OP:
        case UP_EQ_OP:
        case EQ_LT_OP:
        case EQ_GT_OP:
        case EQ_EQ_OP:
        case TRUE_OP:
        case FALSE_OP:
            printf("Token: %s\t\t\tLexeme: %s\n", id[5].c_str(),lexeme.c_str());
            break;
        default:
            break;
    }
}

Parser::Parser() {
    // Remove Blank
    token = lex.lexer();
    printToken(token, lex.getLexeme());
    RAT18S();
}

void Parser::RAT18S() {
    printf("\t<Rat18S> ::= <Opt Function Definitions> %%  <Opt Declaration List>  <Statement List>\n");
    token = lex.lexer();
    token = nonComment();
    printToken(token, lex.getLexeme());
    OptFunctionDefinitions();
    printToken(token, lex.getLexeme());
    if (token == PERCENT) {
        token = lex.lexer();
        token = nonComment();
        printToken(token, lex.getLexeme());
        OptDeclarationList();
        StatementList();
    }
}


void Parser::OptFunctionDefinitions() {
    printf("\t<Opt Function Definitions> ::= <Function Definitions> | <Empty>\n");
    FunctionDefinitions();
    token = nonComment();
}

void Parser::FunctionDefinitions() {
    printf("\t<Function Definitions>  ::= <Function> <Function Definitions Prime>\n");
    token = nonComment();
    Function();
    token = nonComment();
    FunctionDefinitionsPrime();
}

void Parser::FunctionDefinitionsPrime() {
    string lexeme = lex.getLexeme();
    if (token == RIGHT_CURLY_BRACE) {
        printf("\t<Function Definitions Prime>  ::= <Function>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        FunctionDefinitions();
    } else {
        printf("\t<Function Definitions Prime>  ::= ɛ\n");
    }
}

void Parser::Function() {
    string lexeme = lex.getLexeme();
    if ( lexeme == "function" ) {
        printf("\t<Function> ::= function <Identifier> [ <Opt Parameter List> ] <Opt Declaration List> <Body>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        if (token == IDENT) {
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            if (token == LEFT_BLOCK) {
                token = lex.lexer();
                printToken(token, lex.getLexeme());
                OptParameterList();
                if (token == RIGHT_BLOCK) {
                    token = lex.lexer();
                    printToken(token, lex.getLexeme());
                    OptDeclarationList();
                    Body();
                }
            }
        }
    }
}// END Function


void Parser::OptParameterList() {
    printf("\t<Opt Parameter List> ::= <Parameter List> | <Empty>\n");
    ParameterList();
}

void Parser::ParameterList() {
    printf("\t<Parameter List>  ::=  <Parameter> <Parameter List Prime>\n");
    Parameter();
    ParameterListPrime();
}

void Parser::ParameterListPrime() {
    string lexeme = lex.getLexeme();
    if (token == COMMA) {
        printf("\t<Parameter List Prime>  ::=  , <Parameter List>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        ParameterList();
    } else {
        printf("\t<Parameter List Prime>  ::= ɛ\n");
    }
}


void Parser::Parameter() {
    printf("\t<Parameter> ::= <IDs> : <Qualifier>\n");
    if (token == IDENT) {
      token = lex.lexer();
        printToken(token, lex.getLexeme());
      if (token == COLON) {
          token = lex.lexer();
          printToken(token, lex.getLexeme());
          Qualifier();
      } else {
        printf("ERROR*---* No Colon found\n");
      }
    } else {
      printf("ERROR*---* No Identifier found\n");
    }
}

void Parser::Qualifier() {
    string lexeme = lex.getLexeme();
    if (lexeme == "int") {
        printf("\t<Qualifier> ::= int\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
    } else if (lexeme == "real") {
        printf("\t<Qualifier> ::= real\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
    } else if (lexeme == "boolean") {
        printf("\t<Qualifier> ::= boolean\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
    } else {
//        printf("ERROR*---* No Quantifier found\n");
    }
}


void Parser::Body() {
    printf("\t<Body> ::= { <Statement List> }\n");
    if (token == LEFT_CURLY_BRACE) {
        token = lex.lexer();
        token = nonComment();
        printToken(token, lex.getLexeme());
        StatementList();
        if (token != RIGHT_CURLY_BRACE) {
//            printf("ERROR*---* No Right Curly Brace found\n");
        }
    } else {
//        printf("ERROR *---* No Left Curly Brace found\n");
    }
}

void Parser::OptDeclarationList() {
    printf("\t<Opt Declaration List> ::= <Declaration List> | <Empty>\n");
    DeclarationList();
}

void Parser::DeclarationList() {
    printf("\t<Declaration List>  := <Declaration> ; <Declaration List Prime>\n");
    Declaration();
    if (token == SEMICOLON) {
        token = lex.lexer();
        token = nonComment();
        printToken(token, lex.getLexeme());
        DeclarationListPrime();
    }
}

void Parser::DeclarationListPrime() {
    DeclarationList();
}

void Parser::Declaration() {
    printf("\t<Declaration> ::= <Qualifier> <IDs>\n");
    Qualifier();
    IDs();
}


void Parser::IDs() {
    printf("\t<IDs> ::= <Identifier> <IDs Prime>\n");
    if (token == IDENT) {
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        IDsPrime();
    }
}

void Parser::IDsPrime() {
    if (token == COMMA) {
        printf("\t<IDs> ::= , <IDs>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        IDs();
    } else {
        printf("\t<IDs> ::= , ɛ\n");
    }
}


void Parser::StatementList() {
    printf("\t<Statement List> ::= <Statement><Statement List Prime>\n");
    token = nonComment();
    Statement();
    StatementListPrime();
}

void Parser::StatementListPrime() {
    string lexeme = lex.getLexeme();
    if (token == RIGHT_BLOCK || token == SEMICOLON || lexeme == "endif") {
        printf("\t<Statement List Prime> ::= <Statement List>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        StatementList();
    }else {
        printf("\t<Statement List Prime> ::= ɛ\n");
    }
}

void Parser::Statement() {
    token = nonComment();
    string lexeme = lex.getLexeme();
    if (lexeme == "return") {
        printf("\t<Statement> ::= <Return>\n");
        token = lex.lexer();
        Return();
    } else if (lexeme == "if") {
        printf("\t<Statement> ::= <If>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        If();
    } else if (lexeme == "get") {
        printf("\t<Statement> ::= <Scan>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Scan();
    } else if (lexeme == "put") {
        printf("\t<Statement> ::= <Print>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Print();
    } else if (lexeme == "while") {
        printf("\t<Statement> ::= <While>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        While();
    } else if (token == LEFT_CURLY_BRACE){
        printf("\t<Statement> ::= <Compound>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Compound();
    } else if (token == IDENT) {
        printf("\t<Statement> ::= <Assign>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Assign();
    }
}

void Parser::Compound() {
    printf("\t<Compound> ::= { <Statement List> }\n");
    StatementList();
    if (token != RIGHT_CURLY_BRACE) {
        printf("ERROR*---* No Right Curly Brace found\n");
    }
    
}

void Parser::Assign() {
    printf("\t<Assign> ::=  <Identifier> = <Expression> ;\n");
    if (token == EQ_OP) {
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Expression();
    }
}

void Parser::If() {
    printf("\t<If> ::= if ( <Condition> ) <Statement> endif | if  ( <Condition> ) <Statement> else <Statement> endif\n");
    if (token == LEFT_PAREN) {
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Condition();
        if (token == RIGHT_PAREN) {
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            Statement();
        }// right block
    }
}


void Parser::Return() {
    if( token == SEMICOLON ) {
        printf("\t<Return> ::= return ;\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
    } else {
        printf("\t<Return> ::= return <Expression> ;\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Expression();
    }
}


void Parser::Print() {
    if( token == LEFT_PAREN ) {
        printf("\t<Print> ::= put ( <Expression>);\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Expression();
        if (token == RIGHT_PAREN) {
            token = lex.lexer();
            printToken(token, lex.getLexeme());
        }
    }
}

void Parser::Scan() {
    if( token == LEFT_PAREN ) {
        printf("\t<Scan> ::= get ( <IDs> );\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        IDs();
        if (token == RIGHT_PAREN) {
            token = lex.lexer();
            printToken(token, lex.getLexeme());
        }
    }
}

void Parser::While() {
    printf("\t<While> ::= while ( <Condition> ) <Statement> \n");
    if( token == LEFT_PAREN ) {
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Condition();
        if (token == RIGHT_PAREN) {
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            Statement();
        }
    }
    
}

void Parser::Condition() {
    printf("\t<Condition> ::= <Expression> <Relop> <Expression>\n");
    Expression();
    Relop();
    Expression();
}


void Parser::Relop() {
    switch (token) {
        case EQ_EQ_OP: {
            printf("\t<Relop> ::= ==\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case EQ_OP: {
            printf("\t<Relop> ::= =\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case GT_OP: {
            printf("\t<Relop> ::= >\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case LT_OP: {
            printf("\t<Relop> ::= <\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case EQ_GT_OP: {
            printf("\t<Relop> ::= =>\n");
           token =  lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case EQ_LT_OP: {
            printf("\t<Relop> ::= =<\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        default:
            break;
    }
}

void Parser::Expression() {
    printf("\t<Expression> ::= <Term> <Expression Prime>\n");
    Term();
    ExpressionPrime();
}

void Parser::ExpressionPrime() {
    int eplison = 1;
    string lexeme = lex.getLexeme();
    if ( token == ADD_OP ) {
        printf("\t<Expression Prime> ::= + <Term> <Expression Prime>\n");
        eplison = 0;
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Term();
        ExpressionPrime();
    } else if ( token == SUB_OP ) {
        printf("\t<Expression Prime> ::= - <Term> <Expression Prime>\n");
        eplison = 0;
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        Term();
        ExpressionPrime();
    }
    
    if (eplison == 1) { /*printf("<EpressionPrime> -> null\n");*/ }
}


void Parser::Term() {
    printf("\t<Term> ::= <Factor> <Term Prime>\n");
    Factor();
    TermPrime();
}

void Parser::TermPrime() {
    int eplison = 1;
    if ( token == MULT_OP ) {
        printf("\t<Term Prime> ::= * <Factor> <Term Prime>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        eplison = 0;
        Factor();
        TermPrime();
    } else if ( token == DIV_OP ) {
        printf("\t<Term Prime> ::= / <Factor> <Term Prime>\n");
        token = lex.lexer();
        printToken(token, lex.getLexeme());
        eplison = 0;
        Factor();
        TermPrime();
    }
    
    if (eplison == 1) { printf("\t<Term Prime> ::= ɛ\n"); }
}

void Parser::Factor() {
    printf("\t<Factor> ::=  - <Primary> | <Primary>\n");
    if ( token == SUB_OP ) {
        printf("\t<Factor> ::=  - <Primary>\n");
        Primary();
    } else {
        printf("\t<Factor> ::= <Primary>\n");
        Primary();
    }
}

void Parser::Primary() {
    printf("\t<Primary> ::= <Identifier> | <Integer> | <Identifier> ( <IDs> ) | ( <Expression> ) | <Real> | true | false\n");
    switch (token) {
        case IDENT: {
            printf("\t<Primary> ::= <Identifier>\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            if( token == LEFT_PAREN ) {
                printf("\t<Primary> ::= <Identifier> ( <IDs> )\n");
                token = lex.lexer();
                printToken(token, lex.getLexeme());
                IDs();
                if (token == RIGHT_PAREN) {
                    token = lex.lexer();
                    printToken(token, lex.getLexeme());
                }
            }
            break;
        }
        case INT_LIT: {
            printf("\t<Primary> ::= <Integer>\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case LEFT_PAREN: {
            printf("\t<Primary> ::= ( <Expression> )\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            Expression();
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case REAL_LIT: {
            printf("\t<Primary> ::= <Real>\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case TRUE_OP: {
            printf("\t<Primary> ::= true\n");
            token =  lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        case FALSE_OP: {
            printf("\t<Primary> ::= false\n");
            token = lex.lexer();
            printToken(token, lex.getLexeme());
            break;
        }
        default:
            break;
    }
}

void Parser::Empty() {
    printf("<Empty> ::= ɛ\n");
}
