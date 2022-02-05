
#ifndef FREE_H_
#define FREE_H_

#include "game.h"
#include "gameFlow.h"
int UndoStep(Sudoku* sudoku);
int RedoStep(Sudoku* sudoku);
void AppendStep(Sudoku* sudoku, ListOfUnitC* lstModCells);
void AppendUnitC(ListOfUnitC* lst, UnitC* mCell);
#endif
