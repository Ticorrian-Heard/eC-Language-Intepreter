#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"
//headers, defines, and global variables are the most global env
//
lexeme *eval(lexeme *tree, lexeme *env)
{	
		if (tree == NULL) return NULL;

		//data types
		if (strcmp(tree->type,"INTEGER")==0) return tree;
		else if (strcmp(tree->type,"STRING")==0) return tree;
		else if (strcmp(tree->type,"REAL")==0) return tree;
		else if (strcmp(tree->type,"NULL")==0) return tree;
		else if (strcmp(tree->type,"TRUE")==0) return evalBoolean(tree,env);
		else if (strcmp(tree->type,"FALSE")==0) return evalBoolean(tree,env);
		else if (strcmp(tree->type,"VARIABLE")==0) return lookup(tree,env); //looks for the value in env
		else if (strcmp(tree->type,"OPAREN")==0) return eval(tree->left,env); //parathensized expression
		else if (strcmp(tree->type,"VAR")==0) return evalVarDef(tree,env);
		else if (strcmp(tree->type,"ARROW")==0) return evalObject(tree,env);

		//conditionals
		else if (strcmp(tree->type,"EQUALS")==0) return tree;
		else if (strcmp(tree->type,"GREATERTHAN")==0) return tree;
		else if (strcmp(tree->type,"LESSTHAN")==0) return tree;
		else if (strcmp(tree->type,"DOES_NOT_EQUAL")==0) return tree;
		//else if (strcmp(tree->type,"EQUALS")==0) return tree; //ADD >=, <=

		//operations 
		else if (strcmp(tree->type,"PLUS")==0)
			return evalPlus(tree,env);
		else if (strcmp(tree->type,"MINUS")==0)
			return evalMinus(tree,env);
		else if (strcmp(tree->type,"STAR")==0)
			return evalTimes(tree,env);
		else if (strcmp(tree->type,"FORWARDSLASH")==0)
			return evalDiv(tree,env);
		else if (strcmp(tree->type,"MOD")==0)
			return evalMod(tree,env);
		else if (strcmp(tree->type,"ASSIGN")==0)
			return evalAssign(tree,env);
		else if (strcmp(tree->type,"SHORTHAND_PLUS")==0)
			return evalSPlus(tree,env);
		else if (strcmp(tree->type,"SHORTHAND_MINUS")==0)
			return evalSMinus(tree,env);
		else if (strcmp(tree->type,"SHORTHAND_TIMES")==0)
			return evalSTimes(tree,env);
		else if (strcmp(tree->type,"SHORTHAND_DIVIDES")==0)
			return evalSDiv(tree,env);
		else if (strcmp(tree->type,"INC")==0)
			return evalInc(tree,env);
		else if (strcmp(tree->type,"DEC")==0)
			return evalDec(tree,env);

		//arrays
		else if (strcmp(tree->type,"NEW_ARRAY")==0)
			return evalNewArray(tree->left->left,env);
		else if (strcmp(tree->type,"GET_ARRAY")==0)
			return evalGetArray(tree,env);
		else if (strcmp(tree->type,"LIST")==0)
			return evalArgs(tree->left,env);
		
		//structure
		else if (strcmp(tree->type,"PROGRAM")==0) { 
			eval(tree->left,env);
			return eval(tree->right,env);
		}
		else if (strcmp(tree->type,"GLOBAL")==0) {
			eval(tree->left,env);
			return eval(tree->right,env);
		}
		else if (strcmp(tree->type,"HEADER")==0) {
			evalHeader(tree,env);
			return eval(tree->right,env);
		}
		else if (strcmp(tree->type,"DEFINE")==0) {
			evalDefine(tree,env);
			return eval(tree->right,env);
		}
		else if (strcmp(tree->type,"RETURN")==0)
			return evalReturn(tree,env);
		else if (strcmp(tree->type,"BODY")==0)
			return evalBody(tree,env);
		else if (strcmp(tree->type,"LAMBDA")==0) 
			return evalLambda(tree,env);
		else if (strcmp(tree->type,"FUNCTION")==0) 
			return evalFuncDef(tree,env);
		else if (strcmp(tree->type,"FUNCTIONCALL")==0) 
			return evalFuncCall(tree,env);
		else if (strcmp(tree->type,"IFSTATEMENT")==0) 
			return evalIfStatement(tree,env);
		else if (strcmp(tree->type,"ELSE")==0) 
			return evalElseStatement(tree,env);
		else if (strcmp(tree->type,"WHILELOOP")==0) 
			return evalWhileLoop(tree,env);

		else {
			printf("fatal error\n");
			exit(1);
		} 
}

