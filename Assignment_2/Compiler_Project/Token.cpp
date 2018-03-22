//
//  Token.cpp
//  Compiler_Project
//
//  Created by Devontae Reid on 3/21/18.
//  Copyright © 2018 Devontae Reid. All rights reserved.
//

enum Token {
    /* Identifiers Token codes */
    IDENT,INT_LIT,REAL_LIT,KEYWORD,BOOLEAN_LIT,
    ADD_OP,SUB_OP,MULT_OP,DIV_OP,EQ_OP,
    LT_OP,GT_OP,UP_EQ_OP,EQ_LT_OP,EQ_GT_OP,EQ_EQ_OP,
    TRUE_OP, FALSE_OP,
    
    /* Separators  Token codes */
    COLON,COM,SEMICOLON,LEFT_PAREN,RIGHT_PAREN,COMMA,
    LEFT_BLOCK,RIGHT_BLOCK,LEFT_CURLY_BRACE,RIGHT_CURLY_BRACE,
    PERCENT,END_OF_FILE
};
