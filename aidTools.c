//
// Created by nadav on 04/02/2020.
//

#include "aidTools.h"

int bin_to_octal(int binaryNum) 
/*this function converts a number from binary base to octal base, I used a method that we have learned in class.*/
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


/* this function adds a number to the instruction array.
 toShift is the number of bits that is required to set the number in it's place.
example: the call: add_to_arr(2,6), adds the number 2 (in binary) to the 7'th bit.*/
void add_to_arr(int num_to_add, int toShift)
{
    commands_array[IC] |= (num_to_add << toShift);
}

void turn_On_bit_num(int place) /*this function turn on the bit at 'place' of the instruction array[ic].*/
{
    commands_array[IC] = (commands_array[IC] | (int)pow(2, place));
}

/*
this function gets a LineStruct, and returns it's addressing mode:
instantAddressing,
directAddressing,
registerBypass
or registerDirect.
if it's not one of the above - the function returns -1 */
int get_addressing_mode(int operandMethod, int destOrSrc)
{
    if (destOrSrc == DEST_ADDRESS)
    {
        if (operandMethod == instantAddressing)
        {
            return (instantAddressing + DEST_ADDRESS);
        }
        else if (operandMethod == directAddressing) /*in this case were dealing with the direct addresing method.*/
        {
            return (directAddressing + DEST_ADDRESS);
        }
        else if (operandMethod == registerBypass)
        {
            return (DEST_ADDRESS + registerBypass);
        }

        else if (operandMethod == registerDirect)
        {
            return (DEST_ADDRESS + registerDirect);
        }
        else
        {
            return -1;
        }
    }
    else if (destOrSrc == SRC_ADDRESS)
    {
        if (operandMethod == instantAddressing)
        {
            return (instantAddressing + SRC_ADDRESS);
        }
        else if (operandMethod == directAddressing) /*in this case were dealing with the direct addresing method.*/
        {
            return (directAddressing + SRC_ADDRESS);
        }
        else if (operandMethod == registerBypass)
        {
            return (SRC_ADDRESS + registerBypass);
        }

        else if (operandMethod == registerDirect)
        {
            return (SRC_ADDRESS + registerDirect);
        }
        else
        {
            return -1;
        }
    }
}

/*we've decided to implement the instructions table as an array. this function adds a command to the instructions array.
this function get called only after all checks for valid input are o.k.*/
void addToCommandsArray(LineStruct *command, int operands_cnt)
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
        turn_On_bit_num(get_addressing_mode(command->data.operand1, DEST_ADDRESS));
    }
    else if (operands_cnt == 2)
    {
        turn_On_bit_num(get_addressing_mode(command->data.operand2, DEST_ADDRESS)); /*turning on bit that represent the correct addressing method for destination operand*/
        turn_On_bit_num(get_addressing_mode(command->data.operand1, SRC_ADDRESS));  /*turning on bit that represent the correct addressing method for source operand*/
    }
    IC++;

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
            if (command->data.operand1 == instantAddressing) /*in case were dealing with instant mio'n*/
            {
                add_to_arr(command->data.number1, NUM); /* adds after the E,A,R part of the memory word */
                turn_On_bit_num(absolute);
                IC++;
            }

            else if (command->data.operand1 == directAddressing) /*in case were dealing with a direct mio'n*/
            {
                IC++;
            }

            else if (command->data.operand1 == registerBypass) /*in case were dealing with bypass register mio'n*/
            {
                if (operands_cnt == 1)
                {
                    add_to_arr(command->data.reg_op1, DEST_ADDRESS); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    IC++;
                    return;
                }
                else
                {
                    add_to_arr(command->data.reg_op1, 6); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    IC++;
                }
            }

            else if (command->data.operand1 == registerDirect)
            {
                if (operands_cnt == 1)
                {
                    add_to_arr(command->data.reg_op1, DEST_ADDRESS); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    IC++;
                    return;
                }
                else
                {
                    add_to_arr(command->data.operand1, 6);
                    turn_On_bit_num(absolute);
                    IC++;
                }
            }

            if (command->data.operand2 != -1) /*if we have 2 operands...
             a possible bug - this next block should be outside the previous if...*/
            {
                if (command->data.operand2 == instantAddressing) /*in case were dealing with instant mio'n*/
                {
                    add_to_arr(command->data.number2, NUM); /* adds after the E,A,R part of the memory word */
                    turn_On_bit_num(absolute);
                    IC++;
                }

                else if (command->data.operand2 == directAddressing) /*in case were dealing with a direct mio'n*/
                {
                    IC++;
                }

                else if (command->data.operand2 == registerBypass) /*in case were dealing with bypass register mio'n*/
                {
                    add_to_arr(command->data.reg_op2, DEST_ADDRESS); /*adding the number of register to the right bits.*/
                    turn_On_bit_num(absolute);
                    IC++;
                }

                else if (command->data.operand2 == registerDirect) /*in case were dealing with direct register mio'n*/
                {
                    add_to_arr(command->data.reg_op2, DEST_ADDRESS);
                    turn_On_bit_num(absolute);
                    IC++;
                }
            }
        }
    }
}

