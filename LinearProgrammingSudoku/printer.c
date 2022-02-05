#include "printer.h"
/*
 *This module is the center of the print everything
 *includes this method:
 *errorMessage : which take an error and 2 argument which sometimes we need it to indicate cell ,(somthing like this)
 *after that she decode the e in switch case and return a suitable error
 *error_GRB : take an errorGRB and return a suitable error
 *Print_Board : which prints the board according to the project instruction
 *PrintSayingHello : print hello and something like that
 */
void surpMessage(Surprise s){
	switch(s){
		case LUCK:
			printf("Wish luck for you man!.\n");
			break;
		case SOLVABLE:
			printf("the board is solvable.\n");
			break;
		case NOTSOLVABLE:
			printf("the board is notsolvable.\n");
			break;
		case ENVIRONMENT:
			printf("cannot create an environment.\n");
			break;
		case Congratulation:
			printf("\nCongratulation!.\n");
			break;
	}
}
void errorMessage(Error e, char* arg1, char* arg2){
	switch(e){
		case ERROR_IN_ALLOCATE_MEM:
			printf("Cannot allocate.\n");
			break;
		case COMMAND_EMPTY:
			printf("There is no command(empty).\n");
			break;
		case COMMAND_EXCCEED:
			printf("The command is exceed the limit.\n");
			break;
		case ERROR_MODE:
			printf("Cannot use '%s' command in %s mode.\n",arg1, arg2);
			break;
		case NO_ENOUGH_PARAM:
			printf("No enough parameters.\n");
			break;
		case PARAM_EXCEED:
			printf("The parameters are exceed the limit.\n");
			break;
		case NUMBER_INVALID:
			printf("Error at least in one of the parameters (are not number).\n");
			break;
		case OUT_OF_BOUND_INDEX:
			printf("The %s exceed the bound.\n",arg1);
			break;
		case OUT_OF_BOUND_THRESHOLD:
			printf("The threshold %s exceed the bound.\nPlease enter threshold between 0 to 1.\n",arg1);
			break;
		case INVALID_PARAM:
			printf("The parameter %s is invalid.\n",arg1);
			break;
		case SUD_VAL_INVALID:
			printf("Please enter values between 0 to %s.\n",arg1);
			break;
		case FIXED_CELL:
			printf("Error: Cell [%s,%s] is fixed.\n", arg1, arg2);
			break;
		case FILLED_CELL:
			printf("Error: Cell [%s,%s] already contains a value.\n", arg1, arg2);
			break;
		case ERRONEOUS:
			if(arg1!=NULL){
				if(strcmp(arg1, "save_in_edit")==0)
					printf("Cannot save an erroneous game in Edit mode.\n");
				if(strcmp(arg1, "full_board")==0)
					printf("Attention that the board is erroneous.\n");
			}
			else
				printf("The board is erroneous.\n");
			break;
		case ERROR_PATH:
			printf("Cannot find the path:\"%s\".\n", arg1);
			break;
		case INVALID_CHAR:
			printf("The char '%s' is illegal.\n",arg1);
			break;
		case RAND_ERR:
			printf("Error in random");
			break;
		case MANY_VAL:
			printf("There are too many values.\n");
			break;
		case FEWER_VAL:
			printf("There are fewer values.\n");
			break;
		case ERROR_RANGE:
			printf("There is in the file a value out of range.\n");
			break;
		case ERROR_SIZE:
			printf("There is an error in size board.\n");
			break;
		case UNDO_STUCK:
			printf("Cannot undo.\n");
			break;
		case REDO_STUCK:
			printf("Cannot re-do.\n");
			break;
	}
}
void error_GRB(ERRORGRB error, int* arg1, char* arg2){
	switch(error){
		case GRB_AD:
			printf("ERROR %d GRBaddvars %s\n",*arg1,arg2);
			break;
		case GRB_S_ATT:
			printf("ERROR %d GRBsetintattr %s\n",*arg1,arg2);
			break;
		case GRB_MODEL:
			printf("ERROR %d GRBupdatemodel %s\n",*arg1,arg2);
			break;
		case GRB_CONST:
			printf("ERROR %d in cell constraint GRBaddconstr %s\n",*arg1,arg2);
			break;
	}
}
void Print_Board(Sudoku* sudoku){
	Unit temp;
	int i,j,k,l,m;
	int dist =4*sudoku->size +sudoku->rows +1;
	for(i = 0;i< sudoku->cols;i++){
		for(j=0;j<dist;j++)
			printf("-");
		printf("\n");
		for(k=0; k<sudoku->rows;k++){
			for(l = 0 ; l < sudoku->rows; l++){
				printf("|");
				for(m = 0; m<sudoku->cols ; m++){
					printf(" ");
					temp = sudoku->board[(sudoku->rows)*i+k][(sudoku->cols)*l+m];
					if(temp.isFixed)
						printf("%2d.", temp.value);
					else{
						if(temp.value!=0){
							if(temp.isError && sudoku->mark_errors==1)
								printf("%2d*", temp.value);
							else
								printf("%2d ", temp.value);
						}
						else
							printf("   ");
					}
				}
			}
			printf("|\n");
		}
	}
	for(j=0;j<dist;j++)
		printf("-");
	printf("\n");
}
void PrintSayingHello(){
	printf("Hello everyone to the sudokuGame.\n");
	printf("there are 3 modes in the sudokuGame.\n");
	printf("1) INIT.\n");
	printf("2) SOLVE.\n");
	printf("3) EDIT.\n");
}

