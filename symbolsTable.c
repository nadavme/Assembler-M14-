//
// Created by nadav on 04/02/2020.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolsTable.h"



nodePtr newNode(char *symbolName, int address1, int attachedToGuidance, int isExternal1){
    nodePtr new;
    int nameLen = 0;
    if(symbolName==NULL){
        return NULL;
    }
    nameLen = strlen(symbolName);
    new = calloc(1, sizeof(node));
    new->symbolName = calloc(nameLen+1, sizeof(char));
    strncpy(new->symbolName, symbolName, nameLen);
    new->counter = 0;
    new->address = address1;
    new->isAttachedToGuidance = attachedToGuidance;
    new->isExternal = isExternal1;
    return new;
}

void freeNode(nodePtr toFree){/*a recursive function to free a node ana his next node and so on till last one.*/
    if(toFree == NULL){
        return;
    }
    if(toFree->symbolName != NULL){
        free(toFree->symbolName);
    }
    freeNode(toFree->next);
    free(toFree);
}

linkedListPtr newList()
{
    return calloc(1, sizeof(struct linkedList));
}

void addNodeToEnd(linkedListPtr list, char *symbolName, int address1, int attachedToGuidance, int isExternal1){
    nodePtr new, nodePtr1;
    if(list == NULL || symbolName == NULL)
    {
        return;
    }
    new = newNode(symbolName, address1, attachedToGuidance, isExternal1);
    if(!list->size){
        list->head = new;
    }else{
        for(nodePtr1 = list->head ; nodePtr1->next; nodePtr1=nodePtr1->next)
            ;
    
        nodePtr1->next = new;
    }
    new->next = NULL;
    new->counter = 1;
    list->size++;

        
}

void addNodeToStart(linkedListPtr list, char *symbolName, int address1, int attachedToGuidance, int isExternal1) 
    {
        nodePtr new = newNode(symbolName, address1, attachedToGuidance, isExternal1);
        new->next = list->head;
        list->head = new;
        list->size = list->size +1;
    }

    nodePtr searchSymbolNameInList(char symbolName[], linkedListPtr list)
    {
        nodePtr searchedNode = list->head;
        while (searchedNode!=NULL)
    {
        if(strcmp(searchedNode->symbolName,symbolName) == 0)
            return searchedNode;
        searchedNode = searchedNode->next;
    }
    return searchedNode;
    }



    void printList(linkedListPtr listPtr)
    {
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
        if(!node)
        {
            return;
        }
        /*if ((node->next == NULL) && node->counter == 1)
            printf("%s - 1 time\n", node->symbolName);

        else if (node->next == NULL)
            printf("%s - %d times\n", node->symbolName,node->counter); */

        else
            printf("[NAME - %s ***  ADDRESS - %d ***  ", node->symbolName, node->address);   
            if(node->isAttachedToGuidance == 1) printf("is Attached To Guidance? - YES. *** ");
            else if (node->isAttachedToGuidance == 0) printf("is Attached To Guidance? - NO. *** ");

            if (node->isExternal == 1) printf("is EXTERNAL? - YES. *** ]");

            else if (node->isExternal == 0) printf("is EXTERNAL? - NO. *** \n");
    }

    int listIsEmpty(linkedListPtr listPtr)
    {
        if (listPtr->head == NULL)
        {
            return 1;
        }
        return 0;     
    }

    int addSymbolToTable(char* parsedLine, linkedListPtr list, int dc, int attachedToGuidance, int isExternal)/*if the symbol is already in the table - 
    return 1. else if the insertion went well - return 0. */
    {
        if (searchSymbolNameInList(parsedLine, list) != NULL)
            return 1;
        if (listIsEmpty(list)==1)
        {
            addNodeToStart(list, parsedLine, dc + 100, attachedToGuidance, isExternal);
            return 0;
        }
        
        addNodeToEnd(list, parsedLine, dc + 100, attachedToGuidance, isExternal);
        return 0;

        
        
        

    }

