EXEC_FILE = assembler
C_FILES = main.c symbolsTable.c aidTools.c memoryMap.c filesAssembler.c
                  permanentTables.c secondRunOver.c
H_FILES = symbolsTable.h aidTools.h memoryMap.h filesAssembler.h
                            permanentTables.h secondRunOver.h

O_FILES = $(C_FILES:.c=.o)

all: $(EXEC_FILE)
$(EXEC_FILE): $(O_FILES)
	gcc -Wall -ansi -pedantic -g $(O_FILES) -o $(EXEC_FILE)
%.o: %.c $(H_FILES)
	gcc -Wall -ansi -pedantic -c -o $@ $<
clean:
	rm -f *.o $(EXEC_FILE)
