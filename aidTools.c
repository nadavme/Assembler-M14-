//
// Created by nadav on 04/02/2020.
//

#include "aidTools.h" 
#include "main.c"

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

void printBits(size_t const size, void const * const ptr)/*the function prints the binary representation of any type.
size is the number of bytes. an example can be seen in tester_for_matrix.c */
{
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j=7;j>=0;j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

/* this function adds a number to the instruction array.
 toShift is the number of bits that is required to set the number in it's place.
example: the call: add_to_arr(2,6), adds the number 2 (in binary) to the 7'th bit.*/
void add_to_arr(int num_to_add, int toShift,int ic)
{
	instructions_array[ic] |= (num_to_add << toShift);
}

void turn_On_bit_num(int place,int ic)/*this function turn on the bit at'place' of the instruction array[ic].*/
{
    instructions_array[ic] = (instructions_array[ic] | (int)pow(2,place));
}

/*this function and documenation is from Alon, need to change!!!!!!! 
this function gets a token, and returns it's addressing mode:
instant_addressing,
direct_addressing,
or register_addressing.
if it's not one of the above - the function returns -1 */
int get_addressing_mode(instruction operand)
{
	if (operand.type == number_tok) return instant_addressing;
	else if (operand.type == lable_tok) return direct_addressing;
	else if (operand.type == register_tok) return register_addressing;
	else
	{
		return -1;
	}
}

/*we've decided to implement the instructions table as an array. this function adds a command to the instructions array.
this function get called only after all checks for valid input are o.k.*/
void add_to_instructions_array(instruction *command, instruction operands[], int operands_cnt,int ic)
{
	int i;
	/* adding the command word now.*/
	add_to_arr(command->opCode, 11, ic);/*the opCode in the word is at bit number 11*/
	if (operands_cnt == 0) /* no operadnds to add */
	{
        turn_On_bit_num(2,ic);
		return;
	}
	else if (operands_cnt == 1)
	{
		add_to_arr(get_addressing_mode(operands[0]), DEST_ADDRESS,ic);
	}
	else if (operands_cnt == 2)
	{
		add_to_arr(get_addressing_mode(operands[0]), SRC_ADDRESS, ic);
		add_to_arr(get_addressing_mode(operands[1]), DEST_ADDRESS,ic);
	}
	else if (operands_cnt == 3)/*didnt understood this if. a potentialli bug...*/
	{
		add_to_arr(jump_addressing, DEST_ADDRESS, ic);
		add_to_arr(get_addressing_mode(operands[1]), PARAM_1,ic);
		add_to_arr(get_addressing_mode(operands[2]), PARAM_2,ic);
	}

	/* adding the other memory words */
	
	for (i = 0; i<operands_cnt; i++)
	{
		if (operands[i].type == lable_tok)
		{
			add2lable_table(&lable_list, &(operands[i]), CODE_LABLE); /* CODE_LABLE is the type of lable to be added */
		}
		else if (operands[i].type == number_tok)
		{
			add_to_mem(operands[i].data.number, NUM); /* adds after the E,A,R part of the memory word */
		}
		else if (operands[i].type == register_tok)
		{
			if (operands_cnt>1)
			{
				if (i<operands_cnt - 1) /* the source register */
				{
					add_to_mem(operands[i].data.reg, SRC_REG); /* adds after the E,A,R part of the memory word */
				}
				else /* the destination register */
				{
					if (operands[i - 1].type == register_tok) /* if there are two registers, they add to the same memory word */
					{
						IC--; /* adds the register in the same memory word */
					}
					add_to_mem(operands[i].data.reg, DEST_REG);
				}
			}
		}
	}
}


int isStringValid(char **array, int length, char* string)
{
    int i;
    for(i=0;i<length;i++)
    {
        if(strcmp(array[i],string) == 0)
            return 1;
    }
    return 0;
}

//int isInstruction(char* string)
//{
//    return isStringValid(instructions, NUM_OF_INSTRUCTS, string);
//}

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

//int isRegister(char* string)
//{
//    return isStringValid(registers, NUM_OF_REGISTERS, string);
//}

int isExtern(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(EXTERN,string) == 0);
    }
    else
        return 0;
}

int isEntry(char* string)
{
    if ((unsigned char)(*string) == '.')
    {
        string++;
        return (strcmp(ENTRY,string) == 0);
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

