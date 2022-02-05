#include "gameFlow.h"
#define D 5
/*
 * This module centre of the gameflow which means when we free the sudoku this mudole is the manager of that
 * contains this method:
 * HelpFreeing which help us in the function FreeingDoublyLinkedList which make free to it
 * freeIntegerSudoku which frees (int) sudoku
 * FreeingHelp2 like the help 1
 * NullityGame which frees the sudoku board
 * FreeingDoublyLinkedList which frees the DoublyLinkedList used helper function
 * NullityCommand frees the command**
 */
void HelpFreeing(Step* s){
	UnitC* unitC;
	UnitC* temp;
	ListOfUnitC* lst = s->listofunitC;
	unitC = lst->first;
	while(unitC->next != NULL){
		temp = unitC->next;
		free(unitC);
		unitC = temp;
	}
	free(unitC);
	free(lst);
	free(s);
}
void freeIntegerSudoku(int** sudoku, int size){
	int i=0;
	while(i<size){
		free(sudoku[i]);
		i++;
	}
	free(sudoku);
}
void FreeingHelp2(ListS* lst){
	Step* step;
	Step* s;
	if(lst->first->next == lst->last){
		free(lst->first);
		free(lst->last);
		free(lst);
		return;
	}
	step = lst->first->next;
	while(step->next != lst->last){
		s = step->next;
		HelpFreeing(step);
		step = s;
	}

	HelpFreeing(step);
	free(lst->first);
	free(lst->last);
	free(lst);
}
void NullityGAME(Sudoku* sudoku){
	int i=0;
	while(i<sudoku->size){
		free(sudoku->board[i]);
		i++;
	}
	free(sudoku->board);
	if(sudoku->linkedlistm!=NULL)
		FreeingHelp2(sudoku->linkedlistm);
	free(sudoku);
}
void FreeingDoubleLinkedList(Step* step, Step* last){
	Step* s;
	while(step->next != last){
		s = step->next;
		HelpFreeing(step);
		step = s;
	}
	HelpFreeing(step);
}
void NullityComm(char** command){
	int i=0;
	while(i<D){
		if(command[i]!=NULL)
			free(command[i]);
		i++;
	}
}
