/* CS261- Assignment 1 - Q.5*/
/* Name:  Allan Reitan
 * Date:  6/28/2015
 * Solution description:  Sticky Caps conversion of a string of characters.
 */
 
#define _CRT_SECURE_NO_DEPRECATE /* Allows scanf instead of scanf_s in Microsoft Visual C++ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/*converts ch to upper case, assuming it is in lower case currently*/
char toUpperCase(char ch){
     return ch-'a'+'A';
}

/*converts ch to lower case, assuming it is in upper case currently*/
char toLowerCase(char ch){
     return ch-'A'+'a';
}

void sticky(char* word){
     /*Convert to sticky caps*/
	int i = 0;
	char c;

	while (word[i] != '\0')
	{
		c = word[i];
		
		if (i%2==0)
		{
			word[i] = toupper(c);
		}
		else
		{
			word[i] = tolower(c);
		}

		i++;
	}
}

int main(){
    /*Read word from the keyboard using scanf*/
	char MyWord[1000];
	printf("Please give me a word for the Sticky Caps: ");
	scanf("%s", MyWord);

    /*Call sticky*/
	sticky(MyWord);

    /*Print the new word*/
	printf("\n Here is your word using Sticky Caps: ");
	int i = 0;

	while (MyWord[i] != '\0')
	{
		putchar(MyWord[i]);
		i++;
	}
	printf("\n");
    return 0;
}
