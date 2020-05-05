//
// Created by nadav on 27/04/2020.
//

#include "secondRunOver.h"

int secondRunOver(linkedListPtr symbolTable)/*return 0 if theres errors and printing is irrelevant, return 1 if
                                                                        if theres no errors. */
{
    int flag;
    nodePtr curr;
    curr = symbolTable->head;
    flag = 1;
    while (curr) /* not reaching the end of the list */
    {
        /* validation checks */
        if ((curr->entry_extern == ENTRY_SYMBOL) && (curr->address == NOT_DECLARED))
        {
            errorHandler(1,-1,"symbol %s not declared",curr->symbolName);
            curr = curr->next;
            flag = 0;
            continue;
        }
        else if (curr->address == NOT_DECLARED)
        {
            if ((curr->entry_extern != EXTERN_SYMBOL) && (curr->occurrence != NULL))
            {
                errorHandler(1,-1,"symbol %s was used without declaration",curr->symbolName);
                curr = curr->next;
                flag = 0;
                continue;
            }
        }

        /*adding to the commands array's, bassically the core of the second run over...*/

        if (curr->entry_extern == EXTERN_SYMBOL) /* external symbol, will add 'E' in the ERA part of the memory word */
        {
            turnOnBits2Arr(external, curr->occurrence);
        }
        else if (curr->address != NOT_DECLARED) /* all other lables */
        {
            if (curr->data_or_instruction == DATA_SYMBOL)/*מפה לחזור...*/
            {
                lable2array(((FIRST_MEMORY_ADDRESS + (curr->declaration) + IC) << DEST_ADDRESS) | RELOCATABLE, curr->occurrence);
            }
            else /* instruction lable, in the code part */
            {
                lable2array(((FIRST_MEMORY_ADDRESS + (curr->declaration)) << DEST_ADDRESS) | RELOCATABLE, curr->occurrence);
            }
        }
        curr = curr->next;
    }

return flag;
}

/* this function adds number into the array, in all of the lable occurrences */
void turnOnBits2Arr(int bit, occPtr occurrence_list)
{
	occPtr curr = occurrence_list;
	while (curr)
	{
		turn_On_bit_on_cell(curr->line);
		curr = curr->next;
	}
}

void turn_On_bit_on_cell(int place, int cell)
{
    commands_array[cell] |= (int)pow(2, place);
}