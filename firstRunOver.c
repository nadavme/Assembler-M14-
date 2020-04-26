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
        linkedListPtr fileSymbolTable;


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
                    addSymbolToTable(parsedLine, fileSymbolTable, DC, 1, 1);
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
                


            }

        }
        if(isThereExceptions)
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
    if ((parsedLine[0] == '\n') || (parsedLine[0] == ';') || (strncmp(parsedLine[0],".entry",6) == 0) 
        || (strncmp(parsedLine[0],".extern",7) == 0) || (strncmp(parsedLine[0],"mov",3) == 0) ||
         (strncmp(parsedLine[0],"cmp",3) == 0) || (strncmp(parsedLine[0],"add",3) == 0) || (strncmp(parsedLine[0],"sub",3) == 0) ||
          (strncmp(parsedLine[0],"lea",3) == 0)  || (strncmp(parsedLine[0],"clr",3) == 0) || (strncmp(parsedLine[0],"not",3) == 0)
           || (strncmp(parsedLine[0],"inc",3) == 0) || (strncmp(parsedLine[0],"dec",3) == 0) || (strncmp(parsedLine[0],"jmp",3) == 0)
         || (strncmp(parsedLine[0],"bne",3) == 0) || (strncmp(parsedLine[0],"red",3) == 0) || (strncmp(parsedLine[0],"prn",3) == 0)
          || (strncmp(parsedLine[0],"jsr",3) == 0) || (strncmp(parsedLine[0],"rts",3) == 0) || (strncmp(parsedLine[0],"stop",4) == 0)
          )
        return true;

     return (parsedLine && *parsedLine && parsedLine[strlen(parsedLine) - 1] == ':') ? true : false;
      /* this line ceck if the pointer doesnt points to null, and the string is not empty, and the last char in the string is ':' (and than
      it means that the first word is a label).
      if all of the above does happen we can retunr true...*/
    
}