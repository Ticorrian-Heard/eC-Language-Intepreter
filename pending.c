#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"

//covers (< > == != ! & | && ||)
int conditionalPending() {
	return check("GREATERTHAN") || check("LESSTHAN") || check("EQUALS") || check("DOES_NOT_EQUAL") || check("EXCLAMATION") ||
	       check("AMPERSAND") || check("VERTICALBAR") || check("AND") || check("OR");
}
//covers (+ - * / % = += -= *= /=)
int operatorPending()
{
	return check("PLUS") || check("MINUS") || check("STAR") || check("FORWARDSLASH") || check("ARROW") ||
		   check("MOD") || check("ASSIGN") || check("SHORTHAND_PLUS") || check("SHORTHAND_MINUS") ||
		   check("SHORTHAND_TIMES") || check("SHORTHAND_DIVIDES") || check("INCREMENT_OP") || check("DECREMENT_OP"); 
}
//covers ints, reals, and strings
int unaryPending()
{
	return check("INTEGER") || check("REAL") || check("STRING");
}
//covers variables, int, reals, strings
int itemPending()
{
	return check("VARIABLE") || check("INTEGER") || check("REAL") || check("STRING") || check("AMPERSAND");
}
//var and variables
int variablePending()
{
	return check("VAR") || check("VARIABLE");
}
//assignments and shorthands
int assignmentPending()
{
	return check("ASSIGN") || check("SHORTHAND_PLUS") || check("SHORTHAND_MINUS") ||
		   check("SHORTHAND_TIMES") || check("SHORTHAND_DIVIDES");
}

//covers all conditionals
lexeme* conditional() 
{
	lexeme *tree = new_Lexeme();
	if (check("GREATERTHAN"))
		tree = match("GREATERTHAN");
	else if (check("LESSTHAN"))
			tree = match("LESSTHAN");
	else if (check("EQUALS"))
			tree = match("EQUALS");
	else if (check("DOES_NOT_EQUAL"))
			tree = match("DOES_NOT_EQUAL");
	else if (check("EXCLAMATION"))
			tree = match("EXCLAMATION");
	else if (check("VERTICALBAR"))
			tree = match("VERTICALBAR");
	else if (check("AMPERSAND"))
			tree = match("AMPERSAND");
	else if (check("AND"))
			tree = match("AND");
	else  tree = match("OR");

	return tree;
}

//covers all operators
lexeme* operator()
{
	lexeme *tree = new_Lexeme();
	if (check("PLUS"))
		tree= match("PLUS");
	else if (check("MINUS"))
			tree= match("MINUS");
	else if (check("STAR"))
			tree= match("STAR");
	else if (check("FORWARDSLASH"))
			tree= match("FORWARDSLASH");
	else if (check("MOD"))
			tree= match("MOD");
	else if (check("ASSIGN"))
			tree= match("ASSIGN");
	else if (check("SHORTHAND_PLUS"))
			tree= match("SHORTHAND_PLUS");
	else if (check("SHORTHAND_MINUS"))
			tree= match("SHORTHAND_MINUS");
	else if (check("DECREMENT_OP"))
			tree= match("DECREMENT_OP");
	else if (check("INCREMENT_OP"))
			tree= match("INCREMENT_OP");
	else if (check("SHORTHAND_TIMES"))
			tree= match("SHORTHAND_TIMES");
	else tree= match("SHORTHAND_DIVIDES");

	return tree;
}

lexeme* unary()
{
	lexeme *tree = new_Lexeme();
	if (check("INTEGER")) 
		tree = match("INTEGER");
	else if (check("REAL")) 
		tree= match("REAL");
	else tree = match("STRING");
	return tree; 
}
//utility for finding object members
lexeme *arrow()
{
	lexeme *var = match("VARIABLE");

	if (check("ARROW"))
	{
		lexeme *temp = match("ARROW");
		temp->left = var;
		temp->right = arrow(); 
		return temp;
	}
	else return var;
}

lexeme* item() 
{
	lexeme *tree = new_Lexeme();

	if (check("STAR")) { //is it a de-reffed variable
			match("STAR");
			if (check("STAR"))
				match("STAR");
			tree = item();
			return cons("POINTER",NULL,tree);
	}
	else if (check("MINUS")) { //ACCOUNT FOR NEGATIVE NUMBERS
			if (check("INTEGER")){ //negative int
				tree = match("INTEGER");
				return cons("NEGATIVE",tree,NULL);
			}
			else {
				tree = match("REAL"); //negative real
				return cons("NEGATIVE",tree,NULL);
				}
	}
	else if (check("NULL")) //null
		return match("NULL");
	else if (check("LAMBDA")) //LAMBDA
		return lambda();
	else if (check("INTEGER")) //int
		return match("INTEGER");
	else if (check("REAL")) //real
		return match("REAL");
	else if (check("STRING")) //string
		return match("STRING");
	else if (check("TRUE")) //true
		return match("TRUE");
	else if (check("FALSE")) //false
		return match("FALSE");
	else if (check("EOF"))//end of file
		return match("EOF");
	else if (check("AMPERSAND")) {//addresses
		match("AMPERSAND");
		tree = match("VARIABLE");
		return cons("AMPERSAND",NULL,tree);
	}

	else if (check("NEW")) {//new for struct allocation
		match("NEW");
		lexeme *var = match("VARIABLE");
		match("OPAREN");
		var->left = optexpressionlist(); 
		match("CPAREN");
		return cons("NEW",var,NULL);
	}
	else if	(check("VARIABLE")) {//variable
		
		lexeme* var = match("VARIABLE");

		if (check("ARROW")){ //variable->member 
  			lexeme *temp = match("ARROW");
  			temp->left = var;
  			temp->right = arrow();
  			var = temp; 
  			return var;
  		}
  		else if (check("OBRACKET")) {//array index access
			match("OBRACKET");
			if (check("VARIABLE")) var->left = match("VARIABLE");
			else var->left = match("INTEGER");
			match("CBRACKET");
			return cons("GET_ARRAY",var,NULL);
		}
		else if (check("OPAREN")) {//functioncalls
			match("OPAREN");
			var->left = optexpressionlist();
			match("CPAREN");
			return cons("FUNCTIONCALL",var,NULL);
		}
		else return var;
	}
	else {
		match("OPAREN"); //parenthesized expression
		tree = ifexpression();
		match("CPAREN");
		
		if (check("QUESTION_MARK")) { //ternary if else statement
			match("QUESTION_MARK");
			lexeme *a = expression();
			match("COLON");
			lexeme* b = expression();
			return cons("TERNARY",tree,cons("QUESTION_MARK",a,cons("COLON",b,NULL)));
		}
		else return cons("OPAREN",tree,NULL);
	} 
}

