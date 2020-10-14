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

lexeme *lex(FILE*);
lexeme *new_Lexeme();
lexeme *new_p_Lexeme(char *);

