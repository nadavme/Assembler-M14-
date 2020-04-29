#include <stdio.h>
#include "filesAssembler.h"

#define MAX_ARRAY 600 /*just a random length value*/
short int instructions_array[MAX_ARRAY]; /* this array is the instructions table, declared globally. */

int main(int argc, char **argv )
{
    int numOfFiles;
    char** filesToInterpret;
    

    return assembler(filesToInterpret = argv, numOfFiles = argc);
}
