#include "LinkedList.h"
#include <stdlib.h>
/*
 * This module is the responsible of the List because the undo and redo commands
 * it contains the function UndoStep,RedoStep ,AppendStep ,AppendUnitC and other help functions
 * UndoStep :
 * do undo step which get the last (pre) step and every thing relevant
 * RedoStep:
 * redo a step previously undone by the user.
 * AppendStep :
 * push a step
 * AppendUnitC :
 * push a unit that contains information for undo-redo
 *
 */
int HelperListOfUnitC(ListOfUnitC* listofunitC, UnitC* unit){
	UnitC* unitC = listofunitC->first;
	while(unitC!=NULL)
		if(unitC->X == unit->X && unitC->Y == unit->Y)
			return 1;
		else
			unitC = unitC->next;
	return 0;
}
Step* ConstructStep(ListOfUnitC* listofunitC){
	Step* s = (Step*) malloc(sizeof(Step));
	s -> listofunitC = listofunitC;
	s -> next = NULL;
	s -> prev = NULL;
	return s;
}
void AppendStep(Sudoku* sudoku, ListOfUnitC* listofunitC){
	Step* sNew = ConstructStep(listofunitC);
	Step* tempCur;
	Step* temp2;
	tempCur = sudoku->linkedlistm->current;
	temp2 = tempCur->next;
	sudoku->linkedlistm->current = sNew;
	sudoku->linkedlistm->current->next = sudoku->linkedlistm->last;
	tempCur->next = sudoku->linkedlistm->current;
	sudoku->linkedlistm->current-> prev = tempCur;
	if(temp2 != sudoku->linkedlistm->last)
		FreeingDoubleLinkedList(temp2, sudoku->linkedlistm->last);
}
int UndoStep(Sudoku* sudoku){
	UnitC* unitC;
	if(sudoku->linkedlistm->current == sudoku->linkedlistm->first)
		return 0;
	unitC = sudoku->linkedlistm->current->listofunitC->first;
	while(unitC != NULL){
		sudoku->board[unitC->X][unitC->Y].value = unitC->prValue;
		sudoku->board[unitC->X][unitC->Y].isError = unitC->prErr;
		sudoku->board[unitC->X][unitC->Y].Intersection = unitC->IntersectPr;
		unitC = unitC->next;
	}
	sudoku->Fill = sudoku->linkedlistm->current->listofunitC->pre;
	sudoku->linkedlistm->current = sudoku->linkedlistm->current->prev;
	return 1;
}
int RedoStep(Sudoku* sudoku){
	UnitC* unitC;
	if(sudoku->linkedlistm->current->next == sudoku->linkedlistm->last)
		return 0;
	unitC = sudoku->linkedlistm->current->next->listofunitC->first;
	while(unitC != NULL){
		sudoku->board[unitC->X][unitC->Y].value = unitC->currValue;
		sudoku->board[unitC->X][unitC->Y].isError = unitC->cuErr;
		sudoku->board[unitC->X][unitC->Y].Intersection = unitC->IntersectCu;
		unitC = unitC->next;
	}
	sudoku->Fill = sudoku->linkedlistm->current->next->listofunitC->Cur;
	sudoku->linkedlistm->current = sudoku->linkedlistm->current->next;
	return 1;
}
void AppendUnitC(ListOfUnitC* listofunitC, UnitC* unit){
	UnitC* unitC;
	if(listofunitC==NULL){
		free(unit);
		return;
	}
	if(HelperListOfUnitC(listofunitC,unit)){
		free(unit);
		return;
	}
	unitC = listofunitC->first;
	listofunitC->first = unit;
	listofunitC->first->next = unitC;
}



