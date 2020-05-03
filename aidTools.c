//
// Created by nadav on 04/02/2020.
//

#include "aidTools.h"

int bin_to_octal(int binaryNum) /*this function converts a number from binary base to octal base, I used a method that we have learned in class.*/
{
    int i = 0, j = 0;
    int sum = 0;
    int midSum = 0;

    while (binaryNum != 0)
    {
        midSum = 0;
        for (j = 0; j < 3; j++) /*the function basically looks at the 3 most right bits, and check for each bit from right to left - if it's on we add 1 
		multyplied by 2 to the power of the place of the bit (0/1/2) to midSum.*/
        {
            if (binaryNum & 1 == 1)
            {
                midSum = midSum + (int)pow(2, j);
            }
            binaryNum = binaryNum >> 1;
        }
        sum = sum + (int)midSum * pow(10, i); /*we add midSum that fit the right digit*/
        i++;
    }
    return sum;
}

int dec_to_bin(char dec[])
{
    char binNum[MAX_DIGITS_BIN] = {'0', '\0'}; /*creating a char array (a string) which will express the binary 	       number.  the first cell in the array contains the char 0 representation, and all other cells in the 			array 	contain of the integer 0.*/
    int string_length;
    int i;
    char tmp;

    unsigned int decInt = strtoul(dec, NULL, 10); /*converting the decimal number (string) to int*/
    i = 0;
    while (decInt != 0)
    {
        binNum[i] = '0' + decInt % 2; /*collecting the remainders from devision by 2 at the array*/
        decInt = decInt / 2;          /*deviding by 2 (basically cutting out the fractions)*/
        i++;
    }

    /* step 2: reverse string */
    string_length = 0;
    while (binNum[string_length] != '\0')
        string_length = string_length + 1;

    for (i = 0; i < string_length / 2; i++)
    {
        tmp = binNum[i];
        binNum[i] = binNum[string_length - i - 1];
        binNum[string_length - i - 1] = tmp;
    }

    printf("%s\n", binNum); /*printing the binary number*/

    return 0;
}

