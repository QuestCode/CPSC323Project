//
//  Parser.h
//  Compiler
//

#ifndef Parser_h
#define Parser_h

#include <iostream>
#include <iomanip>
#include "lexer.h"
#include "assembly.h"

#define ERROR_FOUND << currentToken.lexeme << "' on line " << currentToken.linenum; exit(1);
#define ADVANCE_AND_PRINT if (tokenCounter < tokenList.size()) { currentToken = tokenList[tokenCounter]; if (printSwitch) { fout << "\nToken: " << left << setw(20) << currentToken.token << left << setw(8) << "Lexeme: " << left << setw(20) << currentToken.lexeme << endl; } tokenCounter++; }

class Parser {
    void OptFuncDef();
    void FuncDef();
    void Func();
    void OptParamList();
    void ParamList();
    void Parameter();
    void Qualifier();
    void Body();
    void OptDecList();
    void DecList();
    void Declaration();
    void IDs();
    void StatementList();
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
    void Empty();
public:
    void Rat18S();
    
};

int tokenCounter = 0;
vector<Token> tokenList;
Token currentToken;
bool printSwitch = true;

int addr = 0;
string symboltype; //for adding symbols to table


void Parser::Rat18S() {
    
    ADVANCE_AND_PRINT
    
    if (printSwitch) {
        fout << "\t<Rat18S> ::= <Opt Function Definitions>\n\t\t\t\t %% <Opt Declaration List> <Statement List> \n";
    }
    
    OptFuncDef();
    
    if (currentToken.lexeme == "%%") {
        ADVANCE_AND_PRINT
        OptDecList();
        StatementList();
        fout << "Finished" << endl;
    }
    else {
        fout << "\nSyntax Error, expecting this %% before '" ERROR_FOUND
    }
}


void Parser::OptFuncDef() {
    
    if (printSwitch) {
        fout << "\t<Opt Function Definition> ::= <Function Definitions> | <Empty>\n";
    }
    
    /*                                      *
     *      FUNCTION DEFINITIONS REMOVE     *
     *                                      */
    
    if (currentToken.lexeme == "%%") {
        Empty();
    }
    else {
        fout << "\nSyntax Error, expecting 'function' or '%%' before '" ERROR_FOUND
    }
    
}

void Parser::FuncDef() {
    
    if (printSwitch) {
        fout << "\t<Function Definitions> ::= <Function> | <Function> <Function Definitions>\n";
    }
    while (currentToken.lexeme == "function") {
        Func();
    }
}

void Parser::Func() {

    if (printSwitch) {
        fout << "\t<Function> ::= function <Identifier> [ <Opt Paramenter List> ] <Opt Declaration List> <fout>\n";
    }
    ADVANCE_AND_PRINT
    
    if (currentToken.token == "Identifier") {
        ADVANCE_AND_PRINT
        if (currentToken.lexeme == "[") {
            ADVANCE_AND_PRINT
            OptParamList();
            if (currentToken.lexeme == "]") {
                ADVANCE_AND_PRINT
                OptDecList();
                Body();
            }
            else {
                fout << "\nSyntax Error, expecting ']' before '" ERROR_FOUND
            }
        }
        else {
            fout << "\nSyntax Error, expecting '[' before '" ERROR_FOUND
        }
    }
    else {
        fout << "\nSyntax Error, expecting <Identifier> before '" ERROR_FOUND
    }
}

void Parser::OptParamList() {
 
    if (printSwitch)
        fout << "\t<Opt Parameter List> ::= <Parameter List> | <Empty>\n";
    
    if (currentToken.token == "Identifier") {
        ParamList();
    }
    else if (currentToken.lexeme == "]") {
        Empty();
    }
    else {
        fout << "\nSyntax Error, expecting <Identifier> before '" ERROR_FOUND
    }
}

