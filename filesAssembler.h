
#ifndef MAABADA_MMN14_FILESASSEMBLER_H
#define MAABADA_MMN14_FILESASSEMBLER_H

#include "aidTools.h"
#include <stdio.h>
#include <stdlib.h>
#include "secondRunOver.h"
#include "memoryMap.h"
#include "symbolsTable.h"





/*!
 *
 * @param filesToInterpret
 * @param numOfFiles
 * @return
 */
int assembler(char* filesToInterpret[], int numOfFiles);


#endif /*MAABADA_MMN14_FILESASSEMBLER_H*/