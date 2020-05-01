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
#include <stdarg.h>
#include "permanantTables.h"
#include "main.c"

#define MAX_DIGITS_BIN 100
#define MAX_DIGITS_DEC 10
#define EXTERN_MACRO "extern"
#define ENTRY_MACRO "entry"
#define MAX_LINE 80


/* types of addressing modes of the command operands */
enum addressing_modes {
	instant_addressing,
	direct_addressing,
	register_bypass,
	register_direct
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
	bypass_register_tok = -6,
    register_tok = -7,
	new_line_tok = -8,
	error_tok = -9
};



void turn_On_bit_num(int place,int ic);/*this function turn on the bit at'place' of the instruction array[ic].*/

/*!
 *
 */
void add_to_arr(int num_to_add, int toShift);/*this function is adding a number to the commands array.*/

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
typedef enum addressingMethod { immediate = 0, direct, regIndirect, regDirect } addrMethod;







/*!
 *
 */
typedef enum ARE { relocatable = 0, external, absolute } ARE;

/*!
 *
 */
typedef enum symbolType { tCode, tData, tString} symbolType;

/*!
 *
 */
typedef  enum isThatExtern {no, yes} isThatExtern;

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


/*!
 *This struct allows us to take a line from the input file and manipulate it, so we can assemble her to a machine
 * language code.
 */
typedef struct LineStruct
{
    int theLinePurpose; /*the line type/ purpose out of LinePurposes that declared above.*/
    
    union
    {
        char* line; /*This is the genuine line from the input, and we run over her*/

        char* symbolName; /*This is where the symbol name parsed and stored, if found.*/

        char* string; /*This is where the data of type string is parsed and stored, if found.*/

        int number; /*This is where the data of type number is parsed and stored, if found*/

        unsigned int lineNumber; /*This is the genuine line number from the input.*/

        bool isTranslated; /*This is a flag, helps us to understand if there is more job on this line.*/

        int command; /*This is where the command name parsed and stored, if found.*/

        int reg; /*This is where the register name parsed and stored, if found.*/

        int opernad1;/*if theres at least 1 operand than one of the values of enum 'linePurposes' will be stored here.*/

        int operand2;/*if theres 2 operands than one of the values of enum 'linePurposes' will be stored here.*/

        int instruction; /*This is where the instruction type name parsed and stored, if found.*/

        /*todo: optional*/
        int L = 1; /*num of machine words needed.*/
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
	SRC_REG = 6,
	DEST_REG = 3
};

int isBothOperandsRegs(lineStruct x,lineStruct y);/*this function check if both operands X and Y are using registers.*/

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
int isSymbol(char* string)

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

void errorHandler(bool mentionLine, int lineIdx, char* errorMsg, ...);

char* parseIntoLineStruct(struct LineStruct* currLine);

#endif //MAABADA_MMN14_AIDTOOLS_H
