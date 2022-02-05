
#ifndef LPSOLVE_H_
#define LPSOLVE_H_
#include "parser.h"
#include "game.h"
#include "gurobi_c.h"
#include "printer.h"
int SOLVE_LP_ILP(Sudoku* sudoku,ListOfUnitC *listMod, int flag, Command command, int X, int Y, float sum);
#endif /* LPSOLVE_H_ */
