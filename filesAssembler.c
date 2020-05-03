//
// Created by nadav on 27/04/2020.
//

#include "filesAssembler.h"

#define INPUT_SUFFIX ".as"
#define OUTPUT_SUFFIX ".ob"
#define EXTERN_OUTPUT_SUFFIX ".ent"
#define EXNTRY_OUTPUT_SUFFIX ".ext"
#define MAX_LINE 82


char fileName[20];
int IC, DC;
char* parsedLine;
int lineCounter;




/*todo: adapt it to previous plan.*/
int assembler(char const* filesToInterpret[], int numOfFiles) {
    FILE *fp;
    int filesCounter;

    for (filesCounter = 1; filesCounter < numOfFiles; filesCounter++)
    {

        /*Initiate variables*/
        IC = 0;
        DC = 0;
        lineCounter = 0;
        char temp;
        char* line;
        char *originalLine = (char *) malloc(sizeof(char) * MAX_LINE);
        lineStruct* currLine = (lineStruct*) malloc(sizeof(lineStruct));
        lineStruct* symbolLine = (lineStruct*) malloc(sizeof(lineStruct));

        if ((currLine == NULL) || (symbolLine == NULL))
        {
            errorHandler(1, 0, "ERROR: Memory allocation has failed.");
            /*todo: update error flag?*/
            continue;/*Should i exit?*/
        }

        while (fgets(line, MAX_LINE + 2, fp) != NULL)
        {
            currLine->data.line = line;
            lineCounter++;
            currLine->data.lineNumber = lineCounter;

            /*Validations on input*/

                /*Length of line validation*/
                if (!strchr(line, '\n'))
                {
                    errorHandler(0, lineCounter, "The line must be shorter than %d characters", MAX_LINE);
                    /*todo: update error flag?*/
                    
                    /*To "cut" the rest  of the line.*/
                    while((temp = fgetc(fp)) != '\n');
                    continue;
                }

                line = parseIntoLineStruct(currLine);

                /*Skip a  comment line\ newline*/
                if ((currLine->theLinePurpose == ';') || (currLine->theLinePurpose == TnewLine)) continue;

                if (currLine->theLinePurpose == Tsymbol)
                {
                    memcpy(symbolLine, currLine, sizeof(lineStruct));/*Deal with the symbols later.*/
                    currLine->data.line++;/*todo: possible one word approach.*/

                    if (currLine->theLinePurpose == ':')/*The valid suffix of a symbol declaration.*/
                    {
                        errorHandler(0, (int)currLine->data.lineNumber, "A symbol declaration must "
                                                                        "end with a colon.");/*todo: update error flag?*/
                        continue;
                    }

                    currLine->data.line++;/*todo: possible one word approach.*/
                    if (currLine->theLinePurpose == Tinstruction)/*todo: possible one word approach.*/
                    {
                        if ((currLine->data.instruction == EXTERN_MACRO) || (currLine->data.instruction == ENTRY_MACRO))
                        {
                            errorHandler(0, (int)currLine->data.lineNumber, "This instruction is not"
                                                                       " valid after a symbol");
                            continue;/*todo: update error flag?*/
                        }
                        addSymbolToTable(, , DATA)/*todo: adapt it to the version of lineStruct.*/
                    }
                    else if (currLine->theLinePurpose == Tcommand)
                    {
                        addSymbolToTable(, , codeSymbolDeclaration)/*todo: adapt it to the version of lineStruct.*/
                    }
                    else
                    {
                        errorHandler(0, (int)currLine->data.lineNumber, "Invalid parameter,"
                                                                        " after a symbol declaration");
                        continue;
                    }
                }
                if (currLine->theLinePurpose == Tinstruction)
                {
                    if (currLine->data.instruction == DATA)
                    {
                        currLine->data.line++;/*todo: possible one word approach.*/
                        if (currLine->theLinePurpose == TnewLine)/*todo: possible one word approach.*/
                        {
                            errorHandler(0, (int)currLine->data.lineNumber, "Expected data after"
                                                                       " '.data' intruction");
                            continue;
                        }
                    }
                    while (currLine->theLinePurpose != TnewLine)
                }




        char* parsedLine;
        const char* instructionType;
        if(!doubleCommasChecker(line)) break;
        strcpy(lineWithNoCommas, commasReplacer(line));
        parsedLine = lineParser(lineWithNoCommas);
        if (!sanityCheck(parsedLine)) isThereExceptions = true;
        if(!isThereExceptions)
        {
            if (isSymbole(&parsedLine[0])) isThereSymbolDeclaration = true;
            const char* instructionType = getInstructionType(parsedLine);
            if((strcmp(instructionType , ".data") == 0) || (strcmp(instructionType , ".string") == 0))
            {
                if(isThereSymbolDeclaration) addSymbolToTable(parsedLine, fileSymbolTable, DC, 1, 1);
                analyzeData(parsedLine, instructionType);
                updateDC(DC);
                continue;
            }
            if((strcmp(instructionType, ".extern") == 0) || (strcmp(instructionType , ".entry") == 0))
                {
                if(strcmp(instructionType, ".entry") == 0) continue;
                else
                    {
                        addSymbolToTable(parsedLine, fileSymbolTable, DC, 1, 0);
                    }
                }
                /*Here we know we are dealing with an instruction line*/
                if(isThereSymbolDeclaration) addSymbolToTable(parsedLine, fileSymbolTable, IC, 1, 1)
                if(!isOpCode(parsedLine[0]))
                {
                    printf("ERROR: Operation code is not valid. The program will continue to check the next line,"
                           "but no output files will be made.");
                    continue;
                }
                L = analizeNumOfOperands(parsedLine);
                for (i = 0; i < L; i++)
                {
                    buildBinaryCode(opCodes, wordNumber, data);

                }
                IC += L;
                continue;

            }

        }
     }

}

//    int linesIdx, bufferCounter;
//        lineStruct *lineStructMain, *lineStructTemp;
//
//        linesIdx = 0, bufferCounter = BUFSIZ;
//        sprintf(fileName, "%s%s", filesToInterpret[filesCounter], INPUT_SUFFIX);
//        fp = fopen(fileName, "r");
//        if (fp == NULL) {
//            fprintf(stderr, "Can't open file %s. Moving on to the next file.", fileName);
//            continue;
//        }
//        /*Initiate variables*/
//        IC = 0;
//        DC = 0;
//        lineCounter = 0;
//
//        /*Allocate memory dynamically.*/
//        lineStructMain = malloc(sizeof(lineStruct) * BUFSIZ);
//        lineStructMain = NULL;
//        lineStructMain[linesIdx].line = malloc(sizeof(char) * MAX_LINE);
//
//        while ((fgets(lineStructMain[linesIdx].line, 82, fp) != EOF)) {
//            if (linesIdx == bufferCounter) {
//                bufferCounter += BUFSIZ;
//                lineStructTemp = realloc(lineStructMain, sizeof(lineStruct) * bufferCounter);
//                if (lineStructTemp) {
//                    lineStructMain = lineStructTemp;
//                } else {
//                    printf("ERROR: Reallocating memory has failed.");
//                    return EXIT_FAILURE;
//                }
//            }
//            lineStructMain[linesIdx].lineNumber = linesIdx + 1;
//            lineStructMain[++linesIdx].line = malloc(sizeof(char) * 82);
//        }
//
//        free(lineStructMain[linesIdx].line);
//
//        if (runFirst(&lineStructMain, linesIdx)) runSecond(lineStructMain);
//    }
//    fclose(fp);
//    return 0;




