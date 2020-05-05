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
    int numOfOperands;
    int sourceAddressingMethods[4];
    int destAddressingMethods[4];
}
/* addressing methods:
	0: instant addressing
	1: direct addressing
	2: register bypass
	3: register direct */
commandsTable[] =
{
        {"mov", (unsigned short) 2032, 2,{ 1,1,1,1 },{ 0,1,1,1 }},

        {"cmp", (unsigned short) 4088, 2,{ 1,1,1,1 },{ 1,1,1,1 }},

        {"add", (unsigned short) 6128, 2,{ 1,1,1,1 },{ 0,1,1,1 }},

        {"sub", (unsigned short) 8176, 2,{ 1,1,1,1 },{ 0,1,1,1 }},

        {"lea", (unsigned short) 8560, 2,{ 1,0,0,0 },{ 0,1,1,1 }},

        {"clr", (unsigned short) 10352, 1,{ 0,0,0,0 },{ 0,1,1,1 }},

        {"not", (unsigned short) 12400, 1,{ 0,0,0,0} ,{ 0,1,1,1 }},

        {"inc", (unsigned short) 14448, 1,{ 0,0,0,0} ,{ 0,1,1,1 }},

        {"dec", (unsigned short) 16496, 1,{ 0,0,0,0} ,{ 0,1,1,1 }},

        {"jmp", (unsigned short) 18480, 1,{ 0,0,0,0} ,{ 0,1,1,0 }},

        {"bne", (unsigned short) 20528, 1,{ 0,0,0,0} ,{ 0,1,1,0 }},

        {"red", (unsigned short) 22640, 1,{ 0,0,0,0} ,{ 0,1,1,1 }},

        {"prn", (unsigned short) 24696, 1,{ 0,0,0,0} ,{ 1,1,1,1 }},

        {"jsr", (unsigned short) 26672, 1,{ 0,0,0,0} ,{ 0,1,1,0 }},

        {"rts", (unsigned short) 28672, 0,{ 0,0,0,0} ,{ 0,0,0,0 }},

        {"stop", 30720, 0,{ 0,0,0,0} ,{ 0,0,0,0 }}
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
