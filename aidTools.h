//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_AIDTOOLS_H
#define MAABADA_MMN14_AIDTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "firstRunOver.h"
#include <ctype.h>

#define MAX_DIGITS_BIN 100
#define MAX_DIGITS_DEC 10
#define EXTERN "extern"
#define ENTRY "entry"



/*!
 *
 */
typedef struct codeNode{ /*we've decided to implement the code table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    second_word data;/*this is not the right word, I need to find the right one*/
    struct codeNode *next;
}*codeNodePtr, codeNode;

/*!
 *
 */
typedef struct codeLinkedList {
    int size;
    codeNodePtr head;
}*codeLinkedListPtr;

/*!
 *
 */
typedef enum opCodes { mov, cmp, add, sub, nnot, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop } opCodes;

/*!
 *
 */
typedef enum addressingMethod { immediate = 0, direct, reg } addrMethod;

/*!
 *
 */
typedef enum ARE { absolute = 0, external, relocatable } ARE;

/*!
 *
 */
typedef enum symbolType { tCode, tData, tString} symbolType;

/*!
 *
 */
typedef  enum isThatExtern {no, yes} isExtern;

/*!
 *
 */
typedef struct lineStruct
{
    char* originalLine;
    char* symbol;
    first_word* translatedWord;
    unsigned char opRepeat;
    unsigned int lineNumber;
    char done;
} lineStruct;

/*!
 *
 * @param binaryNum
 * @return
 */
int bin_to_octal(int binaryNum);/*converts from binary to octal, return the result.*/

/*!
 *
 * @param dec
 * @return
 */
int dec_to_bin(char dec[]); /*converts from decimal to binary, prints the result.*/

/*!
 *
 * @param array
 * @param length
 * @param string
 * @return
 */
int isStringValid(char **array, int length, char* string);

/*!
 *
 * @param string
 * @return
 */
int isInstruction(char* string)

/*!
 *
 * @param string
 * @return
 */
int isData(char* string)

/*!
 *
 * @param string
 * @return
 */
int isRegister(char* string)

/*!
 *
 * @param string
 * @return
 */
int isExtern(char* string)

/*!
 *
 * @param string
 * @return
 */
int isEntry(char* string)

/*!
 *
 * @param line
 * @return
 */
int isWhitespace(char* line)

/*!
 *
 * @param string
 * @return
 */
int isInt(char* string)

/*!
 *
 * @param code
 * @param source
 * @param dest
 * @return
 */
int isValidSourceDest(OpCodes code,opType source, opType dest)


/*!
 *
 * @param operand
 * @return
 */
StatusCode trimOperand(char* operand)

#endif //MAABADA_MMN14_AIDTOOLS_H
