//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA_MMN14_AIDTOOLS_H
#define MAABADA_MMN14_AIDTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include "firstRunOver.h"
#include <ctype.h>
#include "permanantTables.h"
#include "main.c"

#define MAX_DIGITS_BIN 100
#define MAX_DIGITS_DEC 10
#define EXTERN_MACRO "extern"
#define ENTRY_MACRO "entry"
#define MAX_LINE 80


/* this is a token in the file. the token can be one of these following types, or a character.
each token has it's type, and some data (according to it's type) */
typedef struct instruction {
        int type;
		char string[MAX_LINE];/*I have to delete the fields that I dont use here.*/
		int number;
		char ch;
		int opCode;
		int reg;
		int instruction;
	
}instruction;

/* types of addressing modes of the command operands, from Alon, need to check if needed */
enum addressing_modes {
	instant_addressing,
	direct_addressing,
	jump_addressing,
	register_addressing
};

/* This one is from Alon, need to edit!!!!
types of tokens in the assembly program.
the token types are negative, so they will not conflict with the ASCII of a character */
enum tokens {
	lable_tok = -1,
	number_tok = -2,
	instruction_tok = -3,
	string_tok = -4,
	command_tok = -5,
	register_tok = -6,
	new_line_tok = -7,
	error_tok = -8
};



void turn_On_bit_num(int place,int ic);/*this function turn on the bit at'place' of the instruction array[ic].*/

/*!
 *
 */
void add_to_arr(int num_to_add, int toShift,int ic);

/*!
 *
 */
typedef enum opCodes { mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop } opCodes;

/*!
 *
 */
typedef enum addressingMethod { immediate = 0, direct, reg } addrMethod;



typedef enum linePurposes {Tsymbol = -1, Tnumber = -2, Tinstruction = -3,
                           Tstring = -4, Tcommand = -5, Tregister = -6,
                           TnewLine = -7, Terror = -8} ;

/*!
 *
 */
typedef enum opCodes { mov, cmp, add, sub, not, clr, lea, inc, dec, jmp, bne, red, prn, jsr, rts, stop } opCodes;

/*!
 *
 */
typedef enum addressingMethod { immediate = 0, direct, regIndirect, regDirect } addrMethod;







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
typedef  enum isThatExtern {no, yes} isThatExtern;

/*!
 *
 */
typedef struct LineStruct
{
    int theLinePurpose;
    union
    {
        char* line;
        char* symbolName;
        char* string;
        int number;
        unsigned int lineNumber;
        bool isTranslated;
        int command;
        int reg;
        int instruction;
        int L = 1;
    }data;

} lineStruct;

enum memory_word_toShift { /*from Alon need to change a bit*/
	ERA = 0,
	DEST_ADDRESS = 3,
	SRC_ADDRESS = 7,
	COMMAND_OPCODE = 11,
	PARAM_2 = 10,/*do I need to delete this one and next one??????*/
	PARAM_1 = 12,

	NUM = 3,
	SRC_REG = 8,
	DEST_REG = 2
};

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
int isStringValid(char array[], int length, char* string);

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
StatusCode trimOperand(char* operand);

void errorHandler(bool mentionLine, int lineIdx, char* errorMsg);

char* parseIntoLineStruct(struct LineStruct* currLine);

#endif //MAABADA_MMN14_AIDTOOLS_H
