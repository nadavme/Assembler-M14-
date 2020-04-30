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
struct opTable
{
    char *codeName;
    unsigned int word;
}
commandTable[] =
{
        {"mov", (unsigned short) 2032},

        {"cmp", (unsigned short) 4088},

        {"add", (unsigned short) 6128},

        {"sub", (unsigned short) 8176},

        {"lea", (unsigned short) 8560},

        {"clr", (unsigned short) 10352},

        {"not", (unsigned short) 12400},

        {"inc", (unsigned short) 14448},

        {"dec", (unsigned short) 16496},

        {"jmp", (unsigned short) 18480},

        {"bne", (unsigned short) 20528},

        {"red", (unsigned short) 22640},

        {"prn", (unsigned short) 24696},

        {"jsr", (unsigned short) 26672},

        {"rts", (unsigned short) 28672},

        {"stop", 30720}
};



/*!
 *
 */
char validCommands[16][4] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red",
                             "prn", "jsr", "rts", "stop"};

/*!
 *
 */
struct instruction
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
struct Register
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

