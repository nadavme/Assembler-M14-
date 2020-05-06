#include <stdio.h>
#include "filesAssembler.h"
#define MAX_ARRAY 500 /*just a random length value*/
#define MAX_LINE 80

/*a global variables needed for the assembler: */
short int commands_array[MAX_ARRAY]; /* this array is the commands table, declared globally. */




int main(int argc, char const *argv[] )
{

    if (argc < 2)
    {
        printf("No files error");
        return 1;
    }
    return assembler(argv, argc);
}