#include "parser.h"
#define D 5
/*
 * This module is the parser commands and do it.
 * in this module we have this methods
 * commandParser :
 * which get the command of the user and Parse it.
 * CommandTranslator :
 * which take a command and compare it with the commands (set , guess ...) after that call the suitable function
 * 1)_solve:
 * first we check if the syntax correct if not return errormessage , and then start the mode solve and return solve
 * 2)_edit :
 * check if the syntax is correct if not return error message, then init sudoku
 * 3)_mark_errors :
 * check the mode syntax and the syntax , then put sudoku mark errors and return mark_errors
 * 4)_printBoard :
 * print the board to the user with valid modes
 * 5)_set :
 * check the syntax with helps function
 * check valid modes
 * and after that do according to the project instruction (in solve mode do ... )
 * 6)_validate :
 * check if the mode is valid
 * validate the sudoku using the function SOLVE_LP_ILP wich we pass the validate command to do ILP not LP
 * 7)_guess :
 * check if the mode is valid
 * guess a solutin using the function SOLVE_LP_ILP with which we pass the guess command to do LP not ILP
 * 8)_generate :
 * check if the mode is valid
 * check the syntax
 * after that generating according to the instruction in the project
 * 9)_undo :
 * check the validity modes
 * undo a previous step according to the explanation in the project
 * 10)_redo :
 * check the validity modes
 * redo according to the explanation in the project
 * 11)_save :
 * check the validity modes
 * save according to the explanation in the project
 * 12)_hint :
 * check the validity modes
 * check the syntax
 * hint according to the explanation in the project
 * 13)_guesshint :
 * check the validity modes
 * check the syntax
 * guesshint according to the explanation in the project
 * 14)_numSol :
 * check the validity modes and semantics and syntax
 * print the number solution
 * 15)_autofill:
 * check the validity modes
 * autofill according to the explanation in the project
 * 16)_reset :
 * check the validity modes
 * reset according to the explanation in the project
 * 17)_exit :
 * check the validity modes
 * Terminates the program
 * and all of the rest function is a helps functions
 *
 */
Command commandParser(Sudoku** sudoku){
	int i=0,j=0;
	char* code[D];
	char c;
	char command[258]={0};
	for(j=0;j<D;j++)
		code[j] = NULL;
	if(fgets(command, sizeof command, stdin)==NULL)
			return 0;
	if(command[256]!='\0'){
		while ((c = getchar()) != '\n' && c != EOF);
		errorMessage(COMMAND_EXCCEED,NULL,NULL);
		return error__;
	}
	while(command[0]==10){
		if(fgets(command, sizeof command, stdin)==NULL)
					return 0;
			if(command[256]!='\0'){
				errorMessage(COMMAND_EXCCEED,NULL,NULL);
				return error__;
			}
	}
	code[i] = strtok(command," \t\r\n");
	while((code[i]!=NULL && code[i][0]!= 13) && (i<5)){
		i++;
		code[i] = strtok(NULL," \t\r\n");
	}
	return Command_Translator(code, sudoku);
}
Command Command_Translator(char** command , Sudoku** sudoku){
	if(strcmp(command[0], "solve")==0)
	{
		return _solve(command, sudoku);
	}
	if(strcmp(command[0], "edit")==0)
	{
		return _edit(command, sudoku);
	}
	if(strcmp(command[0], "mark_errors")==0)
	{
		return _markError(command, *sudoku);
	}
	if(strcmp(command[0], "print_board")==0)
	{
		return _printBoard(command, *sudoku);
	}
	if(strcmp(command[0], "set")==0)
	{
		return _set(command,*sudoku);
	}
	if(strcmp(command[0], "validate")==0)
	{
		return _validate(command, *sudoku);
	}
	if(strcmp(command[0], "guess")==0)
	{
		return _guess(command, *sudoku);
	}
	if(strcmp(command[0], "generate")==0)
	{
		return _generate(command,*sudoku);
	}
	if(strcmp(command[0], "undo")==0)
	{
		return _undo(command, *sudoku);
	}
	if(strcmp(command[0], "redo")==0)
	{
		return _redo(command, *sudoku);
	}
	if(strcmp(command[0], "save")==0)
	{
		return _save(command, *sudoku);
	}
	if(strcmp(command[0], "hint")==0)
	{
		return _hint(command,*sudoku);
	}
	if(strcmp(command[0], "guess_hint")==0)
	{
		return _guessHint(command,*sudoku);
	}
	if(strcmp(command[0], "num_solutions")==0)
	{
		return _numSolutions(command, *sudoku);
	}
	if(strcmp(command[0], "autofill")==0)
	{
		return _autofill(command, *sudoku);
	}
	if(strcmp(command[0], "reset")==0)
	{
		return _reset(command, *sudoku);
	}
	if(strcmp(command[0], "exit")==0)
	{
		return __exit(command, *sudoku);
	}
	errorMessage(COMMAND_EMPTY,NULL,NULL);
	return error__;
}

