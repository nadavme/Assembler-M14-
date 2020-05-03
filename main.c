#include <stdio.h>
#include "filesAssembler.h"
#define MAX_ARRAY 500 /*just a random length value*/
#define MAX_LINE 80

/*a global variables needed for the assembler: */
short int commands_array[MAX_ARRAY]; /* this array is the commands table, declared globally. */
int wordsWithoutARE[MAX_ARRAY];/*this global array will contain the addresses of words which has at least 1 operand in 
direct addressing (has an operand represented as label), this words also doesnt has a value yet, because the label might
not have defined yet.*/



int main(int argc, char const *argv[] )
{

    if (argc < 2)
    {
        printf("No files error");
        return 1;
    }
    return assembler(argv, argc);
}