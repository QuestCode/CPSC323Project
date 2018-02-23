#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>

#ifndef LEXER_H
#define LEXER_H
class Lexer {
  private:
    int characterClass;
    char lexeme[100];
    char nextCharacter;
    int lexemeLength;
    int token;
    int nextToken;
    FILE *in_fp, *fopen();
    void addCharacter();
    void getCharacter();
    void getNonBlank();
    int lookup(char ch);
    void printResult(int token);
    int lexer();

    /* Identifiers Token codes */
    #define INIT 01
    #define LETTER 02
    #define DIGIT 03
    #define DOLLAR_SIGN 04

    /* Character classes */
    #define UNKNOWN 99

    /* Real or Integer Token codes */
    #define PERIOD 07

    #define IDENT 10
    #define INT_LIT 11
    #define REAL_LIT 12
    #define KEYWORD 13

    /* Operator Token codes */
    #define ASSIGN_OP 20
    #define ADD_OP 21
    #define SUB_OP 22
    #define MULT_OP 23
    #define DIV_OP 24
    #define EQ_OP 25
    #define LT_OP 26
    #define GT_OP 27
    #define COM_OP 28
    #define LEFT_PAREN 30
    #define RIGHT_PAREN 31
    #define LEFT_BLOCK 32
    #define RIGHT_BLOCK 33

  public:
    void checkFile();

};
#endif
