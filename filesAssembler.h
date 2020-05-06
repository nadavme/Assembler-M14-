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