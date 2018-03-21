#include <stdio.h>
#include <iostream>
#include <ctype.h>
#include <string>

#ifndef LEXER_H
#define LEXER_H
class Lexer {
  private:
    int characterClass;
    char lexeme[300];
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

  public:
    /* Identifiers Token codes */
    #define INIT 01
    #define LETTER 02
    #define DIGIT 03
    #define DOLLAR_SIGN 04
    #define COMMENT 05

    /* Character classes */
    #define UNKNOWN 99

    /* Real or Integer Token codes */
    #define PERIOD 07

    #define IDENT 10
    #define INT_LIT 11
    #define REAL_LIT 12
    #define KEYWORD 13
    #define BOOLEAN_LIT 32
    #define COM 14

    /* Operator Token codes */
    #define COMMENT_OP 20
    #define ADD_OP 21
    #define SUB_OP 22
    #define MULT_OP 23
    #define DIV_OP 24
    #define EQ_OP 25
    #define LT_OP 26
    #define GT_OP 27
    #define COLON_OP 28
    #define SEMICOLON_OP 29
    #define UP_EQ_OP 30
    #define EQ_LT_OP 31
    #define EQ_GT_OP 32
    #define EQ_EQ_OP 33

    #define LEFT_PAREN 40
    #define RIGHT_PAREN 41
    #define LEFT_BLOCK 42
    #define RIGHT_BLOCK 43
    #define LEFT_CURLY_BRACE 44
    #define RIGHT_CURLY_BRACE 45
    #define PERCENT_OP 46
    #define COMMA_OP 47


    int lexer();
    void checkFile();
    char* getLexeme();

};
#endif
