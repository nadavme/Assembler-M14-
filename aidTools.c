
/* Created by nadav on 04/02/2020.*/


#include "aidTools.h"
#pragma warning(disable : 4996)
/* addressing methods:
0: instant addressing
1: direct addressing
2: register bypass
3: register direct */
struct opTable commandsTable[16] =
{
	{ "mov", (unsigned short)2032, 2,{ 1,1,1,1 },{ 0,1,1,1 } },

	{ "cmp", (unsigned short)4088, 2,{ 1,1,1,1 },{ 1,1,1,1 } },

	{ "add", (unsigned short)6128, 2,{ 1,1,1,1 },{ 0,1,1,1 } },

	{ "sub", (unsigned short)8176, 2,{ 1,1,1,1 },{ 0,1,1,1 } },

	{ "lea", (unsigned short)8560, 2,{ 0,1,0,0 },{ 0,1,1,1 } },

	{ "clr", (unsigned short)10352, 1,{ 0,0,0,0 },{ 0,1,1,1 } },

	{ "not", (unsigned short)12400, 1,{ 0,0,0,0 } ,{ 0,1,1,1 } },

	{ "inc", (unsigned short)14448, 1,{ 0,0,0,0 } ,{ 0,1,1,1 } },

	{ "dec", (unsigned short)16496, 1,{ 0,0,0,0 } ,{ 0,1,1,1 } },

	{ "jmp", (unsigned short)18480, 1,{ 0,0,0,0 } ,{ 0,1,1,0 } },

	{ "bne", (unsigned short)20528, 1,{ 0,0,0,0 } ,{ 0,1,1,0 } },

	{ "red", (unsigned short)22640, 1,{ 0,0,0,0 } ,{ 0,1,1,1 } },

	{ "prn", (unsigned short)24696, 1,{ 0,0,0,0 } ,{ 1,1,1,1 } },

	{ "jsr", (unsigned short)26672, 1,{ 0,0,0,0 } ,{ 0,1,1,0 } },

	{ "rts", (unsigned short)28672, 0,{ 0,0,0,0 } ,{ 0,0,0,0 } },

	{ "stop", 30720, 0,{ 0,0,0,0 } ,{ 0,0,0,0 } }
};

struct instruction validInstructions[4] =
{
	{ ".data",   DATA },
	{ ".string", STRING },
	{ ".extern", EXTERN },
	{ ".entry",  ENTRY }
};

struct Register validRegisters[7] =
{
	{ "r1", R1 },
	{ "r2", R2 },
	{ "r3", R3 },
	{ "r4", R4 },
	{ "r5", R5 },
	{ "r6", R6 },
	{ "r7", R7 }
};

int bin_to_octal(short bin)
/*this function converts a number from binary base to octal base, I used a method that we have learned in class.*/
{
	int oct = 0, dec = 0, i = 0;

	/* converting binary to decimal*/
	while (bin != 0) {
		dec += (bin % 10) * pow(2, i);
		++i;
		bin /= 10;
	}
	i = 1;

	/* converting to decimal to octal*/
	while (dec != 0) {
		oct += (dec % 8) * i;
		dec /= 8;
		i *= 10;
	}

	return oct;
}

/* this function adds a number to the instruction array.
toShift is the number of bits that is required to set the number in it's place.
example: the call: add_to_arr(2,6), adds the number 2 (in binary) to the 7'th bit.*/
void add_to_arr(int num_to_add, int toShift)
{
	commands_array[IC] |= (short)((num_to_add << toShift));
}

void turn_On_bit_num(int place) /*this function turn on the bit at 'place' of the instruction array[ic].*/
{
	commands_array[IC] = (short)((commands_array[IC] | (int)pow(2, place)));
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
	}
	return -1;
}

