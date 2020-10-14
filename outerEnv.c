/*
Ticorrian Heard
Lusth CS403
Module 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"
lexeme *CurrentLexeme;

lexeme* file()
{
	lexeme *var,*op;
	var = match("FILE");
	match("STAR");
	var->left = match("VARIABLE");
	lexeme *assign = match("ASSIGN");
	op = match("VARIABLE");

	match("OPAREN");
  	op->left = optexpressionlist();
  	match("CPAREN");
  	match("SEMICOLON");

  	return cons((char*)assign->type,var,cons("FUNCTIONCALL",op,NULL));
}
lexeme* function()
{
	lexeme *var,*bod;
	match("FUNCTION");
	var = match("VARIABLE");
	match("OPAREN");
	var->left = parameter();
	match("CPAREN");

	if (check("SEMICOLON")){
	    match("SEMICOLON");
	    return cons("FUNCTION",var,NULL);
	}	     	
	else {
	   match("OBRACE");
	   bod = body();
	   match("CBRACE");
	   return cons("FUNCTION",var,bod);
	}
}
lexeme *lambda()
{
	lexeme *var=NULL;
	var = match("LAMBDA");
	match("OPAREN");
	lexeme *glue = new_p_Lexeme("GLUE");
	var->left = glue;
	var->left->left = optexpressionlist();
	match("CPAREN");
	match("OBRACE");
	var->right = body();
	match("CBRACE");
	return var;
}
lexeme* structure() 
{
	lexeme *var,*bod,*var2=NULL;
	match("TYPEDEF");
	match("STRUCT");
	var = match("VARIABLE");
	match("OBRACE");
	bod = body();
	match("CBRACE");
	if (check("VARIABLE"))
		var->left = match("VARIABLE");
	match("SEMICOLON");

	return cons("STRUCT",var,bod);
}
lexeme* unionstructure()
{
	lexeme *var,*bod,*var2;
	match("UNION");
	var = match("VARIABLE");
	match("OBRACE");
	bod = body();
	match("CBRACE");
	if (check("VARIABLE"))
		var->left = match("VARIABLE");
	match("SEMICOLON");

	return cons("UNION",var,bod);
}
//body of a function
lexeme* body()
{
	lexeme *bod = NULL, *tree = NULL;

	if (variablePending()) {
		tree = variable();
		bod = body();
	}
	else if (check("FUNCTION")){
	 	tree = function();
	 	bod = body();
	}
	else if (check("STAR")) {//pointers
		match("STAR");
		tree = variable();
		bod = body();
	}
	else if (check("DECREMENT_OP")) {//--i;
		tree = decrement();
		bod = body();
	}
	else if (check("INCREMENT_OP")) {//++i;
		tree = increment();
		bod = body();
	}
	else if (check("BREAK")) {//for breaks
		tree = match("BREAK");
		match("SEMICOLON");
		bod = body();
	}
	else if (check("CONTINUE")) {//for continues
		tree = match("CONTINUE");
		match("SEMICOLON");
		bod = body();
	}
	else if (check("IF")) {//ifs
		tree = ifstatement();
		bod = body();
	} 
	else if (check("ELSE")) {//else if, elses
		tree = elsestatement();
		bod = body();
	}
	else if (check("FOR")) {//for loop
		tree = forloop();
		bod = body();
	} 
	else if (check("WHILE")) {//while loop
		tree = whileloop();
		bod = body();
	} 
	else if (check("FILE")) {
		tree = file();
		bod = body();
	}
	else if (check("RETURN")) {//return
		tree = returnstatement();
		bod = body();
	} 
	else return NULL;

	return cons("BODY",tree,bod); //may need to come back to this
} 

//global variable, functions, unions, and structs
lexeme* functionDefAndVarDef() 
{
	lexeme *tree = NULL,*funcAndDef = NULL;

	if ( check("FUNCTION") ) { //covers function defs
	     tree = function();
	     funcAndDef = functionDefAndVarDef();
	 }
	
	else if ( check("TYPEDEF") ) { //covers structs 
		tree = structure();
		funcAndDef = functionDefAndVarDef();
	}
	
	else if ( check("VAR") ) { //covers global variables
		tree = variable();
		funcAndDef = functionDefAndVarDef();
	}
	
	else if ( check("UNION")) { //covers unions
		tree = unionstructure();
		funcAndDef = functionDefAndVarDef();
	}
	
	else if (check("FILE")) {
		tree = file();
		funcAndDef = functionDefAndVarDef();
	}
	else return tree;

	return cons("GLOBAL",tree,funcAndDef);
}
//handles headers and defines
lexeme* headersAndDefs()
{
	lexeme *var = NULL,*tree = NULL;
	if (check("HASHTAG")) {
		match("HASHTAG");
		
		if (check("INCLUDE")) {
			match("INCLUDE");
			var = match("STRING");
			tree = headersAndDefs();
			return cons("HEADER",var,tree);
		}
		else if (check("DEFINE")) {
			match("DEFINE");
			var = match("VARIABLE");
			if (unaryPending())
			var->left = unary();
			tree = headersAndDefs();
			return cons("DEFINE",var,tree);
		}
	}
	else return tree;	
}
//glues entire parse tree together
lexeme* program() 
{ 
	lexeme *headsAndDefs,*funcDefs;
	headsAndDefs = headersAndDefs();
	funcDefs = functionDefAndVarDef();
	return cons("PROGRAM",headsAndDefs,funcDefs);
}