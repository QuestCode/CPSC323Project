#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>

#ifndef PARSER_H
#define PARSER_H
class Parser {
  void RAT18S();
  void OptFunctionDefinitions();
  void OptDeclarationList();
  void StatementList();
  void FunctionDefinitions();
  void Empty();
  void Function();
  void Identifier();
  void OptParameterList();
  void OptDeclarationList();
  void Body();
  void ParameterList();
  void Parameter();
  void IDs();
  void Qualifier();
  void DeclarationList();
  void Declaration();
  void Statement();
  void Compound();
  void Assign();
  void If();
  void Return();
  void Print();
  void Scan();
  void While();
  void Condition();
  void Relop();
  void Expression();
  void ExpressionPrime();
  void Term();
  void TermPrime();
  void Factor();
  void Primary();
  void Integer();
  void Real();
}
#endif
