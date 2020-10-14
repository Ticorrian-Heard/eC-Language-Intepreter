make: 

conditionalsx: conditionals.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run conditionals.txt WATS UPPPPPP
arraysx: arrays.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run arrays.txt hello there
recursionx: recursion.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run recursion.txt
iterationx: iteration.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run iteration.txt
lambdax: lambda.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run lambda.txt
objectsx: objects.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run objects.txt
functionsx: functions.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run functions.txt
error1x: error1.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run error1.txt WATS UPPPPPP
error2x: error2.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run error2.txt hello there
error3x: error3.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run error3.txt
error4x: error4.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run error4.txt
error5x: error5.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run error5.txt
problemx: problem.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c main.c evaluator.c evaluatorFunc.c
	run problem.txt problemtest.txt

conditionals: conditionals.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run conditionals.txt WATS UPPPPPP
arrays: arrays.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run arrays.txt hello there
recursion: recursion.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run recursion.txt
iteration: iteration.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run iteration.txt
lambda: lambda.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run lambda.txt
objects: objects.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run objects.txt
functions: functions.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run functions.txt
error1: error1.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run error1.txt WATS UPPPPPP
error2: error2.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run error2.txt hello there
error3: error3.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run error3.txt
error4: error4.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run error4.txt
error5: error5.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c
	run error5.txt
problem: problem.txt
	gcc -o run scanner.c environment.c pending.c innerEnv.c outerEnv.c parser.c prettyPrinter.c ppmain.c 
	run problem.txt

clean:
	rm -f *.o 