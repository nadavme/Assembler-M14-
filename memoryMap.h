
/* Created by nadav on 04/02/2020.*/


#include "aidTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct dataNode{ /*we've decided to implement the data table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    short word;
    struct dataNode *next;
}*dataNodePtr, dataNode;


typedef struct dataLinkedList {
    int size;
    dataNodePtr head;
}*dataLinkedListPtr;


dataNodePtr newDataNode(char ch, int x, bool isItString); /*is string = true if its .string, false if its .data,
dc with or without 100??? 
return the new node*/


void freeDataNode(dataNodePtr toFree);/*a recursive function to free a node and his next node and so on till last one.
to free the whole list just insert the head as a parameter*/

/*!
 *
 * @return
 */
dataLinkedListPtr newDataList();/*a funtion to create a new data table (linked list)*/


void addDataNodeToEnd(dataLinkedListPtr list,char ch, int x, bool isItString);/*if the list is Null the function does nothing*/


void addDataNodeToStart(dataLinkedListPtr list,char ch, int x, bool isItString);


void analyzeData(char* parsedLine, char instructionType[]);/*is it necasary?*/


dataNodePtr searchDataInList(int address, dataLinkedListPtr list);/*if the data with this address is in the list - the dataNode
    is return*/


void printDataList(dataLinkedListPtr listPtr);/*a function that prints the data table*/


void printDataNode(dataNodePtr node); /* a function used by printList function*/


bool dataTableIsEmpty(dataLinkedListPtr listPtr);/*a function that check if the list is empty*/


int addDataToTable(dataLinkedListPtr list, int x); /*if the data is already in the table - 
    return 1. else if the insertion went well - return 0. */


int addCharToTable(dataLinkedListPtr list,char ch);  /*if the address is already in the table - 
    return 1. else if the insertion went well - return 0. */

void addStringToDataTable(dataLinkedListPtr list, char *str);/*adding a string to the data table.*/

int add100ToMemory();/*this function updates the memory image, as described in the MAMAN.
                            return 0 if both tables are empty, else return 1.*/