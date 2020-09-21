
/* Created by nadav on 04/02/2020.*/


#ifndef MAABADA_MMN14_SYMBOLSTABLE_H
#define MAABADA_MMN14_SYMBOLSTABLE_H

#include "dataStructures.h"
#include "aidTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*!
 * this function adds a SYMBOL into the SYMBOL table, while doing validation chacks
 * @param head
 * @param symbol
 * @param status
 */
void addToSymbolTable(linkedListPtr head,struct Token* symbol, int status, int lineNumber);


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
nodePtr searchSymbolNameInList(char* symbolName, linkedListPtr head);




/*!
 *
 * @param listPtr
 * @return
 */
int listIsEmpty(linkedListPtr listPtr);



int add_symbol_occurrence(occp head, int line);




#endif /*MAABADA_MMN14_SYMBOLSTABLE_H*/