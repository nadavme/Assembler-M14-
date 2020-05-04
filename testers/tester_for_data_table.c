#include "memoryMap.h"
#include "symbolsTable.h"
#include <stdio.h>
#include <math.h>

int main()/*to compile it I need to run gcc aidTools.c -lm -o a.out
						and than ./a.out*/
{
    dataLinkedListPtr dataTable = newDataList();

    addStringToDataTable(dataTable, "ABCDE");
    addCharToTable(dataTable, 'W');
    addDataToTable(dataTable, 10);


    printf("now lets print the list!!!\n");
    printDataList(dataTable);

    return 0;

    
    }
