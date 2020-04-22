#include "symbolsTable.h"
#include "symbolsTable.c"
#include <stdio.h>
#include <math.h>

int main()/*to compile it I need to run gcc aidTools.c -lm -o a.out
						and than ./a.out*/
{
    linkedListPtr symbolTable = newList();

    addNodeToEnd(symbolTable, "MAIN", 100, 0, 1);
    addNodeToEnd(symbolTable, "func1", 103, 0, 0);
    addNodeToEnd(symbolTable, "X", 106, 1, 1);
    addNodeToEnd(symbolTable, "Y", 107, 0, 1);
    addNodeToEnd(symbolTable, "Z" ,110, 0, 0);

    printf("addNodeToEnd(symbolTable, MAIN, 100, 0, 1) AND MORE!!   \n;");

    printf("now lets search func1: if it's in the list it will be printed now - " );
    printNode(searchSymbolNameInList( "func1", symbolTable));


    printf("now lets print the list!!!\n");

    printList(symbolTable);

    return 0;

    
    }