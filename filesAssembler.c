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
            continue;/*Should i exit?*/
        }

        while (fgets(line, MAX_LINE + 2, fp) != NULL)
        {
            currLine->data.line = line;
            lineCounter++;

            /*Validations on input*/

                /*Length of line validation*/




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





