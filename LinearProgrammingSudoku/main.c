#include "SPBufferset.h"
#include "parser.h"
#define START 0
/*
 * Sorry for the bad English.
 */
int main(){
	Sudoku* sudoku;
	Command command;
	SP_BUFF_SET();
	command = START;
	sudoku = initial(START,START);
	modeGame = INIT;
	PrintSayingHello();
	command = commandParser(&sudoku);
	if(command==exit_Command){
		return 0;
	}
	else
	{
		if(command==edit || command==set || command==autofill || command==undo || command==redo ||
				command==generate || command==guess || command==reset || command==solve){
			printBoard(sudoku);
		}
	}
	while(command!=exit_Command){
		command = commandParser(&sudoku);
		if(command == exit_Command)
			break;
		if(command==edit || command==set || command==autofill || command==undo || command==redo ||
					command==generate || command==guess || command==reset || command==solve)
			printBoard(sudoku);
	}
	return 0;
}