/*we've decided to implement the instructions table as an array. this function adds a command to the commands array.
this function get called only after all checks for valid input are o.k.*/
void addToCommandsArray(LineStruct *command, int operands_cnt)/* only if there's Symbol before the command it will														  be stored in symbol, else null*/
{
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
		/* a possible bug - here
		if (symbol != NULL)
		{
		addToSymbolTable(symbolTable->head, symbol, CODE_SYMBOL_DECLARATION, command->data.lineNumber);in case were dealing
		with a declaration
		}*/

		if ((command->data.operand1 != -1) && (command->data.operand2 != NOT_RELAVANT))
		{
			if (isBothOperandsRegs(command->data.operand1, command->data.operand2) == 1)
			{
				/*this is the case when both operands share one memory word*/
				weShare(*command);
				return;
			}
		}
		if (command->data.operand1 != NOT_RELAVANT)
		{
			if (command->data.operand1 == instantAddressing) /*in case were dealing with instant mio'n*/
			{
				add_to_arr(command->data.number1, NUM); /* adds after the E,A,R part of the memory word */
				turn_On_bit_num(absolute);
				IC++;
			}

			else if (command->data.operand1 == directAddressing) /*in case were dealing with a direct mio'n*/
			{
				addToSymbolTable(symbolTable, command->data.operand1Token, CODE_SYMBOL, command->data.lineNumber);
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
					addToSymbolTable(symbolTable, command->data.operand2Token, CODE_SYMBOL, command->data.lineNumber);
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
		return true;
	}
	return false;
}

void weShare(LineStruct x) /*this function inserts 2 operands that use registers to 1 memory word.*/
{
	add_to_arr(x.data.reg_op1, SRC_REG);
	add_to_arr(x.data.reg_op2, DEST_REG);
	turn_On_bit_num(absolute);
	IC++;
}

int isStringValid(char* array[], int length, char *string)
{
	/*The function allows validation of any string(operation, register, etc.)*/
	int i;
	for (i = INITIAL_VALUE; i < length; i++)
	{
		if (strcmp(array[i], string) == 0)
			return true;
	}
	return false;
}

int isInstruction(char *string)
{
	int i;

	for (i = INITIAL_VALUE; validInstructions[i].instruction; i++)
	{
		if (strcmp(string, validInstructions[i].instruction) == 0) /* instruction found */
		{
			return validInstructions[i].insType;
		}
	}
	return NOT_RELAVANT; /* no istruction found */
}

int isCommand(char *string)
{
	int i;

	for (i = INITIAL_VALUE; i <= NUM_OF_COMMAND_CODES; i++)
	{
		if (strcmp(string, commandsTable[i].codeName) == 0)
			return i;
	}

	return NOT_RELAVANT; /*in case it's not a command*/
}

int isRegister(char *string)
{
	int i;
	/*register prefix*/
	if (string[0] == 'r')
	{
		for (i = INITIAL_VALUE; validRegisters[i].regName; i++)
		{
			if (strcmp(string, validRegisters[i].regName) == 0) return validRegisters[i].regNum;
		}

		return -1; /*in case it's not a register*/
	}
	return -1;
}

int isSymbol(char *string)
{
	size_t i;/*strlen returns size_z type*/

	/*validate every char on symbol*/
	/*make sure all are letters or digits*/
	for (i = INITIAL_VALUE; i < strlen(string); i++)
		if (!isalnum(string[i]))
			return false;

	/*symbol name must starts with a letter*/
	if (!isalpha(string[0]))
		return false;

	return true;
}


void errorHandler(int mentionLine, int lineIdx, char *errorMsg, ...)
{
	va_list parameters_to_print;
	errorFlag = true;
	va_start(parameters_to_print, errorMsg);
	if (mentionLine == true) fprintf(stderr, "Error found in line %d: %s\n", lineIdx, errorMsg);
	else
	{
		fprintf(stderr, "%s\n", errorMsg);
	}

	vfprintf(stderr, errorMsg, parameters_to_print);
	fprintf(stderr, "\n");
	va_end(parameters_to_print);
}

char *parseByTokens(char* line, struct Token *currTok)
{

	char token[MAX_STRING_NAME];
	int idx;

	idx = INITIAL_VALUE;

	/*Skip all white spaces at the the beginning of the line*/
	while (isWhiteSpace(*line))
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
			token[idx++] = *line;
			line++;
		} while (!isspace(*line));
		token[idx++] = '\0';

		/*Check for instruction*/
		if ((currTok->data.instruction = isInstruction(token)) >= 0)
		{
			currTok->type = Tinstruction;
		}
		/*We figure out its not an instruction thus its not valid*/
		else currTok->type = Terror;
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
			token[idx++] = *line;
			line++;
		} while (isalnum(*line));
		token[idx] = '\0';

		/*Check for command*/
		if ((currTok->data.command = isCommand(token)) >= 0)
		{
			currTok->type = Tcommand;
			if (!isspace(*line)) currTok->type = Terror;
		}

		/*In case we found a match to a valid register.*/
		
		else if (isRegister(token) >= 0) {
			currTok->data.reg = isRegister(token);
			currTok->type = Tregister;
		}

		/*If all is false, we understand it's a symbol.*/
		else if (isSymbol(token))
		{
			/*This symbol needs to be added to the symbol table.*/
			currTok->type = Tsymbol;
			strcpy(currTok->data.symbol, token);
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

char* parseStringByTokens(char* line, Token* currTok)
{
	char token[MAX_LINE];
	int idx;

	idx = 0;

	currTok->type = Tstring;
	while (isWhiteSpace(*line)) /* skip white spaces */
	{
		line++;
	}
	if (*line == '\"') /* start of the string's content */
	{
		line++;
		if (*line == '\"') /* empty string */
		{
			currTok->data.string[0] = '\0'; /* marks an error */
		}
		else /* not an empty string */
		{
			do {
				token[idx++] = *line;
				line++;
			} while ((*line != '\"') && (*line != '\n'));
			token[idx] = '\0';
			if (*line == '\n') /* missing quote (") at the end of the string */
			{
				currTok->data.string[0] = '\0'; /* marks an error */
			}
			else
			{
				strcpy(currTok->data.string, token);
			}
		}
	}
	else
	{
		currTok->data.string[0] = '\0'; /* marks as an error */
	}
	line++;
	return line;
}


char* fillCurrLineStruct(struct LineStruct* currLine, char* line)
{
	int opCounter;
	Token operands[MAX_OPERANDS + 1]; /* 1 for the new line */

	opCounter = INITIAL_VALUE; /* how many operands found in the line read */




							   /* Getting the the first operand into an array of operands */
	line = parseByTokens(line, &(operands[opCounter]));/*[0]*/

	if (operands[opCounter].type == Tnumber) /* Number must follow an '#' */
	{
		errorHandler(true, (int)currLine->data.lineNumber, "In a command, a number must"
			" follow an  hash ('#') sign");
		return line;
	}
	if (operands[opCounter].type == '#') /* InstantAddressing */
	{
		line = parseByTokens(line, &(operands[opCounter]));/* Get the number */



		if (operands[opCounter].type != Tnumber) /* In a case of a # sign without a number after */
		{
			errorHandler(true, (int)currLine->data.lineNumber, "In a command, a number must "
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
			errorHandler(true, (int)currLine->data.lineNumber, "In a command, a * must "
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
				errorHandler(true, (int)currLine->data.lineNumber, "number must begin"
					" with hash ('#') sign");
				return line;
			}
			if (operands[opCounter].type == '#') /* instantAddressing */
			{
				line = parseByTokens(line, &(operands[opCounter])); /* Get the number */

				if (operands[opCounter].type != Tnumber) /* In a case of a # sign without a number after */
				{
					errorHandler(true, (int)currLine->data.lineNumber, "number must follow '#'");
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
					errorHandler(true, (int)currLine->data.lineNumber, "In a command, a * must "
						"be followed by a register");
					return line;
				}

				currLine->data.reg_op2 = (operands[opCounter]).data.reg;
				currLine->data.operand2 = registerBypass;

			}

			if (operands[opCounter].type == TnewLine) /* Missing an operand */
			{
				errorHandler(0, (int)currLine->data.lineNumber, "comma at the end of the line");
			}
			else /* A valid operand */
			{
				opCounter++; /* Two operands */

				line = parseByTokens(line, &(operands[opCounter]));

				if (operands[opCounter].type != TnewLine) /* After two operands the end of the line char must appears */
				{
					errorHandler(true, (int)currLine->data.lineNumber, "invalid parameter"
						" after the operands ");
					return line;
				}
			}
		}
	}

	/*Operands validation checks- if not valid, return without translating the lines*/
	if (!(operandsValidation(currLine, operands, opCounter)))
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
	int numberOfOperands = commandsTable[currLine->data.command].numOfOperands;
	/* getting the data from the commands table */

																			 /* checking the amount of operands accepted */
	if (numberOfOperands != opCounter)
	{
		errorHandler(true, (int)currLine->data.lineNumber, "Number of operands accepted is not"
			" matching the amount by the commandsTable.");
		return 0;
	}

	/* validating the addressingMethods for this command */

	if (numberOfOperands == 0)
	{

		return 1; /* the operands are valid */
	}

	else if (numberOfOperands == 1)
	{

		/* Only destination addressingMethod is defined, one operand */
		{
			if ((commandsTable[currLine->data.command].destAddressingMethods)[parseAddressingMethod
			(operands[0])]) /* the only operand */
			{
				currLine->data.operand1 = parseAddressingMethod(operands[0]);
				currLine->data.reg_op1 = operands[0].data.reg;
				currLine->data.operand1Token = &operands[0];
				currLine->data.operand2 = -1;

				return true;
			}
		}
	}
	else /* two operands */
	{
		int first = commandsTable[currLine->data.command].sourceAddressingMethods[parseAddressingMethod(operands[0])];
		int second = commandsTable[currLine->data.command].destAddressingMethods[parseAddressingMethod(operands[1])];
			if (first && second);
		{
			currLine->data.operand1Token = &operands[0];
			currLine->data.operand1 = parseAddressingMethod(operands[0]);
			currLine->data.reg_op1 = operands[0].data.reg;

			currLine->data.operand2Token = &operands[1];
			currLine->data.reg_op2 = operands[1].data.reg;
			currLine->data.operand2 = parseAddressingMethod(operands[1]);



			return true; /* is valid */
		}
	}
	errorHandler(0, (int)currLine->data.lineNumber, "invalid operand");
	return false;
}


int parseAddressingMethod(Token operand)
{
	if (operand.type == Tnumber) return instantAddressing;
	if (operand.type == Tsymbol) return directAddressing;
	if (operand.type == Tregister) return registerDirect;
	if (operand.type == '*') return registerBypass;
	return NOT_RELAVANT;

}

FILE* manageFiles(const char* file, char* suffix, char* mode)
{
	FILE* fp;
	char* fullFileName = (char*)malloc(strlen(file) + strlen(suffix) + 1);

	if (fullFileName == NULL)
	{
		errorHandler(1, '\0', "\n Error: memory allocation has failed"
			" during opening file %s", file);
		return NULL;
	}
	strcpy(fullFileName, file);
	strcat(fullFileName, suffix);
	fp = fopen(fullFileName, mode);

	/*Failure*/
	if (fp == NULL)
	{
		errorHandler(1, -1, "\n Error: Failed during openning file %s", fullFileName);
		return NULL;
	}
	/*All good.*/
	return fp;
}

void createObFile(char* fileName)
{
	dataNodePtr curr;
	int i, k, mem_word; /* three counters and a mem_word value */
	FILE *file;
	char number_in_str[MAX_LINE];

	int line_num = MEMORY_START_ADDRESS;
	unsigned short int mask = ((1 << (BITS_IN_WORD - 1)));

	file = manageFiles(fileName, OUTPUT_SUFFIX, "w");

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
			sprintf(number_in_str, "%d", line_num + i); /* changing the line number to string */
			for (k = DIGITS_IN_ADDRESS - strlen(number_in_str); k >0; k--)
			{
				fprintf(file, "0"); /* printing leading zero */
			}
			fprintf(file, "%d ", line_num + i);
			fprintf(file, "%d\n", bin_to_octal(commands_array[line_num + i]));
		}
		/*now running on data table.*/
		line_num += i;
		if (DC > 0)
		{
			curr = dataTable->head;
			mem_word = curr->word;
		}
		for (i = 0; i < DC; i++)
		{
			sprintf(number_in_str, "%d", line_num + i); /* changing the line number to string */
			for (k = DIGITS_IN_ADDRESS - strlen(number_in_str); k > 0; k--)
			{
				fprintf(file, "0"); /* printing leading zero */
			}
			fprintf(file, "%d ", line_num + i);
			fprintf(file, "%d\n", bin_to_octal((int)mem_word));
			if (curr->next) {
				curr = curr->next;
				mem_word = curr->word;
			}
		}
	}
	fclose(file);
}


