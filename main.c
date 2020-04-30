#include <stdio.h>
#include "filesAssembler.h"




int main(int argc, char const *argv[] )
{

    if (argc < 2)
    {
        printf("No files error");
        return 1;
    }
    return assembler(argv, argc);
}
