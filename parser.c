#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"
lexeme *CurrentLexeme;
//confirm lexeme is of correct given type
int check(char *type) 
{
	if (CurrentLexeme == NULL) return 0;
	else if (strcmp(CurrentLexeme->type,type)==0) return 1;
	else return 0;			
}

//call lex to move to next lexeme
lexeme* advance() 
{	
	lexeme *a = CurrentLexeme;
	CurrentLexeme = lex(fp);
	return a;
}

//if match is not correct type syntax error exit program
void matchNoAdvance(char *type)
{
	if (check(type) == 0){
		advance();
		if (CurrentLexeme == NULL) {
			printf("Syntax error at end of code! Possibly last character of your code.\n");
			exit(1);
		}
		else {
			if (strcmp(type,"SEMICOLON")==0){
			printf("missing ';' at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);	
			}
			else if (strcmp(type,"OBRACE")==0){
			printf("missing '{' at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);	
			}
			else if (strcmp(type,"CBRACE")==0){
			printf("missing '}' at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);	
			}
			else if (strcmp(type,"OPAREN")==0){
			printf("missing '(' at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);	
			}
			else if (strcmp(type,"CPAREN")==0){
			printf("missing ')' at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);	
			}
			else if (strcmp(type,"COMMA")==0){
			printf("missing ',' at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);	
			}
			else {
			printf("syntax error at line %d!\n", CurrentLexeme->lineNumber);
			exit(1);
			}
		}
	}
}

//match only if the type is a match 
lexeme* match(char *type)
{
	if  (CurrentLexeme == NULL) {
		printf("Out of input. Syntax error.\n");
		exit(1);
	}
	matchNoAdvance(type);
	return advance();
}

/*void displayTree(lexeme *tree)
{
	if (tree == NULL) {
		printf("\n");
		return;
	}
	printf("%s ",tree->type);
	displayTree(tree->left);
	displayTree(tree->right);
}*/

void displayTree(lexeme *root, int space) 
{ 
    // Base case 
    if (root == NULL){ 
        return; 
    }
  
    // Increase distance between levels 
    space += 10; 
  
    // Process right child first 
    displayTree(root->right, space); 
  
    // Print current node after space 
    // 10 
    printf("\n"); 
    for (int i = 10; i < space; i++) 
        printf(" "); 
    printf("%s\n", root->type); 
  
    // Process left child 
    displayTree(root->left, space); 
} 
//like an advanced scanner
lexeme* parser(char *filename) 
{
	fp = fopen(filename,"r");
	CurrentLexeme = lex(fp);
	lexeme *a = program();

	//displayTree(a,0); //for testing purposes 
	free(CurrentLexeme);
	fclose(fp);

	return a;
}
/*int main(int argc, char *argv[]) 
{
	printf("Starting Parser...\n");	
	parser(argv[1]);
	printf("Compilation Success!\n");
	return 0;
}*/