void Parser::ParamList() {
  
    if (printSwitch)
        fout << "\t<Parameter List> ::= <Parameter> | <Parameter>, <Parameter List>\n";
    
    
    if (currentToken.token == "Identifier") {
        Parameter();
        if (currentToken.lexeme == ",") {
            ADVANCE_AND_PRINT
            ParamList();
        }
    }
}

void Parser::Parameter() {
    
    if (printSwitch)
        fout << "\t<Parameter> ::= <IDs> : <Qualifier>\n";
    
    IDs();
    if (currentToken.lexeme == ":") {
        ADVANCE_AND_PRINT
        Qualifier();
    }
    else {
        fout << "\nSyntax Error, expecting ':' before '" ERROR_FOUND
    }
}

void Parser::Qualifier() {
    
    /*                                      *
     *          real type REMOVE            *
     *                                      */
    
    if (printSwitch)
        fout << "\t<Qualifier> ::= int | boolean \n";
    
    if (currentToken.lexeme == "int" || currentToken.lexeme == "true"
        || currentToken.lexeme == "false" || currentToken.lexeme == "boolean") {
        symboltype = currentToken.lexeme;
        ADVANCE_AND_PRINT
    } else {
        fout << "\nSyntax Error, expecting 'int' or 'boolean' before '" ERROR_FOUND
    }
}

void Parser::Body() {
    
    if (printSwitch)
        fout << "\t<fout> ::= { <Statement List> }\n";
    
    if (currentToken.lexeme == "{") {
        ADVANCE_AND_PRINT
        StatementList();
        if (currentToken.lexeme == "}") {
            ADVANCE_AND_PRINT
        } else {
            fout << "\nSyntax Error, expecting '}' before '" ERROR_FOUND
        }
    } else {
        fout << "\nSyntax Error, expecting '{' before '" ERROR_FOUND
    }
}

void Parser::OptDecList() {
    
    /*                                      *
     *             real type REMOVE         *
     *                                      */
    
    if (printSwitch) {
        fout << "\t<Opt Declaration List> ::= <Declaration List> | <Empty>\n";
    }
    
    if (currentToken.lexeme == "{") {
        Empty();
    }
    else if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean") {
        DecList();
    }
    else {
        fout << "\nSyntax Error, expecting 'int' or 'boolean' before '" ERROR_FOUND
    }
}

void Parser::DecList() {
    
    /*                                      *
     *             real type REMOVE         *
     *                                      */
    
    if (printSwitch) {
        fout << "\t<Declaration List> ::= <Declaration>; | <Declaration> ; <Declaration List>\n";
    }
    
    Declaration();
    if (currentToken.lexeme == ";") {
        ADVANCE_AND_PRINT
        if (currentToken.lexeme == "int" || currentToken.lexeme == "boolean") {
            DecList();
        }
    }
    else {
        fout << "\nSyntax Error, expecting ';' on line " ERROR_FOUND
    }
}

void Parser::Declaration() {
    
    if (printSwitch)
        fout << "\t<Declaration> ::= <Qualifier> <IDs>\n";
    
    Qualifier();
    IDs();
}

void Parser::IDs() {
    
    if (printSwitch) {
        fout << "\t<IDs> ::= <Identifier> | <Identifier>, <IDs>\n";
    }
    if (currentToken.token == "Identifier") {
        add_symbol(currentToken.lexeme, memory_address, symboltype);
        ADVANCE_AND_PRINT
        if (currentToken.lexeme == ",") {
            ADVANCE_AND_PRINT
            IDs();
        } else if (currentToken.token == "Identifier") {
            fout << "\nSyntax Error, expecting ',' between multiple identifiers on line " << currentToken.linenum;
            exit(1);
        }
    }
    else {
        fout << "\nSyntax Error, expecting <Identifier> before '" ERROR_FOUND
    }
}

