//
// Created by nadav on 27/04/2020.
//

#include "filesAssembler.h"


int assembler(char** filesToInterpret, int numOfFiles) {
    FILE *fp;
    int filesCounter;
    char fileName[20];

    for (filesCounter = 1; filesCounter < numOfFiles; filesCounter++) {
        int linesIdx, bufferCounter;
        lineStruct *lineStructMain, *lineStructTemp;

        linesIdx = 0, bufferCounter = BUFSIZ;
        sprintf(fileName, "%s.as", filesToInterpret[filesCounter]);
        fp = fopen(fileName, "r");
        if (fp == NULL) {
            fprintf(stderr, "File error.");
            exit(EXIT_FAILURE);
        }

        lineStructMain = malloc(sizeof(lineStruct) * BUFSIZ);
        lineStructMain = NULL;
        lineStructMain[linesIdx].originalLine = malloc(sizeof(char) * 82);

        while ((fgets(lineStructMain[linesIdx].originalLine, 82, fp) != EOF)) {
            if (linesIdx == bufferCounter) {
                bufferCounter += BUFSIZ;
                lineStructTemp = realloc(lineStructMain, sizeof(lineStruct) * bufferCounter);
                if (lineStructTemp) {
                    lineStructMain = lineStructTemp;
                } else {
                    printf("ERROR: Reallocating memory has failed.");
                    return EXIT_FAILURE;
                }
            }
            lineStructMain[linesIdx].lineNumber = linesIdx + 1;
            lineStructMain[++linesIdx].originalLine = malloc(sizeof(char) * 82);
        }

        free(lineStructMain[linesIdx].originalLine);

        if (runFirst(&lineStructMain, linesIdx)) runSecond(lineStructMain);
    }
    fclose(fp);
    return 0;
}



//            char* parsedLine;
//            const char* instructionType;
//            if(!doubleCommasChecker(line)) break;
//            strcpy(lineWithNoCommas, commasReplacer(line));
//            parsedLine = lineParser(lineWithNoCommas);
//            if (!sanityCheck(parsedLine)) isThereExceptions = true;
//            if(!isThereExceptions)
//            {
//                if (isSymbole(&parsedLine[0])) isThereSymbolDeclaration = true;
//                const char* instructionType = getInstructionType(parsedLine);
//                if((strcmp(instructionType , ".data") == 0) || (strcmp(instructionType , ".string") == 0))
//                {
//                    if(isThereSymbolDeclaration) addSymbolToTable(parsedLine, fileSymbolTable, DC, 1, 1);
//                    analyzeData(parsedLine, instructionType);
//                    updateDC(DC);
//                    continue;
//                }
//                if((strcmp(instructionType, ".extern") == 0) || (strcmp(instructionType , ".entry") == 0))
//                {
//                    if(strcmp(instructionType, ".entry") == 0) continue;
//                    else
//                    {
//                        addSymbolToTable(parsedLine, fileSymbolTable, DC, 1, 0);
//                    }
//                }
//                /*Here we know we are dealing with an instruction line*/
//                if(isThereSymbolDeclaration) addSymbolToTable(parsedLine, fileSymbolTable, IC, 1, 1)
//                if(!isOpCode(parsedLine[0]))
//                {
//                    printf("ERROR: Operation code is not valid. The program will continue to check the next line,"
//                           "but no output files will be made.");
//                    continue;
//                }
//                L = analizeNumOfOperands(parsedLine);
//                for (i = 0; i < L; i++)
//                {
//                    buildBinaryCode(opCodes, wordNumber, data);
//
//                }
//                IC += L;
//                continue;
//
//            }
//
//        }
//     }
//
//}
