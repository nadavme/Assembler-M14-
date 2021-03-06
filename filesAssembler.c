
/* Created by nadav on 27/04/2020.*/


#include "filesAssembler.h"


linkedListPtr symbolTable;

dataLinkedListPtr dataTable;

short int commands_array[MAX_ARRAY];

int DC, IC;

int filesCounter;
int errorFlag, lineCounter;

int assembler(char* filesToInterpret[], int numOfFiles)
{
    FILE *fp;
    arrayInit(commands_array,MAX_ARRAY); /*initializing the array to 0.*/
	char* originalLine;
	char* line;
	char temp;
	LineStruct *currLine, *symbolLine;
	Token *currTok, *symbolTok;
	int isLastLine = false;
    for (filesCounter = 1; filesCounter < numOfFiles; filesCounter++)
    {
        /*Open file for reading*/
        fprintf(stdout, "\nOpening file: %s%s ....\n", filesToInterpret[filesCounter], INPUT_SUFFIX);
		fp = manageFiles(filesToInterpret[filesCounter], INPUT_SUFFIX, "r");
		if (!fp)
        {
            fprintf(stderr, "No output files will be created");
            continue;
        }

        /*Initiate variables*/
        IC = INITIAL_VALUE;
        DC = INITIAL_VALUE;
        errorFlag = false;
        lineCounter = INITIAL_VALUE;

        originalLine = (char *) malloc(sizeof(char) * MAX_LINE);
        currLine = (LineStruct *) malloc(sizeof(LineStruct));
        symbolLine = (LineStruct *) malloc(sizeof(LineStruct));
        currTok = (Token *) malloc(sizeof(Token));
        symbolTok = (Token *) malloc(sizeof(Token));

        /*A symbol table instance, coded by a linked list.*/
        symbolTable = newList();

        /*A data table instance, coded by a linked list.*/
        dataTable = newDataList();


        if ((currTok == NULL) || (symbolTok == NULL) || (symbolLine == NULL)|| (currLine == NULL))
        {
            errorHandler(false, 0, "ERROR: Memory allocation has failed.");
            errorFlag = true;
			exit(1);
        }

        while (fgets(originalLine, MAX_LINE + 2, fp) != NULL)
        {
			/*remove /n from end of string
			if (originalLine[MAX_LINE] == '/n')
				originalLine[MAX_LINE] = 0;
			else originalLine[strlen(originalLine) -1] = 0;*/

            currLine->data.line = originalLine;
            line = originalLine;
            lineCounter++;
            currLine->data.lineNumber = lineCounter;

            /*Validations on input*/

            /*Length of line validation*/
			if (strlen(originalLine) == MAX_LINE || (originalLine[strlen(originalLine) -1] != '\n'))
				isLastLine = true;
            if (!strchr(line, '\n') && !isLastLine) {
                errorHandler(true, lineCounter, "The line must be shorter than %d characters", MAX_LINE);
                /*To "cut" the rest  of the line.*/
                while ((temp = fgetc(fp)) != '\n');
                continue;
            }

            /*Parsing the first token on the input line.*/
            line = parseByTokens(line, currTok);

            /*Skip a  comment line\ newline*/
            if ((currTok->type == ';') || (currTok->type == TnewLine)) continue;

            if (currTok->type == Tsymbol) {
                memcpy(symbolTok, currTok, sizeof(Token));/*Deal with the symbols later.*/

                /*Parsing the next token on the input line.*/
                line = parseByTokens(line, currTok);

                if (currTok->type != ':')/*The valid suffix of a symbol declaration.*/
                {
                    errorHandler(true, (int) currLine->data.lineNumber, "A symbol declaration must "
                                                                     "end with a colon.");
                    continue;
                }

                /*Parsing the next token on the input line.*/
                line = parseByTokens(line, currTok);

                if (currTok->type == Tinstruction)
                {
                    if ((currTok->data.instruction == EXTERN) || (currTok->data.instruction == ENTRY))
                    {
                        errorHandler(true, (int) currLine->data.lineNumber, "This instruction is not"
                                                                         " valid after a symbol");
                        errorFlag = 1;
                        continue;
                    }
                    addToSymbolTable(symbolTable,symbolTok , DATA_SYMBOL, (int) currLine->data.lineNumber);

                }
                else if (currTok->type == Tcommand)
                {
                    addToSymbolTable(symbolTable,symbolTok , CODE_SYMBOL_DECLARATION, (int) currLine->data.lineNumber);

                }
                else {/*In case that after a symbol appears something that is not valid.*/
                    errorHandler(true, (int) currLine->data.lineNumber, "Invalid parameter,"
                                                                     " after a symbol declaration");
                    errorFlag = true;
                    continue;
                }
            }
            if (currTok->type == Tinstruction)
            {
                if (currTok->data.instruction == DATA)
                {

                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type == TnewLine) {
                        errorHandler(true, (int) currLine->data.lineNumber, "Expected data after"
                                                                         " '.data' instruction. Got something else.");
                        errorFlag = true;
                        continue;
                    }
                    while (currTok->type != TnewLine) {
                        if (currTok->type == Tnumber) {
                            /*The data will be added if not in the table already.*/
                            addDataToTable(dataTable, currTok->data.number);

                            /*Parsing the next token on the input line.*/
                            line = parseByTokens(line, currTok);

                            /*Comma is a mandatory separator between values*/
                            if (currTok->type == ',') {
                                /*Parsing the next token on the input line.*/
                                line = parseByTokens(line, currTok);

                                if (currTok->type == TnewLine) {
                                    errorHandler(true, (int) currLine->data.lineNumber, "The line ended"
                                                                                     " with a comma.");
                                    errorFlag = true;
                                }
                            } else if (currTok->type == TnewLine) break; /*end of data.*/

                            else {
                                errorHandler(true, (int) currLine->data.lineNumber, "Expected a number on "
                                                                                 ".data instruction. Got other variable.");
                                errorFlag = true;
                                break;
                            }

                        } else {
                            errorHandler(true, (int) currLine->data.lineNumber, "Expected a number on "
                                                                             ".data instruction. Got other variable.");
                            errorFlag = true;
                            break;
                        }
                    }
                } else if (currTok->data.instruction == EXTERN) {
                    /*Parsing the next token on the input line.*/
                    line = parseByTokens(line, currTok);/*A symbol is expected.*/

                    if (currTok->type != Tsymbol) {
                        errorHandler(true, (int) currLine->data.lineNumber, "An .extern must be"
                                                                         " followed by a symbol declaration.");
                        errorFlag = true;
                        continue;
                    }

                    memcpy(symbolTok, currTok, sizeof(Token));/*Deal with the symbol later.*/

                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type != TnewLine && !isLastLine) {
                        errorHandler(true, (int) currLine->data.lineNumber, "Invalid instruction to"
                                                                         " follow a symbol");
                        errorFlag = true;
                        continue;
                    }

                    addToSymbolTable(symbolTable,symbolTok , EXTERN_SYMBOL, (int) currLine->data.lineNumber);

                } else if (currTok->data.instruction == ENTRY) {
                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type != Tsymbol) {
                        errorHandler(true, (int) currLine->data.lineNumber, "A symbol must "
                                                                         "only follow an .extern.");
                        continue;
                    }
                    memcpy(symbolTok, currTok, sizeof(Token));/*Deal with the symbol later.*/

                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type != TnewLine)
                    {
                        errorHandler(true, (int) currLine->data.lineNumber, "Invalid instruction "
                                                                         "to follow a symbol.");
                        errorFlag = true;
                    }
                    addToSymbolTable(symbolTable,symbolTok , ENTRY_SYMBOL, (int) currLine->data.lineNumber);
                }

                    /*In case of a string token.*/
                else if (currTok->data.instruction == STRING) {
                    /*Parsing the first token on the input line.*/
                    line = parseStringByTokens(line, currTok);

                    /*Check for an empty string*/
                    if (currTok->data.string[0] == '\0') {
                        errorHandler(true, (int) currLine->data.lineNumber, "Invalid string");
                        errorFlag = true;
                        continue;
                    } else/*In caes of a valid string*/
                    {
                        /*adding a string to the data table.*/
                        addStringToDataTable(dataTable, currTok->data.string);

                        /*Parsing the first token on the input line.*/
                        line = parseByTokens(line, currTok);

                        if (currTok->type != TnewLine) {
                            errorHandler(true, (int) currLine->data.lineNumber, "A string must "
                                                                             "be followed by a new line character.");
                            errorFlag = true;
                            continue;
                        }
                    }

                }

                /*This is the core of the program- the translation.*/
            }
            else if (currTok->type == Tcommand)
            {
                currLine->theLinePurpose = Tcommand;
				currLine->data.command = currTok->data.command;
                /*Validates command sentences, and prepering the current LineStruct to translation*/
                line = fillCurrLineStruct(currLine, line);

            }

            else
                {
                errorHandler(true, (int) currLine->data.lineNumber, "Invalid parameter");
                continue;
                }
        }

        
        /*Free all dynamic memory allocation.*/
        free(originalLine);
        free(currLine);
        free(symbolLine);
        free(currTok);
        free(symbolTok);

        add100ToMemory();/*this function updates the memory image, as described in the MAMAN, in page 36*/

        /*=========================================End of first run over==================================*/

        /*Running over the symbol table(second run over)*/
        secondRunOver(symbolTable, dataTable); /*This one will run over the symbol table*/

        /*=========================================End of second run over==================================*/

        if (errorFlag)
        {
            printf("Error: Errors has found on file %s,"
                                " no output files will be created.\n", filesToInterpret[filesCounter]);
            continue;
        }

        /*=========================================Creating output files==================================*/

        createEntExtFiles(filesToInterpret[filesCounter]);
        createObFile(filesToInterpret[filesCounter]);


        fprintf(stdout, "\n Assembling has finished for all valid input files, output files has "
                        "been created for them\n");

        /*free the symbolTable, dataTable, commandsTable etc.*/

        freeDataNode(dataTable);
        freeSymbolsTable(symbolTable);
        fclose(fp);
    }

    return 0;


}








