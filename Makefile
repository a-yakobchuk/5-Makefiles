CC = gcc
CFLAGS = -O1 -g -Wall -std=c99 -pedantic
SOURCE = TestSearch.c LinkedLists.c DynamicArrays.c
OBJ = $(patsubst %.c, %.o, $(SOURCE))
EXE = TestSearch 
VALGRIND = valgrind --tool=memcheck --leak-check=yes --track-origins=yes 
SEARCHWORD = space
#SEARCHWORD = Tera
RESULTS = out.txt
MEMTXT = mem.txt
TESTTXT = engWords.txt

.SILENT:
all: $(EXE)

$(EXE): $(OBJ)
	@echo "Linking program"
	$(CC) $(OBJ) -o $(EXE)

.c.o: 
	@echo "Compiling program $*.c"
	$(CC) $(CFLAGS) $*.c -c


test: $(EXE) 
	./$(EXE) engWords.txt $(SEARCHWORD) > $(RESULTS) 
	cat $(RESULTS)

.PHONY: mem clean test all help
mem: $(EXE)
	@echo "running mem, will take ~5 mins"
	$(VALGRIND) ./$(EXE) $(TESTTXT) $(SEARCHWORD) > $(MEMTXT) 2>&1
	cat $(MEMTXT)

clean: 
	-rm -f $(OBJ) $(EXE) $(RESULTS) $(MEMTXT)

help:
	@echo "make options are: all, clean, mem, test"

