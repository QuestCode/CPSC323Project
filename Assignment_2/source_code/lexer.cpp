#include "lexer.h"

Lexer::Lexer() {
    if ((in_fp = std::fopen("sample.RAT18S", "r")) == NULL)
        printf("ERROR - cannot open sample.RAT18S \n");
}
void Lexer::checkFile() {
  if (in_fp == NULL)
	printf("ERROR - cannot open sample.RAT18S \n");
	else {
            getCharacter();
    	do {
    	   lexer();
    	} while (nextToken != END_OF_FILE);
	}
}

void Lexer::addCharacter() {
  if (lexemeLength <= 300) {
    lexeme[lexemeLength++] = nextCharacter;
    lexeme[lexemeLength] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}

void Lexer::getCharacter() {
  if ((nextCharacter = getc(in_fp)) != EOF) {
    if (isalpha(nextCharacter))
        characterClass = Character::LETTER;
    else if (isdigit(nextCharacter))
      characterClass = Character::DIGIT;
		else if (nextCharacter == '$')
			characterClass = Character::DOLLAR_SIGN;
		else if (nextCharacter == '.')
			characterClass = Character::PERIOD;
    else if (nextCharacter == '!')
  			characterClass = Character::COMMENT;
    else characterClass = Character::UNKNOWN;
  } else {
      characterClass = Character::E_O_F;
  }
}

void Lexer::getNonBlank() {
  while(isspace(nextCharacter))
    getCharacter();
}

Token Lexer::lexer() {
  lexemeLength = 0;
  getNonBlank();
  switch (characterClass) {
    /* Parse identifiers */
      case LETTER: {
          addCharacter();
          getCharacter();

          if (!isspace(nextCharacter)) {
              while (characterClass == LETTER || characterClass == DIGIT) {
                  addCharacter();
                  getCharacter();
                // Check if next character is either a digit or letter
                if (characterClass == LETTER) {
                    nextToken = Token::IDENT;
                } else if (characterClass == DIGIT) {
                    nextToken = Token::IDENT;
                }
          }

              if (characterClass == LETTER || characterClass == DOLLAR_SIGN) {
                    addCharacter();
                    getCharacter();
                    nextToken = Token::IDENT;
              }
          } else { nextToken = Token::IDENT; }
          
          std::string lexString = lexeme;
          
          if (lexString == "true") {
              nextToken = TRUE_OP;
          } else if (lexString == "false") {
              nextToken = FALSE_OP;
          }
          
          // Check if there is a keyword match
          std::string keywords[] = {"if","else","endif","while","return","get","put","function","int","boolean","real"};
          
          for (auto key: keywords) {
              if (key == lexeme) {
                  nextToken = KEYWORD;
              }
          }

      break;
      }
    /* Parse integer literals */
    case DIGIT:
      addCharacter();
      getCharacter();
      while (characterClass == DIGIT) {
        addCharacter();
        getCharacter();
      }

        if (characterClass == PERIOD) {
            addCharacter();
            getCharacter();
            while (characterClass == DIGIT) {
                addCharacter();
                getCharacter();
                nextToken = Token::REAL_LIT;
            }
        } else { nextToken = Token::INT_LIT; }
      break;
      case DOLLAR_SIGN:
          break;
      case PERIOD:
          break;
      case COMMENT:
          addCharacter();
          getCharacter();
          
          while (characterClass != COMMENT) {
              // printf("%c\n", nextCharacter);
              addCharacter();
              getCharacter();
          }
          addCharacter();
          getCharacter();
          nextToken = Token::COM;

      break;
      /* Parentheses and operators */
      case UNKNOWN:
      lookup(nextCharacter);
      getCharacter();
      break;
      /* EOF */
      case E_O_F:
          nextToken = Token::END_OF_FILE;
      break;
    } /* End of switch */
//    printResult(nextToken);
    return nextToken;
}

Token Lexer::lookup(char ch) {
  switch (ch) {
		case '[':
			addCharacter();
			nextToken = LEFT_BLOCK;
		break;
		case ']':
			addCharacter();
			nextToken = RIGHT_BLOCK;
		break;
		case '+':
			addCharacter();
			nextToken = ADD_OP;
		break;
		case '-':
			addCharacter();
			nextToken = SUB_OP;
		break;
		case '*':
			addCharacter();
			nextToken = MULT_OP;
		break;
		case '/':
			addCharacter();
			nextToken = DIV_OP;
		break;
		case '=':
			addCharacter();
			nextToken = EQ_OP;
            getCharacter();
            if (nextCharacter == '=') {
                addCharacter();
                nextToken = EQ_EQ_OP;
            } else if (nextCharacter == '>') {
                addCharacter();
                nextToken = EQ_GT_OP;
            } else if (nextCharacter == '<') {
                addCharacter();
                nextToken = EQ_LT_OP;
            }
		break;
		case '(':
            addCharacter();
            nextToken = LEFT_PAREN;
		break;
		case ')':
            addCharacter();
            nextToken = RIGHT_PAREN;
		break;
      case '^':
          addCharacter();
          nextToken = END_OF_FILE;
          getCharacter();
          if (nextCharacter == '=') {
              addCharacter();
              nextToken = EQ_EQ_OP;
          }
          break;
      case '<':
  		addCharacter();
  		nextToken = LT_OP;
		break;
      case '>':
  		addCharacter();
  		nextToken = GT_OP;
		break;
      case ':':
    		addCharacter();
    		nextToken = COLON;
		  break;
      case ';':
    		addCharacter();
    		nextToken = SEMICOLON;
		  break;
      case '{':
    		addCharacter();
    		nextToken = LEFT_CURLY_BRACE;
		  break;
      case '}':
    		addCharacter();
    		nextToken = RIGHT_CURLY_BRACE;
		  break;
      case '%':
    		addCharacter();
            getCharacter();
            if (nextCharacter == '%') {
              addCharacter();
              nextToken = PERCENT;
            }
		  break;
      case ',':
    		addCharacter();
    		nextToken = COMMA;
		  break;
		default:
			nextToken = END_OF_FILE;
		break;
	}
	return nextToken;
}

void Lexer::printResult(Token token) {
  std::string id[] = {"identifier","keyword", "integer", "real","separator","operator","comment","boolean"};
  std::string keywords[] = {"if","else","endif","while","return","get","put","function","int","boolean","real"};

  switch (token) {
    case IDENT:

      if(nextToken != KEYWORD) {
          printf("%s\t%s\n", id[0].c_str(),lexeme);
      } else {
          printf("%s\t\t%s\n", id[1].c_str(),lexeme);
      }
    break;
    case INT_LIT:
      printf("%s\t\t%s\n", id[2].c_str(),lexeme);
    break;
    case REAL_LIT:
      printf("%s\t\t%s\n", id[3].c_str(),lexeme);
    break;
    case COM:
      printf("%s\t\t%s\n", id[6].c_str(),lexeme);
    break;
    case PERCENT:
    case COMMA:
    case COLON:
    case SEMICOLON:
    case LEFT_BLOCK:
    case LEFT_PAREN:
    case RIGHT_BLOCK:
    case RIGHT_PAREN:
    case LEFT_CURLY_BRACE:
    case RIGHT_CURLY_BRACE:
      printf("%s\t%s\n", id[4].c_str(),lexeme);
    break;
    case ADD_OP:
    case SUB_OP:
    case MULT_OP:
    case DIV_OP:
    case EQ_OP:
    case LT_OP:
    case GT_OP:
    case UP_EQ_OP:
    case EQ_LT_OP:
    case EQ_GT_OP:
    case EQ_EQ_OP:
      /* operators tokens code */
      printf("%s\t%s\n", id[5].c_str(),lexeme);
    break;
    case END_OF_FILE:
    break;
    default:
      printf("UNKNOWN\t\t%s\n",lexeme);
    break;
  }
}

char* Lexer::getLexeme() {
  return lexeme;
}
