#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dynamicArray.h"


/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
	char *end;
	double returnNum;

	if(strcmp(s, "0") == 0)
	{
		*num = 0;
		return 1;
	}
	else 
	{
		returnNum = strtod(s, &end);
		/* If there's anythin in end, it's bad */
		if((returnNum != 0.0) && (strcmp(end, "") == 0))
		{
			*num = returnNum;
			return 1;
		}
	}
	return 0;  //if got here, it was not a number
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their sum is pushed back onto the stack.
*/
void add (struct DynArr *stack)
{
	double item1, item2;
	if (sizeDynArr(stack)>=2)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		item2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, item1 + item2);
	}
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
	double item1, item2;
	if (sizeDynArr(stack) >= 2)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		item2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, item2 - item1);
	}
}

/*	param: stack the stack being manipulated
	pre: the stack contains at least two elements
	post: the top two elements are popped and 
	their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
	double item1, item2;
	if (sizeDynArr(stack) >= 2)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		item2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, item2 / item1);
	}
}

void multiply(struct DynArr *stack)
{
	double item1, item2;
	if (sizeDynArr(stack) >= 2)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		item2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, item1 * item2);
	}
}

void power(struct DynArr *stack)
{
	double item1, item2;
	if (sizeDynArr(stack) >= 2)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		item2 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, pow(item2, item1));
	}
}

void squaring(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, item1 * item1);
	}
}

void cubing(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, item1 * item1 * item1);
	}
}

void absolute(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, abs(item1));
	}
}

void sqroot(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, sqrt(item1));
	}
}

void exponential(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, exp(item1));
	}
}

void natlog(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, log(item1));
	}
}

void logarithm(struct DynArr *stack)
{
	double item1;
	if (sizeDynArr(stack) >= 1)
	{
		item1 = topDynArr(stack);
		popDynArr(stack);
		pushDynArr(stack, log10(item1));
	}
}

double calculate(int numInputTokens, char **inputString)
{
	int i;
	double result = 0.0;
	char *s;
	struct DynArr *stack;

	//set up the stack
	stack = createDynArr(20);

	// start at 1 to skip the name of the calculator calc
	for(i=1;i < numInputTokens;i++) 
	{
		s = inputString[i];

		// Hint: General algorithm:
		// (1) Check if the string s is in the list of operators.
		//   (1a) If it is, perform corresponding operations.
		//   (1b) Otherwise, check if s is a number.
		//     (1b - I) If s is not a number, produce an error.
		//     (1b - II) If s is a number, push it onto the stack

		if(strcmp(s, "+") == 0)
			add(stack);
		else if(strcmp(s,"-") == 0)
			subtract(stack);
		else if(strcmp(s, "/") == 0)
			divide(stack);
		else if(strcmp(s, "x") == 0)
			multiply(stack);
		else if(strcmp(s, "^") == 0)
			power(stack);
		else if(strcmp(s, "^2") == 0)
			squaring(stack);
		else if(strcmp(s, "^3") == 0)
			cubing(stack);
		else if(strcmp(s, "abs") == 0)
			absolute(stack);
		else if(strcmp(s, "sqrt") == 0)
			sqroot(stack);
		else if(strcmp(s, "exp") == 0)
			exponential(stack);
		else if(strcmp(s, "ln") == 0)
			natlog(stack);
		else if(strcmp(s, "log") == 0)
			logarithm(stack);
		else 
		{
			// FIXME: You need to develop the code here (when s is not an operator)
			// Remember to deal with special values ("pi" and "e")

			if (isNumber(s, &result) == 1)
			{
				pushDynArr(stack, result);
			}
			else if (strcmp(s, "pi") == 0)
			{
				result = 3.14159265;
				pushDynArr(stack, result);
			}
			else if (strcmp(s, "e") == 0)
			{
				result = 2.7182818;
				pushDynArr(stack, result);
			}
			else
			{
				printf(" Unknown element found %s\n", s);
			}
		}
	}	//end for 

	/* FIXME: You will write this part of the function (2 steps below) 
	 * (1) Check if everything looks OK and produce an error if needed.
	 * (2) Store the final value in result and print it out.
	 */
	
	result = topDynArr(stack);
	return result;
}

int main(int argc , char** argv)
{
	// assume each argument is contained in the argv array
	// argc-1 determines the number of operands + operators
	if (argc == 1)
		return 0;

	double result = 0;

	result = calculate(argc, argv);
	
	printf(" %f\n", result);

	return 0;
}
