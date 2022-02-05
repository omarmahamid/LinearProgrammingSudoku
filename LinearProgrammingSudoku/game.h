
#ifndef GAME_H_
#define GAME_H_
#include <stdio.h>
typedef enum {
	solve,
	edit,
	mark_errors,
	print_board,
	set,
	validate,
	guess,
	generate,
	undo,
	redo,
	save,
	hint,
	guess_hint,
	num_solutions,
	autofill,
	reset,
	exit_Command,
	error__=-1
} Command;
typedef struct{
	int numOfVal;
	int beginIndex;
	int* posValues;
}Unit_GUROBI;

typedef enum{
	TYPE_ONE
}TYPES;
/*
 * The 3 modes (init,edit,solve) with code to every mode
 */
enum {
	INIT=0
	,EDIT=1
	,SOLVE=2
} modeGame;
/*
 * this is the unit cell in the sudoku board
 */
typedef struct Unit{
	int value;
	unsigned int isFixed;
	unsigned int isError;
	unsigned int Intersection;
}Unit;
/*
 * sudoku board with fields
 */
typedef struct Sudoku{
	int rows;
	int cols;
	int size;
	int Fill;
	int mark_errors;
	struct ListS* linkedlistm;
	Unit** board;
}Sudoku;
/*
 * the prev(before and after) unit cell with fields
 */
typedef struct UnitC{
	struct UnitC* next;
	int X;
	int Y;
	int prValue;
	int currValue;
	int IntersectPr;
	int IntersectCu;
	int prErr;
	int cuErr;

}UnitC;
/*
 *
 */
typedef struct ListOfUnitC{
	UnitC* first;
	int pre;
	int Cur;
}ListOfUnitC;
/*
 * step structure
 * because we need step list
 */
typedef struct Step{
	struct Step* next;
	struct Step* prev;
	ListOfUnitC* listofunitC;
}Step;

typedef struct ListS{
	Step* first;
	Step* current;
	Step* last;
}ListS;
Sudoku* initial(int rows, int cols);
void printBoard(Sudoku* sudoku);
void IsEnd(Sudoku* sudoku);
int Is_Erreneous(Sudoku* sudoku);
int Value_Validation(Sudoku* sudoku, int x, int y, int num, TYPES type);
#endif /* GAME_H_ */
