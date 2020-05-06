//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA-MMN14_FIRSTRUNOVER_H
#define MAABADA-MMN14_FIRSTRUNOVER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "symbolsTable.h"
#include "aidTools.h"

/*!
 *
 * @param linaStruct
 * @param lineIdx
 * @return
 */
int runFirst(LineStruct linaStruct, int lineIdx);

/*!
 *
 * @param line
 * @return
 */
char* commasReplacer(char* line);

/*!
 *
 * @param line
 * @return
 */
char* lineParser(char* line);

/*!
 *
 * @param parsedLine
 * @return
 */
bool isLineValid(char* parsedLine);

/*!
 *
 * @param parsedLine
 * @return
 */
bool isSymbole(char parsedLine[0]);

/*!
 *
 * @param parsedLine
 * @return
 */
char* getInstructionType(char* parsedLine);

/*!
 *
 * @param line
 * @return
 */
bool doubleCommasChecker(char* line);

/*!
 *
 * @param parsedLine
 * @return
 */
bool sanityCheck(char* parsedLine);/* a basic validation function to make sure that a line in the input file is o.k.*/




#endif //MAABADA-MMN14_FIRSTRUNOVER_H