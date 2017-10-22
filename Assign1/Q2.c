/* CS261- Assignment 1 - Q.2*/
/* Name:  Allan Reitan
 * Date:  6/28/2015
 * Solution description: Having fun with passing pointers to a function.
 */
 
#include <stdio.h>
#include <stdlib.h>

int foo(int* a, int* b, int c){
    /*Set a to double its original value*/
	*a *= 2;

    /*Set b to half its original value*/
	*b /= 2;

    /*Assign a+b to c*/
	c = *a + *b;

    /*Return c*/
	return c;
}

int main(){
    /*Declare three integers x,y and z and initialize them to 5, 6, 7 respectively*/
	int x, y, z;
	x = 5;
	y = 6;
	z = 7;

    /*Print the values of x, y and z*/
	printf("Currently the variables are x = %i, y = %i, z = %i\n", x, y, z);
    
    /*Call foo() appropriately, passing x,y,z as parameters*/
    /*Print the value returned by foo*/
	printf("After invoking foo() the return value is: %i\n", foo(&x, &y, z));

    /*Print the values of x, y and z again*/
	printf("Currently the variables are x = %i, y = %i, z = %i\n", x, y, z);

    /*Is the return value different than the value of z?  Yes it should be.
	Why?  Because we just printed the return value of foo() and did not assign it to a variable.
	You would need to use z = foo(&x, &y, z) to actually change the value of foo()*/

    return 0;
}
    
    
