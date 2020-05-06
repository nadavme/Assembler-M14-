
/* Created by nadav on 04/02/2020.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolsTable.h"

/* this function adds a SYMBOL into the SYMBOL table, while doing validation chacks */
void addToSymbolTable(nodePtr head, struct Token *symbol, int status, int lineNumber)
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
		free(node); /* so there is no need for this node */
		switch (status) {
			case CODE_SYMBOL_DECLARATION:
				if ((curr->address != NOT_DECLARED) || (curr->entry_extern == EXTERN_SYMBOL))
				{
                    errorHandler(1, lineNumber, "symbol declared twice");
					return;
				}
				else /* adding the address */
				{
					curr->address = IC;
					curr->data_or_instruction = CODE_SYMBOL;
				}
				break;
			case CODE_SYMBOL:
				if (!add_symbol_occurrence(curr->occurrence, IC)) return; /* adds a new node to the
                                                                            * list of occorances of this SYMBOL*/
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
int add_symbol_occurrence(occp head, int line)
{
	occp node = (occp)malloc(sizeof(occurrence));
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


nodePtr newNode(char *symbolName, int entry_extern, int data_or_instruction)/*a possible bug - there is no decleration for
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
void free_occur_list(occp head)
{
	occp curr;
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
        free_occur_list(toFree->occurrence);/*freeing the allocated memory of the occurences linked list*/
        free(toFree->symbolName);/* maybe I need to free anything else from struct????*/
    }
    freeNode(toFree->next);
    free(toFree);
}

void freeSymbolsTable(linkedListPtr toFree)
{
    freeNode(toFree->head);
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



int listIsEmpty(linkedListPtr listPtr)
{
    if (listPtr->head == NULL)
    {
        return 1;
    }
    return 0;
}