void Parser::StatementList() {
    
    if (printSwitch) {
        fout << "\t<Statement List> ::= <Statement> | <Statement> <Statement List>\n";
    }
    while (currentToken.lexeme == "if" || currentToken.lexeme == "return" || currentToken.lexeme == "put"
           || currentToken.lexeme == "get" || currentToken.lexeme == "while" || currentToken.token == "Identifier"
           || currentToken.lexeme == "function") {
        Statement();
    }
}

void Parser::Statement() {
    
    if (printSwitch)
        fout << "\t<Statement> ::= <Compound> | <Assign> | <If> | <Return> | <Print> | <Scan> | <While>\n";
    
    if (currentToken.lexeme == "{")
        Compound();
    else if (currentToken.token == "Identifier")
        Assign();
    else if (currentToken.lexeme == "if")
        If();
    else if (currentToken.lexeme == "return")
        Return();
    else if (currentToken.lexeme == "put")
        Print();
    else if (currentToken.lexeme == "get")
        Scan();
    else if (currentToken.lexeme =="function")
        Func();
    else if (currentToken.lexeme == "while")
        While();
    else {
        fout << "\nSyntax Error, expecting proper '<Statement>' before '" ERROR_FOUND
    }
}

void Parser::Compound() {
    
    if (printSwitch)
        fout << "\t<Compound> ::= {<Statement List>}\n";
    
    if (currentToken.lexeme == "{") {
        ADVANCE_AND_PRINT
        StatementList();
        if (currentToken.lexeme == "}") {
            ADVANCE_AND_PRINT
        }
    }
}

void Parser::Assign() {
    
    if (printSwitch)
        fout << "\t<Assign> ::= <Identifier> = <Expression>;\n";
    
    if (currentToken.token == "Identifier") {
        save = currentToken;
        ADVANCE_AND_PRINT
        if (currentToken.lexeme == "=") {
            ADVANCE_AND_PRINT
            Expression();
            add_instr("POPM", get_address(save));
            if (currentToken.lexeme == ";") {
                ADVANCE_AND_PRINT
            } else {
                fout << "\n<Assign> Syntax Error";
                exit(1);
            }
        } else {
            fout << "\nSyntax Error, expecting '=' before '" ERROR_FOUND
        }
    }
}

void Parser::If() {
    
    if (printSwitch)
        fout << "\t<If> ::= if (<Condition>) <Statement> endif | if (<Condition>) <Statement> else <Statement> endif\n";
    if (currentToken.lexeme == "if") {
        ADVANCE_AND_PRINT
        if (currentToken.lexeme == "(") {
            ADVANCE_AND_PRINT
            Condition();
            if (currentToken.lexeme == ")") {
                ADVANCE_AND_PRINT
                Statement();
                if (currentToken.lexeme == "endif") {
                    ADVANCE_AND_PRINT
                }
                else if (currentToken.lexeme == "else") {
                    ADVANCE_AND_PRINT
                    Statement();
                    if (currentToken.lexeme == "endif") {
                        ADVANCE_AND_PRINT
                    }
                    else {
                        fout << "\nSyntax Error, expecting 'endif' on line " << currentToken.linenum;
                        exit(1);
                    }
                }
                else {
                    fout << "\nSyntax Error, expecting 'endif' or 'else' on line " << currentToken.linenum;
                    exit(1);
                }
            }
            else {
                fout << "\nSyntax Error, expecting ) after <Condition> on line " << currentToken.linenum;
                exit(1);
            }
        }
        else {
            fout << "\nSyntax Error, expecting ( on line " << currentToken.linenum;
            exit(1);
        }
    }
}

void Parser::Return() {
    
    if (printSwitch)
        fout << "\t<Return> ::= return; | return <Expression>;\n";
    
    ADVANCE_AND_PRINT
    if (currentToken.lexeme == ";") {
        ADVANCE_AND_PRINT
    } else {
        Expression();
        if (currentToken.lexeme == ";") {
            ADVANCE_AND_PRINT
        } else {
            fout << "\nSyntax Error, expecting ';' before '" ERROR_FOUND
        }
    }
}

