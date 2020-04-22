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




typedef struct first_word /*we've choosed to define the machine language word with bit fields, lets see how it goes... Nadav The king, Matan the princess ;-) */
{
    unsigned short external : 1;/*E*/
    unsigned short relocatable : 1; /*R*/
    unsigned short absolute : 1;/*A*/

    unsigned short destination_0 : 1; /*this bit is turned on iff method 0 is used for destination operand */
    unsigned short destination_1 : 1; /*this bit is turned on iff method 1 is used for destination operand */
    unsigned short destination_2 : 1; /*this bit is turned on iff method 2 is used for destination operand */
    unsigned short destination_3 : 1; /*this bit is turned on iff method 3 is used for destination operand */

    unsigned short source_0 : 1; /*this bit is turned on iff method 0 is used for source operand */
    unsigned short source_1 : 1; /*this bit is turned on iff method 1 is used for source operand */
    unsigned short source_2 : 1; /*this bit is turned on iff method 2 is used for source operand */
    unsigned short source_3 : 1; /*this bit is turned on iff method 3 is used for source operand */

    unsigned int opCode : 4; /*this bits will contain the operation code*/
}first_word;

typedef struct second_word /*word for methods 0,1 (mio'n methods)*/
{


    unsigned short op_is_external : 1; /*E*/
    unsigned short op_is_relocatable : 1; /*R*/
    unsigned short op_is_absolute : 1; /*A*/

    unsigned short num_or_address : 12;/*in this 12 bits we'll store the actual value or the memory address.*/
}second_word;

typedef struct third_word /*word for methods 2,3 (mio'n methods)*/
{


    unsigned short op_is_external : 1; /*E*/
    unsigned short op_is_relocatable : 1; /*R*/
    unsigned short op_is_absolute : 1; /*A*/

    unsigned short destination_register : 3;/*this bits will contain the number of register which has the 
                                                                            memory address of the value of the destination operand. */
    
    unsigned short source_register : 3;/*this bits will contain the number of register which has the 
                                                                            memory address of the value of the source operand. */
}third_word;

char* commasReplacer(char* line);

char* lineParser(char* line);

bool isLineValid(char* parsedLine);

bool isSymbole(char parsedLine[0]);

char getInstructionType(char* parsedLine);

bool doubleCommasChecker(char* line);

bool sanityCheck(char* parsedLine);/* a basic validation function to make sure that a line in the input file is o.k.*/




#endif //MAABADA-MMN14_FIRSTRUNOVER_H
