#include <stdio.h>
#include "filesAssembler.h"
#define MAX_ARRAY 500 /*just a random length value*/





int main(int argc, char* argv[] )
{

    if (argc < 2)
    {
        printf("No files error");
        return 1;
    }
    return assembler(argv, argc);
}