void Parser::Print() {
    
    if (printSwitch)
        fout << "\t<Print> ::= print (<Expressions>);\n";
    
    ADVANCE_AND_PRINT
    if (currentToken.lexeme == "(") {
        ADVANCE_AND_PRINT
        Expression();
        add_instr("STDOUT", -1); // INSTR;
        if (currentToken.lexeme == ")") {
            ADVANCE_AND_PRINT
            if (currentToken.lexeme == ";") {
                ADVANCE_AND_PRINT
            } else {
                fout << "\nSyntax Error, expecting ';' before '" ERROR_FOUND
            }
        } else {
            fout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
        }
    } else {
        fout << "\nSyntax Error, expecting '(' before '" ERROR_FOUND
    }
}

void Parser::Scan() {
    
    if (printSwitch)
        fout << "\t<Scan> ::= get (<IDs>);\n";
    
    ADVANCE_AND_PRINT
    if (currentToken.lexeme == "(") {
        add_instr("STDIN", -1); stdinflag = true; // INSTR
        ADVANCE_AND_PRINT
        IDs();
        if (currentToken.lexeme == ")") {
            ADVANCE_AND_PRINT
            if (currentToken.lexeme == ";") {
                ADVANCE_AND_PRINT
            } else {
                fout << "\nSyntax Error. Expecting ';' before '" ERROR_FOUND
            }
        } else {
            fout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
        }
    } else {
        fout << "\nSyntax Error, expecting '(' before '" ERROR_FOUND
    }
}

void Parser::While() {
    
    if (printSwitch)
    fout << "\t<While> ::= while (<Condition>) <Statement>\n";
    
    addr = InstructionTable.size() + 1;
    add_instr("LABEL", -1);
    
    ADVANCE_AND_PRINT
    if (currentToken.lexeme == "(") {
        ADVANCE_AND_PRINT
        Condition();
        if (currentToken.lexeme == ")") {
            ADVANCE_AND_PRINT
            Statement();
            add_instr("JUMP", addr); // INSTR
            back_patch(); // INSTR
        } else {
            fout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
        }
    } else {
        fout << "\nSyntax Error, expecting '(' before '" ERROR_FOUND
    }
}

void Parser::Condition() {
    
    if (printSwitch)
        fout << "\t<Condition> ::= <Expression> <Relop> <Expression>\n";
    
    Expression();
    Relop();
    Expression();
    
    // CASE op
    if (symboltype == "=") { add_instr("EQU", -1); jumpstack.push(InstructionTable.size() ); add_instr("JUMPZ", -1); }
    else if (symboltype == "^=") { add_instr("NEQ", -1); jumpstack.push(InstructionTable.size() ); add_instr("JUMPZ", -1); }
    else if (symboltype == "<") { add_instr("LES", -1); jumpstack.push(InstructionTable.size() ); add_instr("JUMPZ", -1); }
    else if (symboltype == ">") { add_instr("GRT", -1); jumpstack.push(InstructionTable.size() ); add_instr("JUMPZ", -1); }
    else if (symboltype == "=>") { add_instr("GEQ", -1); jumpstack.push(InstructionTable.size() ); add_instr("JUMPZ", -1); }
    else if (symboltype == "<=") { add_instr("LEQ", -1); jumpstack.push(InstructionTable.size() ); add_instr("JUMPZ", -1); }
    
}

void Parser::Relop() {
    
    if (printSwitch)
        fout << "\t<Relop> ::= == | ^= | > | < | => | =<\n";
    
    if (currentToken.lexeme == "==" || currentToken.lexeme == "^=" || currentToken.lexeme == ">"
        || currentToken.lexeme == "<" || currentToken.lexeme == "=>" || currentToken.lexeme == "=<") {
        symboltype = currentToken.lexeme;
        ADVANCE_AND_PRINT
    }
    else
    {
        fout << "\nSyntax error, expecting valid comparison operator before " ERROR_FOUND
    }
}

