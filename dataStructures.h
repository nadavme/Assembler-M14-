
#ifndef MAABADA_MMN14_DATASTRUCTURES_H
#define MAABADA_MMN14_DATASTRUCTURES_H

#define EXTERN_MACRO "extern"
#define ENTRY_MACRO "entry"
#define MAX_LINE 82

#define BITS_IN_WORD 15
#define DIGITS_IN_ADDRESS 4
#define INPUT_SUFFIX ".as"
#define OUTPUT_SUFFIX ".ob"
#define EXTERN_OUTPUT_SUFFIX ".ent"
#define EXNTRY_OUTPUT_SUFFIX ".ext"
#define MAX_LINE 82
#define MEMORY_START_ADDRESS 100 /* can be changed */
#define MAX_ARRAY 500
#define MAX_OPERANDS 2
#define INITIAL_VALUE 0
#define true 1
#define false 0
#define NOT_RELAVANT -1
#define MAX_STRING_NAME


#define isWhiteSpace(x) (((x) == ' ')||((x) == '\t'))



/* types of symbols in the assembly code */
enum symbol_type {
	EXTERN_SYMBOL,
	ENTRY_SYMBOL,
	CODE_SYMBOL_DECLARATION,
	DATA_SYMBOL,
	CODE_SYMBOL, /* used, not declared */
	NOT_DECLARED = -1
};

/* types of addressing modes of the command operands */
enum addressingMethods {
    instantAddressing,
    directAddressing,
    registerBypass,
    registerDirect
};


/*!
 *
 */
typedef enum ARE { external = 0, relocatable, absolute } ARE;


/*!
 *
 */
typedef enum linePurposes {Tsymbol = -1, Tnumber = -2, Tinstruction = -3,
    Tstring = -4, Tcommand = -5, Tregister = -6,
    TnewLine = -7, Terror = -8} linePurposes;

enum memory_word_toShift
{
    ERA = 0,
    DEST_ADDRESS = 3,
    SRC_ADDRESS = 7,
    COMMAND_OPCODE = 11,

    NUM = 3,
    SRC_REG = 6,
    DEST_REG = 3
};

/*!
 *
 */
typedef enum registers {R0, R1, R2, R3, R4, R5, R6, R7} registers;

/*!
 *
 */
typedef enum instructions {STRING, DATA, ENTRY, EXTERN } instructions;



typedef struct Token
{
    int type;
    union
    {
        char symbol[MAX_STRING_NAME];
        char string[MAX_LINE];
        int number;
        char tempCh;
        int command;
        int reg;
        int instruction;
    } data;

} Token;



/*!
 *This struct allows us to take a line from the input file and manipulate it, so we can assemble her to a machine
 * language code.
 */
typedef struct LineStruct
{
    int theLinePurpose; /*the line type/ purpose out of LinePurposes that declared above.*/
    
    union
    {
        char* line; /*This is the genuine line from the input, and we run over it*/

        char* symbolName; /*This is where the symbol name parsed and stored, if found.*/

        char* string; /*This is where the data of type string is parsed and stored, if found.*/

        int number1; /*This is where the data of type number for parameter 1 is parsed and stored, if found */

		int number2; /*This is where the data of type number for parameter 2 is parsed and stored, if found */

		Token* operand1Token;/* if one of the operands is a symbol than this Token will contain its details.*/

        Token* operand2Token;/* if one of the operands is a symbol than this Token will contain its details.*/

        unsigned int lineNumber; /*This is the genuine line number from the input.*/

        int isTranslated; /*This is a flag, helps us to understand if there is more job on this line.*/

        int command; /*This is where the command name parsed and stored, if found.*/

        int reg_op1; /*This is where the register number parsed and stored, if found */

		int reg_op2;/*This is where the register number parsed and stored, if found */

        int operand1;/*if there is at least 1 operand than one of the values of enum 'addressingMethods' will be stored here. if theres only 1 operand
							it will contain the destination operand.*/

        int operand2;/*if there is 2 operands than one of the values of enum 'addressingMethods' will be stored here. this is for destination operand*/

        int instruction; /*This is where the instruction type name parsed and stored, if found.*/

    }data;

} LineStruct;



typedef struct dataNode{ /*we've decided to implement the data table with a linked list, becuse we can't tell
the length of it before the user insert file input. anyway, with linked list we can add nodes dynamically*/
    int address;
    short word;
    struct dataNode *next;
}*dataNodePtr, dataNode;


typedef struct dataLinkedList {
    int size;
    dataNodePtr head;
}dataLinkedList, *dataLinkedListPtr;



/*!
 *
 */
struct opTable
{
    char *codeName;
    unsigned int word;
    int numOfOperands;
    int sourceAddressingMethods[4];
    int destAddressingMethods[4];
}opTable;

struct opTable commandsTable[16];



/*!
 *
 */
struct instruction
{
    char* instruction;
    int insType;
}instruction;

        

/*!
 *
 */
struct Register
{
    char* regName;
    int regNum;
}Register;


typedef struct SYMBOL_occur* occp;

/*!
 *this is one occurrence of a symbol in the file.
 */
typedef struct SYMBOL_occur
{
	int line;
	occp next;
}occurrence;

/*!
 * this node represent a symbol, it will be a part of a linked list 
 * which will represent the symbol table.
 */
typedef struct node{
    char *symbolName;/* the name of the symbol */
    int address;/* the location in memory in which this symbol was declared */
    int entry_extern;/*is it entry or extern?*/
    int data_or_instruction; /* the type of the symbol, from the values of the enum above. */
	occp occurrence; /* a linked list of all the occurrences of this symbol in the code */
    struct node* next;
}*nodePtr, node;


/*!
 *
 */
typedef struct linkedList {
    int size;
    nodePtr head;
}linkedList, *linkedListPtr;

extern int IC,DC;
extern linkedListPtr symbolTable;
extern dataLinkedListPtr dataTable;
extern short int commands_array[MAX_ARRAY];
int errorFlag;


#endif /*MAABADA_MMN14_DATASTRUCTURES_H*/