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
 * @param list
 * @param symbolName
 * @param address1
 * @param isExternal1
 */
void addNodeToEnd(linkedListPtr list, char *symbolName, int address1, int isExternal1);

/*!
 *
 * @param list
 * @param symbolName
 * @param address1
 * @param isExternal1
 */
void addNodeToStart(linkedListPtr list, char *symbolName, int address1, int isExternal1);

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
 * @param isExternal
 * @return
 */
int addSymbolToTable(char *symbolName, linkedListPtr list, int isExternal);

/*!
 *
 */
void secondRunOver();

#endif //MAABADA_MMN14_SYMBOLSTABLE_H