void Parser::Expression() {
    
    if (printSwitch)
        fout << "\t<Expression> ::= <Term> <Expression Prime>\n";
    
    Term();
    ExpressionPrime();
}

void Parser::ExpressionPrime() {
   
    if (printSwitch)
        fout << "\t<Expression Prime> ::= + <Term> <Expression Prime> | - <Term> <Expression Prime> | <Empty>\n";
    
    if (currentToken.lexeme == "+") {
        ADVANCE_AND_PRINT
        Term();
        add_instr("ADD", -1);
        ExpressionPrime();
    } else if (currentToken.lexeme == "-") {
        ADVANCE_AND_PRINT
        Term();
        add_instr("SUB", -1);
        ExpressionPrime();
    } else if (currentToken.token == "Unknown") {
        fout << "\nSyntax error, expecting '+', '-', or nothing before '" ERROR_FOUND
    } else {
        Empty();
    }
}

void Parser::Term() {
    
    if (printSwitch)
        fout << "\t<Term> ::= <Factor> <Term Prime>\n";
    
    Factor();
    TermPrime();
}

void Parser::TermPrime() {
    
    if (printSwitch)
        fout <<  "\t<Term Prime> ::= * <Factor> <Term Prime> | / <Factor> <Term Prime> | <Empty>\n";
    
    if (currentToken.lexeme == "*") {
        ADVANCE_AND_PRINT
        Factor();
        add_instr("MUL", -1);
        TermPrime();
    } else if (currentToken.lexeme == "/") {
        ADVANCE_AND_PRINT
        Factor();
        add_instr("DIV", -1);
        TermPrime();
    } else if (currentToken.token == "Unknown") {
        fout << "\nSyntax Error, expecting '*', '/', or 'Empty' before '" ERROR_FOUND
    } else {
        Empty();
    }
}

void Parser::Factor() {
    
    if (printSwitch)
        fout << "\t<Factor> ::= - <Primary> | <Primary>\n";
    
    if (currentToken.lexeme == "-") {
        ADVANCE_AND_PRINT
        Primary();
    } else if (currentToken.token != "Unknown") {
        Primary();
    }
    
    else {
        fout << "\nSyntax Error, expecting something different before '" ERROR_FOUND
    }
}

void Parser::Primary() {
    
    /*                                      *
     *             real type REMOVE         *
     *                                      */
    
    if (printSwitch)
        fout << "\t<Primary> ::= <Identifier> | <Integer> | <Identifier> [<IDs>] | (<Expression>) | true | false\n";
    
    if (currentToken.token == "Identifier") {
        add_instr("PUSHM", get_address(currentToken));
        ADVANCE_AND_PRINT
        if (currentToken.lexeme == "[") {
            ADVANCE_AND_PRINT
            IDs();
            if (currentToken.lexeme == "]") {
                ADVANCE_AND_PRINT
            }
            else {
                fout << "\nSyntax Error, expecting ']' before '" ERROR_FOUND
            }
        }
        else {
            // Do nothing
        }
        
    } else if (currentToken.token == "Integer") {
        ADVANCE_AND_PRINT
    } else if (currentToken.lexeme == "(") {
        ADVANCE_AND_PRINT
        Expression();
        if (currentToken.lexeme == ")") {
            ADVANCE_AND_PRINT
        }
        else {
            fout << "\nSyntax Error, expecting ')' before '" ERROR_FOUND
        }
    } else if (currentToken.lexeme == "true") {
        add_instr("PUSHI", 1);
        ADVANCE_AND_PRINT
    } else if (currentToken.lexeme == "false") {
        add_instr("PUSHI", 0);
        ADVANCE_AND_PRINT
    } else {
        fout << "\nSyntax Error, expecting '<Identifer>', '<Qualifier>' or '<Expression>' before '" ERROR_FOUND
    }
}

void Parser::Empty() {
    if (printSwitch)
        fout << "\t<Empty> ::= epsilon\n";
    
}



#endif /* Syntax_h */
