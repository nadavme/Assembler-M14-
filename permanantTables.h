//
// Created by nadav on 04/02/2020.
//

#include "firstRunOver.h"
#include <stdio.h>

/*!
 *
 */
typedef enum registers {R0, R1, R2, R3, R4, R5, R6, R7} ;

/*!
 *
 */
typedef enum instructions {STRING, DATA, ENTRY, EXTERN } ;

/*!
 *
 */
typedef struct opTable
{
    char *codeName;
    unsigned int word;
}
matrix[] =
{
        {"mov",
        (unsigned short)2032}

        {
            matrix[1].codeName = "cmp";
            matrix[1].word = (unsigned short) 4088;
        }

        {
            matrix[2].codeName = "add";
            matrix[2].word = (unsigned short) 6128;
        }

        {
            matrix[3].codeName = "sub";
            matrix[3].word = (unsigned short) 8176;
        }

        {
            matrix[4].codeName = "lea";
            matrix[4].word = (unsigned short) 8560;
        }

        {
            matrix[5].codeName = "clr";
            matrix[5].word = (unsigned short) 10352;
        }

        {
            matrix[6].codeName = "not";
            matrix[6].word = (unsigned short) 12400;
        }

        {
            matrix[7].codeName = "inc";
            matrix[7].word = (unsigned short) 14448;
        }

        {
            matrix[8].codeName = "dec";
            matrix[8].word = (unsigned short) 16496;
        }

        {
            matrix[9].codeName = "jmp";
            matrix[9].word = (unsigned short) 18480;
        }

        {
            matrix[10].codeName = "bne";
            matrix[10].word = (unsigned short) 20528;
        }

        {
            matrix[11].codeName = "red";
            matrix[11].word = (unsigned short) 22640;
        }

        {
            matrix[12].codeName = "prn";
            matrix[12].word = (unsigned short) 24696;
        }

        {
            matrix[13].codeName = "jsr";
            matrix[13].word = (unsigned short) 26672;
        }

        {
            matrix[14].codeName = "rts";
            matrix[14].word = (unsigned short) 28672;
        }

        {
            matrix[15].codeName = "stop";
            matrix[15].word = 30720;
        }
};



/*!
 *
 */
char validCommands[16][4] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red",
                             "prn", "jsr", "rts", "stop"};

/*!
 *
 */
typedef struct instruction
{
    char* instruction;
    int insType;
}
    validInstructions[] =
        {
                {".data",   DATA},
                {".string", STRING},
                {".extern", EXTERN},
                {".entry",  ENTRY},
                {NULL}
        };

/*!
 *
 */
typedef struct Register
{
    char* regName;
    int regNum;
}
        validRegisters[] =
        {
                {"r1", R1},
                {"r2", R2},
                {"r3", R3},
                {"r4", R4},
                {"r5", R5},
                {"r6", R6},
                {"r7", R7},
                {NULL}
        };