Command _solve(char** command,Sudoku** sudoku){
	if(command[2]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	if(loadFromFile(sudoku,command[1],"SOLVE")==0)
		return error__;
	surpMessage(LUCK);
	modeGame = SOLVE;
	return solve;
}

Command _edit(char** command,Sudoku** sudoku){
	if(command[2]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	if(command[1]!=NULL){
		if(loadFromFile(sudoku,command[1],"eDIT")==0)
			return error__;
	}
	else{
		NullityGAME(*sudoku);
		*sudoku = initial(3,3);
	}
	surpMessage(LUCK);;
	modeGame = EDIT;

	return edit;
}

Command _markError(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"mark_error","init");
		return error__;
	}
	if(modeGame==EDIT){
		errorMessage(ERROR_MODE,"mark_error","edit");
		return error__;
	}
	if(command[2]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	if(command[1]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return error__;
	}
	sudoku->mark_errors = atoi(command[1]);
	return mark_errors;
}

Command _printBoard(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"print_board","init");
		return error__;
	}
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	printBoard(sudoku);
	return print_board;
}

void set_and_Unit(ListOfUnitC* lst, UnitC* unit, int x, int y, int prValue, int currValue, int IntersectPr, int IntersectCu, int prErr, int cuErr){
	unit->X = x;
	unit->Y = y;
	unit->prValue = prValue;
	unit->currValue = currValue;
	unit->IntersectPr = IntersectPr;
	unit->prErr = prErr;
	unit->IntersectCu = IntersectCu;
	unit->cuErr = cuErr;
	AppendUnitC(lst,unit);
}
void Modify_Sudoku(int y, int x, Sudoku* sudoku, ListOfUnitC* listMod){
	UnitC* unitC;
	int a=x-1;
	int b=y-1;
	int i, j, X_,Y_;
	if(sudoku->board[b][a].value!=0){
		for(i = 0;i<sudoku->size;i++){
			if(sudoku->board[b][i].value == sudoku->board[b][a].value){
				if(i != a){
					unitC = (UnitC*) malloc(sizeof(UnitC));
					set_and_Unit(listMod,unitC,b,i,sudoku->board[b][i].value, sudoku->board[b][i].value, sudoku->board[b][i].Intersection,
							sudoku->board[b][i].Intersection-1, sudoku->board[b][i].isError, sudoku->board[b][i].Intersection == 1 ? 0:1);
				}
				sudoku->board[b][i].Intersection--;
				if(sudoku->board[b][i].Intersection==0)
					sudoku->board[b][i].isError=0;
			}
		}
		for(i = 0;i<sudoku->size;i++){
			if(sudoku->board[i][a].value == sudoku->board[b][a].value){
				if(i!= b){
					unitC = (UnitC*) malloc(sizeof(UnitC));
					set_and_Unit(listMod,unitC, i, a,sudoku->board[i][a].value, sudoku->board[i][a].value, sudoku->board[i][a].Intersection,
							sudoku->board[i][a].Intersection-1, sudoku->board[i][a].isError, sudoku->board[i][a].Intersection == 1 ? 0:1);
				}
				sudoku->board[i][a].Intersection--;
				if(sudoku->board[i][a].Intersection==0)
					sudoku->board[i][a].isError=0;
			}
		}
		X_ = (b) - (b)% sudoku->rows;
		Y_ = (a) - (a)% sudoku->cols;
		for(i = X_ ; i < X_ + sudoku->rows;i++){
			for(j = Y_; j < Y_ + sudoku->cols ; j++){
				if(sudoku->board[i][j].value == sudoku->board[b][a].value && (i!= b) && (j!= a)){
					unitC = (UnitC*) malloc(sizeof(UnitC));
					set_and_Unit(listMod,unitC, i, j,sudoku->board[i][j].value, sudoku->board[i][j].value, sudoku->board[i][j].Intersection,
							sudoku->board[i][j].Intersection-1, sudoku->board[i][j].isError, sudoku->board[i][j].Intersection == 1 ? 0:1);

					sudoku->board[i][j].Intersection--;
					if(sudoku->board[i][j].Intersection==0)
						sudoku->board[i][j].isError=0;
					printf("%d", sudoku->board[i][j].isError);
				}
			}
		}
	}
	sudoku->board[b][a].Intersection = 0;
	sudoku->board[b][a].isError = 0;

}
void _Modify_val(int y, int x, int value, int b, int a, int c, Sudoku* sudoku, ListOfUnitC* listMod){
	UnitC* unitC;
	int i, j,minX,minY, X_,Y_,isError=0;
	minX=x-1;
	minY=y-1;
	for(i = 0;i<sudoku->size;i++){
		if(sudoku->board[minY][i].value == value){
			unitC = (UnitC*) malloc(sizeof(UnitC));
			set_and_Unit(listMod,unitC, minY, i, sudoku->board[minY][i].value, sudoku->board[minY][i].value, sudoku->board[minY][i].Intersection,
					sudoku->board[minY][i].Intersection+1, sudoku->board[minY][i].isError, 1);
			sudoku->board[minY][i].Intersection++;
			sudoku->board[minY][i].isError=1;
			sudoku->board[minY][minX].Intersection++;
			isError = 1;
		}
	}
	for(i = 0;i<sudoku->size;i++){
		if(sudoku->board[i][minX].value == value){
			unitC = (UnitC*) malloc(sizeof(UnitC));
			set_and_Unit(listMod,unitC, i, minX, sudoku->board[i][minX].value, sudoku->board[i][minX].value, sudoku->board[i][minX].Intersection,
					sudoku->board[i][minX].Intersection+1, sudoku->board[i][minX].isError, 1);
			sudoku->board[i][minX].Intersection++;
			sudoku->board[i][minX].isError=1;
			sudoku->board[minY][minX].Intersection++;
			isError = 1;
		}
	}

	X_ = (minY) - (minY)% sudoku->rows;
	Y_ = (minX) - (minX)% sudoku->cols;
	for(i = X_ ; i < X_ + sudoku->rows;i++){
		for(j = Y_; j < Y_ + sudoku->cols ; j++){
			if(sudoku->board[i][j].value == value && (i!= minY) && (j!= minX)){
				unitC = (UnitC*) malloc(sizeof(UnitC));
				set_and_Unit(listMod,unitC, i, j, sudoku->board[i][j].value, sudoku->board[i][j].value, sudoku->board[i][j].Intersection,
						sudoku->board[i][j].Intersection+1, sudoku->board[i][j].isError, 1);
				sudoku->board[i][j].Intersection++;
				sudoku->board[i][j].isError=1;
				sudoku->board[minY][minX].Intersection++;
				isError = 1;
			}
		}
	}

	if(isError==1)
		sudoku->board[minY][minX].isError = 1;

	unitC = (UnitC*) malloc(sizeof(UnitC));
	set_and_Unit(listMod,unitC, minY, minX, b, value, a,
			sudoku->board[minY][minX].Intersection, c, sudoku->board[minY][minX].isError);
}

