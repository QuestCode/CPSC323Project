#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>
#include "Token.cpp"
#include "Character.cpp"

#ifndef LEXER_H
#define LEXER_H
class Lexer {
  private:
    Character characterClass;
    char lexeme[300];
    char nextCharacter;
    int lexemeLength;
    FILE *in_fp, *fopen();
    void addCharacter();
    void getCharacter();
    void getNonBlank();
    void printResult(Token token);
    Token lookup(char ch);
    Token nextToken;

  public:
    Lexer();

    Token lexer();
    void checkFile();
    char* getLexeme();

};
#endif
