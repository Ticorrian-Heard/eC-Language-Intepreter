#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"

//handles if statement expressions
lexeme* ifexpression()
{
	lexeme *u = NULL;
	lexeme *op = NULL;
	lexeme *exp = NULL;
	
	u = item();
	if (operatorPending()) {
		op = operator();
		exp = expression();
		return cons((char*)op->type, u, exp);
	}
	
	else if (conditionalPending()) {
		op = conditional();
		exp = condexpression();
		return cons((char*)op->type, u, exp);
	}
	else return u;
}
lexeme* condexpression() 
{
	lexeme *u = NULL;
	lexeme *cond = NULL;
	lexeme *exp = NULL;

	u = expression();
	if (conditionalPending()) {
		cond = conditional();
		exp = condexpression();
		return cons((char*)cond->type, u, exp);
	}
	else 
		return u;
}
//handles single expression
lexeme* expression() 
{
	lexeme *u = NULL;
	lexeme *op = NULL;
	lexeme *exp = NULL;
	
	u = item();
	if (operatorPending()) {
		op = operator();
		exp = expression();
		return cons((char*)op->type, u, exp);
	}
	else 
		return u; 	
}
//covers the arguments in function calls
lexeme* optexpressionlist() //function(9+9, 99, 100 - 39)
{
	lexeme *exp = NULL;
	lexeme *addexp = NULL;

	if (itemPending()) { //ACCOUNT FOR EMPTY ARGUMENTS IN A FUNCTION CALL
		exp = expression();
		if (check("COMMA")){
			match("COMMA");
			addexp = optexpressionlist();
			return cons("OPTLIST",exp,addexp);
		}
		else return cons("OPTLIST",exp,addexp);
	}
	else return exp; 
}
//arrays, lists 
lexeme* list()
{
	lexeme *tree = NULL;
	//if (check("ASSIGN")) {
	//	match("ASSIGN");
		match("OBRACE");
		tree = optexpressionlist();
		match("CBRACE");
		return cons("LIST",tree,NULL);
	//}
	//else return tree; 
}
//parameters in function definitions
lexeme* parameter()
{ 
	lexeme *tree = NULL,*var = NULL;

   	if (check("VARIABLE")) {
   		var = match("VARIABLE");

   		if (check("ASSIGN")) { //covers default parameter
   			lexeme *temp = var;
			var = match("ASSIGN");
			var->left = temp;
			if (unaryPending())
				var->right = expression();
		}
   		if (check("COMMA")) { //check if there are more than one param
   		   	match("COMMA");
   		   	tree = parameter();
   		}
   		return cons("PARAMLIST",var,tree);
   	}
   	else return tree;
}
//decrement ops
lexeme *decrement()
{
	match("DECREMENT_OP");
	lexeme *var = match("VARIABLE");
	match("SEMICOLON");
	return cons("DEC",var,NULL);
}
//increment ops
lexeme *increment()
{
	match("INCREMENT_OP");
	lexeme *var = match("VARIABLE");
	match("SEMICOLON");
	return cons("INC",var,NULL);
}
//while loops
lexeme* whileloop()
{
	lexeme *exp,*bod;
	match("WHILE");
	match("OPAREN");
	exp = ifexpression();
	match("CPAREN");

	if (check("OBRACE")){ //body of loop
		match("OBRACE");
		bod = body();
		match("CBRACE");
	}
	else if (check("DECREMENT_OP)")) { //--i
		match("DECREMENT_OP");
		lexeme *var = match("VARIABLE");
		match("SEMICOLON");
		bod = cons("DEC",var,NULL);
	}
	else if (check("INCREMENT_OP")) {
		match("INCREMENT_OP"); //++i
		lexeme *var = match("VARIABLE");
		match("SEMICOLON");
		bod = cons("INC",var,NULL);
	}
	else if (check("RETURN")) {
		bod = returnstatement();
		match("SEMICOLON");
	}
	else {
		if (check("VAR"))
			match("VAR");
		bod = expression();
		match("SEMICOLON");
	}
	return cons("WHILELOOP",exp,bod);
}
//for loops
lexeme* forloop()
{
	lexeme *exp1,*exp2,*exp3,*bod;
	match("FOR");   //for (i=0; i<size; )
	match("OPAREN");
	exp1 = expression();
	match("SEMICOLON");
	exp2 = condexpression();
	match("SEMICOLON");

	if (check("VARIABLE")) { //i=i*2
		match("VARIABLE");
		match("ASSIGN");
		exp3 = expression();
	}
	else if (check("DECREMENT_OP)")) { //--i
		match("DECREMENT_OP");
		lexeme *var = match("VARIABLE");
		exp3 = cons("DEC",var,NULL);
	}
	else {
		match("INCREMENT_OP"); //++i
		lexeme *var = match("VARIABLE");
		exp3 = cons("INC",var,NULL);
	}
	match("CPAREN");

	if (check("OBRACE")){ //body of loop
		match("OBRACE");
		bod = body();
		match("CBRACE");
	}
	else if (check("RETURN")) { //return in for loop
		bod = returnstatement();
		match("SEMICOLON");
	}
	else {
		if (check("VAR"))
			match("VAR");
		bod = expression(); //expression without braces
		match("SEMICOLON");
	}
	return cons("FORLOOP",exp1,cons("CONDEXPR",exp2,cons("ITER",exp3,bod)));
}

lexeme* returnstatement()
{
	lexeme *ret = match("RETURN");
	lexeme *exp = expression();
	match("SEMICOLON");
	return cons((char*)ret->type,exp,NULL);
}
//if statments
lexeme* ifstatement() 
{
	lexeme *exp,*bod;
	match("IF");
	match("OPAREN");
	exp = ifexpression();
	match("CPAREN");

	if (check("OBRACE")){ //if (cond) {}
		match("OBRACE");
		bod = body();
		match("CBRACE");
		return cons("IFSTATEMENT",exp,bod);
	}

	else { //if (cond)
		if (check("IF")) bod = ifstatement();
		else if (variablePending()) bod = variable();
		else if (check("INCREMENT_OP")) bod = increment();
		else if (check("DECREMENT_OP")) bod = decrement();
		else if (check("WHILE")) bod = whileloop();
		else if (check("FOR")) bod = forloop();
		else if (check("RETURN")) bod = returnstatement();
		return cons("IFSTATEMENT",exp,bod);
	}
}
//else statements
lexeme* elsestatement()
{
	lexeme *exp,*bod;
	match("ELSE");

	if (check("IF")) { //else if
		exp = ifstatement();
		return cons("ELSE",exp,NULL);
	} 
	else {

		if (check("OBRACE")){ //else {}
			match("OBRACE");
			bod = body();
			match("CBRACE");
			return cons("ELSE",bod,NULL);
		}

		else { //else 
			if (variablePending()) bod = variable();
			else if (check("INCREMENT_OP")) bod = increment();
			else if (check("DECREMENT_OP")) bod = decrement();
			else if (check("WHILE")) bod = whileloop();
			else if (check("FOR")) bod = forloop();
			else bod = returnstatement();
			return cons("ELSE",bod,NULL);
		}
	}
}