void Equal_val(int y,int x, int value,Sudoku* sudoku, ListOfUnitC* listMod){
	UnitC* unitC;
	int i,j, k;
	i = sudoku->board[y-1][x-1].Intersection;
	k = sudoku->board[y-1][x-1].isError;
	j = sudoku->board[y-1][x-1].value;
	if(sudoku->board[y-1][x-1].value==value){
		unitC = (UnitC*) malloc(sizeof(UnitC));
		set_and_Unit(listMod,unitC,y-1,x-1,value, value, sudoku->board[y-1][x-1].Intersection,
				sudoku->board[y-1][x-1].Intersection, sudoku->board[y-1][x-1].isError, sudoku->board[y-1][x-1].isError);
		return;
	}

	Modify_Sudoku(y,x,sudoku,listMod);
	if(value==0){
		unitC = (UnitC*) malloc(sizeof(UnitC));
		set_and_Unit(listMod,unitC, y-1, x-1, j, value, i, sudoku->board[y-1][x-1].Intersection,
				k, sudoku->board[y-1][x-1].isError);
		return;
	}
	else
		_Modify_val(y,x,value,j,i,k,sudoku,listMod);

}

int is_Legal_digits(char* c){
	size_t i;
	for(i=0;i<strlen(c);i++)
		if(isdigit(c[i])==0)
			return 0;
	return 1;
}


