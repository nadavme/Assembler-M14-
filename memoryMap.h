//
// Created by nadav on 04/02/2020.
//

#include "firstRunOver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dataNode{ /*we've decided to implement the data table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    struct second_word word;
    struct dataNode *next;
}*dataNodePtr, dataNode;

typedef struct dataLinkedList {
    int size;
    dataNodePtr head;
}*dataLinkedListPtr;

dataNodePtr newDataNode(char ch, int x, bool isItString, int dc); /*is string = true if its .string, false if its .data,
dc with or without 100??? 
return the new node*/

void freeDataNode(dataNodePtr toFree);/*a recursive function to free a node and his next node and so on till last one.
to free the whole list just insert the head as a parameter*/

dataLinkedListPtr newDataList();/*a funtion to create a new data table (linked list)*/

void addDataNodeToEnd(dataLinkedListPtr list,char ch, int x, int dc, bool isItString);/*if the list is Null the function does nothing*/

void addDataNodeToStart(dataLinkedListPtr list,char ch, int x, int dc, bool isItString);

void analyzeData(char* parsedLine, char instructionType[]);/*is it necasary?*/

dataNodePtr searchDataInList(int address, linkedListPtr list);/*if the data with this address is in the list - the dataNode
    is return*/

void printDataList(dataLinkedListPtr listPtr);/*a function that prints the data table*/

void printDataNode(dataNodePtr node); /* a function used by printList function*/

bool dataTableIsEmpty(dataLinkedListPtr listPtr);/*a function that check if the list is empty*/

int addDataToTable(dataLinkedListPtr list, int x, int dc); /*if the data is already in the table - 
    return 1. else if the insertion went well - return 0. */

int addCharToTable(dataLinkedListPtr list,char ch, int dc);  /*if the address is already in the table - 
    return 1. else if the insertion went well - return 0. */
