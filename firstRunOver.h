//
// Created by nadav on 04/02/2020.
//

#ifndef MAABADA-MMN14_FIRSTRUNOVER_H
#define MAABADA-MMN14_FIRSTRUNOVER_H

#include <stdio.h>


typedef struct first_word /*we've choosed to define the machine language word with bit fields, lets see how it goes... Nadav The king, Matan the princess ;-) */
{
    unsigned short external : 1;
    unsigned short relocatable : 1;
    unsigned short absolute : 1;

    unsigned short destination_0 : 1;
    unsigned short destination_1 : 1;
    unsigned short destination_2 : 1;
    unsigned short destination_3 : 1;

    unsigned short source_0 : 1;
    unsigned short source_1 : 1;
    unsigned short source_2 : 1;
    unsigned short source_3 : 1;

    unsigned int opCode : 4;
};

typedef struct second_word /*word for 1st and 2nd methods (mio'n methods)*/
{


    unsigned short op_is_external : 1;
    unsigned short op_is_relocatable : 1;
    unsigned short op_is_absolute : 1;

    unsigned short num_or_addres : 12;
};

typedef struct third_word /*word for 3rd and 4th methods (mio'n methods)*/
{


    unsigned short op_is_external : 1;
    unsigned short op_is_relocatable : 1;
    unsigned short op_is_absolute : 1;

    unsigned short bit : 3;/*stoped here*/
};


#endif //MAABADA-MMN14_FIRSTRUNOVER_H
