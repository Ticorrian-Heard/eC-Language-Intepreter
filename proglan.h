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
	struct Lexeme *(*fval)(struct Lexeme *); 
	struct Lexeme **aval;
	struct Lexeme *left;
	struct Lexeme *right;
	int arrsize;
	FILE *file;
} lexeme;

//globals
extern lexeme *CurrentLexeme;
static FILE *fp;
extern int countCL;
extern char *argsCL[];

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
lexeme* decrement();
lexeme* increment();
lexeme* body();
lexeme* ifstatement();
lexeme* elsestatement();
lexeme* whileloop();
lexeme* forloop();
lexeme* returnstatement();
lexeme* item();
lexeme* unary();
lexeme* function();
lexeme* lambda();
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
void printArgs(lexeme *);

//evaluator defs
lexeme *eval(lexeme *, lexeme *);
lexeme *evalPlus(lexeme *, lexeme *);
lexeme *evalMinus(lexeme *, lexeme *);
lexeme *evalTimes(lexeme *, lexeme *);
lexeme *evalDiv(lexeme *, lexeme *);
lexeme *evalMod(lexeme *, lexeme *);
lexeme *evalSPlus(lexeme *, lexeme *);
lexeme *evalSMinus(lexeme *, lexeme *);
lexeme *evalSTimes(lexeme *, lexeme *);
lexeme *evalSDiv(lexeme *, lexeme *);
lexeme *evalInc(lexeme *, lexeme *);
lexeme *evalDec(lexeme *, lexeme *);
lexeme *evalBoolean(lexeme *, lexeme *);
//lexeme *evalNew(lexeme *, lexeme *);
lexeme *evalVarDef(lexeme *, lexeme *);
lexeme *evalAssign(lexeme *, lexeme *);
lexeme *evalReturn(lexeme *, lexeme *);
lexeme *evalBody(lexeme *, lexeme *);
lexeme *evalHeader(lexeme *, lexeme *);
lexeme *evalDefine(lexeme *, lexeme *);
lexeme *evalObject(lexeme *, lexeme *);
lexeme *evalFuncDef(lexeme *, lexeme *);
lexeme *evalFuncCall(lexeme *, lexeme *);
lexeme *evalNewFile(lexeme *, lexeme *);
lexeme *evalIfStatement(lexeme *, lexeme *);
lexeme *evalElseStatement(lexeme *, lexeme *);
lexeme *evalWhileLoop(lexeme *, lexeme *);
lexeme *evalLambda(lexeme *, lexeme *);

//built in functions
lexeme *evalPrintln(lexeme *);
lexeme *evalPrint(lexeme *);
lexeme *evalNewArray(lexeme *, lexeme *);
lexeme *evalGetArray(lexeme *, lexeme *);
lexeme *evalSetArray(lexeme *, lexeme *, lexeme *);
lexeme *evalSetINITArray(lexeme *, lexeme *, lexeme *, lexeme *);
lexeme *evalOpenFileForReading(lexeme *);
lexeme *evalReadInteger(lexeme *);
lexeme *evalReadReal(lexeme *);
lexeme *evalReadLine(lexeme *);
lexeme *evalReadString(lexeme *);
lexeme *evalatEOF(lexeme *);
lexeme *evalCloseFile(lexeme *);
lexeme *evalGetArgCount(lexeme *);
lexeme *evalGetArg(lexeme *);
lexeme *GetArraySize(lexeme *);

//utilities
lexeme *skipElse(lexeme *);
char *addString(char *, char *);
int checkCond(lexeme *, lexeme *);
int compare(lexeme *, lexeme *, lexeme *);
void addBuiltins(lexeme *);
char *readLine(FILE *);
char *readString(FILE *);
int readInt(FILE *);
double readReal(FILE *);
int getArraySize(lexeme *,int);
lexeme *getVar(lexeme *);
lexeme *getThis(lexeme *, lexeme *);
lexeme *getFuncCallArgs(lexeme *);
lexeme *getClosureParams(lexeme *);
lexeme *getClosureBody(lexeme *);
lexeme *getClosureEnv(lexeme *);
lexeme *evalArgs(lexeme *, lexeme *);
