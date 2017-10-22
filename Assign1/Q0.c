/* CS261- Assignment 1 - Q. 0*/
/* Name: Allan Reitan
 * Date: 6/28/2015
 * Solution description: Use a pointer to pass a value into a function.  
 *	Then print the actual value.
 */
 
#include <stdio.h>
#include <stdlib.h>

void fooA(int* iptr){
     /*Print the value pointed to by iptr*/
	printf("The value stored in iptr is: %i\n", *iptr);
     /*Print the address pointed to by iptr*/
	printf("The address located IN iptr is: %u\n", iptr);
     /*Print the address of iptr itself*/
	printf("The address of iptr is: %u\n", &iptr);
	return;
}

int main(){
    
    /*declare an integer x*/
	int x = 325;
    
    /*print the address of x*/
	printf(" The address of variable x is: %u\n", &x);
    
    /*Call fooA() with the address of x*/
	fooA(&x);

    /*print the value of x*/
	printf(" The value of variable x is: %i\n", x);
    
    return 0;
}
