//
// Created by nadav on 04/02/2020.
//

#include "firstRunOver.h"


typedef struct dataNode{ /*we've decided to implement the data table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    second_word data;
    struct dataNode *next;
}*dataNodePtr, dataNode;

typedef struct dataLinkedList {
    int size;
    dataNodePtr head;
}*dataLinkedListPtr;


void analyzeData(char* parsedLine, char instructionType[]);/*what is this function do?, Nadav?*/
