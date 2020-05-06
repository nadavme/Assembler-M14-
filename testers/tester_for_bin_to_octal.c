
#include "aidTools.h" 
#include <stdio.h>
#include <math.h>


int bin_to_octal(int binaryNum)/*this function converts a number from binary base to octal base, I used a method that we have learned in class.*/
{
    int i = 0,j = 0;
    int sum = 0;
    int midSum = 0;

    while(binaryNum!=0)
    {
		midSum = 0;
        for (j = 0; j < 3; j++)/*the function basically looks at the 3 most right bits, and check for each bit from right to left - if it's on we add 1 
		multyplied by 2 to the power of the place of the bit (0/1/2) to midSum.*/
        {
            if( binaryNum&1 == 1)
             {
                midSum =midSum + (int)pow(2,j);
             }
        binaryNum = binaryNum>>1;
        }
        sum = sum+ (int)midSum*pow(10,i);/*we add midSum that fit the right digit*/
        i++;

    }
    return sum;
}

void reverse (char s[])
 /* reverse character string, a function from the book, ex. 1-19*/
{
	 int  string_length;
	 int i;
	 char tmp; /*  step  1:  calculate  length  of s */
	 string_length = 0;
	 while  (s[string_length]  !=  '\0')
		 string_length = string_length + 1 ;
		 /* step 2: reverse string */ 
	for(i=0;i<string_length/2; i++) 
	{
		tmp=s[i];
		s[i]=s[string_length-i-1];
		s[string_length-i-1]=tmp ;
	}
}

int translate_dec_hex(char dec[]) /*requested function*/
{
	char binNum[100]= {'0','\0'}; /*creating a char array (a string) which will express the binary 	       number.  the first cell in the array contains the char 0 representation, and all other cells in the 			array 	contain of the integer 0.*/

	unsigned int decInt = strtoul(dec,NULL,10);/*converting the decimal number (string) to int*/
	int i = 0;
	while (decInt != 0)
	{
		binNum[i] ='0' + decInt%2; /*collecting the remainders from devision by 2 at the array*/
		decInt = decInt/2; /*deviding by 2 (basically cutting out the fractions)*/
		i++;		
	}
	
	reverse(binNum); /*we have to reverse the array to get the binary number, as described at class*/
		printf("%s\n",binNum);/*printing the binary number*/
	
	
	return 0;
}




int main()/*to compile it I need to run gcc aidTools.c -lm -o a.out
						and than ./a.out*/
{
    int num = 126;

    char str[12];
    sprintf(str, "%d", num);

    printf("the number %d in binary is -\n" ,num);
    translate_dec_hex(str);
    printf("\n and in octal - %d\n", (int)bin_to_octal(num));
    return 0;
}

