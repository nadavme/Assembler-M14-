#include <stdio.h>
#include "filesAssembler.h"




int main(int argc, char **argv )
{
    int numOfFiles;
    char** filesToInterpret;

    return assembler(filesToInterpret = argv, numOfFiles = argc);
}
