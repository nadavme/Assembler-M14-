
/* Created by nadav on 04/02/2020.*/


#ifndef MAABADA_MMN14_SYMBOLSTABLE_H
#define MAABADA_MMN14_SYMBOLSTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aidTools.h"

typedef struct SYMBOL_occur* occp;

/*!
 *this is one occurrence of a symbol in the file.
 */
typedef struct SYMBOL_occur
{
	int line;
	occp next;
}occurrence;

/*!
 * this node represent a symbol, it will be a part of a linked list 
 * which will represent the symbol table.
 */
typedef struct node{
    char *symbolName;/* the name of the symbol */
    int address;/* the location in memory in which this symbol was declared */
    int entry_extern;/*is it entry or extern?*/
    int data_or_instruction; /* the type of the symbol, from the values of the enum above. */
	occp occurrence; /* a linked list of all the occurrences of this symbol in the code */
    struct node* next;
}*nodePtr, node;

typedef struct  linkedListPtr *symbolT;

/*!
 *
 */
typedef struct linkedList {
    int size;
    nodePtr head;
}*linkedListPtr;

/* types of symbols in the assably code */
enum symbol_type {
	EXTERN_SYMBOL,
	ENTRY_SYMBOL,
	CODE_SYMBOL_DECLARATION,
	DATA_SYMBOL,
	CODE_SYMBOL, /* used, not declared */
	NOT_DECLARED = -1
};

/*!
 * this function adds a SYMBOL into the SYMBOL table, while doing validation chacks
 * @param head
 * @param symbol
 * @param status
 */
void addToSymbolTable(nodePtr head,struct Token *symbol, int status, int lineNumber);


/*!
 * this function adds a SYMBOL into the SYMBOL table, while doing validation checks
 * @param symbolName
 * @param entry_extern
 * @param data_or_instruction
 */
nodePtr newNode(char *symbolName, int entry_extern, int data_or_instruction);



/*!
 *
 * @param toFree
 */
void freeNode(nodePtr toFree);

/*!
*
*@param toFree
*/
void freeSymbolsTable(linkedListPtr toFree);/* a function to free the memory of symbols table*/

/*!
 *
 * @return
 */
linkedListPtr newList();

/*!
 *
 * @param symbolName
 * @param list
 * @return
 */
nodePtr searchSymbolNameInList(char symbolName[], nodePtr head);




/*!
 *
 * @param listPtr
 * @return
 */
int listIsEmpty(linkedListPtr listPtr);



int add_symbol_occurrence(occp head, int line);




#endif /*MAABADA_MMN14_SYMBOLSTABLE_H*/