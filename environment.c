#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"

lexeme *cons(char *type, lexeme *left, lexeme *right)
{
	lexeme *newEnv = new_p_Lexeme(type);   
	newEnv->left = left;
	newEnv->right = right;
	return newEnv;
}
void setcar(lexeme *list, lexeme *set) //set left node
{
	list->left = set;
}
void setcdr(lexeme *list, lexeme *set) //set right node
{
	list->right = set;
}

lexeme *car(lexeme *env)
{
	if (env == NULL) return NULL;
	return env->left;
}
lexeme *cdr(lexeme *env)
{
	if (env == NULL) return NULL;
	return env->right;
}
//-------------------------------------------------
int sameVar(char *variable, lexeme *vars) 
{
	return strcmp(variable,vars->string);
}

int sameType(lexeme *value, lexeme *vals)
{
	if (value == NULL || vals == NULL) return 0;
	else if (strcmp(value->type,"REAL")==0 || strcmp(value->type,"INTEGER")==0) return 0;
	else if (strcmp(value->type,"INTEGER")==0 || strcmp(value->type,"REAL")==0) return 0;
	else return strcmp(value->type,vals->type);
}

lexeme *create()
{
	//printf("---CREATED NEW ENVIRONMENT---\n");
	return cons("ENV", cons("TABLE",NULL,NULL), NULL);
}

lexeme *lookup(lexeme *variable, lexeme *env)
{
 	//printf("---LOOKING FOR VARIABLE: %s\n", variable->string);
	while (env != NULL)
	{
		lexeme *table = car(env);
		lexeme *vars = car(table); //first table entry on variable side
		lexeme *vals = cdr(table); //first table entry on value side
		
		while (vars != NULL)
		{
			if (sameVar(variable->string, car(vars))==0) {
				//printf("     located variable: %s\n", variable->string);
				return car(vals);
			}
		vars = cdr(vars);
		vals = cdr(vals);
		}
		env = cdr(env);
	}
	
	printf("variable %s is undefined\n", variable->string);
	exit(1);	
} 

lexeme *update(lexeme *variable, lexeme *value, lexeme *env)
{
	//printf("---UPDATING VARIABLE: %s\n", variable->string);
	while (env != NULL)
	{
		lexeme *table = car(env);
		lexeme *vars = car(table); //first table entry on variable side
		lexeme *vals = cdr(table); //first table entry on value side

		while (vars != NULL)
		{
			if ( (sameVar(variable->string,car(vars))==0) ) {
			 	if (sameType(value,car(vals))==0) {
					vals->left = value;//seg fault is here
					//printf("     ");
					//printupdate(car(vars),car(vals));
					return car(vals);
				}
				else {
					printf("Cannot Update! Invalid Type\n");
					return car(vals);
					}	
			}
		
		vars = cdr(vars);
		vals = cdr(vals);
		}
		env = cdr(env);
	}
	
	printf("variable %s is undefined\n", variable->string);
	exit(1);
}

lexeme *insert(lexeme *variable, lexeme *value, lexeme *env)
{
	lexeme *table = car(env);
	setcar(table,cons("VAR",variable,car(table)));
	setcdr(table,cons("VAL",value,cdr(table)));
	//printf("     inserting variable and value: ");
	//print(variable,value);
	return value;
}

