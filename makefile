CC = gcc
CFLAGS = -g -Wall -ansi -pedantic

default: Assembler

Assembler: main.o filesAssembler.o symbolsTable.o aidTools.o memoryMap.o secondRunOver.o
	$(CC) $(CFLAGS) -o main.o filesAssembler.o symbolTable.o aidTools.o memoryMap.o secondRunOver.o

main.o: main.c filesAssembler.h
	$(CC) $(CFLAGS) -c main.c

filesAssembler.o: filesAssembler.c filesAssembler.h symbolsTable.h memoryMap.h secondRunOver.h aidTools.h dataStructures.h
	$(CC) $(CFLAGS) -c filesAssembler.c

SymbolsTable.o: symbolslList.c symbolsList.h aidTools.h dataStructures.h
	$(CC) $(CFLAGS) -c SymbolsTable.c

aidTools.o: aidTools.c aidTools.h dataStructures.h symbolsTable.h memoryMap.h
	$(CC) $(CFLAGS) -c aidTools.c

memoryMap.o: memoryMap.c memoryMap.h aidTools.h dataStructures.h
	$(CC) $(CFLAGS) -c memoryMap.c


secondRunOver.o: secondRunOver.c secondRunOver.h aidTools.h filesAssembler.h memoryMap.h symbolTable.h dataStructures.h
	$(CC) $(CFLAGS) -c secondRunOver.c
