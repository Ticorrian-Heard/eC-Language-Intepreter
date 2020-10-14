#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"
int countCL;
char *argsCL[50];

int main(int argc, char *argv[]) 
{
	countCL = argc - 2;
	memcpy(argsCL,argv,sizeof(argsCL));
	
	lexeme *env = create();
	addBuiltins(env);
	lexeme *tree = parser(argv[1]);
	//prettyPrinter(tree);
	eval(tree,env);
	return 0;
}