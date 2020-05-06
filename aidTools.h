
/* Created by nadav on 04/02/2020.*/


#ifndef MAABADA_MMN14_AIDTOOLS_H
#define MAABADA_MMN14_AIDTOOLS_H

#include "dataStructures.h"
#include "symbolsTable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdarg.h>
#include "memoryMap.h"


void turn_On_bit_num(int place);/*this function turn on the bit at'place' of the instruction array[ic].*/

/*!
 *
 */
void add_to_arr(int num_to_add, int toShift);/*this function is adding a number to the commands array.*/


/*!
 *
 * @param command
 * @param operands_cnt
 * @return
 */
void addToCommandsArray(LineStruct *command, int operands_cnt);

/*!
 *
 * @param x
 * @param y
 * @return
 */
int isBothOperandsRegs(int x,int y);/*this function check if both operands X and Y are using registers.*/

/*!
 *
 * @param x
 * 
 * 
 */
void weShare(LineStruct x); /*this function inserts 2 operands that use registers to 1 memory word.*/


/*!
 *
 * @param binaryNum
 * @return
 */
int bin_to_octal(int binaryNum);/*converts from binary to octal, return the result.*/


/*!
 *
 * @param array
 * @param length
 * @param string
 * @return
 */
int isStringValid(char* array[], int length, char* string);

/*!
 *
 * @param string
 * @return
 */
int isInstruction(char* string);



/*!
 *
 * @param string
 * @return
 */
int isRegister(char* string);

/*!
 *
 * @param string
 * @return
 */
int isSymbol(char* string);



/*!
 *
 * @param line
 * @return
 */
int isWhitespace(char* line);



/*!
 *
 * @param mentionLine
 * @param lineIdx
 * @param errorMsg
 * @param ...
 */
void errorHandler(bool mentionLine, int lineIdx, char* errorMsg, ...);


/*!
 *
 * @param line
 * @param currTok
 * @return
 */
char* parseByTokens(char* line, Token* currTok);


char* fillCurrLineStruct(LineStruct* currLine, char* line);


int operandsValidation(LineStruct* currLine, Token* operands, int opCounter);

int parseAddressingMethod(Token operand);


/*!
 *
 * @param file
 * @param suffix
 * @param mode
 * @return
 */
FILE* manageFiles(const char* file, char* suffix, char* mode);

void createObFile(char* fileName);

void createEntExtFiles(char* file);

#endif /*MAABADA_MMN14_AIDTOOLS_H*/