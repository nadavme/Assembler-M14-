//
// Created by nadav on 04/02/2020.
//

#include "aidTools.h" 

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


int dec_to_bin(char dec[]) /*requested function*/
{
	char binNum[MAX_DIGITS_BIN]= {'0','\0'}; /*creating a char array (a string) which will express the binary 	       number.  the first cell in the array contains the char 0 representation, and all other cells in the 			array 	contain of the integer 0.*/
    int  string_length;
	int i;
	char tmp; 

	unsigned int decInt = strtoul(dec,NULL,10);/*converting the decimal number (string) to int*/
	i = 0;
	while (decInt != 0)
	{
		binNum[i] ='0' + decInt%2; /*collecting the remainders from devision by 2 at the array*/
		decInt = decInt/2; /*deviding by 2 (basically cutting out the fractions)*/
		i++;		
	}

     /* step 2: reverse string */
	 string_length = 0;
	 while  (binNum[string_length]  !=  '\0')
		 string_length = string_length + 1 ;
		  
	for(i=0;i<string_length/2; i++) 
	{
		tmp=binNum[i];
		binNum[i]=binNum[string_length-i-1];
		binNum[string_length-i-1]=tmp ;
	}
    
		printf("%s\n",binNum);/*printing the binary number*/
	
	
	return 0;
}