int isBothOperandsRegs(int x, int y) /*this function is checking if both operands use registers mio'n method.*/
{
    if ((x == registerBypass && y == registerBypass) || (x == registerBypass && y == registerDirect) || (x == registerDirect && y == registerBypass) || (x == registerDirect && y == registerDirect))
    {
        return 1;
    }
    return 0;
}

void weShare(LineStruct x) /*this function inserts 2 operands that use registers to 1 memory word.*/
{
    add_to_arr(x.data.reg_op1,SRC_REG);
    add_to_arr(x.data.reg_op2,DEST_REG);
    turn_On_bit_num(absolute);
    IC++;
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
        for (i = 0; commandsTable[i].codeName; i++)
        {
            if (strcmp(string, commandsTable[i].codeName) == 0)
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
    return -1; /*in case it's not a register*/
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

char *parseByTokens(char* line, Token *currTok)
{

    char token[30];
    int idx;

    idx = 0;

    /*Skip all white spaces at the the beginning of the line*/
    while (isWhitespace(line))
        line++;

    /*Check for a number*/
    if ((isdigit(*line)) || (*line == '-'))
    {
        do
        {
            token[idx++] = *line;
            line++;
        } while (isdigit(*line));
        token[idx] = '\0';
        currTok->type = Tnumber;
        currTok->data.number = atoi(token);
    }
    else if (*line == '.') /*Check for instruction prefix*/
    {
        do
        {
            token[idx] = *line;
            line++;
        } while (!isspace(*line));
        token[idx++] = '\0';

        /*Check for instruction*/
        if ((currTok->data.instruction = isInstruction(token)) >= 0)
        {
            currTok->type = Tinstruction;
        }
        /*We figure out its not an instruction thus its not valid*/
        else
            currTok->type = Terror;
    }

    else if (*line == '\n')
    {
        currTok->type = TnewLine;
        line++;
    }

    /*Check if the line is a symbol, command or a register*/
    else if (isalnum(*line))
    {
        do
        {
            token[idx] = *line;
            line++;
        } while (isalnum(*line));
        token[idx] = '\0';

        /*Check for command*/
        if ((currTok->data.command = isCommand(token)) >= 0)
        {
            currTok->type = Tcommand;
            if (!isspace(*line))
                currTok->type = Terror;
        }

        /*In case we found a match to a valid register.*/
        else if ((currTok->data.reg = isRegister(token)) >= 0)
            currTok->type = Tregister;

        /*If all is false, we understand it's a symbol.*/
        else if (isSymbol(token))
        {
            /*This symbol needs to be added to the symbol table.*/
            currTok->type = Tsymbol;
            strcpy(currTok->data.symbolName, token);
        }
        else
            currTok->type = Terror;
    }
    else

    /*We understand that the line is a special character. returns the ascii value of the character.*/
    {
        currTok->type = *line;
        line++;
    }
    return line;
}

char* fillCurrLineStruct(struct LineStruct* currLine, char* line)
{
    int opCounter = 0; /* how many operands found in the line read */
    Token operands[2 + 1]; /* 1 for the new line */


    /* Getting the the first operand into an array of operands */
    line = parseByTokens(line, &(operands[opCounter]));/*[0]*/

    if (operands[opCounter].type == Tnumber) /* Number must follow an '#' */
    {
        errorHandler(0, (int) currLine->data.lineNumber, "In a command, a number must"
                                                         " follow an  hash ('#') sign");
        return line;
    }
    if (operands[opCounter].type == '#') /* InstantAddressing */
    {
        line = parseByTokens(line, &(operands[opCounter]));/* Get the number */



        if (operands[opCounter].type != Tnumber) /* In a case of a # sign without a number after */
        {
            errorHandler(0, (int) currLine->data.lineNumber,  "In a command, a number must "
                                                        "follow an  hash ('#') sign");
            return line;
        }

        currLine->data.number1 = (operands[opCounter]).data.number;
        currLine->data.operand1 = instantAddressing;
    }

    if (operands[opCounter].type == '*') /* registerBypassAddressing */
    {
        line = parseByTokens(line, &(operands[opCounter])); /* Get the register */

        if (operands[opCounter].type != Tregister) /* In a case of a * sign without a register after */
        {
            errorHandler(0, (int) currLine->data.lineNumber,  "In a command, a * must "
                                                              "be followed by a register");
            return line;
        }

        currLine->data.reg_op1 = (operands[opCounter]).data.reg;
        currLine->data.operand1 = registerBypass;
    }
    /*We collected one operand so far*/

    if (operands[opCounter].type != TnewLine) /* If true - it means there are operands */
    {
        opCounter++;

        line = parseByTokens(line, &(operands[opCounter]));

        /*We collected two operands so far*/

        if (operands[opCounter].type == ',') /* So 2 operands are expected, separated by a comma */
        {
            line = parseByTokens(line, &(operands[opCounter])); /* Get the second operand */

            if (operands[opCounter].type == Tnumber) /* In a case of a # sign without a number after */
            {
                errorHandler(0, (int) currLine->data.lineNumber, "number must begin"
                                                                 " with hash ('#') sign");
                return line;
            }
            if (operands[opCounter].type == '#') /* instantAddressing */
            {
                line = parseByTokens(line, &(operands[opCounter])); /* Get the number */

                if (operands[opCounter].type != Tnumber) /* In a case of a # sign without a number after */
                {
                    errorHandler(0 , (int) currLine->data.lineNumber, "number must follow '#'");
                    return line;
                }

                currLine->data.number2 = (operands[opCounter]).data.number;
                currLine->data.operand2 = instantAddressing;
            }

            if (operands[opCounter].type == '*') /* registerBypassAddressing */
            {

                line = parseByTokens(line, &(operands[opCounter])); /* Get the register */


                if (operands[opCounter].type != Tregister) /* a * sign without a register after */
                {
                    errorHandler(0, (int) currLine->data.lineNumber,  "In a command, a * must "
                                                                      "be followed by a register");
                    return line;
                }

                currLine->data.reg_op2 = (operands[opCounter]).data.reg;
                currLine->data.operand2 = registerBypass;

            }

            if (operands[opCounter].type == TnewLine) /* Missing an operand */
            {
                errorHandler(0, (int) currLine->data.lineNumber, "comma at the end of the line");
            }
            else /* A valid operand */
            {
                opCounter++; /* Two operands */

                line = parseByTokens(line, &(operands[opCounter]));

                if (operands[opCounter].type != TnewLine) /* After two operands the end of the line char must appears */
                {
                    errorHandler(0, (int) currLine->data.lineNumber,"invalid parameter"
                                                                    " after the operands ");
                    return line;
                }
            }
        }
    }

    /*Operands validation checks- if not valid, return without translating the lines*/
    if (!operandsValidation(currLine, operands, opCounter))
    {
        return line;
    }



    /* Adds the commands and the operands into the instruction array */
    addToCommandsArray(currLine, opCounter);
    return line;
}

/*todo: edit comments*/
int operandsValidation(LineStruct* currLine, Token* operands, int opCounter)
{
    int numOfOperands = commandsTable[currLine->data.command].numOfOperands; /* getting the data from the commands table */

    /* checking the amount of operands accepted */
    if (numOfOperands != opCounter)
    {
        errorHandler(0, (int) currLine->data.lineNumber,"Number of operands accepted is not"
                                                        " matching the amount by the commandsTable.");
        return 1;
    }

    /* validating the addressingMethods for this command */

    if (numOfOperands == 0)
    {

        return 0; /* the operands are valid */
    }

    else if (numOfOperands == 1)
    {

        /* Only destination addressingMethod is defined, one operand */
        {
            if ((commandsTable[currLine->data.command].destAddressingMethods)[parseAddressingMethod
            (operands[0])]) /* the only operand */
            {
                currLine->data.operand1 = parseAddressingMethod(operands[0]);
                currLine->data.reg_op1 = operands[0].data.reg;
                currLine->data.reg_op1 = -1;
                currLine->data.operand2 = -1;

                return 0;
            }
        }
    }
    else /* two operands */
    {
        if (((commandsTable[currLine->data.command].sourceAddressingMethods)[parseAddressingMethod(operands[0])])
            && ((commandsTable[currLine->data.command].destAddressingMethods)[parseAddressingMethod(operands[1])]))
        {
            currLine->data.operand1 = parseAddressingMethod(operands[0]);
            currLine->data.reg_op1 = operands[0].data.reg;

            currLine->data.reg_op2 = operands[1].data.reg;
            currLine->data.operand2 = parseAddressingMethod(operands[1]);

            return 0; /* is valid */
        }
    }
    errorHandler(0,(int) currLine->data.lineNumber ,"invalid operand");
    return 1;
}


int parseAddressingMethod(Token operand)
{
    if (operand.type == Tnumber) return instantAddressing;
    if (operand.type == Tsymbol) return directAddressing;
    if (operand.type == Tregister) return registerDirect;
    if (operand.type == '*') return registerBypass;

}

FILE* manageFiles(const char* file, char* suffix, char* mode)
{
    FILE* fp;
    char* fullFileName = (char*) malloc(strlen(file) + strlen(suffix) +1);

    if (fullFileName == NULL)
    {
        errorHandler(1, -1, "\n Error: memory allocation has failed"
                            " during openning file %s", file);
        return NULL;
    }
    strcpy(fullFileName, file);
    strcat(fullFileName, suffix);
    fp = fopen(fullFileName, mode);

    /*Failure*/
    if(fp == NULL)
    {
        errorHandler(1, -1, "\n Error: failed during openning file %s", fullFileName);
        return NULL;
    }
    /*All good.*/
    return fp;
}

void createObFile(char* fileName)
{
    dataNodePtr curr;
    int i, j, k, mem_word, lineNumber; /* three counters and a mem_word value */
    FILE *file;
    char number_in_str[MAX_LINE];

    int line_num = MEMORY_START_ADDRESS;
    unsigned short int mask = ((1 << (BITS_IN_WORD - 1)));

    file = manageFiles(fileName,OUTPUT_SUFFIX , "w");

    /* check if the array is empty */
    if ((DC + IC) == 0)
    {
        fprintf(stderr, "%s%s is an empty file", fileName, INPUT_SUFFIX);
        return;
    }
    else
    {
        /* headline  
        and printing the IC and DC:*/
        fprintf(file, "\t%d %d\n", IC, DC);

        /*print the IC and DC array to a file*/
        /*IC array*/
        for (i = 0; i<IC; i++)
        {
            mem_word = commands_array[i];

            /* all the addresses are printed in a 4 digit output: */
            sprintf(number_in_str, "%d",line_num + i); /* changing the line number to string */
            for(k=DIGITS_IN_ADDRESS - strlen(number_in_str) ; k >0; k--)
            {
                fprintf(file, "0" ); /* printing leading zero */
            }
            fprintf(file, "%d ", line_num + i);
            fprintf(file, "%d\n", bin_to_octal((int) commands_array[line_num + i]));
        }
        /*now running on data table.*/
        line_num += i;
        if (DC > 0)
        {
            curr = dataTable->head;
            mem_word = curr->word;
        }
        for (i = 0; i<DC; i++)
        {
            sprintf(number_in_str, "%d",line_num + i); /* changing the line number to string */
            for(k=DIGITS_IN_ADDRESS - strlen(number_in_str) ; k >0; k--)
            {
                fprintf(file, "0" ); /* printing leading zero */
            }
            fprintf(file, "%d ", line_num + i);
            fprintf(file, "%d\n", bin_to_octal((int) mem_word));
            curr = curr->next;
            mem_word = curr->word;
        }
    }
    fclose(file);
}


void createEntExtFiles(char* fileName)

{
    FILE *entryFile, *externFile;
    linkedListPtr curr;
    int address;
    occPtr occurList;

    curr = symbolTable;
    int wasEntry = 0, wasExtern = 0;
    entryFile = manageFiles(fileName, EXNTRY_OUTPUT_SUFFIX , "w");
    externFile = manageFiles(fileName, EXTERN_OUTPUT_SUFFIX , "w");

    while(curr->head) /* going over all the lables */
    {
        if (curr->head->entry_extern == EXTERN_SYMBOL) /* lable is extern lable */
        {
            wasExtern = 1; /* extern lable found */
            occurList = curr->head->occurrence;
            address = 100;
            if(curr->head->data_or_instruction == DATA_SYMBOL)
            {
                address+=IC;
            }
            while(occurList) /* to all occurences */
            {
                fprintf(externFile, "%s\t%d\n", curr->head->symbolName, (occurList->line) + address);
                occurList = occurList->next;
            }
        }
        else if(curr->head->entry_extern == ENTRY_SYMBOL)
        {
            wasEntry = 1;
            address = 100 + curr->head->address;
            if(curr->head->data_or_instruction == DATA_SYMBOL)
            {
                address+=IC;
            }
            fprintf(entryFile, "%s\t%d\n", curr->head->symbolName, address);
        }
        curr->head = curr->head->next;
    }
    fclose(entryFile);
    fclose(externFile);
    if(!wasEntry) /* if no entry lable found at all */
    {
        remove(strcat(fileName,EXNTRY_OUTPUT_SUFFIX )); /* deleteing the file */
    }
    if(!wasExtern) /* if no extern lable found at all */
    {
        remove(strcat(fileName,EXTERN_OUTPUT_SUFFIX )); /* ddeleteing the file */
    }
}
