
#ifndef PRINTER_H_
#define PRINTER_H_
#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef enum{
	LUCK,
	SOLVABLE,
	NOTSOLVABLE,
	ENVIRONMENT,
	Congratulation
}Surprise;
typedef enum{
	GRB_AD,
	GRB_S_ATT,
	GRB_MODEL,
	GRB_CONST
}ERRORGRB;
typedef enum{
	ERROR_IN_ALLOCATE_MEM,
	COMMAND_EXCCEED,
	COMMAND_EMPTY,
	ERROR_MODE,
	NO_ENOUGH_PARAM,
	PARAM_EXCEED,
	NUMBER_INVALID,
	OUT_OF_BOUND_INDEX,
	OUT_OF_BOUND_THRESHOLD,
	INVALID_PARAM,
	SUD_VAL_INVALID,
	FIXED_CELL,
	FILLED_CELL,
	ERRONEOUS,
	ERROR_PATH,
	INVALID_CHAR,
	RAND_ERR,
	MANY_VAL,
	FEWER_VAL,
	ERROR_RANGE,
	ERROR_SIZE,
	UNDO_STUCK,
	REDO_STUCK
} Error;
void surpMessage(Surprise s);
void Print_Board(Sudoku* sudoku);
void PrintSayingHello();
void errorMessage(Error e, char* arg1, char* arg2);
void error_GRB(ERRORGRB error,int* arg1,char* arg2);
#endif /* PRINTER_H_ */
