//
// Created by nadav on 04/02/2020.
//

#include "firstRunOver.h"


void runFirst(const char *file)
{
    {
        int IC, DC;
        FILE *fp;
        char line[82];
        bool isThereExceptions = false;
        bool isThereSymbolDeclaration = false;

        IC = 0;
        DC = 0;
        fp = fopen(file, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "File error.");
            exit(EXIT_FAILURE);
        }

        while((fgets(line, sizeof(line)), fp) != EOF)
        {
            char* parsedLine;
            char instructionType;
            parsedLine = lineParser(line);
            if (!isLineValid(parsedLine)) isThereExceptions = true;
            if(!isThereExceptions)
            {
                if (isSymbole(&parsedLine[0]))
                {
                    isThereSymbolDeclaration = true;
                    instructionType = getInstructionType(parsedLine);
                    if((instructionType == ".data") || (instructionType == ".string"))
                    {
                        addSymbolToTable(parsedLine, instructionType, DC);
                        analyzeData
                    }
                }


            }

        }
        if(!isThereExceptions)
        {
            printf("Exceptions were found in the file, therefore no output file will be created.");
        }


    }
}