void createEntExtFiles(char* fileName)

{
	FILE *entryFile = 0, *externFile = 0;
	linkedListPtr curr;
	int address;
	occp occurList;
	curr = symbolTable;

	while (curr->head) /* going over all the symbols in the list */
	{
		if (curr->head->entry_extern == EXTERN_SYMBOL) /* symbol is an extern symbol */
		{
			externFile = manageFiles(fileName, EXTERN_OUTPUT_SUFFIX, "w");

			occurList = curr->head->occurrence;
			address = 100;
			if (curr->head->data_or_instruction == DATA_SYMBOL)
			{
				address += IC;
			}
			while (occurList) /* to all occurrences */
			{
				fprintf(externFile, "%s %d\n", curr->head->symbolName, (occurList->line) + address);
				occurList = occurList->next;
			}
		}
		else if (curr->head->entry_extern == ENTRY_SYMBOL)
		{
			entryFile = manageFiles(fileName, EXNTRY_OUTPUT_SUFFIX, "w");

			address = 100 + curr->head->address;
			if (curr->head->data_or_instruction == DATA_SYMBOL)
			{
				address += IC;
			}
			fprintf(entryFile, "%s %d\n", curr->head->symbolName, address);
		}
		curr->head = curr->head->next;
	}
	fclose(entryFile);
	fclose(externFile);
}

/* this function initialize every cell to value 0, */
void arrayInit(short int array[], int length)
{
	int i;
	for (i = 0; i<length; i++)
	{
		array[i] = 0;
	}
}
