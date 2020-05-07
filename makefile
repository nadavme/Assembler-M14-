assembler: *.c *.h
	gcc -Wall -ansi -pedantic main.c aidTools.c filesAssembler.c memoryMap.c secondRunOver.c symbolsTable.c -o assembler -lm