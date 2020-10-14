#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "proglan.h"
int main(int argc, char *argv[]) 
{	
	printf("Starting Pretty Printer...\n");
	lexeme *tree = parser(argv[1]);
    printf("\n");
	prettyPrinter(tree);
	return 0;
}