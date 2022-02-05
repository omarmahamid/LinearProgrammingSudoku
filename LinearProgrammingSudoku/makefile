CC = gcc
OBJS = main.o printer.o Manage.o game.o LPSolve.o Auxiliary.o LinkedList.o parser.o gameFlow.o 
EXEC = sudoku
COMP_FLAG = -ansi -Wall -Wextra -Werror -pedantic-errors
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o $@ -lm
main.o: main.c SPBufferset.h parser.h
	$(CC) $(COMP_FLAG) -c $*.c
printer.o: printer.c printer.h
	$(CC) $(COMP_FLAG) -c $*.c
Manage.o: Manage.c Manage.h 
	$(CC) $(COMP_FLAG) -c $*.c
game.o: game.c game.h printer.h
	$(CC) $(COMP_FLAG) -c $*.c
LPSolve.o: LPSolve.c LPSolve.h
	$(CC) $(COMP_FLAGS) $(GUROBI_COMP) -c $*.c
Auxiliary.o: Auxiliary.c Auxiliary.h 
	$(CC) $(COMP_FLAG) -c $*.c
LinkedList.o: LinkedList.c LinkedList.h 
	$(CC) $(COMP_FLAG) -c $*.c
parser.o: parser.c parser.h 
	$(CC) $(COMP_FLAG) -c $*.c
gameFlow.o: gameFlow.c gameFlow.h 
	$(CC) $(COMP_FLAG) -c $*.c

all: $(EXEC)

clean:
	rm -f *.o $(EXEC)
