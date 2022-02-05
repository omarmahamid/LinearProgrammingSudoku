
#ifndef GAMEFLOW_H_
#define GAMEFLOW_H_
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
void freeIntegerSudoku(int** sudoku, int size);
void FreeingDoubleLinkedList(Step* move, Step* last);
void NullityGAME(Sudoku* sudoku);
void NullityComm(char** command);

#endif /* GAMEFLOW_H_ */
