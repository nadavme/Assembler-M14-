//
// Created by nadav on 27/04/2020.
//

#ifndef MAABADA_MMN14_SECONDRUNOVER_H
#define MAABADA_MMN14_SECONDRUNOVER_H

#include "aidTools.h"
#include "filesAssembler.h"
#include "memoryMap.h"


/*!
 *
 * @param symbolTable
 * @return
 */
int secondRunOver(linkedListPtr symbolTable,dataLinkedListPtr dataTable);

#endif //MAABADA_MMN14_SECONDRUNOVER_H

/* this function adds number into the array, in all of the symbol occurrences */
void symbol2array(int number, occPtr occurrence_list);

/* this function adds number into the array, in all of the lable occurrences */
void turnOnBits2Arr(int bit, occPtr occurrence_list);

void turn_On_bit_on_cell(int place, int cell);