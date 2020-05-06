
/* Created by nadav on 27/04/2020.*/


#ifndef MAABADA_MMN14_SECONDRUNOVER_H
#define MAABADA_MMN14_SECONDRUNOVER_H

#include "aidTools.h"
#include "filesAssembler.h"
#include "memoryMap.h"
#include "symbolsTable.h"


/*!
 *
 * @param symbolTable
 * @return
 */
int secondRunOver();

/* this function adds number into the array, in all of the symbol occurrences */
void symbol2array(int number, occp occurrence_list);

/* this function adds number into the array, in all of the lable occurrences */
void turnOnBits2Arr(int bit, occp occurrence_list);

void turn_On_bit_on_cell(int place, int cell);

#endif /*MAABADA_MMN14_SECONDRUNOVER_H*/
