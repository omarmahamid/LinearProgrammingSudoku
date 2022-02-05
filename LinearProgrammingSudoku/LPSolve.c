#include "LPSolve.h"
/*
 * in this modules there is a helper functions and SOLVE_LP_ILP
 * SOLVE_LP_ILP
 * Checking if we need ILP or LP solve by checking the command
 * This function uses the following model for ILPSolving:
     subject to
          sum_v x[i,j,v] = 1
          sum_i x[i,j,v] = 1
          sum_j x[i,j,v] = 1
          sum_block x[i,j,v] = 1
		  as well as x[i,j,v]=1 for every cell [i,j] with a value
 */

int GUROBI_Pos(Unit_GUROBI* UG, int num){
	int i=0;
	for(i=0;i<UG->numOfVal;i++)
		if(UG->posValues[i] == num)
			return i;
	return -1;
}
void InitGUROBI(Unit_GUROBI*** matrix, int size){
	int i;
	(*matrix) = (Unit_GUROBI**) malloc(size*sizeof(Unit_GUROBI*));
	for(i=0;i<size;i++){
		(*matrix)[i] = (Unit_GUROBI*) malloc(size*sizeof(Unit_GUROBI));
	}
}
void FreeGUROBI(Unit_GUROBI*** matrix, int size){
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if((*matrix)[i][j].numOfVal!=0)
				free((*matrix)[i][j].posValues);
		}
		free((*matrix)[i]);
	}
	free((*matrix));
}
int Variables_GUROBI(Sudoku* sudoku, Unit_GUROBI*** matrix){
	int count = 0;
	int i, j, k,counter;
	for(i=0;i<sudoku->size;i++){
		for(j=0;j<sudoku->size;j++){
			if(sudoku->board[i][j].value==0){
				(*matrix)[i][j].beginIndex = count;
				counter = 0;
				for(k=1;k<=sudoku->size;k++){
					if(!Value_Validation(sudoku,i,j,k,TYPE_ONE)){
						counter ++;
					}
				}
				(*matrix)[i][j].numOfVal = counter;
				(*matrix)[i][j].posValues = (int*) calloc (counter, sizeof(int));
				counter = 0;
				for(k=1;k<=sudoku->size;k++){
					if(!Value_Validation(sudoku,i,j,k,TYPE_ONE)){
						(*matrix)[i][j].posValues[counter++] = k;
						count ++;
					}
				}
			}
			else
				(*matrix)[i][j].numOfVal = 0;
		}
	}
	return count;
}
int SOLVE_LP_ILP(Sudoku* sudoku,ListOfUnitC *listMod, int flag, Command command, int X, int Y, float sum){
	int f_GRB ,X_,Y_, _goal=0;
	int k=0;
	int y,i,j,n, l, m, index;
	int* ind;
	int number;
	GRBmodel *model;
	GRBenv   *env;
	Command temp;
	double* val;
	double* obj;
	char* vtype;
	double* sol;
	double max;
	double nm;
	Unit_GUROBI** GRB_S;
	UnitC* mCell;
	InitGUROBI(&GRB_S, sudoku->size);
	env = NULL;
	model = NULL;
	temp=command;
	number = Variables_GUROBI(sudoku, &GRB_S);
	f_GRB=1;
	f_GRB = GRBloadenv(&env, "mip1.log");
	if(env==NULL){
		surpMessage(ENVIRONMENT);
		exit(1);
	}
	if(f_GRB){
		surpMessage(ENVIRONMENT);
		exit(1);
	}
    GRBsetintparam(env, GRB_INT_PAR_LOGTOCONSOLE, 0);
    f_GRB = GRBnewmodel(env, &model,"mip1",0, NULL,NULL,NULL,NULL,NULL);
    if(f_GRB){
    	error_GRB(GRB_MODEL,NULL,NULL);
    	return -1;
    }
	obj = (double*) calloc(number, sizeof(double));
	vtype = (char*) calloc(number, sizeof(char));
	sol = (double*) calloc(number, sizeof(double));
    ind = (int*)calloc(number, sizeof(int));
    val = (double*) calloc(number, sizeof(double));
    /*putting the mishtanem according to flag (if flag ==1 ) then ILP else LP*/
    if(flag){
    	for(i=0;i<number;i++){
    		obj[i]=0;
    		vtype[i]= GRB_BINARY;
    	}
    }
    else
    {
    	for(i=0;i<number;i++){
    		obj[i]=rand()%sudoku->size;
    		vtype[i]= GRB_CONTINUOUS;
    	}
    }
    f_GRB = GRBaddvars(model, number, 0, NULL, NULL, NULL, obj, NULL, NULL, vtype, NULL);
    if (f_GRB) {
    	error_GRB(GRB_AD,NULL,NULL);
    	return -1;
    }
    f_GRB = GRBsetintattr(model, GRB_INT_ATTR_MODELSENSE, GRB_MAXIMIZE);
    if (f_GRB) {
    	error_GRB(GRB_S_ATT,NULL, NULL);
    	return -1;
    }
    f_GRB = GRBupdatemodel(model);
    if (f_GRB) {
    	error_GRB(GRB_MODEL,NULL,NULL);
    	return -1;
    }
    /* Each cell gets a single value */
	for(i=0;i<sudoku->size;i++){
		for(j=0;j<sudoku->size;j++){
			if(sudoku->board[i][j].value == 0){
				index = 0;
				for(n=1;n<=sudoku->size;n++){
					if(!Value_Validation(sudoku,i,j,n,TYPE_ONE)){
						ind[index] = GRB_S[i][j].beginIndex + GUROBI_Pos(&(GRB_S[i][j]), n);
						val[index++] = 1;
					}
				}
				f_GRB = GRBaddconstr(model, index, ind, val, GRB_EQUAL, 1.0, NULL);
				if (f_GRB) {
					error_GRB(GRB_CONST,NULL,NULL);
					return -1;
	             }
			}
		}
	}
	 /* Each value appears once in each col */
	for(j=0;j<sudoku->size;j++){
		for(n=1;n<=sudoku->size;n++){
			index=0;
			for(i=0;i<sudoku->size;i++){
				if(sudoku->board[i][j].value == 0){
					if(!Value_Validation(sudoku,i,j,n,TYPE_ONE)){
						ind[index]= GRB_S[i][j].beginIndex + GUROBI_Pos(&(GRB_S[i][j]), n);
						val[index++] = 1;
					}
				}
			}
			if(index!=0){
				f_GRB = GRBaddconstr(model, index, ind, val, GRB_EQUAL, 1.0, NULL);
				if (f_GRB) {
					error_GRB(GRB_CONST,NULL,NULL);
					return -1;
				}
			}
		}
	}
	/* Each value appears once in each column */
	for(i=0;i<sudoku->size;i++){
		for(n=1;n<=sudoku->size;n++){
			index=0;
			for(j=0;j<sudoku->size;j++){
				if(sudoku->board[i][j].value == 0){
					if(!Value_Validation(sudoku,i,j,n,TYPE_ONE)){
						ind[index]= GRB_S[i][j].beginIndex + GUROBI_Pos(&(GRB_S[i][j]), n);
						val[index++] = 1;
					}
				}
			}
			if(index!=0){
				f_GRB = GRBaddconstr(model, index, ind, val, GRB_EQUAL, 1.0, NULL);
				if (f_GRB) {
					error_GRB(GRB_CONST,NULL,NULL);
					 return -1;
				}
			}
		}
	}
	/* Each value appears once in each block */
	for(i=0;i<sudoku->cols;i++){
		for(j=0;j<sudoku->rows;j++){
			X_ = i*sudoku->rows;
			Y_ = j*sudoku->cols;
			for(n=1;n<=sudoku->size;n++){
				index=0;
				for(l = X_ ; l < X_ + sudoku->rows;l++){
					for(m = Y_; m < Y_ + sudoku->cols ; m++){
						if(sudoku->board[l][m].value == 0){
							if(!Value_Validation(sudoku,l,m,n,TYPE_ONE)){
								ind[index]= GRB_S[l][m].beginIndex + GUROBI_Pos(&(GRB_S[l][m]), n);
								val[index++] = 1;
							}
						}
					}
				}
				if(index!=0){
					f_GRB = GRBaddconstr(model, index, ind, val, GRB_EQUAL, 1.0, NULL);
					if (f_GRB) {
						error_GRB(GRB_CONST,NULL,NULL);
						return -1;
					}
				}
			}
		}
	}
	f_GRB = GRBoptimize(model);
	if (f_GRB){
		printf("ERROR %d GRBoptimize %s\n", f_GRB, GRBgeterrormsg(env));
		return -1;
	}
	f_GRB = GRBwrite(model, "mip1.lp");
	if (f_GRB){
		printf("ERROR %d GRBwrite %s\n", f_GRB, GRBgeterrormsg(env));
		return -1;
	}
	f_GRB = GRBgetintattr(model, GRB_INT_ATTR_STATUS, &_goal);
	if (f_GRB){
		printf("ERROR %d GRBgetintattr %s\n", f_GRB, GRBgeterrormsg(env));
		return -1;
	}
	if (_goal == GRB_OPTIMAL){
		f_GRB = GRBgetdblattr(model, GRB_DBL_ATTR_OBJVAL, &nm);
		if (f_GRB){
			printf("ERROR %d GRBgettdblattr %s\n", f_GRB, GRBgeterrormsg(env));
			return -1;
		}
		f_GRB = GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, number, sol);
		if (f_GRB){
			printf("ERROR %d GRBgetdblattrarray %s\n", f_GRB, GRBgeterrormsg(env));
			return -1;
		}
		if(temp==generate){
			for(k=0;k<sudoku->size;k++){
		  		for(y=0;y<sudoku->size;y++){
		  			if(sudoku->board[k][y].value==0){
		  				for(i= GRB_S[k][y].beginIndex;i<GRB_S[k][y].beginIndex+GRB_S[k][y].numOfVal;i++){
		  					if(sol[i] != 0){
		  						sudoku-> board[k][y].value=GRB_S[k][y].posValues[i-GRB_S[k][y].beginIndex];
		  			 	  }
		  			   }
		  			}
		  		}
			}
		}
		if(temp==hint){
			for(i= GRB_S[X][Y].beginIndex;i<GRB_S[X][Y].beginIndex+GRB_S[X][Y].numOfVal;i++)
				if(sol[i] != 0)
					printf("We would recommend you to fill cell [%d,%d] with the value %d.\n",Y+1,X+1,GRB_S[X][Y].posValues[i-GRB_S[X][Y].beginIndex]);
		}
		if(temp==guess){
			for(k=0;k<sudoku->size;k++){
				for(y=0;y<sudoku->size;y++){
					max=0;
					if(sudoku->board[k][y].value==0){
						for(i= GRB_S[k][y].beginIndex;i<GRB_S[k][y].beginIndex+GRB_S[k][y].numOfVal;i++){
							if(sol[i]>=sum && !Value_Validation(sudoku,k,y,GRB_S[k][y].posValues[i-GRB_S[k][y].beginIndex],TYPE_ONE) && max<=sol[i]  ){
								max=sol[i];
								if(sudoku-> board[k][y].value==0){
		  						sudoku->Fill++;
		  						mCell = (UnitC*) malloc(sizeof(UnitC));
		  						set_and_Unit(listMod,mCell,k,y,0,GRB_S[k][y].posValues[i-GRB_S[k][y].beginIndex],sudoku->board[k][y].Intersection,sudoku->board[k][y].Intersection,sudoku->board[k][y].isError,0);
								}
		  						 mCell->currValue=GRB_S[k][y].posValues[i-GRB_S[k][y].beginIndex];
		  						 sudoku-> board[k][y].value=GRB_S[k][y].posValues[i-GRB_S[k][y].beginIndex];
							}
						}
					}
				}
			}
		}
		if(temp==guess_hint){
			for(i= GRB_S[X][Y].beginIndex;i<GRB_S[X][Y].beginIndex+GRB_S[X][Y].numOfVal;i++)
				if(sol[i] > 0)
					printf("You can fill cell [%d,%d] with the value %d with score of %f.\n",Y+1,X+1,GRB_S[X][Y].posValues[i-GRB_S[X][Y].beginIndex],sol[i]);
		}
	}
	/* There No Sol found */
	else if (_goal == GRB_INF_OR_UNBD) {
		return 0;
	}
	else {
		return 0;
	}
	free(ind);
	free(val);
	free(obj);
	free(vtype);
	free(sol);
	FreeGUROBI(&GRB_S, sudoku->size);
	GRBfreemodel(model);
	GRBfreeenv(env);
	return 1;
}
