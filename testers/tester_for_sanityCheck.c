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
    if ((parsedLine[0] == '\n') || (parsedLine[0] == ';') || (strncmp(parsedLine,".entry",6) == 0) 
        || (strncmp(parsedLine,".extern",7) == 0) || (strncmp(parsedLine,"mov",3) == 0) ||
         (strncmp(parsedLine,"cmp",3) == 0) || (strncmp(parsedLine,"add",3) == 0) || (strncmp(parsedLine,"sub",3) == 0) ||
          (strncmp(parsedLine,"lea",3) == 0)  || (strncmp(parsedLine,"clr",3) == 0) || (strncmp(parsedLine,"not",3) == 0)
           || (strncmp(parsedLine,"inc",3) == 0) || (strncmp(parsedLine,"dec",3) == 0) || (strncmp(parsedLine,"jmp",3) == 0)
         || (strncmp(parsedLine,"bne",3) == 0) || (strncmp(parsedLine,"red",3) == 0) || (strncmp(parsedLine,"prn",3) == 0)
          || (strncmp(parsedLine,"jsr",3) == 0) || (strncmp(parsedLine,"rts",3) == 0) || (strncmp(parsedLine,"stop",4) == 0)
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
