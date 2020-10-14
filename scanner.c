/*
Ticorrian L. Heard
Lusth CS403
Module 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"

#define true 1
#define false 0

char pushBackChar = '\0';
int charPushed = false;
int lineNumber = 1;

//default constructor for lex struct
lexeme *new_Lexeme()
{
	lexeme *lex = (lexeme*)malloc(sizeof(lexeme));
	lex->type = "";
	lex->string = "";
	lex->number = 0;
	lex->dub = 0.0;
	lex->lineNumber = 0;
	lex->left = NULL;
	lex->right = NULL;
	return lex;
}
//paramaterized constructor for lex struct
lexeme *new_p_Lexeme(char *type)
{
	lexeme *lex = (lexeme*)malloc(sizeof(lexeme));
	lex->type = type;
	lex->string = "";
	lex->number = 0;
	lex->dub = 0.0;
	lex->lineNumber = 0;
	lex->left = NULL;
	lex->right = NULL;
	return lex;
}

//utility for lex
char myRead(FILE *fp) 
{
	if (charPushed == true) {
		charPushed = false;
		return pushBackChar;
	}
	else {
		char ch;
		if (fscanf(fp,"%c",&ch) == EOF) return '\0';
		if (ch == '\n') { lineNumber++; return ch; }
		else return ch; 
	}
}

//utility for lex
void pushBack(char ch)
{
	if (charPushed == true) {
		printf("too many pushbacks!");
		exit(EXIT_FAILURE);
	}
	charPushed = true;
	pushBackChar = ch;
}
void clear_pushBackChar()
{
	pushBackChar = '\0';
	charPushed =false;
}

//utility for lex
void skipWhiteSpace(FILE *fp)
{
	char ch = myRead(fp);
	while (isspace(ch)) {
		ch = myRead(fp);
	}
 	pushBack(ch); //push char that got us out of loop
}

//skips comments duh
int skipComment(FILE *fp)
{
	char c = pushBackChar;
	clear_pushBackChar();
	char ch = myRead(fp);

	if ( (c == '/' && ch != '/') && (c == '/' && ch != '*') ) { 
		pushBack(ch);
		return 0;
	}

	if (c == '/' && ch == '/') {
		while(ch != '\n') {
			ch = myRead(fp);
		}
		clear_pushBackChar();
	}

	else if (c == '/' && ch == '*') { 
			char ch_prev = c;
			while ( true ) { 
				ch_prev = ch;
				ch = myRead(fp);
				if (ch_prev == '*' && ch == '/') break;
			}
			clear_pushBackChar();
	}
	return 1;
}
//utility for strcat function
void increase_size(char **string)
{
	//printf("%lu\n", sizeof(*string));
	char *temp = realloc(*string, 2*sizeof(char));
	if (temp) { 
		*string = temp;
	} else {
		printf("Allocation problem when trying to use realloc");
	}	
}

lexeme *lexNumber(FILE *fp) //write code to account for doubles
{
	lexeme *lex = new_Lexeme();
	char *string = malloc(sizeof(char));
	
	//create string for 2nd arg in strcat
	char ch[2]; 
	ch[0] = myRead(fp);
	ch[1] = '\0';  //null terminator required by strcat
	
	//builds integer string to store in lexeme
	while ( isdigit(ch[0]) || ch[0] == '.') {
		
		if (ch[0] == '.') lex->type = "REAL"; //check for REAL
		
		strcat(string, ch);
		increase_size(&string);
		ch[0] = myRead(fp);
	}

	pushBack(ch[0]);//save character that got us out of loop for next scan

	//return the real number
	if (strcmp(lex->type, "REAL") == 0) {
		lex->dub = atof(string);
		return lex;
	}

	lex->type = "INTEGER";
	lex->number = atoi(string);
	return lex;
}

lexeme *lexVarOrKey(FILE *fp) //problem here
{
	lexeme *lex = new_Lexeme();
	char *string =  malloc(sizeof(char)); //problem here 

	char ch[2];
	ch[0] = myRead(fp);
	ch[1] = '\0';
	
	//build string value for lex 
	while ( isalpha(ch[0]) || isdigit(ch[0]) || ch[0] == '&') {
		strcat(string, ch);
		increase_size(&string);
		ch[0] = myRead(fp);
	}
	
	pushBack(ch[0]); //push back character that got us out of loop
	
	//if lexeme is a keyword
	if (strcmp(string,"var") == 0) {
		lex->type = "VAR";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"if") == 0) {
		lex->type = "IF";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"else") == 0) {
		lex->type = "ELSE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"for") == 0) {
		lex->type = "FOR";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"while") == 0) {
		lex->type = "WHILE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"typedef") == 0) {
		lex->type = "TYPEDEF";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"struct") == 0) {
		lex->type = "STRUCT";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"union") == 0) {
		lex->type = "UNION";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"include") == 0) {
		lex->type = "INCLUDE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"define") == 0) {
		lex->type = "DEFINE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"function") == 0) {
		lex->type = "FUNCTION";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"NULL") == 0) {
		lex->type = "NULL";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"return") == 0) {
		lex->type = "RETURN";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"new") == 0) {
		lex->type = "NEW";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"lambda") == 0) {
		lex->type = "LAMBDA";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"FILE") == 0) {
		lex->type = "FILE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"EOF") == 0) {
		lex->type = "EOF";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"break") == 0) { //ADD THIS
		lex->type = "BREAK";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"continue") == 0) { //ADD THIS
		lex->type = "CONTINUE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"true") == 0) {
		lex->type = "TRUE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (strcmp(string,"false") == 0) {
		lex->type = "FALSE";
		lex->lineNumber = lineNumber;
		return lex;
	}
	//lexeme is a variable type
	else {
		lex->type = "VARIABLE";
		lex->string = string;
		lex->lineNumber = lineNumber;
		return lex;
	}
}	

lexeme *lexString(FILE *fp) 
{
	lexeme *lex = new_Lexeme();
	char *string = malloc(1000*sizeof(char));

	char ch[2];
	char check = myRead(fp);

	ch[0] = myRead(fp);//reads in first double quote
	ch[1] = '\0';

	strcat(string, ch);

	ch[0] = myRead(fp); //reads in first character after double quote
	while (ch[0] != '\"') {
		strcat(string, ch);
		ch[0] = myRead(fp);       //INFINITE LOOP BUG HERE
	}

	lex->type = "STRING";
	lex->string = string;
	lex->lineNumber = lineNumber;
	lex->lineNumber = lineNumber;
	return lex;
}
//--------------------------------------
int shortHandCheck(FILE* fp)
{
	char ch = myRead(fp);
	clear_pushBackChar();

	if (ch == '\0') return false;

	if (ch == '='){
		return true;
		} else {
		pushBack(ch);
		return false;
		}
}
int arrowCheck(FILE* fp)
{
	char ch = myRead(fp);
	clear_pushBackChar();

	if (ch == '\0') return false;

	if (ch == '>'){
		return true;
		} else {
		pushBack(ch);
		return false;
		}
}
int equalCheck(char match, FILE *fp) 
{
	char ch = myRead(fp);
	clear_pushBackChar();

	if (ch == '\0') return false;

	if (match == ch){
		return true;
	} else {
		pushBack(ch);
		return false;
		}	
}
//----------------------------------------
lexeme* lex(FILE *fp) 
{
	char ch;
	skipWhiteSpace(fp);
	ch = myRead(fp);
	lexeme *lex = new_Lexeme();
	
	if (ch == '\0') return NULL;
	
	while (ch == '/') {
		pushBack(ch); 
		if (skipComment(fp) == 1) {
			skipWhiteSpace(fp);
			ch = myRead(fp);
		}
		else {
			ch = '/';
			break;
		}
	}

//single char check
	switch(ch) {
		case '#':
			lex->type = "HASHTAG";
			lex->lineNumber = lineNumber;
			return lex;
		case '(':
			lex->type = "OPAREN";
			lex->lineNumber = lineNumber;
			return lex;			 
		case ')':
			lex->type = "CPAREN";
			lex->lineNumber = lineNumber;
			return lex;
		case '{':
			lex->type = "OBRACE";
			lex->lineNumber = lineNumber;
			return lex;
		case '}':
			lex->type = "CBRACE";
			lex->lineNumber = lineNumber;
			return lex;
		case '[':
			lex->type = "OBRACKET";
			lex->lineNumber = lineNumber;
			return lex;
		case ']':
			lex->type = "CBRACKET";
			lex->lineNumber = lineNumber;
			return lex;
		case ',':
			lex->type = "COMMA";
			lex->lineNumber = lineNumber;
			return lex;
		case '<':
			lex->type = "LESSTHAN";
			lex->lineNumber = lineNumber;
			return lex;
		case '>':
			lex->type = "GREATERTHAN";
			lex->lineNumber = lineNumber;
			return lex;
		case '%':
			lex->type = "MOD";
			lex->lineNumber = lineNumber;
			return lex;
		case ';':
			lex->type = "SEMICOLON";
			lex->lineNumber = lineNumber;
			return lex;
		case ':':
			lex->type = "COLON";
			lex->lineNumber = lineNumber;
			return lex;
		case '?':
			lex->type = "QUESTION_MARK";
			lex->lineNumber = lineNumber;
			return lex;
	}
	//check arithmetic for shorthand 1 and 2-char operators
	if (ch == '+') {
		char match = ch;
		if (equalCheck(match,fp) == true) { //check for ++
			lex->type = "INCREMENT_OP";
			lex->lineNumber = lineNumber;
			return lex;
		}
		else if (shortHandCheck(fp) == true) { //check for +=
			lex->type = "SHORTHAND_PLUS";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "PLUS";  //check for +
		lex->lineNumber = lineNumber; 
		return lex;
	}
	else if (ch == '-') {
		char match = ch;
		if (equalCheck(match,fp) == true) { //check for --
			lex->type = "DECREMENT_OP";
			lex->lineNumber = lineNumber;
			return lex;
		}
		else if (shortHandCheck(fp) == true) { //check for -=
			lex->type = "SHORTHAND_MINUS";
			lex->lineNumber = lineNumber;
			return lex;
		}
		else if (arrowCheck(fp) == true) { //check for -=
			lex->type = "ARROW";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "MINUS"; //check for -
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (ch == '=') {
		char match = ch;
		if (equalCheck(match,fp) == true) { //check for ==
			lex->type = "EQUALS";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "ASSIGN"; //check for =
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (ch == '|') {
		char match = ch;
		if (equalCheck(match,fp) == true) { //check for ||
			lex->type = "OR";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "VERTICALBAR"; //check for |
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (ch == '&') {
		char match = ch;
		if (equalCheck(match,fp) == true) { //check for &&
			lex->type = "AND";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "AMPERSAND"; //check for &
		lex->lineNumber = lineNumber; 
		return lex;
	}
	else if (ch == '!') {
		if (shortHandCheck(fp) == true) { //check for !=
			lex->type = "DOES_NOT_EQUAL";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "EXCLAMATION"; //check for !
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (ch == '*') {
		if (shortHandCheck(fp) == true) { //check for *=
			lex->type = "SHORTHAND_TIMES";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "STAR";
		lex->lineNumber = lineNumber;
		return lex;
	}
	else if (ch == '/') {
		if (shortHandCheck(fp) == true) { //check for /=
			lex->type = "SHORTHAND_DIVIDES";
			lex->lineNumber = lineNumber;
			return lex;
		}
		lex->type = "FORWARDSLASH";
		lex->lineNumber = lineNumber;
		return lex;
	}

//multi char check(strings, numbers, or keywords/variables)
	else if (isdigit(ch) || ch == '.') {
		pushBack(ch);
		return lexNumber(fp);
	}
	else if (ch == '\"') {
		pushBack(ch);
		return lexString(fp);
	}
	else if (isalpha(ch) || ch == '_') {
		pushBack(ch);
		return lexVarOrKey(fp);
	}
	//unknown char read or EOF */
	else {
		printf("Line number %d: Unknown character read! Abort!!! Abort!!! Abort!!!", lineNumber);
		return lex;
	}
}