int checkSetCommandError(char** command,Sudoku* sudoku){
	char arr[3];
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"set","init");
		return 0;
	}
	if(command[3]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return 0;
	}
	if(command[4]!=NULL){
		errorMessage(PARAM_EXCEED,NULL, NULL);
		return 0;
	}
	if(!is_Legal_digits(command[1]) ||!is_Legal_digits(command[2]) ||!is_Legal_digits(command[3])){
		errorMessage(NUMBER_INVALID,NULL,NULL);
		return 0;
	}
	if(atoi(command[1])>sudoku->size || atoi(command[1])<1){
		errorMessage(OUT_OF_BOUND_INDEX,"X",NULL);
		return 0;
	}
	if(atoi(command[2])>sudoku->size || atoi(command[2])<1){
		errorMessage(OUT_OF_BOUND_INDEX,"Y",NULL);
		return 0;
	}
	if(atoi(command[3])>sudoku->size || atoi(command[3])<0){
		sprintf(arr, "%d", sudoku->size);
		errorMessage(SUD_VAL_INVALID, arr, NULL);
		return 0;
	}
	if(sudoku->board[atoi(command[2])-1][atoi(command[1])-1].isFixed){
		errorMessage(FIXED_CELL,command[2],command[1]);
		return error__;
	}

	return 1;

}
Command _set(char** command,Sudoku* sudoku){
	int c1,c2;
	ListOfUnitC* listMod;

	if(!checkSetCommandError(command,sudoku))
		return error__;
	c1 = atoi(command[2])-1;
	c2 = atoi(command[1])-1;
	listMod = (ListOfUnitC*) malloc(sizeof(ListOfUnitC));
	listMod->pre = sudoku->Fill;
	listMod-> first = NULL;

	Equal_val(c1+1,c2+1,atoi(command[3]),sudoku , listMod);
	if(sudoku->board[c1][c2].value!=0 && atoi(command[3])==0)
		sudoku->Fill--;
	if(sudoku->board[c1][c2].value==0 && atoi(command[3])!=0)
		sudoku->Fill++;
	listMod->Cur = sudoku->Fill;

	AppendStep(sudoku,listMod);
	sudoku->board[c1][c2].value = atoi(command[3]);
	IsEnd(sudoku);
	return set;
}


Command _validate(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"validate","init");
		return error__;
	}
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	if(SOLVE_LP_ILP(sudoku,NULL,1,validate,0,0,0.0f))
		surpMessage(SOLVABLE);
	else
		surpMessage(NOTSOLVABLE);
	return validate;
}

