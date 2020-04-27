//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_AIDTOOLS_H
#define MAABADA_MMN14_AIDTOOLS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_DIGITS_BIN 100
#define MAX_DIGITS_DEC 10
#include "firstRunOver.h"


typedef struct codeNode{ /*we've decided to implement the code table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    second_word data;/*this is not the right word, I need to find the right one*/
    struct codeNode *next;
}*codeNodePtr, codeNode;

typedef struct codeLinkedList {
    int size;
    codeNodePtr head;
}*codeLinkedListPtr;

typedef enum opCode { mov, cmp, add, sub, nnot, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop } opCode;

typedef enum addressingMethod { immediate = 0, direct, reg } addrMethod;

typedef enum ARE { absolute = 0, external, relocatable } ARE;

typedef enum symbolType { tCode, tData, tString} symbolType;

typedef  enum isExtern {no, yes} isExtern;

typedef struct lineStruct
{
    char* originalLine;
    char* symbol;
    first_word* translatedWord;
    unsigned char opRepeat;
    unsigned int lineNumber;
    char done;
} *lineStruct;

int bin_to_octal(int binaryNum);/*converts from binary to octal, return the result.*/

int dec_to_bin(char dec[]); /*converts from decimal to binary, prints the result.*/

#endif //MAABADA_MMN14_AIDTOOLS_H
