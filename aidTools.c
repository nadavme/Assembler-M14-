//
// Created by nadav on 04/02/2020.
//

#include "aidTools.h" 

int bin_to_octal(int binaryNum)/*this function converts a number from binary base to octal base, I used a method that we have learned in class.*/
{
    int i = 0,j = 0;
    int sum = 0;
    int midSum = 0;

    while(binaryNum!=0)
    {
		midSum = 0;
        for (j = 0; j < 3; j++)/*the function basically looks at the 3 most right bits, and check for each bit from right to left - if it's on we add 1 
		multyplied by 2 to the power of the place of the bit (0/1/2) to midSum.*/
        {
            if( binaryNum&1 == 1)
             {
                midSum =midSum + (int)pow(2,j);
             }
        binaryNum = binaryNum>>1;
        }
        sum = sum+ (int)midSum*pow(10,i);/*we add midSum that fit the right digit*/
        i++;

    }
    return sum;
}


int dec_to_bin(char dec[])
{
	char binNum[MAX_DIGITS_BIN]= {'0','\0'}; /*creating a char array (a string) which will express the binary 	       number.  the first cell in the array contains the char 0 representation, and all other cells in the 			array 	contain of the integer 0.*/
    int  string_length;
	int i;
	char tmp; 

	unsigned int decInt = strtoul(dec,NULL,10);/*converting the decimal number (string) to int*/
	i = 0;
	while (decInt != 0)
	{
		binNum[i] ='0' + decInt%2; /*collecting the remainders from devision by 2 at the array*/
		decInt = decInt/2; /*deviding by 2 (basically cutting out the fractions)*/
		i++;		
	}

     /* step 2: reverse string */
	 string_length = 0;
	 while  (binNum[string_length]  !=  '\0')
		 string_length = string_length + 1 ;
		  
	for(i=0;i<string_length/2; i++) 
	{
		tmp=binNum[i];
		binNum[i]=binNum[string_length-i-1];
		binNum[string_length-i-1]=tmp ;
	}
    
		printf("%s\n",binNum);/*printing the binary number*/
	
	
	return 0;
}

int isStringValid(char array[], int length, char* string)
{
    /*The function allows validation of any string(operation, register, etc.)*/
    int i;
    for(i=0;i<length;i++)
    {
        if(strcmp(array[i],string) == 0)
            return 0;
    }
    return -1;
}

int isInstruction(char* string)
{
    return isStringValid(validInstructions, strlen(string), string);
}

int isCommand(char* string)
{
    int i;
    /*register prefix*/
    if (string[0] != 'r')
    {
        for (i = 0; matrix[i].codeName ; i++)
        {
            if (strcmp(string, matrix[i].codeName) ==0) return i;
        }
    }
    return -1;/*in case it's not a command*/
}

int isRegister(char* string)
{
    int i;
    /*register prefix*/
    if (string[0] != 'r')
    {
        for (i = 0; matrix[i].codeName ; i++)
        {
            if (strcmp(string, matrix[i].codeName) ==0) return i;
        }
    }
    return -1;/*in case it's not a command*/
}



//int isData(char* string)
//{
//    if ((unsigned char)(*string) == '.')
//    {
//        string++;
//        return isStringValid(dataTypes, NUM_OF_DATA_TYPES, string);
//    }
//    else
//        return 0;
//}



int isExtern(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(EXTERN_MACRO,string) == 0);
    }
    else
        return 0;
}

int isEntry(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(ENTRY_MACRO,string) == 0);
    }
    else
        return 0;
}

int isWhitespace(char* line)
{
    while (*line != '\0') {
        if (!isspace((unsigned char)(*line)))
            return 0;
        line++;
    }
    return 1;
}

int isInt(char* string)
{
    char *ptr;
    long int result;
    strtol(string, &ptr, 10);
    result = strtol(string, &ptr, 10);
    (void)result;
    return (isWhitespace(ptr) || *ptr == '\0'); /* If the rest of the string is empty it still counts as an int*/
}

//int isValidSourceDest(OpCodes code,opType source, opType dest)
//{
//    int result = 0;
//    switch(code)
//    {
//        case mov:
//            result = dest != Immediate;
//            break;
//        case cmp:
//            result = 1;
//            break;
//        case add:
//        case sub:
//        case nnot:
//        case clr:
//            result = dest != Immediate;
//            break;
//        case lea:
//            result = (source == Direct || source == Struct) && dest != Immediate;
//            break;
//        case inc:
//        case dec:
//        case jmp:
//        case bne:
//        case red:
//            result = dest != Immediate;
//            break;
//        case prn:
//            result = 1;
//            break;
//        case jsr:
//            result = dest != Immediate;
//            break;
//        case rts:
//        case stop:
//            result = 1;
//            break;
//    }
//    return result;
//}

///*The function trim the operand and checks if there's more then one operand*/
//StatusCode trimOperand(char* operand)
//{
//    char first[LINE_LENGTH];
//    char second[LINE_LENGTH];
//    if(sscanf(operand,"%s %s",first,second) != 1) /* Testing if there is more than 1 operand */
//        return wrong_number_of_operands;
//    else
//        strcpy(operand,first);
//    return success;
//}

void errorHandler(bool mentionLine, int lineIdx, char* errorMsg)
{
    if (mentionLine == 0) fprintf(stderr, "Error found in line %d: %s\n", lineIdx, errorMsg);
    else fprintf(stderr, "%s\n", errorMsg);
}

char* parseIntoLineStruct(struct LineStruct* currLine)
{

    char token[30];
    int idx;

    idx = 0;

    /*Skip all white spaces at the the beginning of the line*/
    while (isWhitespace(currLine->data.line)) currLine->data.line++;

    /*Check for a number*/
    if ((isdigit(*currLine->data.line)) || (*currLine->data.line == '-'))
    {
       do
           {
           token[idx++] = *currLine->data.line;
           currLine->data.line++;
           }
       while (isdigit(*currLine->data.line));
       token[idx] = '\0';
        currLine->theLinePurpose = Tnumber;
        currLine->data.number = atoi(token);
    }
    else if (*currLine->data.line == '.')/*Check for instruction prefix*/
    {
        do
        {
            token[idx] = *currLine->data.line;
            currLine->data.line++;
        }
        while (!isspace(*currLine->data.line));
        token[idx++] = '\0';

        /*Check for instruction*/
        if ((currLine->data.instruction = isInstruction(token)) >= 0)
        {
            currLine->theLinePurpose = Tinstruction;
        }
        /*We figure out its not an instruction thus its not valid*/
        else currLine->theLinePurpose = Terror;
    }

    else if (*currLine->data.line == '\n')
    {
        currLine->theLinePurpose = TnewLine;
        currLine->data.line++;
    }

    /*Check if the line is a symbol, command or a register*/
    else if (isalnum(*currLine->data.line))
    {
        do
        {
            token[idx] = *currLine->data.line;
            currLine->data.line++;
        }
        while (isalnum(*currLine->data.line));
        token[idx] = '\0';

        /*Check for command*/
        if ((currLine->data.command = isCommand(token)) >= 0)
        {
            currLine->theLinePurpose = Tcommand;
            if (!isspace(*currLine->data.line)) currLine->theLinePurpose = Terror;
        }
        else if((currLine->data.reg = isRegister(token)) >= 0) currLine->theLinePurpose = Tregister;

    }
}

