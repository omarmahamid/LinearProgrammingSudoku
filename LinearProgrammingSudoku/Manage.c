/*
 * this module for managing the files
 */
#include "Manage.h"
int ValidateTexture(char* c){
	size_t i;
	char str[1];
	for(i=0;i<strlen(c);i++){
		if(c[i]!=10 && c[i]!=13 && c[i]!= 9 && c[i]!=32 && c[i]!= 46 && isdigit(c[i])==0){
			printf("There is %c in the file", c[i]);
			sprintf(str, "%c", c[i]);
			errorMessage(INVALID_CHAR,str,NULL);
			return 0;
		}
	}
	return 1;
}
int Help12(char* c){
	size_t j;
	for(j=0;j<strlen(c);j++){
		if(c[j] == 46 &&  (isdigit(c[j-1])==0|| c[j-1]=='0')){
			errorMessage(RAND_ERR,NULL,NULL);
			return 0;
		}
	}
	return 1;
}
int validateAftervalidation(char* c){
	if(!ValidateTexture(c)){
		return 0;
	}
	if(!Help12(c)){
		return 0;
	}
	return 1;
}
int IF_DIMO(char** chMat, int* rows, int* cols){
	size_t i;
	size_t cnt=0;
	char* temp;
	temp = *chMat;
	for(i=0;i<strlen(temp)-1;i++){
		if(isdigit(temp[i])){
			if(isdigit(temp[i+1])|| temp[i+1] == 46 ){
				return 0;
			}
			else{
				if(cnt==0)
					rows[0] = temp[i]-'0';
				else
					cols[0] = temp[i]-'0';
				cnt++;
			}
		}
		if(cnt==2){
			(*chMat)+= i+1;
			return 1;
		}
	}
	return 0;

}
int ExceedValues(char* txt,int size){
	size_t i;
	int counter=0;
	i=0;
	while(i<=strlen(txt)){
		if(isdigit(txt[i])){
			i++;
			while(isdigit(txt[i]) && i<strlen(txt))
				i++;
			counter++;
		}
		i++;
	}
	if(counter>size){
		errorMessage(MANY_VAL,NULL, NULL);
		return 0;
	}
	if(counter<size){
		printf("%d",counter);
		errorMessage(FEWER_VAL,NULL, NULL);
		return 0;
	}
	return 1;
}
void ReadFile(FILE* fptr,char** abs) {
    char try;
    int i=0;
    while ((try = fgetc(fptr)) != EOF)
        (*abs)[i++] = try;
    (*abs)[i] = '\0';
}
int Is_In_Range(int size, int** matrix){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(abs(matrix[i][j])>=0 && abs(matrix[i][j])<=size){
				return 1;
			}
		}
	}
	errorMessage(ERROR_RANGE,NULL,NULL);
	return 0;
}
int TextVal(int size,int*** Umat, char* chT){
	int temp, counter, i;
	int** mat;
	size_t j;
	counter = 0;
	mat = (int**) malloc(size*sizeof(int*));
	if(mat==NULL){
		errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
		return 0;
	}
	for(i=0;i<size;i++){
		mat[i] = (int*) malloc(size*sizeof(int));
		if(mat[i]==NULL){
			errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
			return 0;
		}
	}
	j=0;
	while(j<strlen(chT)){
		if(isdigit(chT[j])){
			temp = chT[j]-'0';
			j++;
			while(isdigit(chT[j]) && j<strlen(chT)){
				temp = temp*10 + (chT[j]-'0');
				j++;
			}
			if(chT[j] == 46)
				temp *= -1;
			mat[counter/size][counter % size] = temp;
			counter++;
		}
		j++;
	}
	*Umat = mat;

	return 1;
}
Sudoku* NewSud(Sudoku* sudoku,int** matrix, int rows, int cols, char* modeGame){
	int i, j, value;
	Sudoku* newGame;
	sudoku->size +=0;
	NullityGAME(sudoku);
	newGame = initial(rows,cols);
	for(i=0;i<newGame->size;i++){
		for(j=0;j<newGame->size;j++){
			if(matrix[i][j]>=0){
				newGame->board[i][j].isFixed=0;
				value = matrix[i][j];
			}
			else{
				if(strcmp(modeGame, "EDIT")!=0)
					newGame->board[i][j].isFixed=1;
				else
					newGame->board[i][j].isFixed=0;
				value = matrix[i][j]*-1;
			}
			Equal_val(i+1,j+1,value,newGame, NULL);
			if(newGame->board[i][j].value!=0 && value==0)
				newGame->Fill--;
			if(newGame->board[i][j].value==0 && value!=0)
				newGame->Fill++;
			newGame->board[i][j].value = value;
		}
	}
	return newGame;
}
size_t DoSizing(FILE* fptr){
    int size;
    fseek(fptr, 0, SEEK_END);
    size= ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    return size+1;
}

int loadFromFile(Sudoku** sudoku ,char* FilePath,char* modeGame){
    FILE* fptr;
    char* txt;
    char* preT;
    int row,col;
    int** natN;
	if ((fptr = fopen(FilePath, "r")) == NULL){
		errorMessage(ERROR_PATH, FilePath, NULL);
		return 0;
	}
	txt = (char*) malloc((DoSizing(fptr))*sizeof(char));
    preT = txt;
    if(txt == NULL){
    	errorMessage(ERROR_IN_ALLOCATE_MEM,NULL,NULL);
    }
    ReadFile(fptr,&txt);
	fclose(fptr);
	if(!validateAftervalidation(txt))
		return 0;
	if(!IF_DIMO(&txt,&row,&col)){
		errorMessage(ERROR_SIZE, NULL, NULL);
		return 0;
	}

	if((row < 1 || row > 5)||(col < 1 || col > 5)){
		errorMessage(ERROR_SIZE, NULL, NULL);
		return 0;
	}
	if(!ExceedValues(txt,(row*col)*(row*col)))
		return 0;
	if(!TextVal((row*col), &natN, txt))
		return 0;

	if(!Is_In_Range((row*col),natN))
		return 0;
	*sudoku = NewSud(*sudoku,natN, row, col,modeGame);

	free(preT);
	freeIntegerSudoku(natN, (*sudoku)->size);
	return 1;
}

Command saveToFile(Sudoku* sudoku, char* FilePath){
	FILE *fptr = NULL;
	int i,j;
	if ((fptr = fopen(FilePath,"w")) == NULL){
		errorMessage(ERROR_PATH,FilePath,NULL);
		return error__;
	}
	fprintf(fptr,"%d %d\n",sudoku->rows,sudoku->cols);
	for(i=0;i<sudoku->size;i++){
		for(j=0;j<sudoku->size;j++){
			if(sudoku->board[i][j].isFixed)
				fprintf(fptr,"%d.",sudoku->board[i][j].value);
			else{
				if(modeGame == EDIT && sudoku->board[i][j].value!=0)
					fprintf(fptr,"%d.",sudoku->board[i][j].value);
				else
					fprintf(fptr,"%d",sudoku->board[i][j].value);
			}
			if(j!=(sudoku->size)-1)
				fprintf(fptr," ");
		}
		fprintf(fptr,"\n");
	}
	fclose(fptr);
	return 1;
}
