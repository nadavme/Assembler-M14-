//
// Created by nadav on 04/02/2020.
//

#include "firstRunOver.h"

int ARGS_NUM = 0;


void runFirst(const char *file)
{
    {
        int IC, DC;
        FILE *fp;
        char* line;
        bool isThereExceptions = false;
        bool isThereSymbolDeclaration = false;
        char lineWithNoCommas[120];


        IC = 0;
        DC = 0;
        fp = fopen(file, "r");
        if (fp == NULL)
        {
            fprintf(stderr, "File error.");
            exit(EXIT_FAILURE);
        }

        while((fgets(line, 82, fp) != EOF))
        {
            char* parsedLine;
            char instructionType;
            if(!doubleCommasChecker(line)) break;
            strcpy(lineWithNoCommas, commasReplacer(line));
            parsedLine = lineParser(lineWithNoCommas);
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
                        analyzeData(parsedLine, instructionType);

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

char* commasReplacer(char* line)
{
    int i= 0;
    while(line[i] != '\0')
    {
        if (line[i] == ',')
        {
            line[i] = ' ';
        }
        i++;
    }
    return line;
}

bool doubleCommasChecker(char* line)
{
    char *token;
    token = strtok(line, " \t");
    int i = strlen(token) -1;
    int j;
    int counter=0 , first = 0, commasCounter =0;
    for (j = i; j < strlen(line) -1; j++)
    {
        if(line[j] == 'S') counter++;
        if ((line[i] == 's')&& (counter = 1)) first = i;
        if((line[j] == 'S')&& (counter>2)) break;
    }
    i= first;
    while(i < j)
    {
        if (line[i] ==',') commasCounter++;
        i++;
    }
    if (commasCounter > 2) return true;
    return false;
}

char* lineParser(char* line)
{
    static char parsedLineLocal[40][10];
    int i =0;
    char *token;
    token = strtok(line, " \t");
    while(token != NULL)
    {
        strcpy(parsedLineLocal[i], token);
        ARGS_NUM ++;
        token = strtok(NULL, " \t");
        i++;
    }
    return *parsedLineLocal;
}

bool sanityCheck(char* parsedLine)
/*a basic Validation function. checking if the line is one of the follow -
1. תווית.
2. entry
3. extern
4. שורה ריקה\ הערה
7. הוראה

(דאטה וסטרינג לא צריך לבדוק כי הם תחת תווית??)

return true if the line is at list one of the above
 */
{
    if ((strcmp(parsedLine,'\n') == 0) || (strncmp(parsedLine,';',1) == 0) || (strncpy(parsedLine,".entry",6) == 0) 
        || (strncpy(parsedLine,".extern",7) == 0) || (strncpy(parsedLine,""))) /* צריך להכניס פה גם את כל אחת מההוראות , וגם מחוץ לאיף הזה לבדוק תווית*/
        return true;

    while (parsedLine!=)
    {
        
    }
    
}