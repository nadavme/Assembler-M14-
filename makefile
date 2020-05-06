EXEC_FILE = assembler
C_FILES = main.c aidTools.c filesAssembler.c memoryMap.c secondRunOver.c symbolsTable.c
H_FILES = assembler.h aidTools.h filesAssembler.h memoryMap.h secondRunOver.h symbolsTable.h dataStructures.h

O_FILES = $(C_FILES:.c=.o)

all: $(EXEC_FILE)
$(EXEC_FILE): $(O_FILES)
	gcc -Wall -ansi -pedantic -g $(O_FILES) -o $(EXEC_FILE)
%.o: %.c $(H_FILES)
	gcc -Wall -ansi -pedantic -c -o $@ $<
clean:
	rm -f *.o $(EXEC_FILE)
