//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_SYMBOLSTABLE_H
#define MAABADA_MMN14_SYMBOLSTABLE_H

/*!
 *this is one occurrence of a symbol in the file.
 */
typedef struct SYMBOL_occur {
	int line;
	occPtr next;
}occurrence, *occPtr;

/*!
 * this node represent a symbol, it will be a part of a linked list 
 * which will represent the symbol table.
 */
typedef struct node{
    char *symbolName;/* the name of the symbol */
    int address;/* the location in memory in which this symbol was declared */
    int entry_extern;/*is it entry or extern?*/
    int data_or_instruction; /* the type of the symbol, from the values of the enum above. */
	occPtr occurrence; /* a linked list of all the occurrences of this symbol in the code */
    struct node *next; 
}*nodePtr, node;

typedef struct  node *symbolT;

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
void addToSymbolTable(nodePtr head, Token *symbol, int status, int lineNumber);


/*!
 * this function adds a SYMBOL into the SYMBOL table, while doing validation checks
 * @param symbolName
 * @param entry_extern
 * @param data_or_instruction
 */
nodePtr newNode(char *symbolName, int entry_extern, int data_or_instruction);

/*!
 *
 * @param str
 * @return
 */
int parsStr(char *str);

/*!
 *
 * @param symbolName
 * @param address1
 * @param isExternal1
 * @return
 */
nodePtr newNode(char *symbolName, int address1, int isExternal1);

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
 * @param node
 */
void printNode(nodePtr node);

/*!
 *
 * @param listPtr
 */
void printList(linkedListPtr listPtr);

/*!
 *
 * @param listPtr
 * @return
 */
int listIsEmpty(linkedListPtr listPtr);

/*!
 *
 * @param c
 * @return
 */
int strToInt(char c[]);



#endif //MAABADA_MMN14_SYMBOLSTABLE_H