#include "Parser.h"
#include <string> // std::string, std::to_string

int main() {
    
    Lexer lex;
    Parser parse;
    vector<Token> tokens;
    string current = "";
    string infilepath;
    string outfilepath;
    int numberOfFiles = 3;
    int lineNumber = 0;
    
    
    // loop through input files and create outputfiles
    for(int i = 1;i <= numberOfFiles;++i) {
        string inputFile = "inputfile"+ to_string(i) + ".txt";
        string outputFile = "outputfile"+ to_string(i) + ".txt";
        fin.open(inputFile);
        lastfout.open(outputFile);

        if (!fin) {
            cout << "Error. Unable to read file." << endl;
            return -1;
        }
        
        while (getline(fin, current)) {
            
            lineNumber++;
            tokens = lex.lexical(current, lineNumber);
            for (int i = 0; i < tokens.size(); i++) {
                tokens[i].linenum = lineNumber;
            }
            
            tokenList.insert(tokenList.end(), tokens.begin(), tokens.end());
            tokens.clear();
        }
        
        fin.close();
        parse.Rat18S();
        printST();
        lastfout << "\n\n";
        printIT();
        lastfout.close();
        SymbolTable.clear();
        InstructionTable.clear();
        memory_address = 2000; // Global starting address variable
        stdinflag = false;
        cout << "Completed " + inputFile +"\n";
    }
    
    
    
    
   
    
    
    return 0;
}
