//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_AIDTOOLS_H
#define MAABADA_MMN14_AIDTOOLS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


int bin_to_octal(int binaryNum);

#endif //MAABADA_MMN14_AIDTOOLS_H