int isFloat(char *str){
	int count=0;
	size_t i;
	for(i=0;i<strlen(str);i++){
		if(str[i]=='.'){
			if(count){
				return 0;
			}
			else
				count ++;
		}
		else
			if(isdigit(str[i])==0){
			return 0;
			}
	}
	return 1;
}
int checkGuessCommandError(char** command,Sudoku *sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"guess","init");
		return 0;
	}
	if(modeGame==EDIT){
		errorMessage(ERROR_MODE,"guess","edit");
		return 0;
	}
	if(command[2]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return 0;
	}
	if(command[1]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return 0;
	}
	if(isFloat(command[1])==0){
		errorMessage(NUMBER_INVALID,NULL,NULL);
		return 0;
	}
	if(atof(command[1])< 0 || atof(command[1])>1){
		errorMessage(OUT_OF_BOUND_THRESHOLD,"X",NULL);
		return 0;
	}
	if(!Is_Erreneous(sudoku)){
		errorMessage(ERRONEOUS,NULL,NULL);
		return 0;
	}

	return 1;

}
Command _guess(char** command,Sudoku* sudoku){
	ListOfUnitC *listMod;
	if(!checkGuessCommandError(command,sudoku))
		return error__;
	listMod = (ListOfUnitC*) malloc(sizeof(ListOfUnitC));
	listMod->pre = sudoku->Fill;
	listMod-> first = NULL;
	if(!SOLVE_LP_ILP(sudoku,listMod,0,guess,0,0,(float)atof(command[1]))){
		surpMessage(NOTSOLVABLE);
		free(listMod);
		return error__;
	}
	listMod->Cur = sudoku->Fill;
	AppendStep(sudoku,listMod);
	IsEnd(sudoku);
	return guess;
}