lexeme *extend(lexeme *variables, lexeme *values, lexeme *env)
{	
	lexeme *newEnv = cons("ENV", cons("TABLE",variables,values), env);
	//printf("---EXTENDING ENVIRONMENT---\n");
	//display(newEnv);
	return newEnv;
}
void printupdate(lexeme *vars, lexeme * vals)
{	
	if (vals == NULL) printf("updated %s's value to NULL\n", vars->string);
	else if (strcmp(vals->type,"ENV")==0)  printf("updated %s's value to ENV\n", vars->string);
	else if (strcmp(vals->type,"CLOSURE")==0)  printf("updated %s's value to CLOSURE\n", vars->string);
	else if (strcmp(vals->type,"STRING")==0)  printf("updated %s's value to %s\n", vars->string, vals->string);
	else if (strcmp(vals->type,"INTEGER")==0) printf("updated %s's value to %d\n", vars->string, vals->number);
	else if (strcmp(vals->type,"REAL")==0) printf("updated %s's value to %lf\n", vars->string, vals->dub);
}
void print(lexeme *vars, lexeme * vals)
{
	if (vals == NULL) printf("%s NULL\n", vars->string);
	else if (strcmp(vars->type,"THIS")==0)  printf("%s xenv\n", vars->type);
	else if (strcmp(vars->type,"ARRAY")==0)  printf("%s ARRAY\n", vars->string);
	else if (strcmp(vars->type,"HEADER")==0)  printf("%s %s\n", vars->type, vals->string);
	else if (strcmp(vals->type,"CLOSURE")==0)  printf("%s %s\n", vars->string, vals->type);
	else if (strcmp(vals->type,"BUILTIN")==0)  printf("%s %s\n", vars->string, vals->type);
	else if (strcmp(vals->type,"STRING")==0)  printf("%s %s\n", vars->string, vals->string);
	else if (strcmp(vals->type,"INTEGER")==0) printf("%s %d\n", vars->string, vals->number);
	else if (strcmp(vals->type,"REAL")==0) printf("%s %lf\n", vars->string, vals->dub);
}
void display(lexeme *env)
{
	printf("---DISPLAYING LOCAL AND GLOBAL ENVIRONMENTS---\n");
	printf("     Local environment:\n");

lexeme *dis = env;

	while (dis != NULL)
	{
		lexeme *table = car(dis);
		lexeme *vars = car(table); //first table entry on variable side
		lexeme *vals = cdr(table); //first table entry on value side
		
		if ( car(car(dis)) == NULL && cdr(car(dis)) == NULL ) { //check if empty
			printf("   Environment empty.\n");
		}
		else 
		{
			while (vars != NULL)
			{
				printf("       ");
				print(car(vars), car(vals));
				vars = cdr(vars);
				vals = cdr(vals);
			}
		}
		dis = cdr(dis);
		if (dis != NULL) printf("     Global environment:\n");
	}
}
void displayLocal(lexeme *env)
{
	printf("---DISPLAYING LOCAL ENVIRONMENT---\n");

	if ( car(car(env)) == NULL && cdr(car(env)) == NULL ) {
		printf("   Environment empty.\n");
		return;
	}

	lexeme *dis = env;

		lexeme *table = car(dis);
		lexeme *vars = car(table); //first table entry on variable side
		lexeme *vals = cdr(table); //first table entry on value side
		while (vars != NULL)
		{
			printf("     ");
			print(car(vars), car(vals));
		
		vars = cdr(vars);
		vals = cdr(vals);
		}
		
}
/*int main()
{
	lexeme *env = create();

	//variables
	lexeme *a = new_Lexeme();
	a->type = "VARIABLE";
	a->string = "a";
	lexeme *b = new_Lexeme();
	b->type = "VARIABLE";
	b->string = "b";
	lexeme *c = new_Lexeme();
	c->type = "VARIABLE";
	c->string = "c";

	//values
	lexeme *a1 = new_Lexeme();
	a1->type = "INTEGER";
	a1->number = 9;
	lexeme *b1 = new_Lexeme();
	b1->type = "REAL";
	b1->dub = 2.5;
	lexeme *c1 = new_Lexeme();
	c1->type = "STRING";
	c1->string = "hello";

	insert(a,a1,env);
	insert(b,b1,env);
	insert(c,c1,env);

     //ENVIRONMENT 1
//----------------------------------------------------
	displayLocal(env);
	printf("\n");
	lexeme *env2 = create();

	//variables
	lexeme *num = new_Lexeme();
	num->type = "VARIABLE";
	num->string = "num";
	lexeme *dub = new_Lexeme();
	dub->type = "VARIABLE";
	dub->string = "dub";
	lexeme *var = new_Lexeme();
	var->type = "VARIABLE";
	var->string = "string";

	//values
	lexeme *num1 = new_Lexeme();
	num1->type = "INTEGER";
	num1->number = 1000000;
	lexeme *dub1 = new_Lexeme();
	dub1->type = "REAL";
	dub1->dub = 69.69;
	lexeme *var1 = new_Lexeme();
	var1->type = "STRING";
	var1->string = "wats up";

	insert(num,num1,env2);
	insert(dub,dub1,env2);
	insert(var,var1,env2);

	//ENVIRONMENT 2

	displayLocal(env2);
//----------------------------------------------------
printf("\n");
	lexeme *find = lookup(a,env);
	update(num, find, env2);
	update(dub, b1,env2);
	update(c, var1,env);

printf("\n");
	lexeme *tab = car(env2);
	lexeme *newEnv = extend(car(tab), cdr(tab), env);
	display(newEnv);

	return 0;

}*/
