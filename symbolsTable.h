//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_SYMBOLSTABLE_H
#define MAABADA_MMN14_SYMBOLSTABLE_H

/*!
 *
 */
typedef struct node{
    char *symbolName;
    int address;/*I did the symbol table as Dani Kalfon instructs in his lecture about the project (at time 2:01 in the video you can see the table...)*/
    int isEntry;
    int isExternal;
    struct node *next;
}*nodePtr, node;

/*!
 *
 */
typedef struct linkedList {
    int size;
    nodePtr head;
}*linkedListPtr;

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
 * @param isEntry
 * @param isExternal1
 * @return
 */
nodePtr newNode(char *symbolName, int address1, int isEntry, int isExternal1);

/*!
 *
 * @param toFree
 */
void freeNode(nodePtr toFree);

/*!
 *
 * @return
 */
linkedListPtr newList();

/*!
 *
 * @param list
 * @param symbolName
 * @param address1
 * @param isEntry
 * @param isExternal1
 */
void addNodeToEnd(linkedListPtr list, char *symbolName, int address1, int isEntry, int isExternal1);

/*!
 *
 * @param list
 * @param symbolName
 * @param address1
 * @param isEntry
 * @param isExternal1
 */
void addNodeToStart(linkedListPtr list, char *symbolName, int address1, int isEntry, int isExternal1);

/*!
 *
 * @param symbolName
 * @param list
 * @return
 */
nodePtr searchSymbolNameInList(char symbolName[], linkedListPtr list);

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

/*!
 *
 * @param parsedLine
 * @param list
 * @param dc
 * @param isEntry
 * @param isExternal
 * @return
 */
int addSymbolToTable(char* parsedLine, linkedListPtr list, int dc, int isEntry, int isExternal);

#endif //MAABADA_MMN14_SYMBOLSTABLE_H
