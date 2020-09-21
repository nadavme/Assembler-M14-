
/* Created by nadav on 04/02/2020.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbolsTable.h"
#pragma warning(disable : 4996)
/* this function adds a SYMBOL into the SYMBOL table, while doing validation chacks */
void addToSymbolTable(linkedListPtr symbols, struct Token *symbol, int status, int lineNumber)
{
	
	nodePtr newNode = (nodePtr)malloc(sizeof(node));
	newNode->symbolName = (char*)malloc(sizeof(char)* MAX_STRING_NAME);
	nodePtr curr;

	if (!newNode)
	{
		errorHandler(1, -1, "Memory allocation has failed");
		return;
	}
	if ((curr = searchSymbolNameInList(symbol->data.symbol, symbols)) == NULL) /* this is a new SYMBOL to add */
	{
		/* creating the node */
		strcpy(newNode->symbolName, symbol->data.symbol);/*initializing the fields*/
		newNode->address = NOT_DECLARED;
		newNode->data_or_instruction = NOT_DECLARED;
		newNode->entry_extern = NOT_DECLARED;
		newNode->occurrence = NULL;

		switch (status) /* which type of declaration there is... */
		{
			case CODE_SYMBOL_DECLARATION:
				newNode->address = IC;
				break;
			case CODE_SYMBOL:
				if (!add_symbol_occurrence(newNode->occurrence, IC)) return; /* adds the line to the list of occurances of this symbol */
				break;
			case DATA_SYMBOL:
				newNode->address = DC;
				newNode->data_or_instruction = DATA_SYMBOL;
				break;
			case ENTRY_SYMBOL:
			case EXTERN_SYMBOL:
				newNode->entry_extern = status;
				break;
		}
		/* linking to the tail of the list */
		newNode->next = 0;
		if (symbols->head == NULL) {
			symbols->head = newNode;
		}
		else {
			curr = symbols->head;
			while (curr->next)
				curr = curr->next;
			curr->next = newNode;
		}
		return;
	}
	else /* if the SYMBOL is already in the table */
	{
		free(newNode); /* so there is no need for this node */
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

/* this function adds a new symbol occurrence to a symbol node */
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

nodePtr searchSymbolNameInList(char* symbolName, linkedListPtr symbols)
{
    nodePtr searchedNode = symbols->head;
    while (searchedNode != NULL)
    {
        if (!strcmp(searchedNode->symbolName, symbolName))
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