int checkGenerateCommandError(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"generate","init");
		return 0;
	}
	if(modeGame==SOLVE){
		errorMessage(ERROR_MODE,"generate","solve");
		return 0;
	}
	if(command[3]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return 0;
	}
	if(command[2]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return 0;
	}
	if(!is_Legal_digits(command[1]) ||!is_Legal_digits(command[2])){
		errorMessage(NUMBER_INVALID,NULL,NULL);
		return 0;
	}
	if(atoi(command[1])>(sudoku->size*sudoku->size-sudoku->Fill) || atoi(command[1])<0){
		errorMessage(INVALID_PARAM,"X",NULL);
		return 0;
	}
	if(atoi(command[2])>(sudoku->size*sudoku->size) || atoi(command[2])<0){
		errorMessage(INVALID_PARAM,"Y",NULL);
		return 0;
	}
	if(!Is_Erreneous(sudoku)){
		errorMessage(ERRONEOUS,NULL,NULL);
		return 0;
	}
	return 1;
}
int findOptions(Unit** board,int size,int rows,int cols,int* indexs,int *options){
	int pos,m1,m2,flag;
	int c=0;
	Unit temp;
	for(pos=1;pos<=size;pos++){
		flag=0;
		for( m1=0;m1<rows;m1++){
				for( m2=0;m2<cols;m2++){
					temp=board[(rows)*indexs[0]+m1][(cols)*indexs[2]+m2];
					if((temp.value==pos)&(indexs[1]!=m1)&(indexs[3]!=m2)){
						flag=1;
						break;
					}
				}
		}
		for( m1=0;m1<size;m1++){
			temp= board[(rows)*indexs[0]+indexs[1]][m1];
			if((temp.value==pos)&(m1!=(cols)*indexs[2]+indexs[3])){
				flag=1;
				break;
			}
			temp= board[m1][(cols)*indexs[2]+indexs[3]];
			if((temp.value==pos)&(m1!=(rows)*indexs[0]+indexs[1])){
				flag=1;
				break;
			}
		}
		if(!flag){
			options[c++]=pos;
		}
	}
	return c;


}
Sudoku* copyGame(Sudoku* sudoku){
	Sudoku* sud=(Sudoku*)malloc(sizeof(Sudoku));
	sud->cols=sudoku->cols;
	sud->rows=sudoku->rows;
	sud->Fill=sudoku->Fill;
	sud->mark_errors=sudoku->mark_errors;
	sud->size=sudoku->size;
	sud->linkedlistm=NULL;
	return sud;
}
int randomlyFill(Unit** board ,int r,int size,int rows,int cols){
	int arr[4]={0};
	int i,k,l,m,count=0, *val,c;
	val=(int*)malloc(size*sizeof(int));
	for(i = 0;i< cols;i++){
		for(k=0; k<rows;k++){
			for(l = 0 ; l < rows; l++){
				for(m = 0; m< cols ; m++){
					if(board[rows*i+k][cols*l+m].value==0){
						count++;
					}
					if(count==r){
						arr[0]=i;
						arr[1]=k;
						arr[2]=l;
						arr[3]=m;
						c=findOptions(board,size,rows,cols,arr,val);
						if(c==0){
							free(val);
							return 0;
						}
						board[rows*i+k][cols*l+m].value=val[rand()%c];
						free(val);
						return 1;
					}
				}
			}
		}
	}
	free(val);
	return 0;
}
void rand_d(Sudoku* sudoku,ListOfUnitC* listMod, Sudoku* sudoku2,int lim){
	int i,j,number,count;
	int st=0,l=0,m=0,flag=1;
	UnitC* unitC,*temp;
	int cnt=sudoku2->size*sudoku2->size;
	for(i=0;i<sudoku2->size;i++)
		for(j=0;j<sudoku2->size;j++){
			unitC = (UnitC*) malloc(sizeof(UnitC));
			set_and_Unit(listMod,unitC,i,j,sudoku2->board[i][j].value,0,sudoku2->board[i][j].Intersection,sudoku2->board[i][j].Intersection,sudoku2->board[i][j].isError,0);
		}
	for(l=0;l<sudoku2->size;l++){
		for(m=0;m<sudoku2->size;m++){
			sudoku2->board[l][m].isFixed=0;
			sudoku2->board[l][m].value=0;
		}
	}
	while(st<lim){
		flag=1;
		temp=listMod->first;
		number=rand()%cnt+1;
		count=0;
		for(i=sudoku2->size-1;i>=0 && flag==1;i--){
			for(j=sudoku2->size-1;j>=0 && flag==1;j--){
				if(sudoku2->board[i][j].value==0)
					count++;
				if(count==number){
					st++;
					cnt--;
					sudoku2->board[i][j].value=sudoku->board[i][j].value;
					temp->currValue=sudoku->board[i][j].value;
					flag=0;
				}
				if(flag==1)
					temp=temp->next;
			}
		}
	}
}
Command _generate(char** command,Sudoku* sudoku){
	int cnt,i,randoms,flag;
	int try=0,flag2=1;
	Unit** board;
	Sudoku* game2;
	ListOfUnitC* listMod;
	if(!checkGenerateCommandError(command,sudoku))
		return error__;
	listMod = (ListOfUnitC*) malloc(sizeof(ListOfUnitC));
	listMod->pre = sudoku->Fill;
	listMod-> first = NULL;
	while(try<1000){
		flag2=1;
		board=sudokuCp(sudoku);
		cnt=sudoku->size*sudoku->size-sudoku->Fill;
		for(i=0;i<atoi(command[1]) && flag2==1 ;i++){
			randoms=rand()%cnt+1;
			flag=randomlyFill(board,randoms,sudoku->size,sudoku->rows,sudoku->cols);
			if(!flag){
				try++;
				while(i<sudoku->size){
					 free(board[i]);
					 i++;
				}
				free(board);
				flag2=0;
			}
		}
		if(flag2==1){
			game2=copyGame(sudoku);
			game2->board=board;
			game2->Fill=sudoku->Fill+atoi(command[1]);
			flag=SOLVE_LP_ILP(game2,NULL,1,generate,0,0,0.0f);
			if(flag==1){
				rand_d(game2,listMod,sudoku,atoi(command[2]));
				sudoku->Fill=atoi(command[2]);
				listMod->Cur = sudoku->Fill;
				AppendStep(sudoku,listMod);
				NullityGAME(game2);
				surpMessage(LUCK);
				IsEnd(sudoku);
				return generate ;
			}
			try++;
			NullityGAME(game2);
		}
	}
	surpMessage(NOTSOLVABLE);
	free(listMod);
	return error__;
}
Command _undo(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"undo","Init");
		return error__;
	}
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL, NULL);
		return error__;
	}

	if(!UndoStep(sudoku)){
		errorMessage(UNDO_STUCK,NULL, NULL);
		return error__;
	}

	return undo;
}
Command _redo(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"redo","Init");
		return error__;
	}
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL, NULL);
		return error__;
	}

	if(!RedoStep(sudoku)){
		errorMessage(REDO_STUCK,NULL, NULL);
		return error__;
	}

	return undo;
}

