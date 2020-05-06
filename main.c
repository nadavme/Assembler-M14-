#include <stdio.h>
#include "filesAssembler.h"
#define MAX_ARRAY 500 /*just a random length value*/


/*a global variables needed for the assembler: */
short int commands_array[MAX_ARRAY]; /* this array is the commands table, declared globally. */




int main(int argc, char* argv[] )
{

    if (argc < 2)
    {
        printf("No files error");
        return 1;
    }
    return assembler(argv, argc);
}