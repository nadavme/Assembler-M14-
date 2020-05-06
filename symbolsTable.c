//
// Created by nadav on 04/02/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolsTable.h"
#include "filesAssembler.h"

/* this function adds a SYMBOL into the SYMBOL table, while doing validation chacks */
void addToSymbolTable(nodePtr head, Token *symbol, int status, int lineNumber)
{
	nodePtr node = (nodePtr)malloc(sizeof(node));
	nodePtr curr;

	if (!node)
	{
		errorHandler(1, -1, "Memory allocation has failed");
		return;
	}
	if ((curr = searchSymbolNameInList(symbol->data.symbol, head)) == NULL) /* this is a new SYMBOL to add */
	{
		/* creating the node */
		strcpy(node->symbolName, symbol->data.symbol);/*initializing the fields*/
		node->address = NOT_DECLARED;
		node->data_or_instruction = NOT_DECLARED;
		node->entry_extern = NOT_DECLARED;
		node->occurrence = NULL; 

		switch (status) /* which type of declaration there is... */
		{
			case CODE_SYMBOL_DECLARATION:
				node->address = IC;
				break;
			case CODE_SYMBOL:
				if (!add_symbol_occurrence(node->occurrence, IC)) return; /* adds the line to the list of occurances of this symbol */
				break;
			case DATA_SYMBOL:
				node->address = DC;
				node->data_or_instruction = DATA_SYMBOL;
				break;
			case ENTRY_SYMBOL:
			case EXTERN_SYMBOL:
				node->entry_extern = status;
				break;
		}
		/* linking to the head of the list */
		if (head == NULL) {
			node->next = NULL;
		}
		else {
			node->next = head;
		}
		head = node;
		return;
	}
	else /* if the SYMBOL is already in the table */
	{
		free(node); /* so theres no need for this node */
		switch (status) {
			case CODE_SYMBOL_DECLARATION:
				if ((curr->address != NOT_DECLARED) || (curr->entry_extern == EXTERN_SYMBOL))
				{
                    errorHandler(1, lineNumber, "symbol declared twice");
					return;
				}
				else /* adding the addres */
				{
					curr->address = IC;
					curr->data_or_instruction = CODE_SYMBOL;
				}
				break;
			case CODE_SYMBOL:
				if (!add_SYMBOL_occurrence(curr->occurrence, IC)) return; /* adds a new node to the list of occorances of this SYMBOL*/
				break;
			case DATA_SYMBOL:
				if ((curr->address != NOT_DECLARED) || (curr->entry_extern == EXTERN_SYMBOL))
				{
					errorHandler(1, lineNumber, "symbol declared twice");
					return;
				}
				else
				{
					curr->address = DC;
					curr->data_or_instruction = DATA_SYMBOL;
				}
				break;
			case ENTRY_SYMBOL:
				if (curr->entry_extern != NOT_DECLARED)
				{
					errorHandler(1, lineNumber, "symbol declared twice");
					return;
				}
				else
				{
					curr->entry_extern = status; /* ENTRY_SYMBOL */
				}
				break;
			case EXTERN_SYMBOL:
				if ((curr->address != NOT_DECLARED) || (curr->entry_extern != NOT_DECLARED))
				{
					errorHandler(1, lineNumber, "symbol declared twice");
					return;
				}
				else
				{
					curr->entry_extern = status; /* EXTERN_SYMBOL */
				}
				break;
		}
	}
}

/* this function adds a new lable occurrence to a lable node */
int add_symbol_occurrence(occPtr head, int line)
{
	occPtr node = (occPtr)malloc(sizeof(occurrence));
	if (node == NULL)
	{
        errorHandler(1, line, "Memory allocation has failed");
		return 0;
	}
	node->line = line;
	if (head == NULL) { /* no nodes in the list */
		node->next = NULL;
	}
	else
	{
		node->next = head;
	}
	head = node;
	return 1;
}


nodePtr newNode(char *symbolName, int entry_extern, int data_or_instruction)/*a possible bug - theres no decleration for 
                                                                                            occurences linked list*/
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
    new->address = DC;
    new->entry_extern = entry_extern;
    new->data_or_instruction = data_or_instruction;
    return new;
}

/* frees the memory of the occurance list in each node */
void free_occur_list(occPtr head)
{
	occPtr curr;
	if (head != NULL)
	{
		curr = (head)->next;
		for (; curr; curr = curr->next) {
			free(head);
			head = curr;
		}
		free(head);
	}
}

void freeNode(nodePtr toFree)
{ /*a recursive function to free a node ana his next node and so on till last one.*/
    if (toFree == NULL)
    {
        return;
    }
    if (toFree->symbolName != NULL)
    {
        free_occur_list(&(curr->occurrence));/*freeing the allocated memory of the occurences linked list*/
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

nodePtr searchSymbolNameInList(char symbolName[], nodePtr head)
{
    nodePtr searchedNode = head;
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