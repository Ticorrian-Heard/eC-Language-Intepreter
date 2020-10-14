#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Lexeme {
	const char *type;
	char *string;
	int number;
	double dub;
	int lineNumber;
	struct Lexeme *left;
	struct Lexeme *right;
} lexeme;

//global lexeme for reading 
extern lexeme *CurrentLexeme;
static FILE *fp;

lexeme *lex(FILE*);
lexeme *new_Lexeme();
lexeme *new_p_Lexeme(char *);


//function definitions
lexeme* program();
lexeme* functionDefAndVarDef();
lexeme* headersandDefs();
lexeme* variable();
lexeme* parameter();
lexeme* list();
lexeme* assignment();
lexeme* ifexpression();
lexeme* condexpression();
lexeme* expression();
lexeme* optexpressionlist();
lexeme* operator();
lexeme* conditional();
lexeme* body();
lexeme* ifstatement();
lexeme* elsestatement();
lexeme* whileloop();
lexeme* forloop();
lexeme* returnstatement();
lexeme* item();
lexeme* unary();
lexeme* function();
lexeme* structure();
lexeme* unionstructure();
lexeme* file();
lexeme *parser(char *);

int conditionalPending();
int variablePending();
int itemPending();
int unaryPending();
int operatorPending();
int assignmentPending();

int check(char *);
lexeme* advance();
void matchNoAdvance(char *);
lexeme* match(char *);

//environment defs
lexeme *cons(char *, lexeme *, lexeme *);
void setcar(lexeme *, lexeme *);
void print(lexeme *,lexeme *);
void printupdate(lexeme *, lexeme *);
void display(lexeme *);
lexeme *car(lexeme *);
lexeme *cdr(lexeme *);
void resetVal(lexeme *, lexeme *);
int sameVar(char *, lexeme *);
int sameType(lexeme *, lexeme *);
lexeme *create();
lexeme *lookup(lexeme *, lexeme *);
lexeme *update(lexeme *, lexeme *, lexeme *);
lexeme *insert(lexeme *, lexeme *, lexeme *);
lexeme *extend(lexeme *, lexeme *, lexeme *);

//pretty printer defs
lexeme *prettyPrinter(lexeme *);