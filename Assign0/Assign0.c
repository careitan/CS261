/* CS261- Assignment 0 - Assign0.c */
/* Name: Allan Reitan
* Date: 6/28/2015
* Solution description: Basic I/O demonstration of concepts
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
	//Declare Variables
	int i = 0;

	//Begin Routine
	printf("Please give me an Integer value: ");
	scanf("%i", &i);

	if (i % 2 == 0)
	{
		printf("\n Your integer is an EVEN number.\n");
	}
	else
	{
		printf("\n Your integer is an ODD number.\n");
	}
	return 0;
}