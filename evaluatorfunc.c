#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"

lexeme *evalPlus(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right,env);
	lexeme* result = new_Lexeme();

		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the plus operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number + arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = arg1->number + arg2->number + arg1->dub + arg2->dub;
		}	
		else if(strcmp(arg1->type,"STRING")==0 && strcmp(arg2->type,"STRING")==0){
			result->type = "STRING";
			result->string = addString(arg1->string, arg2->string);
		}
		return result;
} 
lexeme* evalMinus(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the plus operation is NULL\n");
			exit(1);
		}	
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number - arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = (arg1->number + arg1->dub) - (arg2->number + arg2->dub);	
		}
		return result;
}
lexeme* evalTimes(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the times operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number * arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = (arg1->number + arg1->dub) * (arg2->number + arg2->dub);
		}
		return result;
}
lexeme* evalDiv(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the divides operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number / arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = (arg1->number + arg1->dub) / (arg2->number + arg2->dub);	
		}
		return result;
}
lexeme* evalMod(lexeme *tree, lexeme *env) 
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the mod operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number % arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0/* || strcmp(arg2->type,"REAL")==0*/){
			result->type = "REAL";
			result->dub = (int)(arg1->number + arg1->dub) % (int)(arg2->number + arg2->number);	
		}
		return result;
}
lexeme *evalSPlus(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right,env);

	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the short hand plus operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number + arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = arg1->number + arg2->number + arg1->dub + arg2->dub;
		}	
		update(tree->left,result,env);
		return result;
}
lexeme *evalSMinus(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
		lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the short hand minus operation is NULL\n");
			exit(1);
		}

		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number - arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = (arg1->number + arg1->dub) - (arg2->number + arg2->dub);	
		}
		update(tree->left,result,env);
		return result;
}
lexeme *evalSTimes(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the short hand times operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number * arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = (arg1->number + arg1->dub) * (arg2->number + arg2->dub);
		}
		update(tree->left,result,env);
		return result;
}
lexeme *evalSDiv(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *arg2 = eval(tree->right, env);
	lexeme* result = new_Lexeme();
		if (arg1 == NULL || arg2 == NULL){
			printf("One of the binary operands of the short hand divides operation is NULL\n");
			exit(1);
		}
		if (strcmp(arg1->type,"INTEGER")==0 && strcmp(arg2->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number / arg2->number;
		}
		else if (strcmp(arg1->type,"REAL")==0 || strcmp(arg2->type,"REAL")==0){
			result->type = "REAL";
			result->dub = (arg1->number + arg1->dub) / (arg2->number + arg2->dub);	
		}
		update(tree->left,result,env);
		return result;
}

lexeme *evalInc(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *result = new_Lexeme();
		if (arg1 == NULL){
			printf("INC undefined of the operation\n");
			exit(1);
		}
	if (strcmp(arg1->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number + 1;
	}
	else {
		result->type = "REAL";
		result->dub = arg1->dub + 1.0;
	}
	update(tree->left,result,env);
	return result;

}
lexeme *evalDec(lexeme *tree, lexeme *env)
{
	lexeme *arg1 = eval(tree->left,env);
	lexeme *result = new_Lexeme();
		if (arg1 == NULL){
			printf("DEC undefined on line\n");
			exit(1);
		}
	if (strcmp(arg1->type,"INTEGER")==0){
			result->type = "INTEGER";
			result->number = arg1->number - 1;
	}
	else {
		result->type = "REAL";
		result->dub = arg1->dub - 1.0;
	}
	update(tree->left,result,env);
	return result;
}
lexeme *evalBoolean(lexeme *tree, lexeme *env)
{
	lexeme *boolean = new_p_Lexeme("INTEGER");
	if (strcmp(tree->type,"TRUE")==0) {
		boolean->number = 0;
		return boolean;
	}
	else {
		boolean->number = 1;
		return boolean;
	}
}
lexeme *evalVarDef(lexeme *tree, lexeme *env)
{
	return insert(tree->left, NULL, env);
} 

lexeme *evalAssign(lexeme *tree, lexeme *env)
{	
	lexeme *value = eval(tree->right,env);

	if (strcmp(tree->left->type,"VAR")==0) {
		eval(tree->left,env);
		if (strcmp(value->type,"CLOSURE")==0) insert(tree->left->left,value,env); //handles closures
		else return update(tree->left->left,value,env);
	}
	else if (strcmp(tree->left->type,"ARROW")==0) { 
		lexeme *obj = getThis(tree->left->left,env); //LHS of ARROW is the object
		return update(getVar(tree->left),value,obj); //value should = ENV
	}
	else if (strcmp(tree->left->type,"FILE")==0) {
		evalNewFile(tree->left->left,env); //insert new file
		return update(tree->left->left,value,env);
	}
	else if (strcmp(tree->left->type,"SET_ARRAY")==0) {
		lexeme* size = new_p_Lexeme("INTEGER");
		 size->number = getArraySize(tree->right->left,0);

		if (tree->left->left->left != NULL) {
			tree->left->left->left->left = size;
			lexeme *arr = evalNewArray(tree->left->left->left,env);
			evalSetINITArray(arr,value,size,env);
		}
		else {
			lookup(tree->left->left,env);
			tree->left->left->left = size;
			lexeme *arr = evalNewArray(tree->left->left,env);
			evalSetINITArray(arr,value,size,env);
		}
	}
	else if (strcmp(tree->left->type,"GET_ARRAY")==0) {
		evalSetArray(tree->left->left,value,env);
	}
	else if (strcmp(value->type,"CLOSURE")==0) {
		insert(tree->left,value,env);
	}
	else return update(tree->left,value,env); 
}

lexeme *evalBody(lexeme *tree, lexeme *env)
{
	lexeme *result;
	while (tree != NULL)
	{
		if (strcmp(tree->left->type,"RETURN")==0) { //return in body
			return evalReturn(tree->left,env);
		}

		else if (strcmp(tree->left->type,"IFSTATEMENT")==0){
			if (tree->left->right != NULL){ //return for if statement or else
				if (strcmp(tree->left->right->type,"RETURN")==0){
					if (checkCond(tree->left,env))
						return evalReturn(tree->left->right,env);
				}
				else if (checkCond(tree->left,env)) { //if a cond is met you have to skip the other else and else if statements
					eval(tree->left,env);
					tree = skipElse(tree->right);
					continue;
				}
			}
		}
		else if (strcmp(tree->left->type,"ELSE")==0){
			if (tree->left->left != NULL){
				if (strcmp(tree->left->left->type,"RETURN")==0)
					return evalReturn(tree->left->left,env);
				if (strcmp(tree->left->left->type,"IFSTATEMENT")==0){
					if (tree->right != NULL){ //return for if statement or else
						if (strcmp(tree->right->type,"RETURN")==0){
							if (checkCond(tree->left->left,env)) 
								return evalReturn(tree->left->left->right,env);
							}
						else if (checkCond(tree->left->left,env)) {
							eval(tree->left->left,env);
							tree = skipElse(tree->right);
							continue;
						}
					}
				}
			}
		}

		result = eval(tree->left,env);
		tree = tree->right;
	}
	return result;
}

lexeme *evalReturn(lexeme *tree, lexeme *env)
{
	return eval(tree->left,env);
}

lexeme *evalHeader(lexeme *tree, lexeme *env)
{
	return insert(tree,tree->left,env);
}

lexeme *evalDefine(lexeme *tree, lexeme *env)
{
	return insert(tree->left,tree->left->left,env);
}

lexeme *evalObject(lexeme *tree, lexeme *env)
{
	lexeme *obj = getThis(tree->left,env); //LHS of ARROW is the object
	return eval(tree->right, obj); //objects are environments
}

//closures hold the function and the env the function is in
lexeme *evalFuncDef(lexeme *tree, lexeme*env)
{
	lexeme *closure = cons("CLOSURE",env,tree);
	insert(tree->left,closure,env);
	//start body evaluation at main
	if (strcmp(tree->left->string, "main")==0) eval(tree->right, env); 
}

lexeme *evalFuncCall(lexeme *tree, lexeme *env)
{

	lexeme *closure = eval(tree->left, env);
	lexeme *args = getFuncCallArgs(tree);
	lexeme *eargs = evalArgs(args, env);

		if (strcmp(closure->type, "BUILTIN")==0) return closure->fval(eargs);//handles bultin functions
	
	else {
		lexeme *params = getClosureParams(closure);
		lexeme *body = getClosureBody(closure);
		lexeme *senv = getClosureEnv(closure);
		lexeme *xenv = extend(params, eargs, senv);
	
			lexeme *this = new_Lexeme(); //"this"'s value is the local env
			this->type = "THIS";
			this->string = "this";
	
		insert(this, xenv, xenv);
	
		return eval(body,xenv);
	}
}
lexeme *evalLambda(lexeme *tree, lexeme *env)
{
	return cons("CLOSURE",env,tree);
}
lexeme *evalArgs(lexeme *tree, lexeme *env) 
{
	if (tree == NULL) return NULL;
	else { 
		lexeme *e;
		lexeme *adde;
		
		e = eval(tree->left,env);
		adde = evalArgs(tree->right,env);
		return cons("VAL",e,adde);
	}
}

//-----------------ARRAYS----------------------------
lexeme *evalNewArray(lexeme *newArr, lexeme *env)
{
 	lexeme *arr = new_p_Lexeme("ARRAY");
 	arr->string = newArr->string;

	if (newArr->left == NULL) return insert(arr, NULL, env);

 	lexeme *size = eval(newArr->left,env);
 	lexeme *arrVal = new_p_Lexeme("ARRAY");
 	arrVal->aval = malloc(sizeof(lexeme *) * size->number);
 	arrVal->arrsize = size->number;

 	insert(arr, arrVal, env);
 	return newArr;
}
lexeme *evalGetArray(lexeme *index, lexeme *env)
{
	lexeme *arr = eval(index->left,env);
	lexeme *i = eval(index->left->left,env);
	return arr->aval[i->number];
}
lexeme *evalSetArray(lexeme *index, lexeme *value, lexeme *env)
{
	lexeme *arr = eval(index,env);
	lexeme *i = eval(index->left,env);
	arr->aval[i->number] = value;
}
lexeme *evalSetINITArray(lexeme *arr, lexeme *values, lexeme *size, lexeme *env)
{
	lexeme *array = eval(arr,env);
	int i = 0;
	
	while(i != size->number) {
		array->aval[i] = values->left;
		values = values->right;
		i++;
	}
}

lexeme *evalIfStatement(lexeme *tree, lexeme *env)
{
	lexeme *cond = eval(tree->left,env);
	lexeme *right = eval(tree->left->right,env);
	lexeme *left = eval(tree->left->left,env);

	if (compare(cond,right,left))  return eval(tree->right,env);
	else return NULL;
}

lexeme *evalElseStatement(lexeme *tree, lexeme *env)
{
	if (strcmp(tree->left->type,"IFSTATEMENT")==0) evalIfStatement(tree->left,env);
	return eval(tree->left,env);
}
lexeme *evalWhileLoop(lexeme *tree, lexeme *env)
{
	lexeme *cond = eval(tree->left,env);
	lexeme *right = eval(tree->left->right,env);
	lexeme *left = eval(tree->left->left,env);

	if (strcmp(cond->type,"GREATERTHAN")==0 || strcmp(cond->type,"LESSTHAN")==0){
			if (!compare(cond,right,left)) return NULL;
			else {
				eval(tree->right,env);
				evalWhileLoop(tree,env);
			}
	} 
	else{
		if (compare(cond,right,left)) {
			eval(tree->right,env);
			evalWhileLoop(tree,env);
		}
		else return NULL;
	}
}
//-------------------BUILT-IN FUNCTIONS--------------------------
lexeme *evalNewFile(lexeme *tree, lexeme *env)
{
	insert(tree,NULL,env);
}
lexeme *evalOpenFileForReading(lexeme *args)
{
	if (strcmp(args->left->type,"STRING")!=0){
		printf("No string provided in FILE read\n");
		exit(1);
	}
	lexeme *filename = args->left;
	lexeme *fp = new_p_Lexeme("FILE_POINTER  ");
	fp->file = fopen(filename->string,"read");
	return fp;
}
lexeme *evalReadInteger(lexeme *args)
{
	FILE *fp = args->left->file;
	int x = readInt(fp);
	
	lexeme *new = new_p_Lexeme("INTEGER");
	new->number = x;
	return new;
}
lexeme *evalReadReal(lexeme *args)
{
	FILE *fp = args->left->file;
	double x = readReal(fp);
	
	lexeme *new = new_p_Lexeme("REAL");
	new->dub = x;
	return new;
}
lexeme *evalReadString(lexeme *args)
{
	FILE *fp = args->left->file;
	char *string = readString(fp);

	lexeme *str = new_p_Lexeme("STRING");
	str->string = string;
	return str;
}
lexeme *evalReadLine(lexeme *args)
{
	FILE *fp = args->left->file;
	char *string = readLine(fp);	
	
	lexeme *str = new_p_Lexeme("STRING");
	str->string = string;
	return str;
}

lexeme *evalatEOF(lexeme *args)
{
	FILE *fp = args->left->file;
	if (feof(fp)){
			lexeme *b = new_p_Lexeme("INTEGER");
			b->number = 1;
		return b;
		}
	else {
		lexeme *b = new_p_Lexeme("INTEGER");
		b->number = 0;
		return b;
	}
	
}
lexeme *evalCloseFile(lexeme *args)
{
	FILE *fp = args->left->file;
	return new_p_Lexeme("TRUE");
}
lexeme *evalPrintln(lexeme *eargs){
	if (eargs == NULL) {
		printf("\n");
		return NULL;
	}
	else {
		if (strcmp(eargs->left->type,"INTEGER")==0) printf("%d", eargs->left->number);   
		else if (strcmp(eargs->left->type,"STRING")==0) printf("%s", eargs->left->string);
		else if (strcmp(eargs->left->type,"REAL")==0) printf("%lf", eargs->left->dub);
		evalPrintln(eargs->right);
	}
}
lexeme *evalPrint(lexeme *eargs){
	if (eargs == NULL) return NULL;
	else {
		if (strcmp(eargs->left->type,"INTEGER")==0) printf("%d", eargs->left->number);   
		else if (strcmp(eargs->left->type,"STRING")==0) printf("%s", eargs->left->string);
		else if (strcmp(eargs->left->type,"REAL")==0) printf("%lf", eargs->left->dub);
		evalPrint(eargs->right);
	}
}
lexeme *evalGetArgCount(lexeme *args){
	if (args != NULL) {
		printf("No arguments needed for argc()\n");
		exit(1);
	}
	lexeme *count = new_p_Lexeme("INTEGER");
	count->number = countCL;
}
lexeme *evalGetArg(lexeme *args){
	lexeme *index = args->left;

	if (index->number > countCL) {
		printf("Invalid argv access. argc = %d\n", countCL);
		exit(1);
	}
	lexeme *arg = new_p_Lexeme("STRING");
	arg->string = argsCL[index->number+2];
	return arg;
}
lexeme *GetArraySize(lexeme *arr)
{
	lexeme *size = new_p_Lexeme("INTEGER");
	size->number = arr->left->arrsize;
	return size;
}
//--------------------UTILITIES-----------------------------
//utility for evalBody
char *addString(char *str1, char *str2)
{
	int a = strlen(str1);
	int b = strlen(str2);
	char *string = malloc( (a+b) * sizeof(char));
	strcat(string,str1);
	strcat(string,str2);
	return string;
}
int checkCond(lexeme *tree, lexeme *env)
{
	lexeme *cond = eval(tree->left,env);
	lexeme *right = eval(tree->left->right,env);
	lexeme *left = eval(tree->left->left,env);
	return (compare(cond,right,left));
}
//utilty for evalIfStatment
int compare(lexeme *cond, lexeme *right, lexeme *left)
{
	if (right == NULL || left == NULL) {
		printf("Operand not defined in IFSTATEMENT\n");
		exit(1);
	}

	if (strcmp(cond->type,"EQUALS")==0){
		if (strcmp(left->type,"NULL")==0) return (strcmp(right->string,"")==0) ? 1 : 0;
		if (strcmp(right->type,"NULL")==0) return (strcmp(left->string,"")==0) ? 1 : 0;
		if (strcmp(left->type,right->type)!=0){
			printf("wrong comparison between types %s and %s.\n", left->type, right->type); 
			exit(1);
		}
		if (strcmp(left->type,"INTEGER")==0)  return (right->number == left->number);
		else if (strcmp(left->type,"REAL")==0)  return (right->dub == left->dub);
		else return (strcmp(right->string,left->string)==0) ? 1 : 0;
	}
	else if (strcmp(cond->type,"DOES_NOT_EQUAL")==0){
		if (strcmp(left->type,"NULL")==0) return (strcmp(right->string,"")!=0) ? 1 : 0;
		if (strcmp(right->type,"NULL")==0) return (strcmp(left->string,"")!=0) ? 1 : 0;
		if (strcmp(left->type,right->type)!=0){
			printf("wrong comparison between types %s and %s.\n", left->type, right->type); 
			exit(1);
		}
		if (strcmp(left->type,"INTEGER")==0)  return (right->number == left->number) ? 1 : 0;
		else if (strcmp(left->type,"REAL")==0)  return (right->dub != left->dub) ? 1 : 0;
		else return (strcmp(right->string,left->string)!=0) ? 1 : 0;
	}
	else if (strcmp(cond->type,"GREATERTHAN")==0){
		if (strcmp(left->type,right->type)!=0){
			printf("wrong comparison between types %s and %s.\n", left->type, right->type); 
			exit(1);
		}
		if (strcmp(left->type,"INTEGER")==0) return (left->number > right->number) ? 1 : 0;
		else if (strcmp(left->type,"REAL")==0)  return (left->dub > right->dub) ? 1 : 0;
	}
	else if (strcmp(cond->type,"LESSTHAN")==0){
		if (strcmp(left->type,right->type)!=0){
			printf("wrong comparison between types %s and %s.\n", left->type, right->type); 
			exit(1);
		}
		if (strcmp(left->type,"INTEGER")==0)  return (left->number < right->number) ? 1 : 0; 
		else if (strcmp(left->type,"REAL")==0)  return (left->dub < right->dub) ? 1 : 0;
	}
}
//utility for evalBody
lexeme *skipElse(lexeme *tree)
{
	if (tree == NULL) return NULL;
	else if (strcmp(tree->left->type,"ELSE")==0) skipElse(tree->right);
	else return tree;
}
//utility for evalReadInteger
int readInt(FILE *fp)
{
	int c;
	fscanf(fp,"%d",&c);
	return c;
}
//utility for evalReadReal
double readReal(FILE *fp)
{
	double c;
	fscanf(fp,"%lf",&c);
	return c;
}
//utility for evalReadLine
char *readLine(FILE *fp)
{
	char *str = malloc(256*sizeof(char));
	fgets(str,256,fp);
	return str;
}
//utility for evalReadString
char *readString(FILE *fp)
{
	char *str = malloc(256*sizeof(char));
	fscanf(fp,"%s",str);
	return str;
}
//utility for evalAssign(return list size)
int getArraySize(lexeme *arr, int size)
{
	if (arr == NULL) return size;
	++size;
	getArraySize(arr->right,size);
}
//utility for evalAssign(returns correct object member in case of multiple members)
lexeme *getVar(lexeme *tree)
{
	if (strcmp(tree->right->type,"ARROW")==0) getVar(tree->right);
	else return tree->right;
}
//utility for evalObject(returns the local env stored in this for access to object members)
lexeme *getThis(lexeme *tree, lexeme * env)
{
	return lookup(tree,env); //return "this" 
}
//utility for evalFuncCall
lexeme *getFuncCallArgs(lexeme *tree)
{
	return tree->left->left;
}
//utility for evalFuncCall
lexeme *getClosureParams(lexeme *closure) //THIS NEEDS TO SEND AN EVALUATED LIST OF PARAMS BACK
{
	return closure->right->left->left;
}
//utility for evalFuncCall
lexeme *getClosureBody(lexeme *closure)
{
	return closure->right->right;
}
//utility for evalFuncCall
lexeme *getClosureEnv(lexeme *closure)
{
	return closure->left;
}