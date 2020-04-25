#include "aidTools.h"
#include <stdio.h>

int main()
{
	char decNum[MAX_DIGITS_DEC] = {0};/*initializing a string(representing the decimal number) with maximum 10 		digits*/
	printf("Hello!\nPlease enter a decimal number:\n");/*friendly message for user*/
	scanf ("%s", decNum);/*input from user*/
	printf("\ngreat...\nyour number expressed in the base-2 numeral system is - ");
	dec_to_bin(decNum);
	


	return EXIT_SUCCESS;
}