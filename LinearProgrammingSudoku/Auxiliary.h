
#ifndef AUXILIARY_H_
#define AUXILIARY_H_
#include "game.h"
#include "gameFlow.h"

typedef struct Con{
	int BlockRow;
	int BlockCol;
	int BoardRow;
    int BoardCol;
    int flag;
    Unit* temp;
    struct Con* next;
    struct Con* prev;
}Con;

typedef struct Stack{
	Con *first;
	Con *last;
}Stack;

int numOfSol(Sudoku* sudoku);
Unit** sudokuCp(Sudoku* sudoku);
#endif /* AUXILIARY_H_ */
