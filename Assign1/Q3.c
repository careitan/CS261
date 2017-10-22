/* CS261- Assignment 1 - Q.3*/
/* Name: Allan Reitan
 * Date: 6/28/2015
 * Solution description: Create a random array and then sort that array.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

// Create bool as a typedef in C in stead of #include <stdbool.h>
typedef int bool;
#define true 1
#define false 0

void sort(int* number, int n){
     /*Sort the given array number , of length n*/ 
	bool Swapped = false;

	do
	{
		Swapped = false;

		for (int i = 0; i < n-1; i++)
		{
			if (number[i] > number[i+1])
			{
				int j;

				// Swap the numbers
				j = number[i + 1];
				number[i + 1] = number[i];
				number[i] = j;

				Swapped = true;
			}
		}
	} while (Swapped);

}

int main(){
	srand(8000);
    /*Declare an integer n and assign it a value of 20.*/
	int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
	int* MyNumbers = malloc(n * sizeof(int));
    
    /*Fill this array with random numbers, using rand().*/
	for (int i = 0; i < n; i++)
	{
		MyNumbers[i] = rand() % 200 + 1;
	}
    
    /*Print the contents of the array.*/
	printf("Here is your original array of numbers:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%i; ", MyNumbers[i]);
	}
	printf("\n\n");

    /*Pass this array along with n to the sort() function of part a.*/
	sort(MyNumbers, n);

    /*Print the contents of the array.*/    
	printf("PRESTO! Here is your sorted array of numbers:\n");
	for (int i = 0; i < n; i++)
	{
		printf("%i; ", MyNumbers[i]);
	}
	printf("\n");
    return 0;
}
