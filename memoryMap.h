//
// Created by nadav on 04/02/2020.
//

#include "firstRunOver.h"
#include "filesAssembler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 *
 */
typedef struct dataNode{ /*we've decided to implement the data table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    short word;
    struct dataNode *next;
}*dataNodePtr, dataNode;

/*!
 *
 */
typedef struct dataLinkedList {
    int size;
    dataNodePtr head;
}*dataLinkedListPtr;

/*!
 *
 * @param ch
 * @param x
 * @param isItString
 * @return
 */
dataNodePtr newDataNode(char ch, int x, bool isItString); /*is string = true if its .string, false if its .data,
dc with or without 100??? 
return the new node*/

/*!
 *
 * @param toFree
 */
void freeDataNode(dataNodePtr toFree);/*a recursive function to free a node and his next node and so on till last one.
to free the whole list just insert the head as a parameter*/

/*!
 *
 * @return
 */
dataLinkedListPtr newDataList();/*a funtion to create a new data table (linked list)*/

/*!
 *
 * @param list
 * @param ch
 * @param x
 * @param isItString
 */
void addDataNodeToEnd(dataLinkedListPtr list,char ch, int x, bool isItString);/*if the list is Null the function does nothing*/

/*!
 *
 * @param list
 * @param ch
 * @param x
 * @param isItString
 */
void addDataNodeToStart(dataLinkedListPtr list,char ch, int x, bool isItString);

/*!
 *
 * @param parsedLine
 * @param instructionType
 */
void analyzeData(char* parsedLine, char instructionType[]);/*is it necasary?*/

/*!
 *
 * @param address
 * @param list
 * @return
 */
dataNodePtr searchDataInList(int address, dataLinkedListPtr list);/*if the data with this address is in the list - the dataNode
    is return*/

/*!
 *
 * @param listPtr
 */
void printDataList(dataLinkedListPtr listPtr);/*a function that prints the data table*/

/*!
 *
 * @param node
 */
void printDataNode(dataNodePtr node); /* a function used by printList function*/

/*!
 *
 * @param listPtr
 * @return
 */
bool dataTableIsEmpty(dataLinkedListPtr listPtr);/*a function that check if the list is empty*/

/*!
 *
 * @param list
 * @param x
 * @param dc
 * @return
 */
int addDataToTable(dataLinkedListPtr list, int x); /*if the data is already in the table - 
    return 1. else if the insertion went well - return 0. */

/*!
 *
 * @param list
 * @param ch
 * @return
 */
int addCharToTable(dataLinkedListPtr list,char ch);  /*if the address is already in the table - 
    return 1. else if the insertion went well - return 0. */

void addStringToDataTable(dataLinkedListPtr list, char *str);/*adding a string to the data table.*/