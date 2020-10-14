#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"
//headers, defines, and global variables are the most global env
//
void printArgs(lexeme *tree)
{
	while (tree != NULL) 
	{
		prettyPrinter(tree->left);
		if (tree->right != NULL) printf(", ");
		tree = tree->right;
	} 
}

lexeme *prettyPrinter(lexeme *tree)
{
		if (tree == NULL){ 
			printf("\n");
			return NULL;
		}
	
		else if (strcmp(tree->type,"INTEGER")==0) printf("%d", tree->number);   
		else if (strcmp(tree->type,"STRING")==0) printf("\"%s\"", tree->string);
		else if (strcmp(tree->type,"REAL")==0) printf("%lf", tree->dub);
		else if (strcmp(tree->type,"TRUE")==0) printf("true");
		else if (strcmp(tree->type,"FALSE")==0) printf("false");
		else if (strcmp(tree->type,"NULL")==0) printf("NULL");

		else if (strcmp(tree->type,"PROGRAM")==0) {
			prettyPrinter(tree->left);
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"GLOBAL")==0) {
			prettyPrinter(tree->left);
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"HEADER")==0) {
			printf("#include \"%s\" \n", tree->left->string);
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"DEFINE")==0) {
			printf("#define %s ",tree->left->string);
			prettyPrinter(tree->left->left);
		}
		else if (strcmp(tree->type,"STRUCT")==0) {
			printf("\ntypedef struct %s\n{", tree->left->string);
			prettyPrinter(tree->right);
			if (tree->left->left != NULL) printf("}%s;",tree->left->left->string);
			else printf("};\n");
		}
		else if (strcmp(tree->type,"UNION")==0) {
			printf("\nunion %s\n{", tree->left->string);
			prettyPrinter(tree->right);
			if (tree->left->left != NULL) printf("}%s;",tree->left->left->string);
			else printf("};\n");
		}
		else if (strcmp(tree->type,"FUNCTION")==0) {//when i hit main or any other function call this make another env and extend it to the prev env
			printf("\nfunction %s(",tree->left->string);
			printArgs(tree->left->left);
			printf(")\n");
			printf("{");
			prettyPrinter(tree->right);
			printf("}\n");
		}
		else if (strcmp(tree->type,"LAMBDA")==0) {//when i hit main or any other function call this make another env and extend it to the prev env
			printf("lambda(");
			printArgs(tree->left->left);
			printf(")\n");
			printf("   {");
			prettyPrinter(tree->right);
			printf("   }");
		}
		else if (strcmp(tree->type,"BODY")==0) {
			if ((strcmp(tree->left->type,"IFSTATEMENT")==0)||
				(strcmp(tree->left->type,"ELSE")==0)||
				(strcmp(tree->left->type,"WHILELOOP")==0)||
				(strcmp(tree->left->type,"FORLOOP")==0)||
				(strcmp(tree->left->type,"FUNCTION")==0)||
				(strcmp(tree->left->type,"LAMBDA")==0))

				{
					printf("\n   ");
					prettyPrinter(tree->left);
					prettyPrinter(tree->right);
				}
			else {
				printf("\n   ");
				prettyPrinter(tree->left);
				printf(";");
				prettyPrinter(tree->right);	
			}
		}
		else if (strcmp(tree->type,"NEW")==0) {
			printf("new ");
			printf("%s",tree->left->string);
			printf("(");
			printArgs(tree->left->left);
			printf(")");
		}
		else if (strcmp(tree->type,"VAR")==0) {
			printf("var ");
			prettyPrinter(tree->left);
		}
		else if (strcmp(tree->type,"VARIABLE")==0) {
			printf("%s", tree->string);
			if (tree->left != NULL && strcmp(tree->left->type,"INTEGER")!=0 ) {
				prettyPrinter(tree->left);
			}
		}
		else if (strcmp(tree->type,"SET_ARRAY")==0) { //FIGURE OUT THE ARRAY PRINTING HERE
			prettyPrinter(tree->left);
			printf("[]");
		}
		else if (strcmp(tree->type,"NEW_ARRAY")==0 ) { //AND HERE
			prettyPrinter(tree->left);
			printf("[");
			if (tree->left->left->left != NULL) prettyPrinter(tree->left->left->left);
			printf("]");
		}
		else if (strcmp(tree->type,"GET_ARRAY")==0) {
			printf("%s",tree->left->string);
			printf("[");
			prettyPrinter(tree->left->left);
			printf("]");
		}
		else if (strcmp(tree->type,"ARROW")==0) {
			prettyPrinter(tree->left);
			printf("->");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"LIST")==0) {
			printf("{");
			printArgs(tree->left);
			printf("}");
		}
		else if (strcmp(tree->type,"OPTLIST")==0) {
			printArgs(tree);
		}
		else if (strcmp(tree->type,"OPAREN")==0) {
			printf("(");
			prettyPrinter(tree->left);
			printf(")");
		}
		else if (strcmp(tree->type,"PLUS")==0) {
			prettyPrinter(tree->left);
			printf(" + ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"NEGATIVE")==0) {
			printf("-");
			if (strcmp(tree->left->type,"INTEGER")==0) printf("%d", tree->left->number); 
			else printf("%lf", tree->left->dub);
		}
		else if (strcmp(tree->type,"MINUS")==0) {
			prettyPrinter(tree->left);
			printf(" - ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"STAR")==0) {
			prettyPrinter(tree->left);
			printf(" * ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"FORWARDSLASH")==0) {
			prettyPrinter(tree->left);
			printf(" / ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"MOD")==0) {
			prettyPrinter(tree->left);
			printf(" %c ", '%');
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"ASSIGN")==0) { 
			prettyPrinter(tree->left);
			printf(" = ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"FUNCTIONCALL")==0) {
			printf("%s", tree->left->string);
			printf("(");
			printArgs(tree->left->left);
			printf(")");
		}
		else if (strcmp(tree->type,"FILE")==0) {
			if (tree->right != NULL) {
				printf("FILE *%s = ", tree->left->string);
				prettyPrinter(tree->right);
			}
			else printf("FILE *%s", tree->left->string);
			
		}
		else if (strcmp(tree->type,"IFSTATEMENT")==0) {
			printf("if (");
			prettyPrinter(tree->left);
			printf(") ");
			if (tree->right != NULL) {
				if (strcmp(tree->right->type,"BODY")==0) {
					printf("{");
					prettyPrinter(tree->right);
					printf("   }");
				}
				else {
					prettyPrinter(tree->right);
					printf(";");
				}
			}	
		}
		else if (strcmp(tree->type,"ELSE")==0) {
			printf("else ");
			if (strcmp(tree->left->type,"BODY")==0) {
				printf("{");
				prettyPrinter(tree->left);
				printf("   }");
			}
			else {
				prettyPrinter(tree->left);
				printf(";");
			}
		}
		else if (strcmp(tree->type,"WHILELOOP")==0) {
			printf("while (");
			prettyPrinter(tree->left);
			printf(") ");
			if (strcmp(tree->right->type,"BODY")==0) {
				printf("{");
				prettyPrinter(tree->right);
				printf("   }");
			}
			else {
				prettyPrinter(tree->right);
				printf(";");
			}
		}
		else if (strcmp(tree->type,"FORLOOP")==0) {
			printf("for (");
			prettyPrinter(tree->left);
			printf("; "); 
			prettyPrinter(tree->right->left);
			printf("; ");
			prettyPrinter(tree->right->right->left);
			printf(") ");
			if (tree->right->right->right != NULL) {
					if (strcmp(tree->right->right->right->type,"BODY")==0) {
						printf("{");
						prettyPrinter(tree->right->right->right);
						printf("   }");
					}
					else {
						prettyPrinter(tree->right->right->right);
						printf(";");
					}
			}		
		}
		else if (strcmp(tree->type,"RETURN")==0) {
			printf("return ");
			prettyPrinter(tree->left);
		}
		else if (strcmp(tree->type,"EQUALS")==0) {
			prettyPrinter(tree->left);
			printf(" == ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"DOES_NOT_EQUAL")==0) {
			prettyPrinter(tree->left);
			printf(" != ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"LESSTHAN")==0) {
			prettyPrinter(tree->left);
			printf(" < ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"GREATERTHAN")==0) {
			prettyPrinter(tree->left);
			printf(" > ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"SHORTHAND_PLUS")==0) { 
			prettyPrinter(tree->left);
			printf(" += ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"SHORTHAND_MINUS")==0) { 
			prettyPrinter(tree->left);
			printf(" -= ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"SHORTHAND_TIMES")==0) { 
			prettyPrinter(tree->left);
			printf(" *= ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"SHORTHAND_DIVIDES")==0) { 
			prettyPrinter(tree->left);
			printf(" /= ");
			prettyPrinter(tree->right);
		}
		else if (strcmp(tree->type,"INC")==0) { 
			printf("++");
			prettyPrinter(tree->left);
		}
		else if (strcmp(tree->type,"DEC")==0) { 
			printf("--");
			prettyPrinter(tree->left);
		}
}