void addBuiltins(lexeme *env)
{
	//builtins
	lexeme *println = new_Lexeme(); //add println function
	println->string = "println";
	lexeme *printlnVal = new_Lexeme();
	printlnVal->type = "BUILTIN";
	printlnVal->fval = &evalPrintln;
	insert(println, printlnVal, env);

	lexeme *print = new_Lexeme(); //add print function
	print->string = "print";
	lexeme *printVal = new_Lexeme();
	printVal->type = "BUILTIN";
	printVal->fval = &evalPrint;
	insert(print, printVal, env);

	lexeme *fopen = new_Lexeme(); 
	fopen->string = "fopen";
	lexeme *fopenVal = new_Lexeme();
	fopenVal->type = "BUILTIN";
	fopenVal->fval = &evalOpenFileForReading;
	insert(fopen, fopenVal, env);

	lexeme *fclose = new_Lexeme(); 
	fclose->string = "fclose";
	lexeme *fcloseVal = new_Lexeme();
	fcloseVal->type = "BUILTIN";
	fcloseVal->fval = &evalCloseFile;
	insert(fclose, fcloseVal, env);

	lexeme *eof = new_Lexeme(); 
	eof->string = "eof";
	lexeme *eofVal = new_Lexeme();
	eofVal->type = "BUILTIN";
	eofVal->fval = &evalatEOF;
	insert(eof, eofVal, env);

	lexeme *readint = new_Lexeme(); 
	readint->string = "readInt";
	lexeme *readintVal = new_Lexeme();
	readintVal->type = "BUILTIN";
	readintVal->fval = &evalReadInteger;
	insert(readint, readintVal, env);

	lexeme *readreal = new_Lexeme(); 
	readreal->string = "readReal";
	lexeme *readrealVal = new_Lexeme();
	readrealVal->type = "BUILTIN";
	readrealVal->fval = &evalReadReal;
	insert(readreal, readrealVal, env);

	lexeme *readstring = new_Lexeme(); 
	readstring->string = "readString";
	lexeme *readstringVal = new_Lexeme();
	readstringVal->type = "BUILTIN";
	readstringVal->fval = &evalReadString;
	insert(readstring, readstringVal, env);

	lexeme *readline = new_Lexeme(); 
	readline->string = "readLine";
	lexeme *readlineVal = new_Lexeme();
	readlineVal->type = "BUILTIN";
	readlineVal->fval = &evalReadLine;
	insert(readline, readlineVal, env);

	lexeme *readargc = new_Lexeme(); 
	readargc->string = "argc";
	lexeme *readargcVal = new_Lexeme();
	readargcVal->type = "BUILTIN";
	readargcVal->fval = &evalGetArgCount;
	insert(readargc, readargcVal, env);

	lexeme *readargv = new_Lexeme(); 
	readargv->string = "argv";
	lexeme *readargvVal = new_Lexeme();
	readargvVal->type = "BUILTIN";
	readargvVal->fval = &evalGetArg;
	insert(readargv, readargvVal, env);

	lexeme *readarrsize = new_Lexeme(); 
	readarrsize->string = "length";
	lexeme *readarrsizeVal = new_Lexeme();
	readarrsizeVal->type = "BUILTIN";
	readarrsizeVal->fval = &GetArraySize;
	insert(readarrsize, readarrsizeVal, env);
}