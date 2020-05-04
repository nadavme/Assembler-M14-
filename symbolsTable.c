//
// Created by nadav on 04/02/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolsTable.h"
#include "filesAssembler.h"


nodePtr newNode(char *symbolName, int address1, int isExternal1)
{
    nodePtr new;
    int nameLen = 0;
    if (symbolName == NULL)
    {
        return NULL;
    }
    nameLen = strlen(symbolName);
    new = calloc(1, sizeof(node));
    new->symbolName = calloc(nameLen + 1, sizeof(char));
    strncpy(new->symbolName, symbolName, nameLen);
    new->address = address1;
    new->isExternal = isExternal1;
    return new;
}

void freeNode(nodePtr toFree)
{ /*a recursive function to free a node ana his next node and so on till last one.*/
    if (toFree == NULL)
    {
        return;
    }
    if (toFree->symbolName != NULL)
    {
        free(toFree->symbolName);/* maybe I need to free anything else from struct????*/
    }
    freeNode(toFree->next);
    free(toFree);
}

void freeSymbolsTable(linkedListPtr toFree)
{
    freeNode(toFree->head);
    return;
}

linkedListPtr newList()
{
    return calloc(1, sizeof(struct linkedList));
}

void addNodeToEnd(linkedListPtr list, char *symbolName, int address1, int isExternal1)
{
    nodePtr new, nodePtr1;
    if (list == NULL || symbolName == NULL)
    {
        return;
    }
    new = newNode(symbolName, address1, isExternal1);
    if (!list->size)
    {
        list->head = new;
    }
    else
    {
        for (nodePtr1 = list->head; nodePtr1->next; nodePtr1 = nodePtr1->next)
            ;

        nodePtr1->next = new;
    }
    new->next = NULL;
    list->size++;
}

void addNodeToStart(linkedListPtr list, char *symbolName, int address1, int isExternal1)
{
    nodePtr new = newNode(symbolName, address1, isExternal1);
    new->next = list->head;
    list->head = new;
    list->size = list->size + 1;
}

nodePtr searchSymbolNameInList(char symbolName[], linkedListPtr list)
{
    nodePtr searchedNode = list->head;
    while (searchedNode != NULL)
    {
        if (strcmp(searchedNode->symbolName, symbolName) == 0)
            return searchedNode;
        searchedNode = searchedNode->next;
    }
    return searchedNode;
}

void printList(linkedListPtr listPtr)
{
    /*   some code from stack overflow: */


    /*fp = fopen("newfile.txt", "w+");

    // Get the size of the linked list and write as the first piece of data.
    size_t listSize = getLinkedListSize(head)

        fwrite(&listSize, 1, sizeof(size_t), fp);

    // Now write each node of the linked list.
    while (iterator != NULL)
    {
        fwrite(&(iterator->data), 1, sizeof(iterator->data), fp);
        iterator = iterator->next;
    }*/

    int i;
    nodePtr node = listPtr->head;

    for (i = 0; i < listPtr->size; i++)
    {
        printNode(node);
        printf("                            ||                        \n");
        printf("                            ||                        \n");
        node = node->next;
    }
}

void printNode(nodePtr node)
{
    if (!node)
    {
        return;
    }
    /*if ((node->next == NULL) && node->counter == 1)
            printf("%s - 1 time\n", node->symbolName);

        else if (node->next == NULL)
            printf("%s - %d times\n", node->symbolName,node->counter); */

    else
        printf("[NAME - %s ***  ADDRESS - %d ***  ", node->symbolName, node->address);

    if (node->isExternal == 1)
        printf("is EXTERNAL? - YES. *** ]");

    else if (node->isExternal == 0)
        printf("is EXTERNAL? - NO. *** \n");
}

int listIsEmpty(linkedListPtr listPtr)
{
    if (listPtr->head == NULL)
    {
        return 1;
    }
    return 0;
}

int addSymbolToTable(char *symbolName, linkedListPtr list, int isExternal) /*if the symbol is already in the table - 
    return 1. else if the insertion went well - return 0. */
{
    if (searchSymbolNameInList(symbolName, list) != NULL)
    {
        printf("Error!\n The symbol is already in the table.");
        return 1;
    }
    if (listIsEmpty(list) == 1)
    {
        addNodeToStart(list, symbolName, DC + 100, isExternal);
        IC++;
        return 0;
    }

    addNodeToEnd(list, symbolName,  DC, isExternal);
    IC++;
    return 0;
}
