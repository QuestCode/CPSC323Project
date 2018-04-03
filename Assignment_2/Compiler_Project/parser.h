#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include "lexer.h"

#ifndef PARSER_H
#define PARSER_H
class Parser {
    
public:
  Parser();
    
    
private:
    Token token;
    Lexer lex;
    
    Token nonComment();
    void printToken(Token token,std::string);
    
    void RAT18S();                    // Function 1
    void OptFunctionDefinitions();    // Function 2
    void FunctionDefinitions();       // Function 3
    void FunctionDefinitionsPrime();  // Function 4         Prime
    void Function();                  // Function 5
    void OptParameterList();          // Function 6
    void ParameterList();             // Function 7
    void ParameterListPrime();        // Function 8         Prime
    void Parameter();                 // Function 9
    void Qualifier();                 // Function 10
    void Body();                      // Function 11
    void OptDeclarationList();        // Function 12
    void DeclarationList();           // Function 13
    void DeclarationListPrime();      // Function 14         Prime
    void Declaration();               // Function 15
    void IDs();                       // Function 16
    void IDsPrime();                  // Function 17         Prime
    void StatementList();             // Function 18
    void StatementListPrime();        // Function 19         Prime
    void Statement();                 // Function 20
    void Compound();                  // Function 21
    void Assign();                    // Function 22
    void If();                        // Function 23
    void Return();                    // Function 24
    void Print();                     // Function 25
    void Scan();                      // Function 26
    void While();                     // Function 27
    void Condition();                 // Function 28
    void Relop();                     // Function 29
    void Expression();                // Function 30
    void ExpressionPrime();           // Function 31         Prime
    void Term();                      // Function 32
    void TermPrime();                 // Function 33         Prime
    void Factor();                    // Function 34
    void Primary();                   // Function 35
    void Empty();                     // Function 36
};
#endif
