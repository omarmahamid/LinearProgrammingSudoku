
#ifndef PARESER_H_
#define PARESER_H_
#include "game.h"
#include "Manage.h"
#include "LinkedList.h"
#include "Auxiliary.h"
#include "LPSolve.h"
#include "gameFlow.h"


Command commandParser(Sudoku** sudoku);
void Equal_val(int y,int x, int value,Sudoku* sudoku, ListOfUnitC* listMod);
/*Sudoku is the sudoku board and command is the user input*/

Command Command_Translator(char** command , Sudoku** sudoku);
Command _set(char** command,Sudoku* sudoku);
Command _solve(char** command,Sudoku** sudoku);
Command _edit(char** command,Sudoku** sudoku);
Command _markError(char** command,Sudoku* sudoku);
Command _printBoard(char** command,Sudoku* sudoku);
Command _validate(char** command,Sudoku* sudoku);
Command _guess(char** command,Sudoku* sudoku);
Command _generate(char** command,Sudoku* sudoku);
Command _undo(char** command,Sudoku* sudoku);
Command _redo(char** command,Sudoku* sudoku);
Command _save(char** command,Sudoku* sudoku);
Command _hint(char** command,Sudoku* sudoku);
Command _guessHint(char** command,Sudoku* sudoku);
Command _numSolutions(char** command,Sudoku* sudoku);
Command _autofill(char** command,Sudoku* sudoku);
Command _reset(char** command,Sudoku* sudoku);
Command __exit(char** command,Sudoku* sudoku);
void set_and_Unit(ListOfUnitC* lst, UnitC* mCell, int x, int y, int orgVal, int newVal, int orgNumCont, int newNumCont, int orgError, int newError);
#endif /* PARESER_H_ */
