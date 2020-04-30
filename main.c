#include <stdio.h>
#include "filesAssembler.h"
#define MAX_ARRAY 600 /*just a random length value*/
#define MAX_LINE 80

short int instructions_array[MAX_ARRAY]; /* this array is the instructions table, declared globally. */



int main(int argc, char const *argv[] )
{

    if (argc < 2)
    {
        printf("No files error");
        return 1;
    }
    return assembler(argv, argc);
}
