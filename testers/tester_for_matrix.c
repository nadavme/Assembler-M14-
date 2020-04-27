
#include "permanantTables.h"


void opTableInit()\
{\
    opTable matrix[16];\
    \
    matrix[0].codeName = "mov";\
    matrix[0].word = (unsigned short)2032; \
    \
    matrix[1].codeName = "cmp";\
    matrix[1].word = (unsigned short)4088; \
    \
    matrix[2].codeName = "add";\
    matrix[2].word = (unsigned short)6128; \
    \
    matrix[3].codeName = "sub";\
    matrix[3].word =(unsigned short) 8176; \
    \
    matrix[4].codeName = "lea";\
    matrix[4].word =(unsigned short) 8560; \
    \
    matrix[5].codeName = "clr";\
    matrix[5].word = (unsigned short)10352; \
    \
    matrix[6].codeName = "not";\
    matrix[6].word =(unsigned short) 12400; \
    \
    matrix[7].codeName = "inc";\
    matrix[7].word = (unsigned short)14448; \
    \
    matrix[8].codeName = "dec";\
    matrix[8].word =(unsigned short) 16496; \
    \
    matrix[9].codeName = "jmp";\
    matrix[9].word = (unsigned short)18480; \
    \
    matrix[10].codeName = "bne";\
    matrix[10].word = (unsigned short)20528; \
    \
    matrix[11].codeName = "red";\
    matrix[11].word = (unsigned short)22640; \
    \
    matrix[12].codeName = "prn";\
    matrix[12].word = (unsigned short)24696; \
    \
    matrix[13].codeName = "jsr";\
    matrix[13].word =(unsigned short) 26672; \
    \
    matrix[14].codeName = "rts";\
    matrix[14].word = (unsigned short)28672; \
    \
    matrix[15].codeName = "stop";\
    matrix[15].word = (unsigned short)30720; \
    \ 
} 

char validInstructions[16][4] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red",
                                     "prn", "jsr", "rts", "stop"};

void printBits(size_t const size, void const * const ptr)
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

int main()
{
    int i = 0;
    
    
    struct opTable matrix[16];
    
    matrix[0].codeName = "mov";
    matrix[0].word = (unsigned short)2032;
    
    
    matrix[1].codeName = "cmp";
    matrix[1].word = (unsigned short)4088; 
    
    matrix[2].codeName = "add";
    matrix[2].word = (unsigned short)6128; 
    
    matrix[3].codeName = "sub";
    matrix[3].word =(unsigned short) 8176; 
    
    matrix[4].codeName = "lea";
    matrix[4].word =(unsigned short) 8560; 
    
    matrix[5].codeName = "clr";
    matrix[5].word = (unsigned short)10352; 
    
    matrix[6].codeName = "not";
    matrix[6].word =(unsigned short) 12400; 
    
    matrix[7].codeName = "inc";
    matrix[7].word = (unsigned short)14448; 
    
    matrix[8].codeName = "dec";
    matrix[8].word =(unsigned short) 16496; 
    
    matrix[9].codeName = "jmp";
    matrix[9].word = (unsigned short)18480; 
    
    matrix[10].codeName = "bne";
    matrix[10].word = (unsigned short)20528; 
    
    matrix[11].codeName = "red";
    matrix[11].word = (unsigned short)22640; 
    
    matrix[12].codeName = "prn";
    matrix[12].word = (unsigned short)24696; 
    
    matrix[13].codeName = "jsr";
    matrix[13].word =(unsigned short) 26672; 
    
    matrix[14].codeName = "rts";
    matrix[14].word = (unsigned short)28672; 
    
    matrix[15].codeName = "stop";
    matrix[15].word = 30720;

    int x;
    x = sizeof(matrix[0].word);
    for (i = 0; i < 16; i++)
    {
        printf("matrix[i].codeName: %s\n",matrix[i].codeName);
        
        printBits(x, &matrix[i].word);
        printf("\n\n");
    }
    return 0; 
}
