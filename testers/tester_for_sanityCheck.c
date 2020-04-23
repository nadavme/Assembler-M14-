#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

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


int main()
{
    char *parsedLine;
    *parsedLine = "MAIN:";

bool x;

x = sanityCheck("MAIN:");

printf("sanityCheck(MAIN:) = %d", x);/*changed %s to %d*/
    return 0;
}
