/* CS261- Assignment 1 - Q.4*/
/* Name:  Allan Reitan
 * Date:  6/28/2015
 * Solution description: 
 *
 */
 
#include <stdio.h>
#include <stdlib.h>

// Create bool as a typedef in C in stead of #include <stdbool.h>
typedef int bool;
#define true 1
#define false 0

struct student{
	int id;
	int score;
};

void sort(struct student* students, int n){
     /*Sort the n students based on their score*/ 
	bool Swapped = false;

	do
	{
		Swapped = false;

		for (int i = 0; i < n - 1; i++)
		{
			if (students[i].score > students[i + 1].score)
			{
				struct student j;

				// Swap the numbers
				j = students[i + 1];
				students[i + 1] = students[i];
				students[i] = j;

				Swapped = true;
			}
		}
	} while (Swapped);
}

int DetectIDs(struct student* students, int N)
{
	// Function will count up the allocated IDs and the total for all ten should equal (n/2) * (n+1)
	int value = 0;

	for (int i = 0; i < N; i++)
	{
		value += students[i].id;
	}

	return value;
}

void generate(struct student* students, int N){
	/*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	int IDval;
	int SumSeries;

	// Determine if N is even or odd
	if (N%2==0)
	{
		SumSeries = (N + 1)*(N / 2);
	}
	else
	{
		SumSeries = (N + 1)*(N / 2)+((N+1)/2); // Accounting for the middle number in the series.
	}

	do
	{
		IDval = rand() % N + 1; //Generate Number between 1 and N

		if (students[IDval - 1].id != IDval)
		{
			students[IDval - 1].id = IDval;
			students[IDval - 1].score = rand() % 100 + 1; //Generate Exam Score between 1 and 100
		}

	} while (DetectIDs(students, N) != SumSeries);

	return;
}

void output(struct student* students, int N){
	/*Output information about the ten students in the format:
	ID1 Score1
	ID2 score2
	ID3 score3
	...
	ID10 score10*/
	printf("\nHere are %i Random Student IDs and their Exam scores:\n", N);

	for (int i = 0; i < N; i++)
	{
		printf("%i %i\n", students[i].id, students[i].score);
	}

	return;
}


int main(){
	srand(7500);
    /*Declare an integer n and assign it a value.*/
	int n = 24;
    
    /*Allocate memory for n students using malloc.*/
	struct student *myStudents = malloc(n * sizeof(struct student));
    
    /*Generate random IDs and scores for the n students, using rand().*/
	generate(myStudents, n);

    /*Print the contents of the array of n students.*/
	output(myStudents, n);

    /*Pass this array along with n to the sort() function*/
	sort(myStudents, n);

    /*Print the contents of the array of n students.*/
	output(myStudents, n);

    return 0;
}
