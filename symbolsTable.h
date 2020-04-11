//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_SYMBOLSTABLE_H
#define MAABADA_MMN14_SYMBOLSTABLE_H

typedef struct node{
    int counter;/* can I delete this field????????????????? */
    char *symbolName;
    int address;/*I did the symbol table as Dani Kalfon instructs in his lecture about the project (at time 2:01 in the video you can see the table...)*/
    int isAttachedToGuidance;
    int isExternal;
    struct node *next;
}*nodePtr, node;

typedef struct linkedList {
    int size;
    nodePtr head;
}*linkedListPtr;

int parsStr(char *str);

nodePtr newNode(char *symbolName, int address1, int attachedToGuidance, int isExternal1);

void freeNode(nodePtr toFree);

linkedListPtr newList();

void addNodeToEnd(linkedListPtr list, char *symbolName, int address1, int attachedToGuidance, int isExternal1);

void addNodeToStart(linkedListPtr list, char *symbolName, int address1, int attachedToGuidance, int isExternal1);

nodePtr searchSymbolNameInList(char symbolName[], linkedListPtr list);

void printNode(nodePtr node);

void printList(linkedListPtr listPtr);

int listIsEmpty(linkedListPtr listPtr);

int strToInt(char c[]);

#endif //MAABADA_MMN14_SYMBOLSTABLE_H
