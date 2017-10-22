/* CS261- Assignment 1 - Q.1*/
/* Name: Allan Reitan
 * Date: 6/30/2015
 * Solution description: Generating 10 random student IDs and Test Scores.
 *	Then displaying and rending information about the Students.
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
	struct student *myStudents = malloc(10 * sizeof(struct student));

     /*return the pointer*/
	return myStudents;
}

int DetectIDs(struct student* students)
{
	// Function will count up the allocated IDs and the total for all ten should equal (n/2) * (n+1)
	int value = 0;

	for (int i = 0; i < 10; i++)
	{
		value += students[i].id;
	}

	return value;
}

void generate(struct student* students){
     /*Generate random ID and scores for ten students, ID being between 1 and 10, scores between 0 and 100*/
	int IDval;
	
	do
	{
		IDval = rand() % 10 + 1; //Generate Number between 1 and 10

		if (students[IDval-1].id != IDval)
		{
			students[IDval - 1].id = IDval;
			students[IDval - 1].score = rand() % 100 + 1; //Generate Exam Score between 1 and 100
		}

	} while (DetectIDs(students) != 55);

	return;
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
	printf("Here are 10 Random Student IDs and their Exam scores:\n\n");

	for (int i = 0; i < 10; i++)
	{
		printf("%i %i\n", students[i].id, students[i].score);
	}

	return;
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the ten students*/
	int MinScore, MaxScore, AvgScore;

	for (int i = 0; i < 10; i++)
	{
		switch (i)
		{
		case 0:
			MinScore = MaxScore = students[i].score;
			AvgScore = students[i].score;
			break;
		default:
			if (students[i].score<MinScore)
			{
				MinScore = students[i].score;
			}
			else if (students[i].score>MaxScore)
			{
				MaxScore = students[i].score;
			}
			else
			{

			}
			AvgScore += students[i].score;
			break;
		}
	}
	// Compute AvgScore after loop is concluded.
	AvgScore /= 10;
    
	// Render the output
	printf("\n");
	printf("The Min Score is: %i\n", MinScore);
	printf("The Max Score is: %i\n", MaxScore);
	printf("The Avg Score is: %i\n", AvgScore);

	return;
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
	free(stud);

	return;
}

int main(){
	srand(6000); // Populating the Seed number.
    struct student* stud = NULL;
    
    /*call allocate*/
	stud = allocate();

    /*call generate*/
	generate(stud);

    /*call output*/
	output(stud);

    /*call summary*/
	summary(stud);

    /*call deallocate*/
	deallocate(stud);

    return 0;
}
