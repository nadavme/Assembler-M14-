//
// Created by nadav on 04/02/2020.
//

#include "aidTools.h"


int bin_to_octal(int binaryNum)
{
long int octalnum = 0, j = 1, remainder;
 
    while (binarynum != 0)
    {
        remainder = binarynum % 10;
        octalnum = octalnum + remainder * j;
        j = j * 2;
        binarynum = binarynum / 10;
    }
    printf("Equivalent octal value: %lo", octalnum);
    return 0;
}

int main()
{
    long int num = 10;
    printf("the number in binary is - %d and in octal - %d\n", (int)num, (int)bin_to_octal(num));
    return 0;
}

