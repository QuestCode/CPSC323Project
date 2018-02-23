#include "lexer.h"

void Lexer::checkFile() {
  if ((in_fp = std::fopen("sample.RAT18S", "r")) == NULL)
	printf("ERROR - cannot open sample.RAT18S \n");
	else {
	   getCharacter();
    	do {
    	   lexer();
    	} while (nextToken != EOF);
	}
}

void Lexer::addCharacter() {
  if (lexemeLength <= 98) {
    lexeme[lexemeLength++] = nextCharacter;
    lexeme[lexemeLength] = 0;
  }
  else
    printf("Error - lexeme is too long \n");
}

void Lexer::getCharacter() {
  if ((nextCharacter = getc(in_fp)) != EOF) {
    if (isalpha(nextCharacter))
      characterClass = LETTER;
    else if (isdigit(nextCharacter))
      characterClass = DIGIT;
		else if (nextCharacter == '$')
			characterClass = DOLLAR_SIGN;
		else if (nextCharacter == '.')
			characterClass = PERIOD;
    else characterClass = UNKNOWN;
  } else {
      characterClass = EOF;
  }
}

void Lexer::getNonBlank() {
  while(isspace(nextCharacter))
    getCharacter();
}

int Lexer::lexer() {
  lexemeLength = 0;
  getNonBlank();
  switch (characterClass) {
    /* Parse identifiers */
    case LETTER:
      addCharacter();
      getCharacter();

			if (!isspace(nextCharacter)) {
				while (characterClass == LETTER || characterClass == DIGIT) {
	          addCharacter();
	          getCharacter();
	      }

				if (characterClass == LETTER || characterClass == DOLLAR_SIGN) {
						addCharacter();
						getCharacter();
				}
			}

      nextToken = IDENT;
      break;
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
	      }

				nextToken = REAL_LIT;
			} else {
				nextToken = INT_LIT;
			}
      break;
      /* Parentheses and operators */
      case UNKNOWN:
      lookup(nextCharacter);
      getCharacter();
      break;
      /* EOF */
      case EOF:
        nextToken = EOF;
      break;
    } /* End of switch */
    printResult(nextToken);
    return nextToken;
}

int Lexer::lookup(char ch) {
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
		break;
		case '(':
  		addCharacter();
  		nextToken = LEFT_PAREN;
		break;
		case ')':
  		addCharacter();
  		nextToken = RIGHT_PAREN;
		break;
    case '<':
  		addCharacter();
  		nextToken = LT_OP;
		break;
    case '>':
  		addCharacter();
  		nextToken = GT_OP;
		break;
    case '!':
  		addCharacter();
  		nextToken = COM_OP;
		break;
		default:
			nextToken = EOF;
		break;
	}
	return nextToken;
}

void Lexer::printResult(int token) {
  std::string id[6] = {"identifier","keyword", "integer", "real","separator","operator"};
  std::string keywords[] = {"int","if","else","endif","while","return","get","put"};

  switch (token) {
    case IDENT:
      for (auto key: keywords) {
          if (key == lexeme) {
            nextToken = KEYWORD;
          }
      }

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
    case LEFT_BLOCK:
    case LEFT_PAREN:
    case RIGHT_BLOCK:
    case RIGHT_PAREN:
      printf("%s\t%s\n", id[4].c_str(),lexeme);
    break;
    case EOF:
    break;
    default:
      /* operators tokens code */
      printf("%s\t%s\n", id[5].c_str(),lexeme);
    break;
  }
}
