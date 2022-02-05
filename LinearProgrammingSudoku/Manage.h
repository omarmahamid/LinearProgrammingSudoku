/*
 * FileManager
 */
#ifndef MANAGE_H_
#define MANAGE_H_

#include "game.h"
#include "parser.h"
#include "gameFlow.h"
int saveToFile(Sudoku* sudoku, char* path);
int loadFromFile(Sudoku** sudoku ,char* path, char* mode);
#endif /* MANAGE_H_ */
