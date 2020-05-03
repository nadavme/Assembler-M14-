//
// Created by nadav on 27/04/2020.
//

#ifndef MAABADA_MMN14_FILESASSEMBLER_H
#define MAABADA_MMN14_FILESASSEMBLER_H

#include "filesAssembler.c"
#include "aidTools.h"
#include "firstRunOver.h"
#include <stdio.h>
#include <stdlib.h>
#include "secondRunOver.h"

/*!
 *
 * @param filesToInterpret
 * @param numOfFiles
 * @return
 */
int assembler(char const* filesToInterpret[], int numOfFiles);

/*A symbol table instance, coded by a linked list.*/
extern linkedListPtr symbolTable;

#endif //MAABADA_MMN14_FILESASSEMBLER_H