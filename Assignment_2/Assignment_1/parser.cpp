#include "parser.h"

Parser::Parser() {
    lex.lexer();
    RAT18S();
}

void Parser::RAT18S() {
    OptFunctionDefinitions();
    if (lex.lexer() == PERCENT_OP) {
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

}
