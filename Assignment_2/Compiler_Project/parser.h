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
    void RAT18S();                    // Function 1
    void OptFunctionDefinitions();    // Function 2
    void OptDeclarationList();        // Function 3
    void StatementList();             // Function 4
    void FunctionDefinitions();       // Function 5
    void Empty();                     // Function 6
    void Function();                  // Function 7
    void Identifier();                // Function 8
    void OptParameterList();          // Function 9
    void Body();                      // Function 10
    void ParameterList();             // Function 11
    void Parameter();                 // Function 12
    void IDs();                       // Function 13
    void Qualifier();                 // Function 14
    void DeclarationList();           // Function 15
    void Declaration();               // Function 16
    void Statement();                 // Function 17
    void Compound();                  // Function 18
    void Assign();                    // Function 19
    void If();                        // Function 20
    void Return();                    // Function 21
    void Print();                     // Function 22
    void Scan();                      // Function 23
    void While();                     // Function 24
    void Condition();                 // Function 25
    void Relop();                     // Function 26
    void Expression();                // Function 27
    void ExpressionPrime();           // Function 28
    void Term();                      // Function 29
    void TermPrime();                 // Function 30
    void Factor();                    // Function 31
    void Primary();                   // Function 32
    void Integer();                   // Function 33
    void Real();                      // Function 34
    
};
#endif
