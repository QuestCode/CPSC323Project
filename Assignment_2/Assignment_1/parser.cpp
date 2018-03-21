#include "parser.h"

Parser::Parser() {
    lex.lexer();
    RAT18S();
}

void Parser::RAT18S() {
    OptFunctionDefinitions();
    int lexer = lex.lexer();
    if (lexer == lex.PERCENT_OP) {
        OptDeclarationList();
        StatementList();
    }
}

void Parser::OptFunctionDefinitions() {
    FunctionDefinitions();
}

void Parser::FunctionDefinitions() {
    Function();
}

void Parser::Empty() {

}

void Parser::Function() {
    if (lex.getLexeme() == "function") {
        int lexer = lex.lexer();
        if (lexer == lex.LEFT_BLOCK) {
            OptParameterList();
            int lexer = lex.lexer();
            if (lexer == lex.RIGHT_BLOCK) {
                OptDeclarationList();
                Body();
            }
        }
    }
}// END Function

void Parser::ParameterList() {
    Parameter();
    int lexer = lex.lexer();
    if (lexer == lex.COMMA_OP) {
        Parameter();
        ParameterList();
    }
}


void Parser::Parameter() {
    int lexer = lex.lexer();
    if (lexer == lex.IDENT) {
      int lexer = lex.lexer();
      if (lexer = lex.COLON_OP) {
        Qualifier();
      } else {
        printf("No Colon found\n");
      }
    } else {
      printf("No Identifier found\n");
    }
}

void Parser::Qualifier() {
    int lexeme = lex.getLexeme();
    if (lexeme == "int" || lexeme == "real" || lexeme == "boolean") {

    } else {
      printf("No Qualifier found\n");
    }
}

void Parser::Body() {
    int lexer = lex.lexer();
    if (lexer == lex.LEFT_CURLY_BRACE) {
        StatementList();
        int lexer = lex.lexer();
        if (lexer != lex.RIGHT_CURLY_BRACE) {
            printf("No Right Curly Brace found\n");
        }
    } else {
      printf("No Left Curly Brace found\n");
    }
}

void Parser::StatementList() {
    Statement();
}
