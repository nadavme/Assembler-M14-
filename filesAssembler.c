
/* Created by nadav on 27/04/2020.*/


#include "filesAssembler.h"
#include <errno.h>


linkedListPtr symbolTable;

dataLinkedListPtr dataTable;

short int commands_array[MAX_ARRAY];

int DC, IC;

int filesCounter;
int errorFlag, lineCounter;

int assembler(char* filesToInterpret[], int numOfFiles)
{
    FILE *fp;
    int errNum;
    arrayInit(commands_array,MAX_ARRAY);/*initializing the array to 0.*/

    for (filesCounter = 1; filesCounter < numOfFiles; filesCounter++)
    {
        char *line;
        char temp;

        /*Open file for reading*/
        fprintf(stdout, "\nOpening file: %s%s ....\n", filesToInterpret[filesCounter], INPUT_SUFFIX);
        if (!manageFiles(filesToInterpret[filesCounter], INPUT_SUFFIX, "r"))
        {
            errNum = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error opening file: %s\n", strerror( errNum ));
            fprintf(stderr, "No output files will be created");
            continue;
        }
        fp = manageFiles(filesToInterpret[filesCounter], INPUT_SUFFIX, "r");

        /*Initiate variables*/
        IC = 0;
        DC = 0;
        errorFlag = 1;
        lineCounter = 0;

        char *originalLine = (char *) malloc(sizeof(char) * MAX_LINE);
        LineStruct *currLine = (LineStruct *) malloc(sizeof(LineStruct));
        LineStruct *symbolLine = (LineStruct *) malloc(sizeof(LineStruct));
        Token *currTok = (Token *) malloc(sizeof(Token));
        Token *symbolTok = (Token *) malloc(sizeof(Token));

        /*A symbol table instance, coded by a linked list.*/
        symbolTable = newList();

        /*A data table instance, coded by a linked list.*/
        dataTable = newDataList();


        if ((currTok == NULL) || (symbolTok == NULL))
        {
            errorHandler(1, 0, "ERROR: Memory allocation has failed.");
            errorFlag = 0;
            continue;/*Should i exit?*/
        }

        while (fgets(originalLine, MAX_LINE + 2, fp) != NULL)
        {
            currLine->data.line = originalLine;
            line = originalLine;
            lineCounter++;
            currLine->data.lineNumber = lineCounter;

            /*Validations on input*/

            /*Length of line validation*/
            if (!strchr(line, '\n')) {
                errorHandler(0, lineCounter, "The line must be shorter than %d characters", MAX_LINE);
                errorFlag = 0;
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

                if (currTok->type == ':')/*The valid suffix of a symbol declaration.*/
                {
                    errorHandler(0, (int) currLine->data.lineNumber, "A symbol declaration must "
                                                                     "end with a colon.");
                    errorFlag = 0;
                    continue;
                }

                /*Parsing the next token on the input line.*/
                line = parseByTokens(line, currTok);

                if (currTok->type == Tinstruction) {
                    if ((currTok->data.instruction == EXTERN) || (currTok->data.instruction == ENTRY)) {
                        errorHandler(0, (int) currLine->data.lineNumber, "This instruction is not"
                                                                         " valid after a symbol");
                        errorFlag = 0;
                        continue;
                    }
                    addToSymbolTable(symbolTable->head,symbolTok , DATA_SYMBOL, currLine->data.lineNumber);

                }
                else if (currTok->type == Tcommand)
                {
                    addToSymbolTable(symbolTable->head,symbolTok , CODE_SYMBOL_DECLARATION, currLine->data.lineNumber);
                }
                else {/*In case that after a symbol appears something that is not valid.*/
                    errorHandler(0, (int) currLine->data.lineNumber, "Invalid parameter,"
                                                                     " after a symbol declaration");
                    errorFlag = 0;
                    continue;
                }
            }
            if (currTok->type == Tinstruction) {
                if (currTok->data.instruction == DATA) {
                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type == TnewLine) {
                        errorHandler(0, (int) currLine->data.lineNumber, "Expected data after"
                                                                         " '.data' instruction. Got something else.");
                        errorFlag = 0;
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
                                    errorHandler(0, (int) currLine->data.lineNumber, "The line ended"
                                                                                     " with a comma.");
                                    errorFlag = 0;
                                }
                            } else if (currTok->type == TnewLine) break; /*end of data.*/

                            else {
                                errorHandler(0, (int) currLine->data.lineNumber, "Expected a number on "
                                                                                 ".data instruction. Got other variable.");
                                errorFlag = 0;
                                break;
                            }

                        } else {
                            errorHandler(0, (int) currLine->data.lineNumber, "Expected a number on "
                                                                             ".data instruction. Got other variable.");
                            errorFlag = 0;
                            break;
                        }
                    }
                } else if (currTok->data.instruction == EXTERN) {
                    /*Parsing the next token on the input line.*/
                    line = parseByTokens(line, currTok);/*A symbol is expected.*/

                    if (currTok->type != Tsymbol) {
                        errorHandler(0, (int) currLine->data.lineNumber, "An .extern must be"
                                                                         " followed by a symbol declaration.");
                        errorFlag = 0;
                        continue;
                    }

                    memcpy(symbolTok, currTok, sizeof(Token));/*Deal with the symbol later.*/

                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type != TnewLine) {
                        errorHandler(0, (int) currLine->data.lineNumber, "Invalid instruction to"
                                                                         " follow a symbol");
                        errorFlag = 0;
                        continue;
                    }

                    addToSymbolTable(symbolTable->head,symbolTok , EXTERN_SYMBOL, (int) currLine->data.lineNumber);

                } else if (currTok->data.instruction == ENTRY) {
                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type != Tsymbol) {
                        errorHandler(0, (int) currLine->data.lineNumber, "A symbol must "
                                                                         "only follow an .extern.");
                        continue;
                    }
                    memcpy(symbolTok, currTok, sizeof(Token));/*Deal with the symbol later.*/

                    /*Parsing the first token on the input line.*/
                    line = parseByTokens(line, currTok);

                    if (currTok->type != TnewLine)
                    {
                        errorHandler(0, (int) currLine->data.lineNumber, "Invalid instruction "
                                                                         "to follow a symbol.");
                        errorFlag = 0;
                    }
                    addToSymbolTable(symbolTable->head,symbolTok , ENTRY_SYMBOL, (int) currLine->data.lineNumber);
                }

                    /*In case of a string token.*/
                else if (currTok->data.instruction == STRING) {
                    /*Parsing the first token on the input line.*/
                    line = parseStringByTokens(line, currTok);

                    /*Check for an empty string*/
                    if (currTok->data.string[0] == '\0') {
                        errorHandler(0, (int) currLine->data.lineNumber, "Invalid string");
                        errorFlag = 0;
                        continue;
                    } else/*In caes of a valid string*/
                    {
                        /*adding a string to the data table.*/
                        addStringToDataTable(dataTable, currTok->data.string);

                        /*Parsing the first token on the input line.*/
                        line = parseByTokens(line, currTok);

                        if (currTok->type != TnewLine) {
                            errorHandler(0, (int) currLine->data.lineNumber, "A string must "
                                                                             "be followed by a new line character.");
                            errorFlag = 0;
                            continue;
                        }
                    }

                }

                /*This is the core of the program- the translation.*/
            }
            else if (currTok->type == Tcommand)
            {
                currLine->theLinePurpose = Tcommand;

                /*Validates command sentences, and prepering the current LineStruct to translation*/
                line = fillCurrLineStruct(currLine, line);

            }

            else
                {
                errorHandler(0, (int) currLine->data.lineNumber, "Invalid parameter");
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
                                " no output files will be created.", filesToInterpret[filesCounter]);
            continue;
        }

        /*=========================================Creating output files==================================*/

        createEntExtFiles(filesToInterpret[filesCounter]);
        createObFile(filesToInterpret[filesCounter]);


        fprintf(stdout, "\n Assembling has finished for all valid input files, output files has "
                        "been created for them\n");

        /*free the symbolTable, dataTable, commandsTable etc.*/
        freeDataNode((dataNodePtr) dataTable);
        freeSymbolsTable(symbolTable);
        fclose(fp);
    }

    return 0;


}