void printBits(size_t const size, void const *const ptr) /*the function prints the binary representation of any type.
size is the number of bytes. an example can be seen in tester_for_matrix.c */
{
    unsigned char *b = (unsigned char *)ptr;
    unsigned char byte;
    int i, j;

    for (i = size - 1; i >= 0; i--)
    {
        for (j = 7; j >= 0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

/* this function adds a number to the instruction array.
 toShift is the number of bits that is required to set the number in it's place.
example: the call: add_to_arr(2,6), adds the number 2 (in binary) to the 7'th bit.*/
void add_to_arr(int num_to_add, int toShift)
{
    commands_array[ic] |= (num_to_add << toShift);
}

void turn_On_bit_num(int place) /*this function turn on the bit at 'place' of the instruction array[ic].*/
{
    commands_array[ic] = (commands_array[ic] | (int)pow(2, place));
}

/*
this function gets a lineStruct, and returns it's addressing mode:
instant_addressing,
direct_addressing,
register_bypass
or register_direct.
if it's not one of the above - the function returns -1 */
int get_addressing_mode(int operandMethod, int destOrSrc)
{
    if (destOrSrc == DEST_ADDRESS)
    {
        if (operandMethod == instant_addressing)
        {
            return (instant_addressing + DEST_ADDRESS);
        }
        else if (operandMethod == direct_addressing) /*in this case were dealing with the direct addresing method.*/
        {
            return (direct_addressing + DEST_ADDRESS);
        }
        else if (operandMethod == register_bypass)
        {
            return (DEST_ADDRESS + register_bypass);
        }

        else if (operandMethod == register_direct)
        {
            return (DEST_ADDRESS + register_direct);
        }
        else
        {
            return -1;
        }
    }
    else if (destOrSrc == SRC_ADDRESS)
    {
        if (operandMethod == instant_addressing)
        {
            return (instant_addressing + SRC_ADDRESS);
        }
        else if (operandMethod == direct_addressing) /*in this case were dealing with the direct addresing method.*/
        {
            return (direct_addressing + SRC_ADDRESS);
        }
        else if (operandMethod == register_bypass)
        {
            return (SRC_ADDRESS + register_bypass);
        }

        else if (operandMethod == register_direct)
        {
            return (SRC_ADDRESS + register_direct);
        }
        else
        {
            return -1;
        }
    }
}

/*we've decided to implement the instructions table as an array. this function adds a command to the instructions array.
this function get called only after all checks for valid input are o.k.*/
void add_to_comands_array(lineStruct *command, int operands_cnt)
{
    int i;
    /* adding the command word now.*/
    add_to_arr(command->data.command, COMMAND_OPCODE); /*the opCode in the word is at bit number 11*/
    turn_On_bit_num(absolute);
    if (operands_cnt == 0) /* no operadnds to add */
    {
        return;
    }
    else if (operands_cnt == 1)
    {
        turn_On_bit_num(get_addressing_mode(command->data.opernad1, DEST_ADDRESS));
    }
    else if (operands_cnt == 2)
    {
        turn_On_bit_num(get_addressing_mode(command->data.operand2, DEST_ADDRESS)); /*turning on bit that represent the correct addressing method for destination operand*/
        turn_On_bit_num(get_addressing_mode(command->data.operand1, SRC_ADDRESS));  /*turning on bit that represent the correct addressing method for source operand*/
    }
    ic++;

    /* adding the other memory words: */

    {
        /*if we are dealing with symbols here, let this code free (after edit)
		if (operands[i].type == lable_tok)
		{
			add2lable_table(&lable_list, &(operands[i]), CODE_LABLE); /* CODE_LABLE is the type of lable to be added 
		}
		else*/
        if ((command->data.operand1 != -1) && (command->data.operand2 != -1)) /*might check null, possible bug!!*/
        {
            if (isBothOperandsRegs(command->data.operand1, command->data.operand2) == 1)
            {
                /*this is the case when both operands share one memory word*/
                weShare(*command);
                return;
            }
        }
        if (command->data.operand1 != -1)
        {
            if (command->data.operand1 == instant_addressing) /*in case were dealing with instant mio'n*/
            {
                add_to_arr(command->data.number1, NUM); /* adds after the E,A,R part of the memory word */
                turn_On_bit_num(absolute);
                ic++;
            }

            else if (command->data.operand1 == direct_addressing) /*in case were dealing with a direct mio'n*/
            {
                wordsWithoutARE[ic] = 1;
                ic++;
            }

            else if (command->data.operand1 == register_bypass) /*in case were dealing with bypass register mio'n*/
            {
                if (operands_cnt == 1)
                {
                    add_to_arr(command->data.reg_op1, DEST_ADDRESS); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    ic++;
                    return;
                }
                else
                {
                    add_to_arr(command->data.reg_op1, 6); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    ic++;
                }
            }

            else if (command->data.operand1 == register_direct)
            {
                if (operands_cnt == 1)
                {
                    add_to_arr(command->data.reg_op1, DEST_ADDRESS); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    ic++;
                    return;
                }
                else
                {
                    add_to_arr(command->data.operand1, 6);
                    turn_On_bit_num(absolute);
                    ic++;
                }
            }

            if (command->data.operand2 != -1) /*if we have 2 operands...
             a possible bug - this next block should be outside the previous if...*/
            {
                if (command->data.operand2 == instant_addressing) /*in case were dealing with instant mio'n*/
                {
                    add_to_arr(command->data.number2, NUM); /* adds after the E,A,R part of the memory word */
                    turn_On_bit_num(absolute);
                    ic++;
                }

                else if (command->data.operand2 == direct_addressing) /*in case were dealing with a direct mio'n*/
                {
                    wordsWithoutARE[ic] = 1;
                    ic++;
                }

                else if (command->data.operand2 == register_bypass) /*in case were dealing with bypass register mio'n*/
                {
                    add_to_arr(command->data.reg_op2, DEST_ADDRESS); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    ic++;
                }

                else if (command->data.operand2 == register_direct) /*in case were dealing with direct register mio'n*/
                {
                    add_to_arr(command->data.reg_op2, DEST_ADDRESS);
                    turn_On_bit_num(absolute);
                    ic++;
                }
            }
        }
    }
}

int isBothOperandsRegs(int x, int y) /*this function is checking if both operands use registers mio'n method.*/
{
    if ((x == register_bypass && y == register_bypass) || (x == register_bypass && y == register_direct) || (x == register_direct && y == register_bypass) || (x == register_direct && y == register_direct))
    {
        return 1;
    }
    return 0;
}

void weShare(lineStruct x) /*this function inserts 2 operands that use registers to 1 memory word.*/
{
    add_to_arr(x.data.reg_op1,SRC_REG);
    add_to_arr(x.data.reg_op2,DEST_REG);
    turn_On_bit_num(absolute);
    ic++;
}

int isStringValid(char array[], int length, char *string)
{
    /*The function allows validation of any string(operation, register, etc.)*/
    int i;
    for (i = 0; i < length; i++)
    {
        if (strcmp(array[i], string) == 0)
            return 0;
    }
    return -1;
}

int isInstruction(char *string)
{
    return isStringValid(validInstructions, strlen(string), string);
}

int isCommand(char *string)
{
    int i;
    /*register prefix*/
    if (string[0] != 'r')
    {
        for (i = 0; commandTable[i].codeName; i++)
        {
            if (strcmp(string, commandTable[i].codeName) == 0)
                return i;
        }
    }
    return -1; /*in case it's not a command*/
}

int isRegister(char *string)
{
    int i;
    /*register prefix*/
    if (string[0] != 'r')
    {
        for (i = 0; validRegisters[i].regName; i++)
        {
            if (strcmp(string, validRegisters[i].regName) == 0)
                return i;
        }
    }
    return -1; /*in case it's not a command*/
}

int isSymbol(char *string)
{
    int i;

    /*validate every char on symbol*/
    /*make sure all are letters or digits*/
    for (i = 0; i < strlen(string); i++)
        if (!isalnum(string[i]))
            return 0;

    /*symbol name must starts with a letter*/
    if (!isalpha(string[0]))
        return 0;

    return 1;
}

//int isData(char* string)
//{
//    if ((unsigned char)(*string) == '.')
//    {
//        string++;
//        return isStringValid(dataTypes, NUM_OF_DATA_TYPES, string);
//    }
//    else
//        return 0;
//}

int isExtern(char *string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(EXTERN_MACRO, string) == 0);
    }
    else
        return 0;
}

int isEntry(char *string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(ENTRY_MACRO, string) == 0);
    }
    else
        return 0;
}

