//
// Created by nadav on 04/02/2020.
//

#include "memoryMap.h"

dataNodePtr newDataNode(char ch, int x, bool isItString, int dc){ /*is string = true if its .string, false if its .data,
dc with or without 100??? 
return the new node*/
    dataNodePtr new;
    int nameLen = 0;
    if(ch==0 && isItString == true){
        return NULL;
    }
    new = calloc(1, sizeof(dataNode));
    new->address = dc;

    if (isItString == true)
    {
        new->word.num_or_address = (unsigned short)ch; /*maybe this line will cause trouble, maybe the cast, shouldnt be*/
    }

    else if (isItString == false)
    {
        new->word.num_or_address = (unsigned short)x;/*maybe this line will cause trouble, maybe the cast, shouldnt be*/
    }
    
    return new;
}

void freeDataNode(dataNodePtr toFree){/*a recursive function to free a node and his next node and so on till last one.
to free the whole list just insert the head as a parameter*/
    if(toFree == NULL){
        return;
    }

    freeDataNode(toFree->next);
    free(toFree);
}

dataLinkedListPtr newDataList()/*a funtion to create a new data table (linked list)*/
{
    return calloc(1, sizeof(struct dataLinkedList));
}

void addDataNodeToEnd(dataLinkedListPtr list,char ch, int x, int dc, bool isItString){/*if the list is Null the function does nothing*/
    dataNodePtr new, dataNodePtr1;
    if(list == NULL)
    {
        return;
    }
    new = newDataNode(ch, x, isItString,dc);
    if(!list->size){
        list->head = new;
    }else{
        for(dataNodePtr1 = list->head ; dataNodePtr1->next; dataNodePtr1=dataNodePtr1->next)
            ;
    
        dataNodePtr1->next = new;
    }
    new->next = NULL;
    list->size++;

        
}

void addDataNodeToStart(dataLinkedListPtr list,char ch, int x, int dc, bool isItString) 
    {
        dataNodePtr new = newDataNode(ch, x, isItString, dc);
        new->next = list->head;
        list->head = new;
        list->size = list->size +1;
    }

    dataNodePtr searchDataInList(int address, linkedListPtr list)/*if the data with this address is in the list - the dataNode
    is return*/
    {
        dataNodePtr searchedNode = list->head;
        while (searchedNode!=NULL)
    {
        if(address == searchedNode->address)
            return searchedNode;
        searchedNode = searchedNode->next;
    }
    return searchedNode;
    }



    void printDataList(dataLinkedListPtr listPtr)
    {
        int i;
        dataNodePtr node = listPtr->head;

        for (i = 0; i < listPtr->size; i++)
        {
            printDataNode(node);
            printf("                            ||                        \n");
            printf("                            ||                        \n");
            node = node->next;

        }
        
    }

    void printDataNode(dataNodePtr node)
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
        {
            printf("***  ADDRESS - %d\n" , node->address);
            printf("***  VALUE(BINARY)- %hu\n", node->word);
        }
            return;
    }

    bool dataTableIsEmpty(dataLinkedListPtr listPtr)
    {
        if (listPtr->head == NULL)
        {
            return true;
        }
        return false;     
    }

    int addDataToTable(dataLinkedListPtr list, int x, int dc) /*if the address is already in the table - 
    return 1. else if the insertion went well - return 0. */
    {
        if (searchDataInList(dc, list) != NULL)
        {
            printf("Error!\n The address is already in the table.");
            return 1;
        }
        if (dataTableIsEmpty(list)==true)
        {
            addDataNodeToStart(list,0, x, dc,false);
            return 0;
        }
        
        addDataNodeToEnd( list, 0, x, dc, false);
        return 0;
        
}


int addCharToTable(dataLinkedListPtr list,char ch, int dc)  /*if the address is already in the table - 
    return 1. else if the insertion went well - return 0. */
{
    {
        if (searchDataInList(dc, list) != NULL)
        {
            printf("Error!\n The address is already in the table.");
            return 1;
        }
        if (dataTableIsEmpty(list)==true)
        {
            addDataNodeToStart(list,ch, 0, dc,true);
            return 0;
        }
        
        addDataNodeToEnd(list, ch, 0, dc, true);
        return 0;
}