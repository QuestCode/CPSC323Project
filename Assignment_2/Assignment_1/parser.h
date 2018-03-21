#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include "lexer.cpp"

#ifndef PARSER_H
#define PARSER_H
class Parser {
public:
  Parser();
private:
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
  void OptDeclarationList();        // Function 10
  void Body();                      // Function 11
  void ParameterList();             // Function 12
  void Parameter();                 // Function 13
  void IDs();                       // Function 14
  void Qualifier();                 // Function 15
  void DeclarationList();           // Function 16
  void Declaration();               // Function 17
  void Statement();                 // Function 18
  void Compound();                  // Function 19
  void Assign();                    // Function 20
  void If();                        // Function 21
  void Return();                    // Function 22
  void Print();                     // Function 23
  void Scan();                      // Function 24
  void While();                     // Function 25
  void Condition();                 // Function 26
  void Relop();                     // Function 27
  void Expression();                // Function 28
  void ExpressionPrime();           // Function 29
  void Term();                      // Function 30
  void TermPrime();                 // Function 31
  void Factor();                    // Function 32
  void Primary();                   // Function 33
  void Integer();                   // Function 34
  void Real();                      // Function 35
}
#endif