int isWhitespace(char *line)
{
    while (*line != '\0')
    {
        if (!isspace((unsigned char)(*line)))
            return 0;
        line++;
    }
    return 1;
}

int isInt(char *string)
{
    char *ptr;
    long int result;
    strtol(string, &ptr, 10);
    result = strtol(string, &ptr, 10);
    (void)result;
    return (isWhitespace(ptr) || *ptr == '\0'); /* If the rest of the string is empty it still counts as an int*/
}

//int isValidSourceDest(OpCodes code,opType source, opType dest)
//{
//    int result = 0;
//    switch(code)
//    {
//        case mov:
//            result = dest != Immediate;
//            break;
//        case cmp:
//            result = 1;
//            break;
//        case add:
//        case sub:
//        case nnot:
//        case clr:
//            result = dest != Immediate;
//            break;
//        case lea:
//            result = (source == Direct || source == Struct) && dest != Immediate;
//            break;
//        case inc:
//        case dec:
//        case jmp:
//        case bne:
//        case red:
//            result = dest != Immediate;
//            break;
//        case prn:
//            result = 1;
//            break;
//        case jsr:
//            result = dest != Immediate;
//            break;
//        case rts:
//        case stop:
//            result = 1;
//            break;
//    }
//    return result;
//}

///*The function trim the operand and checks if there's more then one operand*/
//StatusCode trimOperand(char* operand)
//{
//    char first[LINE_LENGTH];
//    char second[LINE_LENGTH];
//    if(sscanf(operand,"%s %s",first,second) != 1) /* Testing if there is more than 1 operand */
//        return wrong_number_of_operands;
//    else
//        strcpy(operand,first);
//    return success;
//}

void errorHandler(bool mentionLine, int lineIdx, char *errorMsg, ...)
{
    va_list parameters_to_print;
    va_start(parameters_to_print, errorMsg);
    if (mentionLine == 0)
        fprintf(stderr, "Error found in line %d: %s\n", lineIdx, errorMsg);
    else
        fprintf(stderr, "%s\n", errorMsg);
    vfprintf(stderr, errorMsg, parameters_to_print);
    fprintf(stderr, "\n");
    va_end(parameters_to_print);
}

char *parseIntoLineStruct(struct LineStruct *currLine)
{

    char token[30];
    int idx;

    idx = 0;

    /*Skip all white spaces at the the beginning of the line*/
    while (isWhitespace(currLine->data.line))
        currLine->data.line++;

    /*Check for a number*/
    if ((isdigit(*currLine->data.line)) || (*currLine->data.line == '-'))
    {
        do
        {
            token[idx++] = *currLine->data.line;
            currLine->data.line++;
        } while (isdigit(*currLine->data.line));
        token[idx] = '\0';
        currLine->theLinePurpose = Tnumber;
        currLine->data.number = atoi(token);
    }
    else if (*currLine->data.line == '.') /*Check for instruction prefix*/
    {
        do
        {
            token[idx] = *currLine->data.line;
            currLine->data.line++;
        } while (!isspace(*currLine->data.line));
        token[idx++] = '\0';

        /*Check for instruction*/
        if ((currLine->data.instruction = isInstruction(token)) >= 0)
        {
            currLine->theLinePurpose = Tinstruction;
        }
        /*We figure out its not an instruction thus its not valid*/
        else
            currLine->theLinePurpose = Terror;
    }

    else if (*currLine->data.line == '\n')
    {
        currLine->theLinePurpose = TnewLine;
        currLine->data.line++;
    }

    /*Check if the line is a symbol, command or a register*/
    else if (isalnum(*currLine->data.line))
    {
        do
        {
            token[idx] = *currLine->data.line;
            currLine->data.line++;
        } while (isalnum(*currLine->data.line));
        token[idx] = '\0';

        /*Check for command*/
        if ((currLine->data.command = isCommand(token)) >= 0)
        {
            currLine->theLinePurpose = Tcommand;
            if (!isspace(*currLine->data.line))
                currLine->theLinePurpose = Terror;
        }

        /*In case we found a match to a valid register.*/
        else if ((currLine->data.reg = isRegister(token)) >= 0)
            currLine->theLinePurpose = Tregister;

        /*If all is false, we understand it's a symbol.*/
        else if (isSymbol(token))
        {
            /*This symbol needs to be added to the symbol table.*/
            currLine->theLinePurpose = Tsymbol;
            strcpy(currLine->data.symbolName, token);
        }
        else
            currLine->theLinePurpose = Terror;
    }
    else

    /*We understand that the line is a special character. returns the ascii value of the character.*/
    {
        currLine->theLinePurpose = currLine->data.line;
        currLine->data.line++;
    }
}