Command _save(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE, "save", "init");
		return error__;
	}
	if(modeGame==EDIT && !Is_Erreneous(sudoku)){
		errorMessage(ERRONEOUS,"save_in_edit",NULL);
		return error__;
	}
	if(command[1]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return error__;
	}
	if(command[2]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	if(saveToFile(sudoku,command[1])==0)
		return error__;


	return save;
}

int errHint(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"hint","init");
		return error__;
	}
	if(modeGame==EDIT){
		errorMessage(ERROR_MODE,"hint","Edit");
		return 0;
	}
	if(command[3]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return 0;
	}
	if(command[2]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return 0;
	}
	if(!is_Legal_digits(command[1]) ||!is_Legal_digits(command[2])){
		errorMessage(NUMBER_INVALID,NULL,NULL);
		return 0;
	}
	if(atoi(command[1])>sudoku->size || atoi(command[1])<1){
		errorMessage(OUT_OF_BOUND_INDEX,"X",NULL);
		return 0;
	}
	if(atoi(command[2])>sudoku->size || atoi(command[2])<1){
		errorMessage(OUT_OF_BOUND_INDEX,"Y",NULL);
		return 0;
	}

	if(sudoku->board[atoi(command[2])-1][atoi(command[1])-1].isFixed){
		errorMessage(FIXED_CELL,command[2],command[1]);
		return error__;
	}
	if(sudoku->board[atoi(command[2])-1][atoi(command[1])-1].value!=0){
		errorMessage(FILLED_CELL,command[2],command[1]);
		return error__;
	}

	return 1;

}
Command _hint(char** command,Sudoku* sudoku){
	if(!errHint(command,sudoku))
		return error__;

	if(!SOLVE_LP_ILP(sudoku,NULL,1,hint,atoi(command[2])-1,atoi(command[1])-1,0.0f)){
		surpMessage(NOTSOLVABLE);
		return error__;
	}
	return hint;
}
int errGuessH(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"guess_hint","init");
		return 0;
	}
	if(modeGame==EDIT){
		errorMessage(ERROR_MODE,"guess_hint","edit");
		return 0;
	}
	if(command[3]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return 0;
	}
	if(command[2]==NULL){
		errorMessage(NO_ENOUGH_PARAM,NULL,NULL);
		return 0;
	}
	if(!is_Legal_digits(command[1]) ||!is_Legal_digits(command[2])){
		errorMessage(NUMBER_INVALID,NULL,NULL);
		return 0;
	}
	if(atoi(command[1])>sudoku->size || atoi(command[1])<1){
		errorMessage(OUT_OF_BOUND_INDEX,"X",NULL);
		return 0;
	}
	if(atoi(command[2])>sudoku->size || atoi(command[2])<1){
		errorMessage(OUT_OF_BOUND_INDEX,"Y",NULL);
		return 0;
	}

	if(sudoku->board[atoi(command[2])-1][atoi(command[1])-1].isFixed){
		errorMessage(FIXED_CELL,command[2],command[1]);
		return 0;
	}
	if(sudoku->board[atoi(command[2])-1][atoi(command[1])-1].value!=0){
		errorMessage(FILLED_CELL,command[2],command[1]);
		return 0;
	}
	if(!Is_Erreneous(sudoku)){
		errorMessage(ERRONEOUS,NULL,NULL);
		return 0;
	}

	return 1;

}
Command _guessHint(char** command,Sudoku* sudoku){
	if(!errGuessH(command,sudoku))
			return error__;

	if(!SOLVE_LP_ILP(sudoku,NULL,0,guess_hint,atoi(command[2])-1,atoi(command[1])-1,0.0f)){
		surpMessage(NOTSOLVABLE);
		return error__;
	}

	return guess_hint;
}
Command _numSolutions(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"num_solutions","init");
		return error__;
	}
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	if(!Is_Erreneous(sudoku)){
		errorMessage(ERRONEOUS,NULL,NULL);
			return error__;
	}
	printf("There are %d legal available board.\n", numOfSol(sudoku));
	return num_solutions;
}

