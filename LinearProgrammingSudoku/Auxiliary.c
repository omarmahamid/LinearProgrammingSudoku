#include "Auxiliary.h"
#include <stdio.h>
/*
 * This module manage the stack and everything relevant to the stack
 * with methods :
 * ConstructTheStack which init the stack
 * ConstructL which construct a new linkedlist
 * Push which push elements to the stack in LIFO method
 * Pop which remove the last element
 * Head which return the last element
 * CheckingTheNumberAccordingToSudoku which find the first valid number , then check if it valid according to sudoku
 * Skip which skips to next unit
 * End which tell us if the sudoku filled
 * MoveUnit1ToUnit2 which move the information from unit1 to unit2
 * Backtracking which do backtrack algorithm and return 1 if there is a solution to sudoku,the algorithm is LRTB,left,right,top,bottom,with stack simulation
 * numOfSol which return the number of solution of the sudoku
 *
 */
Stack* ConstructTheStack(){
	Stack* stack=(Stack*)malloc(sizeof(Stack));
	stack->first=NULL;
	stack->last=NULL;
	return stack;
}
Con* ConstructL(int BlockRow, int BlockCol,int BoardRow, int BoardCol){
	Con* l1=(Con*)malloc(sizeof(Con));
	l1->BlockCol=BlockCol;
	l1->BoardCol=BoardCol;
	l1->BlockRow=BlockRow;
	l1->BoardRow=BoardRow;
	l1->temp=NULL;
	l1->next=NULL;
	l1->prev=NULL;
	return l1;
}
void push(Stack* stack,Con* Dlist){

	if(stack->first==NULL){
		stack->first=Dlist;
		stack->last=Dlist;
	}
	else{
		stack->last->next=Dlist;
	 	Dlist->prev=stack->last;
	 	stack->last=Dlist;
	}
}
void pop(Stack* stack){
	Con *temp=stack->last;
	if(stack->first==NULL)
		return;
	if(temp->prev!=NULL){
		stack->last=stack->last->prev;
		stack->last->next=NULL;
	}
	else{
		stack->first=NULL;
		stack->last=NULL;
	}
	free(temp);
}
Con* Head(Stack* stack){
	return stack->last;
}
 int CheckingTheNumberAccordingToSudoku(Sudoku* sudoku, Unit* Utmp,Unit** matrix,int n,int size,Con *Dlist){
	 int flag,i,j,pos;
	 Unit Utmp2;
	 for(pos=n;pos<=size;pos++){
		 flag=0;
		 for(i=0;i<sudoku->rows;i++){
			 for(j=0;j<sudoku->cols;j++){
				 Utmp2=matrix[(sudoku->rows)*Dlist->BoardRow+i][(sudoku->cols)*Dlist->BoardCol+j];
				 if((Utmp2.value==pos)&(Dlist->BlockRow!=i)&(Dlist->BlockCol!=j)){
					 flag=1;
				 }
			 }
		 }
		 for( i=0;i<size;i++){
			 Utmp2= matrix[(sudoku->rows)*Dlist->BoardRow+Dlist->BlockRow][i];;
			 if((Utmp2.value==pos)&(i!=(sudoku->cols)*Dlist->BoardCol+Dlist->BlockCol)){
				 flag=1;
			 }
			 Utmp2= matrix[i][(sudoku->cols)*Dlist->BoardCol+Dlist->BlockCol];
			 if((Utmp2.value==pos)&(i!=(sudoku->rows)*Dlist->BoardRow+Dlist->BlockRow)){
				 flag=1;
			 }
		 }
		 if(flag==0){
			 Utmp->value=pos;
			 return flag;
		 }
 	}
	 Utmp->value=0;
	 return 1;
 }
 Con* Skip(Sudoku* sudoku,Con* Dlist){
	 int x=sudoku->rows-1;
	 int y=sudoku->cols-1;
	 if(Dlist->BlockRow==x && (Dlist->BoardCol==x && Dlist->BlockCol ==y)){
		 Dlist->BoardRow++;
		 Dlist->BlockRow=0;
		 Dlist->BoardCol=0;
		 Dlist->BlockCol=0;
		 return Dlist;
	 }
	 if(Dlist->BoardCol==x && Dlist->BlockCol ==y){
		 Dlist->BlockRow++;
		 Dlist->BoardCol=0;
		 Dlist->BlockCol=0;
		 return Dlist;
	 }
	 if(Dlist->BlockCol< y){
		 Dlist->BlockCol++;
		 return Dlist;
	 }else{
		 Dlist->BoardCol++;
		 Dlist->BlockCol=0;
		 return Dlist;
	 }
 }

 int End(Sudoku* sudoku,Con *Dlist){
	 int x=(sudoku->rows)*Dlist->BoardRow+Dlist->BlockRow;
	 int size=sudoku->size ;
	 int y=(sudoku->cols)*Dlist->BoardCol+Dlist->BlockCol;
	 if(x==size && y==0){
		 return 1;
	 }
	 return 0;
 }

 void MoveUnit1ToUnit2(Unit* U1, Unit* U2){
	 U2-> value = U1->value;
	 if(U2-> value !=0)
		 U2->isFixed = 1;
	 else
		 U2->isFixed=0;
	 U2->isError=U1->isError;
 }
 Unit** sudokuCp(Sudoku* sudoku){
	 int i,j;
	 int size= sudoku->cols * sudoku->rows;
	 Unit** matrix;
	 matrix = (Unit**) malloc(size*sizeof(Unit*));
	 for(i=0;i<size;i++){
		 matrix[i] = (Unit*) malloc(size*sizeof(Unit));
	 }
	 for(i=0; i< size;i++)
		 for(j=0;j<size;j++)
			 MoveUnit1ToUnit2(&sudoku->board[i][j], &matrix[i][j]);
	 return matrix;
 }

 int Backtracking(Sudoku* sudoku,Stack* stack,Unit** matrix){
	 int flag=0;
	 int check1,check2;
	 Con* Dlist;
	 check1=Head(stack)->temp->isFixed;
	 Head(stack)->temp=&(matrix[(sudoku->rows)*Head(stack)->BoardRow+Head(stack)->BlockRow][(sudoku->cols)*Head(stack)->BoardCol+Head(stack)->BlockCol]);
	 if(check1==0)
		 flag=1;
	 while(stack->first!=NULL){
		 if(flag==0){
			 Dlist=ConstructL(Head(stack)->BlockRow,Head(stack)->BlockCol,Head(stack)->BoardRow,Head(stack)->BoardCol);
			 Dlist=Skip(sudoku,Dlist);
			 if(End(sudoku,Dlist)==1){
				 free(Dlist);
				 return 1;
			 }
			 Dlist->temp=&(matrix[(sudoku->rows)*Dlist->BoardRow+Dlist->BlockRow][(sudoku->cols)*Dlist->BoardCol+Dlist->BlockCol]);
		 }
		 else
			 Dlist=Head(stack);
		 if(End(sudoku,Dlist)==1){
			 free(Dlist);
			 return 1;
		 }
		 check2=Dlist->temp->isFixed;
		 if(check2==0){
			 Dlist->flag=CheckingTheNumberAccordingToSudoku(sudoku,Dlist->temp,matrix,Dlist->temp->value+1,sudoku->size,Dlist);
			 if(Dlist->flag){
				 if(flag==0){
					 push(stack,Dlist);
				 }
				 flag=1;
 			}
			 if(flag==0){
				 push(stack,Dlist);
			 }
			 else{
				 if(!Dlist->flag)
					 flag=0;
				 else
					 pop(stack);
			 }
		 }
		 else{
			 if(flag==1)
				 pop(stack);
			 else
				 push(stack,Dlist);
		 }
	 }
	 return 0;
 }
 int numOfSol(Sudoku* sudoku){
	 int i=0;
	 int a=0,b=0,c=0,d=0;
	 int check;
	 int numOfSol=0;
	 int cnt,flag,num;
	 Unit** matrix= sudokuCp(sudoku);
	 Stack* temp1=ConstructTheStack();
	 Stack* temp2=ConstructTheStack();
	 Con *Dlist=ConstructL(a,b,c,d);
	 push(temp2,Dlist);
	 cnt = Backtracking(sudoku,temp2,matrix);
	 if(cnt==1){
		 numOfSol++;
		 temp1->last=temp2->last;
		 temp1->first=temp2->first;
		 temp2->first=NULL;
		 temp2->last=NULL;
	 }
	 while(temp1->first!=NULL){
		 while(temp1->first!=NULL){
			 check=Head(temp1)->temp->isFixed;
			 if(check==1){
				 pop(temp1);
				 continue;
			 }
			 num=Head(temp1)->temp->value;
			 flag=CheckingTheNumberAccordingToSudoku(sudoku,Head(temp1)->temp,matrix,num+1,sudoku->size,Head(temp1));
			 if(flag==0)
				 break;
			 pop(temp1);
		 }
		 if(flag==0){
			 Dlist=ConstructL(Head(temp1)->BlockRow,Head(temp1)->BlockCol,Head(temp1)->BoardRow,Head(temp1)->BoardCol);
			 Dlist->temp=Head(temp1)->temp;
			 Dlist->temp->value=num;
			 push(temp2,Dlist);
			 pop(temp1);
			 cnt=Backtracking(sudoku,temp2,matrix);
			 if(cnt){
				 numOfSol++;
				 if(temp1->first==NULL){
					 temp1->first=temp2->first;
					 temp1->last=temp2->last;
				 }
				 else{
					 temp1->last->next=temp1->first;
					 temp1->first->prev=temp1->last;
					 temp1->last=temp2->last;
				 }
				 temp2->first=NULL;
				 temp2->last=NULL;
			 }
		 }
		 else
			 break;
	 }
	 while(temp2->first!=NULL){
	 	pop(temp2);
	 }
	 free(temp2);
	 while(temp1->first!=NULL){
	 	pop(temp1);
	 }
	 free(temp1);
	 while(i<sudoku->size){
	 	free(matrix[i]);
	 	i++;
	 }
	 free(matrix);
	 return numOfSol;
 }
