//
// Created by nadav on 27/04/2020.
//

#ifndef MAABADA_MMN14_FILESASSEMBLER_H
#define MAABADA_MMN14_FILESASSEMBLER_H

#include "aidTools.h"
#include "firstRunOver.h"
#include <stdio.h>
#include <stdlib.h>
#include "secondRunOver.h"
#include "memoryMap.h"

extern int DC, IC;

extern MEMORY_START_ADDRESS 100 /* can be changed */

/*a global variables needed for the assembler: */
extern short int commands_array[MAX_ARRAY]; /* this array is the commands table, declared globally. */

extern int wordsWithoutARE[MAX_ARRAY];/*this global array will contain the addresses of words which has at least 1 operand in
direct addressing (has an operand represented as label), this words also doesnt has a value yet, because the label might
not have defined yet.*/

extern linkedListPtr symbolTable;

extern dataLinkedListPtr dataTable;

#define INPUT_SUFFIX ".as"
#define OUTPUT_SUFFIX ".ob"
#define EXTERN_OUTPUT_SUFFIX ".ent"
#define EXNTRY_OUTPUT_SUFFIX ".ext"
#define MAX_LINE 82


/*!
 *
 * @param filesToInterpret
 * @param numOfFiles
 * @return
 */
int assembler(char const* filesToInterpret[], int numOfFiles);


#endif //MAABADA_MMN14_FILESASSEMBLER_H