void checkingauto(int y,int x,Sudoku* sudoku, int **mat){
	int a=y-1;
	int b=x-1;
	int i, j, X_,Y_;
	int cnt=0,sum=0;
	int maxSum = ((sudoku->size+1)*sudoku->size)/2;
	for(i = 0;i<sudoku->size;i++){
		if(sudoku->board[a][i].value == 0 && i != b)
			cnt++;
		sum += sudoku->board[a][i].value;
	}
	if(cnt==0){
		mat[a][b]=maxSum-sum;
		return;
	}
	cnt = 0;
	sum = 0;
	for(i = 0;i<sudoku->size;i++){
		if(sudoku->board[i][b].value == 0 && i != (a))
			cnt++;
		sum += sudoku->board[i][b].value;
	}
	if(cnt==0){
		mat[a][b]=maxSum-sum;
		return;
	}
	cnt = 0;
	sum = 0;
	X_ = (a) - (a)% sudoku->rows;
	Y_ = (b) - (b)% sudoku->cols;

	for(i = X_ ; i < X_ + sudoku->rows;i++){
		for(j = Y_; j < Y_ + sudoku->cols ; j++){
			if(sudoku->board[i][j].value == 0 && (i != a || j != b ))
				cnt++;
			sum += sudoku->board[i][j].value;
		}
	}
	if(cnt==0){
		mat[a][b]=maxSum-sum;
	}
}
int helpautofilmat(Sudoku* sudoku, int*** matrix){
	int** mat, i, j;
	mat = (int**) malloc(sudoku->size*sizeof(int*));
		if(mat==NULL){
			errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
			return 0;
		}
		for(i=0;i<sudoku->size;i++){
			mat[i] = (int*) malloc(sudoku->size*sizeof(int));
			if(mat[i]==NULL){
				errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
				return 0;
			}
		}
		for(i=0;i<sudoku->size;i++)
			for(j=0;j<sudoku->size;j++)
				mat[i][j]=0;
	*matrix = mat;
	return 1;
}
Command _autofill(char** command, Sudoku* sudoku){


	int i,j;
	int** mat;
	ListOfUnitC* list;
	if(modeGame==INIT){
		errorMessage(ERROR_MODE,"autofill","init");
		return error__;
	}
	if(modeGame==EDIT){
		errorMessage(ERROR_MODE,"autofill","edit");
		return error__;
	}

	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}

	if(!Is_Erreneous(sudoku)){
		errorMessage(ERRONEOUS,NULL,NULL);
		return error__;
	}

	list = (ListOfUnitC*) malloc(sizeof(ListOfUnitC));
	list->pre = sudoku->Fill;
	list-> first = NULL;

	if(helpautofilmat(sudoku, &mat)==0)
		return error__;

	for(i=0;i<sudoku->size;i++)
		for(j=0;j<sudoku->size;j++)
			if(sudoku->board[i][j].value==0)
				checkingauto(i+1,j+1,sudoku, mat);

	for(i=0;i<sudoku->size;i++){
		for(j=0;j<sudoku->size;j++){
			if(mat[i][j]!=0){
				Equal_val(i+1,j+1,mat[i][j],sudoku,list);
				sudoku->board[i][j].value=mat[i][j];
				sudoku->Fill++;
			}
		}
	}

	list->Cur = sudoku->Fill;
	AppendStep(sudoku,list);


	freeIntegerSudoku(mat,sudoku->size);
	IsEnd(sudoku);

	return autofill;
}

Command _reset(char** command,Sudoku* sudoku){
	if(modeGame==INIT){
		errorMessage(ERROR_MODE, "reset", "init");
		return error__;
	}
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	while(sudoku->linkedlistm->current != sudoku->linkedlistm->first)
		UndoStep(sudoku);
	return autofill;
}
Command __exit(char** command,Sudoku* sudoku){
	if(command[1]!=NULL){
		errorMessage(PARAM_EXCEED,NULL,NULL);
		return error__;
	}
	NullityGAME(sudoku);
	return exit_Command;
}

