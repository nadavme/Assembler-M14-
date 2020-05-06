
/* Created by nadav on 04/02/2020.*/


#ifndef MAABADA_MMN14_AIDTOOLS_H
#define MAABADA_MMN14_AIDTOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdarg.h>
#include "permanentTables.h"
#include "memoryMap.h"
#include "symbolsTable.h"


#define EXTERN_MACRO "extern"
#define ENTRY_MACRO "entry"
#define MAX_LINE 82

#define BITS_IN_WORD 15
#define DIGITS_IN_ADDRESS 4
#define INPUT_SUFFIX ".as"
#define OUTPUT_SUFFIX ".ob"
#define EXTERN_OUTPUT_SUFFIX ".ent"
#define EXNTRY_OUTPUT_SUFFIX ".ext"
#define MAX_LINE 82
#define MEMORY_START_ADDRESS 100 /* can be changed */

extern int DC, IC;


/*a global variables needed for the assembler: */
extern short int commands_array[MAX_ARRAY]; /* this array is the commands table, declared globally. */

extern linkedListPtr symbolTable;

extern dataLinkedListPtr dataTable;



/* types of addressing modes of the command operands */
enum addressingMethods {
	instantAddressing,
	directAddressing,
	registerBypass,
	registerDirect
};

void turn_On_bit_num(int place);/*this function turn on the bit at'place' of the instruction array[ic].*/

/*!
 *
 */
void add_to_arr(int num_to_add, int toShift);/*this function is adding a number to the commands array.*/


/*!
 *
 */
typedef enum linePurposes {Tsymbol = -1, Tnumber = -2, Tinstruction = -3,
                           Tstring = -4, Tcommand = -5, Tregister = -6, 
                           TnewLine = -7, Terror = -8} ;

/*!
 *
 */
typedef enum ARE { external = 0, relocatable, absolute } ARE;



typedef struct Token
{
    int type;
    union
    {
        char symbol[31];
        string[82];
        int number;
        char tempCh;
        int command;
        int reg;
        int instruction
    } data;
} Token;

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

        int number1; /*This is where the data of type number for parameter 1 is parsed and stored, if found */

		int number2; /*This is where the data of type number for parameter 2 is parsed and stored, if found */

        unsigned int lineNumber; /*This is the genuine line number from the input.*/

        bool isTranslated; /*This is a flag, helps us to understand if there is more job on this line.*/

        int command; /*This is where the command name parsed and stored, if found.*/

        int reg_op1; /*This is where the register number parsed and stored, if found */

		int reg_op2;/*This is where the register number parsed and stored, if found */

        int operand1;/*if theres at least 1 operand than one of the values of enum 'addressingMethods' will be stored here. if theres only 1 operand
							it will contain the destination operand.*/

        int operand2;/*if theres 2 operands than one of the values of enum 'addressingMethods' will be stored here. this is for destination operand*/

        int instruction; /*This is where the instruction type name parsed and stored, if found.*/

    }data;

} LineStruct;

enum memory_word_toShift
{ 
	ERA = 0,
	DEST_ADDRESS = 3,
	SRC_ADDRESS = 7,
	COMMAND_OPCODE = 11,

	NUM = 3,
	SRC_REG = 6,
	DEST_REG = 3
};

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
int isStringValid(char array[], int length, char* string);

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