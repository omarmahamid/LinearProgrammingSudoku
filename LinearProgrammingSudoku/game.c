#include <stdlib.h>
#include "game.h"
#include "printer.h"
/*
 * this module contains this method :
 * Value Validation :
 * which check if in the sudoku game there is a value which equal in (Row,Block,Col)
 * initial:
 * which initialize the suodku game with dimension (Row,Col)
 * printboard:
 * which prints the board according to the project instructions
 * is end :
 * check if the sudoku is filled , (every unit in the board contains a num)
 * is erenous:
 * check if errenous
 *
 */
int Value_Validation(Sudoku* sudoku, int x, int y, int num, TYPES type){
	int i, j, X_, Y_;
	X_ = (x) - (x)% sudoku->rows;
	Y_ = (y) - (y)% sudoku->cols;
	if(type==TYPE_ONE){
		for(i=0;i<sudoku->size;i++)
		{
			if(sudoku->board[x][i].value == num)
			{
				return 1;
			}
		}
		for(i=0;i<sudoku->size;i++)
		{
			if(sudoku->board[i][y].value == num)
			{
				return 1;
			}
		}
		for(i = X_ ; i < X_ + sudoku->rows;i++){
			for(j = Y_; j < Y_ + sudoku->cols ; j++)
			{
				if(sudoku->board[i][j].value == num)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}
Sudoku* initial(int rows, int cols){
	int i,j;
	int size=rows*cols;
	Sudoku* sudoku;
	Unit **matrix;
	Step* first;
	Step* last;
	ListS* listS;
	listS = (ListS*) malloc(sizeof(ListS));
	first = (Step*) malloc(sizeof(Step));
	last = (Step*) malloc(sizeof(Step));
	listS->first = first;
	listS->current = listS->first;
	listS->last = last;
	listS->current->next  = listS->last;
	sudoku = (Sudoku*) malloc(sizeof(Sudoku));
	if(sudoku == NULL)
		errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
	matrix = (Unit**) malloc(size*sizeof(Unit*));
	if(matrix==NULL)
		errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
	for(i=0;i<size;i++){
		matrix[i] = (Unit*) malloc(size*sizeof(Unit));
		if(matrix[i]==NULL)
			errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
	}
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			matrix[i][j].isFixed = 0;
			matrix[i][j].isError = 0;
			matrix[i][j].value = 0;
			matrix[i][j].Intersection = 0;
		}
	}
	sudoku->rows = rows;
	sudoku->cols = cols;
	sudoku->size = size;
	sudoku->linkedlistm = listS;
	sudoku->mark_errors = 1;
	sudoku->Fill = 0;
	sudoku->board = matrix;
	return sudoku;
}
void printBoard(Sudoku* sudoku){
	Print_Board(sudoku);
}
void IsEnd(Sudoku* sudoku){
	if(sudoku->Fill == (sudoku->size*sudoku->size)){
		if(Is_Erreneous(sudoku)==0)
			errorMessage(ERRONEOUS,"full_board",NULL);
		else{
			surpMessage(Congratulation);
			printf("\nYou can choosing another time one of the modes.\n");
			modeGame = INIT;
		}
	}
}
int Is_Erreneous(Sudoku* sudoku){
	int i,j;
	for(i=0;i<sudoku->size;i++)
		for(j=0;j<sudoku->size;j++)
			if(sudoku->board[i][j].Intersection!=0){
				printf("%d %d", i+1, j+1);
				return 0;
			}
	return 1;
}