//variables(arrays too) initialized or not
lexeme* variable()
{
	lexeme *var=NULL,*tree=NULL;
	//check for vars
	if (check("VAR")) { //variable with/without an expression
	    var = match("VAR");

	    if (check("STAR")) { //if pointer or double pointer var *i;
			match("STAR");
			if(check("STAR"))
				match("STAR");
		}

	    var->left = match("VARIABLE");

	    if (check("OBRACKET")) {
	    	match("OBRACKET"); //arrays and list for var i[];
	    	if (check("INTEGER")) {
	    		var->left->left = match("INTEGER");
	    		match("CBRACKET");
	    		match("SEMICOLON");
  		 		return cons("NEW_ARRAY",var,tree);
	    	}
  		 	match("CBRACKET");
  		 	
  		 	if (check("ASSIGN")) { //var i[] = {9,9,9};
  		 		match("ASSIGN");
  		 		lexeme *arr = cons("SET_ARRAY",var,NULL);
  		 		tree = list();
  		 		match("SEMICOLON");
  		 		return cons("ASSIGN",arr,tree);
  		 	}
  		 	match("SEMICOLON");
  		 	return cons("NEW_ARRAY",var,tree);
		}

	    else if (assignmentPending()) { //covers var i = 0;
	     	lexeme *assign = assignment();
	     	tree = expression();
	     	match("SEMICOLON");
	     	return cons((char*)assign->type,var,tree);
	    }

	    else {
	    	match("SEMICOLON"); 
	    	return var;
	    }
	}
//check for just variable
	else if (check("VARIABLE")) {
  		
  		if (check("STAR")) { //if pointer or double pointer var *i;
			match("STAR");
			if(check("STAR"))
				match("STAR");
		}

  		var = match("VARIABLE");

  		if (check("ARROW")){ //in case of variable->member
  			lexeme *temp = match("ARROW");
  			temp->left = var;
  			temp->right = arrow();
  			var = temp;
  		}
  		if (assignmentPending()) { //assignments
  			lexeme *assign = assignment();
  			if (check("OBRACE")) {
  				tree = list();
  				match("SEMICOLON");
  				return cons((char*)assign->type,var,tree); //b={1,2,3};
  			}
	     	tree = expression();
	     	match("SEMICOLON");
	     	return cons((char*)assign->type,var,tree);
  		}
  		else if (check("OPAREN")) { //functioncalls
  			match("OPAREN");
  			var->left = optexpressionlist();
  			match("CPAREN");
  			match("SEMICOLON");
  			return cons("FUNCTIONCALL",var,NULL);
  		}
  		else {  
  		 	match("OBRACKET"); //array index access or array/list initialization
  		 	if (check("INTEGER")){
  		 		var->left = match("INTEGER");
  		 		match("CBRACKET");
  		 		lexeme *index = cons("GET_ARRAY",var,NULL);
  		 		lexeme *assign = assignment();
  		 		tree = expression();
  		 		match("SEMICOLON");
  		 		return cons((char *)assign->type,index,tree);
  		 	}
  		 	else if (check("VARIABLE")){
  		 		var->left = match("VARIABLE");
  		 		match("CBRACKET");
  		 		lexeme *index = cons("GET_ARRAY",var,NULL);
  		 		lexeme *assign = assignment();
  		 		tree = expression();
  		 		match("SEMICOLON");
  		 		return cons((char *)assign->type,index,tree);
  		 	}
  		 	match("CBRACKET");
  		 	if (check("ASSIGN")){
  		 		lexeme *arr = cons("SET_ARRAY",var,NULL);
  		 		match("ASSIGN");
  		 		tree = list();
  		 		match("SEMICOLON");
  		 		return cons("ASSIGN",arr,tree);
  		 	}
  		 	match("SEMICOLON");
  		 	return cons("SET_ARRAY",var,tree);
		}	
	}
}
//handles all assignment operators 
lexeme* assignment() 
{
	lexeme *tree = new_Lexeme();
		 if (check("ASSIGN"))
			tree = match("ASSIGN");
	else if (check("SHORTHAND_PLUS"))
			tree = match("SHORTHAND_PLUS");
	else if (check("SHORTHAND_MINUS"))
			tree = match("SHORTHAND_MINUS");
	else if (check("SHORTHAND_TIMES"))
			tree = match("SHORTHAND_TIMES");
	else tree = match("SHORTHAND_DIVIDES");
	return tree;
}